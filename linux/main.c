int g(int x)
{
    printf("%d", x);
      return x + 3;
}

int f(int x)
{
      return g(x);
}

int t(int x) {
    char c = 'A' + x;
    write(1, &c, 1);
}
main:
    pushl   %ebp
    movl    %esp, %ebp
    andl    $-16, %esp
    subl    $32, %esp
    movl    $10, 28(%esp)
    cmpl    $10, 28(%esp)
    jle .L8 
    movl    28(%esp), %eax
    movl    %eax, (%esp)
    call    t   
    movl    28(%esp), %eax
    movl    %eax, (%esp)
    call    g   
    jmp .L7 
    .L8:
        movl    $8, (%esp)
        call    f   
        addl    $1, %eax
    .L7:
        leave
        ret 
int main()
{
    int x = 10;
    if (x > 10) {
        t(x);
    } else {
        return f(8) + 1;
    }

    g(x);
}
