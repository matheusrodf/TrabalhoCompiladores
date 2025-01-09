.data
.printInt: .string "%d\n"
.printChar: .string "%c\n"
.globl main
c_10:
.long 10
c_2:
.long 2
c_4:
.long 4
c_5:
.long 5
_1:
.long 0
_a:
.long 0
_b:
.long 0
temp0:
.long 0
temp1:
.long 0
temp2:
.long 0
temp3:
.long 0
.text
main:
movl c_2(%rip), %eax
 movl %eax, _a(%rip)
movl c_4(%rip), %eax
 movl %eax, _b(%rip)
_main:
 pushq %rbp
 movq %rsp, %rbp
movl c_5(%rip), %eax
 addl c_2(%rip), %eax
 movl %eax, temp0(%rip)
movl _a(%rip), %edx
 movl temp0(%rip), %eax
 imull %edx, %eax
 movl %eax, temp1(%rip)
movl temp1(%rip), %eax
 movl c_2(%rip), %ecx
 cltd
 idivl %ecx, %eax
 movl %eax, temp2(%rip)
movl temp2(%rip), %eax
 subl _b(%rip), %eax
 movl %eax, temp3(%rip)
movl temp3(%rip), %eax
 movl %eax, _a(%rip)
movl _a(%rip), %eax
 movl %eax, %esi
 leaq .printInt(%rip), %rax
 movq %rax, %rdi
 call printf@PLT
movl c_2(%rip), %eax
 movl %eax, _b(%rip)
popq %rbp
 ret
_fun:
 pushq %rbp
 movq %rsp, %rbp
movl c_10(%rip), %eax
 movl %eax, _1(%rip)
movl _1(%rip), %eax
popq %rbp
 ret
popq %rbp
 ret
.section .note.GNU-stack,"",@progbits
