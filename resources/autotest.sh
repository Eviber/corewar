for enemy in `ls champions/championships/*/all/*.cor`
do
	./corewar $1 $enemy | grep -e Player -e Contestant
	./corewar $enemy $1 | grep Contestant
	echo ""
done
