# Author: PrasannaSai Meruga
# Section: Majeed 10 AM (0103)
# TerpConnect: pmeruga
# UID: 113557576

# The purpose of this program is to read an integer from input
# and then count how many digits it has
# Returns: a value greater than or equal to 1 even if input is negative
	
	.data
n:	.word 0

	.text
	
main:	li $sp, 0x7ffffffc	# prepare the stack
	
	li $v0, 5		# scanf(d, &n)
	syscall
	sw $v0, n

	lw $t2, n
	sw $t2, ($sp)
	sub $sp, $sp, 4		# push n onto the stack
	jal countd		# call the count_digits function

	add $sp, $sp, 4		# pop the stack

	move $t3, $v0		# acquire the returned value

	li $v0, 1		# printf(d\n, count_digits(n)) 
	move $a0, $t3
	syscall

	li $v0, 11
	li $a0, 10
	syscall

	li $v0, 10		# exit
	syscall

countd:	sub $sp, $sp, 12	# grow stack (PROLOGUE)
	sw $ra, 12($sp)		# save return address
	sw $fp, 8($sp)		# save old frame pointer
	add $fp, $sp, 12	# make new frame pointer
	
	
	lw $t0, 4($fp)		# load param value
	li $t1, 0		# num_digits = 0

	bgez $t0, loop 		# if (value >= 0) go to loop
	neg $t0, $t0		# value = -value

loop:	div $t0, $t0, 10	# do value /= 10
	add $t1, $t1, 1		# num_digits++
	blez $t0, return	# if (value <= 0) go to return
	j loop			# else loop again

return: move $v0, $t1		# $v0 contains the num_digit value to return
	lw $ra, 12($sp)		# load the return address (EPILOGUE)
	lw $fp, 8($sp)		# load the old frame pointer
	add $sp, $sp, 12	# pop the stack
	jr $ra			# return
