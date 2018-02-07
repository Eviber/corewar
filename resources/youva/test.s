.name "train"
.comment "TCHOUTCHOU"

begin:
	st r1, 0
	ldi %:begin, %0, r1
	fork %:train
loop:
	sti r1, %:init, %1
	sti r1, %:launch, %1
	sti r1, %:start, %1
	sti r1, %:live1, %1
	sti r1, %:live2, %1
	sti r1, %:end, %1
	and %1, %2, r2
start:
	live %42
	fork %:start
live1:
	live %42
	fork %:start
live2:
	live %42
	fork %:start
end:
	live %42
	zjmp %:end
train:
	ld %33554431, r5    ;01 ff ff ff
	ld %4278933506, r6  ;ff 0b 58 02
	ld %50460425, r7    ;03 01 f7 09
	ld %32964608, r8    ;01 f7 00 00

	ld %225285, r9      ;00 03 70 05
	ld %33489776, r10   ;01 ff 03 70
	ld %100793859, r11  ;06 01 fe 03
	ld %1879507453, r12 ;70 07 01 fd
	ld %57673729, r13   ;03 70 08 01
	ld %4228448747, r14 ;fc 09 01 eb
init:
	live %42
	fork %:split
	ld %33751040, r2    ;02 03 00 00
	ld %8, r3
	and %1, %2, r4
	zjmp %:launch
split:
	ld %190317059, r2   ;0b 58 02 03
	ld %6, r3
	and %1, %2, r4
	zjmp %:launch
launch:
	live %42
	st r9, 510
	st r10, 509
	st r11, 508
	st r12, 507
	st r13, 506
	st r14, 505
	zjmp %481
