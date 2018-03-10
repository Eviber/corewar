#!/bin/zsh

dir=test
rm -r $dir
mkdir -p $dir
find resources/champions -type f | grep -e \\.cor > $dir/test_files.txt
list=`cat $dir/test_files.txt`
rm $dir/test_files.txt
mkdir -p $dir/champions
cp $list $dir/champions/.
list=`find $dir/champions -type f`

for file in $list
do
	vs_dir=`echo $file | cut -d. -f1`
	mkdir -p $vs_dir
	for file2 in $list
	do
		vs=`echo $file2 | cut -d/ -f3 | cut -d. -f1`
		mkdir -p $vs_dir/$vs
		echo "Test $file vs $file2..." > $vs_dir/$vs/$vs.txt
		echo "Test $file vs $file2..."
		./resources/corewar $file $file2 -v 18 | sed '1,/ADV/d' | sed '$d' > $vs_dir/$vs/result_zaz.txt
		./corewar -n -1 $file -n -2 $file2 -v 10 | sed '1,/ADV/d' | sed '$d' | sed '$d' > $vs_dir/$vs/result_vm.txt
		diff $vs_dir/$vs/result_zaz.txt $vs_dir/$vs/result_vm.txt >> $vs_dir/$vs/$vs.txt
		echo "[------------------------------------------------------------]">> $vs_dir/$vs/$vs.txt
		cat $vs_dir/$vs/$vs.txt >> $dir/all_result.txt
		echo "Test $file vs $file2 : done."
	done
done
