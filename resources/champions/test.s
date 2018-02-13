.name "demo_test"
.comment "juste a little test"

init:	sti r1, %:see, %1
		sti r1, %:first, %1
		sti r1, %:shadow, %1
		ld 

create:	live %42
		fork %:double
		zjmp %:see

double:	fork %:first
		zjmp %:shadow

first:	live %42
		

shadow:	live %42
