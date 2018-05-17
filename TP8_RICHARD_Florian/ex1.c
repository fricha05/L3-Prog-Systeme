#include "ex1.h"

void repeat(char* message, int delay){
    while(1){
        write(1, message, strlen(message));
        write(1,"\n",sizeof(char));
        usleep(delay);
    }
}

int main(int argc, char const *argv[]) {
    repeat("salut", 3000000);
    exit(EXIT_SUCCESS);
}
