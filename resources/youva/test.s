.name "train"
.comment "TCHOUTCHOU"


; 0b 58 06 03 00 1e 0b 58 07 03 00 1c 0b 58 08 03 00 1a 0b 58 09 03 00 18 0b 58 0a 03 00 16 0b 58 0b 03 00 14 0b 58 0c 03 00 12 09 fe 0c 09 01 ff

;sti r2, r3, r16      0b 54 02 03 10
;add r3, r4, r3       04 54 03 04 03
;xor r3, r5, r16      08 54 03 05 10
;zjmp %-511           09 fe 01
;xor r16, r16, r16    08 54 10 10 10
;zjmp %:loop          09 ff e9

start:
	st r1, -4
	ld %1, r1
	st r1, -20
	ldi %:start, %-4, r1
load:
	ld %252645135, r2
	ld %350, r3
	ld %32, r4
	ld %542, r5

	ld %2900, r6        ;00 00 0b 54
	ld %33755140, r7    ;02 03 10 04
	ld %1409483779, r8  ;54 03 04 03
	ld %139723525, r9   ;08 54 03 05
	ld %269090433, r10  ;10 09 fe 01
	ld %139726864, r11  ;08 54 10 10
	ld %269090793, r12  ;10 09 ff e9

	st r1, 6
	live %0
done:
	zjmp %:done
loop:
	xor r16, r16, r16
	sti r6, r3, %61
	sti r7, r3, %59
	sti r8, r3, %57
	sti r9, r3, %55
	sti r10, r3, %53
	sti r11, r3, %51
	sti r12, r3, %49
	zjmp %371
	zjmp %-383
