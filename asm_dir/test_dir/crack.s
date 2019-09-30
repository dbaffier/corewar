.name "i"
.comment "
blabla"

<<<<<<< HEAD
label01: 
ldi r1,r1,r1#nullr1,r1 #lllll
	ldi r1,r1,r1#nullr1,r1 #lllll
=======
l:	ldi -345, r1, r1
	live %-42
	zjmp %23
	fork %4
	lfork %10
>>>>>>> 100e41ba54419ce810df68991b734e0bde981747
