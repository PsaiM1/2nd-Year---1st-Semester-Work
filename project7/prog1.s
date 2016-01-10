# Author: PrasannaSai Meruga
# Section: Majeed 10 AM (0103)
# TerpConnect: pmeruga
# UID: 113557576

# The function of this program is to read 3 integers from input
# and then counts the number of multiples of the 3rd int that lies between the
# first 2 numbers inclusively
# Returns: A value greater than or equal to 0
	
	.data

m:	.word 0
n:	.word 0
mod_value:	.word 0
count:	.word 0

	.text

main:	li $v0, 5		 # scanf for m
	syscall
	sw $v0, m

	li $v0, 5		 # scanf for n
	syscall
	sw $v0, n

	li $v0, 5
	syscall
	sw $v0, mod_value	 # scanf for mod_value

	lw $t0, n
	lw $t1, mod_value

while:	lw $t2, m
	bgt $t2, $t0, endloop	 # while loop, if m > n then go to endloop
	rem $t3, $t2, $t1	 # mod % mod_value
	bnez $t3, endif 	 # if (m % mod_value != 0) go to endif
	lw $t4, count		 # load count
	add $t4, $t4, 1		 # count++
	sw $t4, count		 # store count

endif:	add $t2, $t2, 1		 # m++
	sw $t2, m		 # store m
	j while			 # loop if condition met


endloop:
	li $v0, 1
	lw $a0, count 		 # print count
	syscall

	li $v0, 11
	li $a0, 10 		 # print a newline
	syscall

	li $v0, 10		 # exit
	syscall
