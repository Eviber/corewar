.name "test"
.comment "IMDUMBLOL"

init:
	st r1, 0
	ldi %:init, %0, r1
loop:
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
end:
	live %42
	zjmp %:end
