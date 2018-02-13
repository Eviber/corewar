.name "demo_test"
.comment "just a little test"

		ld %0, r2
		zjmp %:init

move:	live %42
		sti r5, %-436, %0
		sti r6, %-436, %-3
		sti r7, %-436, %-6
		sti r8, %-436, %-9
		sti r9, %-436, %-12
		sti r10, %-436, %-15
		sti r11, %-436, %-18
		sti r12, %-436, %-21
		sti r13, %-436, %-24
		sti r1, %-436, %-27
		fork %-506
		zjmp %-473

init:	sti r1, %:while, %1
		sti r1, %:fork, %1
		sti r1, %:move, %1
		sti r1, %:clone, %1
		sti r1, %:cloner, %1
		ldi %:clone, %0, r2
		ldi %:clone, %4, r3
		ldi %:clone, %8, r4
		ldi %:cloner, %0, r5
		ldi %:cloner, %4, r6
		ldi %:cloner, %8, r7
		ldi %:cloner, %12, r8
		ldi %:cloner, %16, r9
		ldi %:cloner, %20, r10
		ldi %:cloner, %24, r11
		ldi %:cloner, %28, r12
		ldi %:cloner, %32, r13
		ldi %:cloner, %36, r1
		ld %16, r16

while:	live %42
		ld %0, r14
		fork %:while

fork:	live %42
		fork %:while
		zjmp %:move

cloner:	live %42
		sti r2, r15, %-22
		sti r3, r15, %-24
		sti r4, r15, %-26
		sub r15, r16, r15
		sub r14, r14, r14
		zjmp %-33
		zjmp %-53

clone:	live %42
		fork %-5
		zjmp %-25
