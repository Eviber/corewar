.name "test"
.comment "test"

		sti r1, %:fork1, %1
		sti r1, %:fork2, %1
		sti r1, %:clone, %1
		ld %16777216, r2
		ld %167770880, r3
		ld %80, r4
		ld %9, r7
		ld %47, r8

fork1:	live %42
		add r4, r5, r6
		sti r6, %1, %8
		ld %42, r5
		fork %:fork1

fork2:	live %42
		fork %:fork1

clone:	live %42
		sti r2, r5, %0
		sti r1, r5, %-5
		sti r3, r5, %-7
		sub r5, r8, r6
		sti r6, %1, %22
		sti r7, %1, %13
		ld %0, r10


