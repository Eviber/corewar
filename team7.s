.name "train"
.comment "TCHOUTCHOU"

;sti r2, r4, r6     ;0b 54 02 04 06
;sti r3, r5, r6     ;0b 54 03 05 06
;live %42           ;01 00 00 00 2a

start:
	st r1, 0
	ld %1, r2
	st r2, -16
	ldi %:start, %0, r1
init:
	fork %:split
	ld %190054916, r2         ;0b 54 02 04 190054916 ar2
	ldi %:start, %-3, r3
	and r3, %65535, r3        ;00 00 FF FF
	or r3, %84279296, r3      ;05 06 00 00
;	ld %84279552, r3          ;05 06 01 00 84279552  ar3
	ld %15, r4
	ld %18, r5
	and %1, %2, r16
	zjmp %:launch
split:
	ld %101405699, r2         ;06 0b 54 03 101405699 br2
	ldi %:start, %1, r3
	and r3, %4294967040, r3   ;FF FF FF 00
	or r3, %11, r3            ;00 00 00 0b
;	ld %10752, r3             ;00 00 2a 0b 10752     br3
	ld %19, r4
	ld %22, r5
	and %1, %2, r16
	zjmp %:launch
launch:
	sti r2, r4, %490
	sti r3, r5, %489
	zjmp %493
