#include <stdio.h>

int main (int argc,char* argv[]) {
    //on s'assure qu'il n'y aura pas de probl�me de bufferisation
    setvbuf(stdout,NULL,_IONBF,0);

    while(1) {
        int a;
        int b;
        scanf("%d %d",&a,&b) ;
        printf("%d\n",a - b) ;
    }

    return 0;
}
