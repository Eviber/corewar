.name "train"
.comment "TCHOUTCHOU"

;LAUNCHER 2
;sti r9, r4, %490   ;0b 58 09 04 01 ea
;sti r10, r5, %489  ;0b 58 0a 05 01 e9
;zjmp %494          ;09 01 ee

;LAUNCHER 1
;sti r7, r4, %490   ;0b 58 07 04 01 ea
;sti r8, r5, %489   ;0b 58 08 05 01 e9
;zjmp %494          ;09 01 ee

;LAUNCHER 0
;sti r2, r4, %490   ;0b 58 02 04 01 ea
;sti r3, r5, %489   ;0b 58 03 05 01 e9
;zjmp %493          ;09 01 ed

;TRAIN
;sti r2, r4, r6     ;0b 54 02 04 06
;sti r3, r5, r6     ;0b 54 03 05 06
;live %42           ;01 XX XX XX XX

start:
	st r1, 0
	ld %1, r2
	st r2, -16
	ldi %:start, %0, r1
init:
	fork %:split
                              ;TRAIN
	ld %190054916, r2         ;0b 54 02 04
	ldi %:start, %-3, r3
	or r3, %84279296, r3      ;05 06 00 00
	ld %15, r4
	ld %18, r5
                              ;LAUNCHER 0
	ld %743426, r7            ;00 0b 58 02
	ld %1476592897, r8        ;58 03 05 01

	ld %743431, r9            ;00 0b 58 07
	ld %1476920577, r10       ;58 08 05 01

	ld %743433, r11           ;00 0b 58 09
	ld %1477051649, r12       ;58 0a 05 01

	and %1, %2, r6
	zjmp %:launch
split:
                              ;TRAIN
	ld %101405699, r2         ;06 0b 54 03
	ldi %:start, %0, r3
	or r3, %11, r3            ;00 00 00 0b
	ld %19, r4
	ld %22, r5
                              ;LAUNCHER 0
	ld %67234315, r7          ;04 01 ea 0b
	ld %3909681645, r8        ;e9 09 01 ed

	ld %67234315, r9          ;04 01 ea 0b
	ld %3909681646, r10       ;e9 09 01 ee

	ld %67234315, r11         ;04 01 ea 0b
	ld %3909681646, r12       ;e9 09 01 ee

	and %1, %2, r6
	zjmp %:launch
launch:
	sti r11, r4, %384
	sti r12, r5, %383
	zjmp %388

