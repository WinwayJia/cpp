.data
    hw:
        .string "hello world\n"
    fmt:
        .string "x = %d\n"

.text
.globl main
max:
    push    %ebp
    movl    %esp, %ebp
    movl    8(%ebp), %eax
    movl    12(%ebp), %ebx
    cmpl    %eax, %ebx
    jle     .LESS
    movl    $10, %eax
    jmp     .MORE
.LESS:
    movl $-10, %eax
.MORE:
    leave
    ret

sum:
    push    %ebp
    movl    %esp, %ebp

    movl    8(%ebp), %eax
    addl    12(%ebp), %eax

    leave
    ret

call_c_lib:
    pushl   %ebp
    movl    %esp, %ebp
    subl    $40, %esp
# call sum
    movl    $12, 4(%esp)
    movl    $13, (%esp)
    call    sum
#movl    8(%ebp), %eax
    movl    %eax, 4(%esp)
    movl    $fmt, (%esp)
    call    printf
    leave
    ret

print:
    pushl   %ebp
    movl    %esp, %ebp
    subl    $32, %esp
    movl    8(%ebp), %eax
    addl    $64, %eax
    movb    $0x41, -9(%ebp)
    movb    $0x42, -10(%ebp)
    movb    $0x43, -11(%ebp)
    movb    $0x44, -12(%ebp)
    movb    $10, -8(%ebp)
#    movl    $0x41424344, -12(%ebp)

    # last parameter
    movl    $5, 8(%esp)

    # second parameter
    leal    -12(%ebp), %eax
    movl    %eax, 4(%esp)

    # first parameter
    movl    $1, (%esp)

    call    write

    leave
    ret

main:
    movl    $4,%eax
    movl    $1,%ebx
    movl    $hw,%ecx
    movl    $12,%edx
    int     $0x80

    subl    $4, %esp
    movl    $4, (%esp)
    call    print

    subl    $8, %esp
    movl    $4, (%esp)
    movl    $5, 4(%esp)
    call    max

    subl    $4, %esp
    movl    %eax, (%esp)
    call    call_c_lib

    movl    $1,%eax
    xorl    %ebx,%ebx
    int     $0x80

    ret
