#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void bye()
{
    printf("bye\n");
}

void byebye()
{
    printf("bye-bye\n");
}

int main()
{
    atexit(bye);
    atexit(byebye);
    
    _exit(0);

    return 0;
}
