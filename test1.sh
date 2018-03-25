./resources/asm  resources/champions/$1.s;
./corewar  resources/champions/$1.cor > test.txt;
./asm resources/champions/$1.s;
./corewar  resources/champions/$1.cor > test2.txt;
diff test.txt test2.txt;
