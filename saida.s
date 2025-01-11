.data
.printInt: .string "%d"
.printChar: .string "%c"
.printNewLine: .string "\n"
.readChar: .string " %c"
.globl main
stringName4:
.string " eh maior que "
stringName3:
.string " eh menor que "
stringName2:
.string "A letra "
stringName1:
.string "Insira um numero: "
stringName0:
.string "Insira uma letra: "
c_1:
.long 1
c_2:
.long 2
c_3:
.long 3
_a:
.long 0
_b:
.long 0
_c:
.long 0
temp0:
.long 0
temp1:
.long 0
.text
main:

 # MOVE
movl c_1(%rip), %eax
 movl %eax, _a(%rip)

 # MOVE
movl c_2(%rip), %eax
 movl %eax, _b(%rip)

 # MOVE
movl c_3(%rip), %eax
 movl %eax, _c(%rip)

 # BEGINFUN
_main:
 pushq %rbp
 movq %rsp, %rbp

 # PRINT_STRING
leaq stringName0(%rip), %rax
 movq %rax, %rdi
 call printf@PLT
leaq .printNewLine(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # READ_CHAR
leaq _b(%rip), %rax
 movq %rax, %rsi
leaq .readChar(%rip), %rax
 movq %rax, %rdi
 call scanf@PLT

 # PRINT_STRING
leaq stringName1(%rip), %rax
 movq %rax, %rdi
 call printf@PLT
leaq .printNewLine(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # READ_INT
leaq _a(%rip), %rax
 movq %rax, %rsi
leaq .printInt(%rip), %rax
 movq %rax, %rdi
 call scanf@PLT

 # LESS
movl _b(%rip), %edx
 movl _a(%rip), %eax
 cmpl %eax, %edx
 setl %al
 movzbl %al, %eax
 movl %eax, temp1(%rip)

 # IF
movl temp1(%rip), %eax
 testl %eax, %eax
 je label2

 # PRINT_STRING
leaq stringName2(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # PRINT_CHAR
movl _b(%rip), %eax
 movl %eax, %esi
 leaq .printChar(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # PRINT_STRING
leaq stringName3(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # PRINT_INT
movl _a(%rip), %eax
 movl %eax, %esi
 leaq .printInt(%rip), %rax
 movq %rax, %rdi
 call printf@PLT
leaq .printNewLine(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # JMP
jmp label3
label2:

 # PRINT_STRING
leaq stringName2(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # PRINT_CHAR
movl _b(%rip), %eax
 movl %eax, %esi
 leaq .printChar(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # PRINT_STRING
leaq stringName4(%rip), %rax
 movq %rax, %rdi
 call printf@PLT

 # PRINT_INT
movl _a(%rip), %eax
 movl %eax, %esi
 leaq .printInt(%rip), %rax
 movq %rax, %rdi
 call printf@PLT
leaq .printNewLine(%rip), %rax
 movq %rax, %rdi
 call printf@PLT
label3:

 # ENDFUN
popq %rbp
 ret
.section .note.GNU-stack,"",@progbits
