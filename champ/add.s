.name "add"
.comment ""

ld		%-1, r2
ld		%1, r4
add		r1, r2, r3
st		r3, 50
sub		r1, r4, r3
st		r3, 50
