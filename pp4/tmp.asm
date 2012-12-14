	# standard Decaf preamble 
	  .text
	  .align 2
	  .globl main
  Cow.labelPrefixMoo:
	# BeginFunc 20
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 20	# decrement sp to make space for locals/temps
	# _tmp0 = i + j
	  lw $t0, 8($fp)	# load i from $fp+8 into $t0
	  lw $t1, 12($fp)	# load j from $fp+12 into $t1
	  add $t2, $t0, $t1	
	# _tmp1 = _tmp0 + k
	  lw $t3, 16($fp)	# load k from $fp+16 into $t3
	  add $t4, $t2, $t3	
	# _tmp2 = _tmp1 + l
	  lw $t5, 20($fp)	# load l from $fp+20 into $t5
	  add $t6, $t4, $t5	
	# _tmp3 = _tmp2 + m
	  lw $t7, 24($fp)	# load m from $fp+24 into $t7
	  add $s0, $t6, $t7	
	# _tmp4 = _tmp3 + n
	  lw $s1, 28($fp)	# load n from $fp+28 into $s1
	  add $s2, $s0, $s1	
	# Return _tmp4
	  move $v0, $s2		# assign return value into $v0
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
  Cow.labelPrefixMethod:
	# BeginFunc 24
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 24	# decrement sp to make space for locals/temps
	# _tmp5 = 0
	  li $t0, 0		# load constant value 0 into $t0
	# IfZ _tmp5 Goto _L0
	# (save modified registers before flow of control change)
	  sw $t0, -8($fp)	# spill _tmp5 from $t0 to $fp-8
	  beqz $t0, _L0	# branch if _tmp5 is zero 
	# PushParam a
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, 8($fp)	# load a from $fp+8 into $t0
	  sw $t0, 4($sp)	# copy param value to stack
	# PushParam a
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t0, 4($sp)	# copy param value to stack
	# PushParam a
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t0, 4($sp)	# copy param value to stack
	# PushParam a
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t0, 4($sp)	# copy param value to stack
	# PushParam a
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t0, 4($sp)	# copy param value to stack
	# PushParam a
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t0, 4($sp)	# copy param value to stack
	# PushParam this
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t1, 4($fp)	# load this from $fp+4 into $t1
	  sw $t1, 4($sp)	# copy param value to stack
	# _tmp6 = *(this)
	  lw $t2, 0($t1) 	# load with offset
	# _tmp7 = *(_tmp6)
	  lw $t3, 0($t2) 	# load with offset
	# _tmp8 = ACall _tmp7
	# (save modified registers before flow of control change)
	  sw $t2, -12($fp)	# spill _tmp6 from $t2 to $fp-12
	  sw $t3, -16($fp)	# spill _tmp7 from $t3 to $fp-16
	  jalr $t3            	# jump to function
	  move $t0, $v0		# copy function return value from $v0
	# PopParams 28
	  add $sp, $sp, 28	# pop params off stack
	# Goto _L1
	# (save modified registers before flow of control change)
	  sw $t0, -20($fp)	# spill _tmp8 from $t0 to $fp-20
	  b _L1		# unconditional branch
  _L0:
  _L1:
	# _tmp9 = 3
	  li $t0, 3		# load constant value 3 into $t0
	# PushParam _tmp9
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	# (save modified registers before flow of control change)
	  sw $t0, -24($fp)	# spill _tmp9 from $t0 to $fp-24
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp10 = 4
	  li $t0, 4		# load constant value 4 into $t0
	# PushParam _tmp10
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	# (save modified registers before flow of control change)
	  sw $t0, -28($fp)	# spill _tmp10 from $t0 to $fp-28
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# VTable for class Cow
	  .data
	  .align 2
	  Cow:		# label for class Cow vtable
	  .word Cow.labelPrefixMoo
	  .word Cow.labelPrefixMethod
	  .text
  main:
	# BeginFunc 40
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 40	# decrement sp to make space for locals/temps
	# _tmp11 = 0
	  li $t0, 0		# load constant value 0 into $t0
	# _tmp12 = 4
	  li $t1, 4		# load constant value 4 into $t1
	# _tmp13 = _tmp12 + _tmp11
	  add $t2, $t1, $t0	
	# PushParam _tmp13
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t2, 4($sp)	# copy param value to stack
	# _tmp14 = LCall _Alloc
	# (save modified registers before flow of control change)
	  sw $t0, -12($fp)	# spill _tmp11 from $t0 to $fp-12
	  sw $t1, -16($fp)	# spill _tmp12 from $t1 to $fp-16
	  sw $t2, -20($fp)	# spill _tmp13 from $t2 to $fp-20
	  jal _Alloc         	# jump to function
	  move $t0, $v0		# copy function return value from $v0
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp15 = Cow
	  la $t1, Cow	# load label
	# *(_tmp14) = _tmp15
	  sw $t1, 0($t0) 	# store with offset
	# c = _tmp14
	  move $t2, $t0		# copy value
	# _tmp16 = 6
	  li $t3, 6		# load constant value 6 into $t3
	# PushParam _tmp16
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t3, 4($sp)	# copy param value to stack
	# PushParam c
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  sw $t2, 4($sp)	# copy param value to stack
	# _tmp17 = *(c)
	  lw $t4, 0($t2) 	# load with offset
	# _tmp18 = *(_tmp17 + 4)
	  lw $t5, 4($t4) 	# load with offset
	# ACall _tmp18
	# (save modified registers before flow of control change)
	  sw $t0, -24($fp)	# spill _tmp14 from $t0 to $fp-24
	  sw $t1, -28($fp)	# spill _tmp15 from $t1 to $fp-28
	  sw $t2, -8($fp)	# spill c from $t2 to $fp-8
	  sw $t3, -32($fp)	# spill _tmp16 from $t3 to $fp-32
	  sw $t4, -36($fp)	# spill _tmp17 from $t4 to $fp-36
	  sw $t5, -40($fp)	# spill _tmp18 from $t5 to $fp-40
	  jalr $t5            	# jump to function
	# PopParams 8
	  add $sp, $sp, 8	# pop params off stack
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
