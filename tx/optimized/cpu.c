#include <unistd.h>

int main() {
    fork();
    fork();
    fork();
    while(1);
}
