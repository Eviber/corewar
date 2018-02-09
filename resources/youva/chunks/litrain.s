.name "train"
.comment "TCHOUTCHOU"

init:
	st r1, 0
	ldi %:init, %0, r1
	sti r1, %:launcher, %1
load:
	ld %151220226, r2   ;09 03 70 02

	ld %57672193, r5    ;03 70 02 01
	ld %4278415362, r6   ;ff 03 70 02
	ld %33491201, r7      ;01 ff 09 01
	ld %4127195136, r8    ;f6 00 00 00

	ld %57672961, r9    ;03 70 05 01
	ld %4278415366, r10 ;ff 03 70 06
	ld %33424240, r11   ;01 fe 03 70
	ld %117570819, r12  ;07 01 fd 03
	ld %1879572988, r13 ;70 08 01 fc
	ld %16777216, r14   ;01 00 00 00
	ld %151119360, r15  ;09 01 e6 00
	and %1, %2, r4
launcher:
	live %42
	st r9, 511
	st r10, 510
	st r11, 509
	st r12, 508
	st r13, 507
	st r14, 506
	st r1, 502
	st r15, 501
	zjmp %471
