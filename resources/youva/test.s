.name "train"
.comment "TCHOUTCHOU"

;sti r2, r4, r6     ;0b 54 02 04 06
;sti r3, r5, r6     ;0b 54 03 05 06
;live %42           ;01 00 00 00 2a

begin:
	st r1, 0
	ldi %:begin, %0, r1
	fork %:train
loop:
	sti r1, %:init, %1
	sti r1, %:launch, %11
	sti r1, %:start, %1
	sti r1, %:live1, %1
	sti r1, %:live2, %1
	sti r1, %:end, %1
	and %1, %0, r2
start:
	live %-1
	fork %:start
live1:
	live %-1
	fork %:start
live2:
	live %-1
	fork %:start
end:
	live %-1
	zjmp %:end
train:
init:
	live %-1
	fork %:split
	ld %190054916, r2    ;0b 54 02 04 190054916 ar2
	ldi %:start, %-2, r3
	and r3, %65535, r3        ;00 00 FF FF
	or r3, %84279296, r3      ;05 06 00 00
;	ld %84279552, r3     ;05 06 01 00 84279552  ar3
	ld %15, r4
	ld %18, r5
	and %1, %2, r16
	zjmp %:launch
split:
	ld %101405699, r2    ;06 0b 54 03 101405699 br2
	ldi %:start, %2, r3
	and r3, %4294967040, r3        ;FF FF FF 00
	or r3, %11, r3      ;00 00 00 0b
;	ld %10752, r3        ;00 00 2a 0b 10752     br3
	ld %19, r4
	ld %22, r5
	and %1, %2, r16
	zjmp %:launch
launch:
	sti r2, r4, r6
	sti r3, r5, r6
	live %-1

; 03 70 01 00 00 0a a4 ff fb 00 00 01 0c 00 58 0b 68 01 00 55 00 01 0b 68 01 00 aa 00 0b 0b 68 01 00 27 00 01 0b 68 01 00 28 00 01 0b 68 01 00 29 00 01 0b 68 01 00 2a 00 01 06 a4 00 00 00 01 00 00 00 02 02 01 ff ff ff ff 0c ff fb 01 ff ff ff ff 0c ff f3 01 ff ff ff ff 0c ff eb 01 ff ff ff ff 09 ff fb 01 ff ff ff ff 0c 00 2d 02 90 0b 54 02 04 02 02 90 05 06 01 00 03 02 90 00 00 00 0f 04 02 90 00 00 00 12 05 06 a4 00 00 00 01 00 00 00 02 10 09 00 2d 02 90 06 0b 54 03 02 02 90 00 00 2a 00 03 02 90 00 00 00 13 04 02 90 00 00 00 16 05 06 a4 00 00 00 01 00 00 00 02 10 09 00 03 0b 54 02 04 06 0b 54 03 05 06 01 ff ff ff ff
