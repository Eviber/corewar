.name "test"
.comment "test"

lab:	st r2, r3
		zjmp %42
		sti r2, %:label, %1
		st r1, :label
		ld %2483027968, r2
		fork %:label
		lfork %:label
		sti r2, %:label, %1

label:	ld %0, r1
		sti r1, %0, %10
