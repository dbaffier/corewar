.name "i"
.comment "blabla"

label01: 
ldi r1,r1,r1#nullr1,r1 #lllll
	ldi r1,r1,r1#nullr1,r1 #lllll
l:	ldi -345, r1, r1
	live %2
	zjmp %23
	fork %4
	lfork %10
