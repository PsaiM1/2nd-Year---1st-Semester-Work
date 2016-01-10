# Author: PrasannaSai Meruga
# Section: Majeed 10 AM (0103)
# TerpConnect: pmeruga
# UID: 113557576

# This program reads ints from its input until it gets 0 and stores it
# into an array of size 100
# It then reads another list of ints and then proceeds to search for them
# in the array and if the int is found it's index is then printed
# otherwise a -1 is printed
	
	.data
arr:	.space 400		# arr[100]
n:	.word 0			# n = 0
max:	.word 0			# max = 0
element:	.word 0		# element = 0
idx:	.word 0			# idx = 0

	.text

main:	li $v0, 5		# scanf(d, &n)
	syscall	
	move $t0, $v0		
	sw $t0, n

loop1:	beqz $t0, endloop1	# if (n == 0)
	lw $t1, max
	li $t6, 100
	bge $t1, $t6, endif1	# if (max >= 100) then endif1
	mul $t1, $t1, 4 	# multiply by 4 so it indexes properly
	sw $t0, arr($t1)	# arr[max] = n
	div $t1, $t1, 4		# divide by 4 to reset max
	add $t1, $t1, 1		# max++
	sw $t1, max		# store max

endif1:	li $v0, 5		# scanf(d, n)
	syscall
	move $t0, $v0
	sw $t0, n		# store n
	j loop1

endloop1:
	li $v0, 5 		# scanf(d, &element)
	syscall
	move $t2, $v0
	sw $t2, element

loop2:  lw $t2, element		# load element
	beqz $t2, endloop2	# if (element == 0) go to endloop2
	lw $t3, idx		# loads it, idx already 0

loop3:	slt $t4, $t3, $t2	# idx < max
	mul $t3, $t3, 4		# idx * 4 for proper indexing
	lw $t5, arr($t3)	# load arr[idx]
	sne $t5, $t5, $t2	# arr[idx] != element
	and $t5, $t5, $t4	# idx < max && arr[idx] != element
	lw $t3, idx		# reset idx
	beqz $t5, endloop3	# while(idx < max && arr[idx] != element)
	add $t3, $t3, 1		# idx++
	sw $t3, idx		# store idx
	j loop3

endloop3:
	beqz $t4, else		# if (idx < max) is false goto else
	li $v0, 1		# printf(d, idx)
	move $a0, $t3
	syscall
	j cont			# avoid the else

else:	li $v0, 1		# printf(d, -1)
	li $t3, -1
	move $a0, $t3
	syscall

cont:	li $v0, 11		# printf(\n)
	li $t6, 10
	move $a0, $t6
	syscall

	li $v0, 5		# scanf(d, &element)
	syscall
	move $t3, $v0
	sw $t3, element		# store it in element
	
	j loop2

endloop2:
	li $v0, 10		# exit
	syscall
	
