	.text
	.file	"division_solution.ll"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %code
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -16
	movl	$3, %eax
	movl	$0, 28(%rsp)
	movl	$13, 8(%rsp)
	.p2align	4, 0x90
.LBB0_1:                                # %mycode
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_2 Depth 2
	movl	$1, 24(%rsp)
	movl	$1, 16(%rsp)
	movl	%eax, 20(%rsp)
	movl	%eax, 12(%rsp)
	cmpl	8(%rsp), %eax
	jg	.LBB0_3
	.p2align	4, 0x90
.LBB0_2:                                # %WHILE_LOOP
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	24(%rsp), %ecx
	movl	%ecx, 16(%rsp)
	movl	20(%rsp), %edx
	movl	%edx, 12(%rsp)
	addl	%edx, %edx
	movl	%edx, 20(%rsp)
	addl	%ecx, %ecx
	movl	%ecx, 24(%rsp)
	cmpl	8(%rsp), %edx
	jle	.LBB0_2
.LBB0_3:                                # %WHILE_LOOP_END
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	8(%rsp), %ecx
	subl	12(%rsp), %ecx
	movl	%ecx, 8(%rsp)
	movl	16(%rsp), %edx
	addl	%edx, 28(%rsp)
	cmpl	%eax, %ecx
	jge	.LBB0_1
# %bb.4:                                # %MY_CODE_END
	movl	28(%rsp), %esi
	movl	8(%rsp), %ebx
	movl	$.L.str, %edi
	xorl	%eax, %eax
	callq	printf
	movl	$.L.str, %edi
	xorl	%eax, %eax
	movl	%ebx, %esi
	callq	printf
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbx
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata,"a",@progbits
.L.str:
	.asciz	"Output: %d\n"
	.size	.L.str, 12


	.section	".note.GNU-stack","",@progbits
