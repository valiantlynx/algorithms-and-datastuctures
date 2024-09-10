	.file	"Math.cpp"
	.text
	.p2align 4
	.globl	_Z8Multiplyii
	.def	_Z8Multiplyii;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z8Multiplyii
_Z8Multiplyii:
.LFB0:
	.seh_endprologue
	movl	%ecx, %eax
	imull	%edx, %eax
	ret
	.seh_endproc
	.ident	"GCC: (MinGW-W64 x86_64-msvcrt-posix-seh, built by Brecht Sanders) 13.1.0"
