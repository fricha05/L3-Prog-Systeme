#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern char filetype(mode_t st_mode);
extern void affiche_infos(const struct stat * buf, char type, const char * s);
extern void affiche_inode(const struct stat * buf) ;

char filetype(mode_t st_mode) {
    short i;

    /** pour �viter les suites de if ou les switch/case */
    struct _typemap {
        char type;
        short macro;
    } typemap[] = {
        {'f', S_ISREG(st_mode)}, // fichier r�gulier
        {'d', S_ISDIR(st_mode)} // directory
    };

    for (i = 0; i < 2; ++i)
        if (typemap[i].macro == 1)
            return typemap[i].type;
    return '?';
}


void affiche_infos(const struct stat * buf, char type, const char * s) {
    affiche_inode(buf);
    printf("%c ", type);
    printf("%s\n", s);
}

void affiche_inode(const struct stat * buf) {
    printf("%ld ", buf->st_ino);
    printf("%8ld ", buf->st_size);
    printf("%ld\n", buf->st_mtime);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        struct stat buf;

        if (stat(argv[1], &buf) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }

        char type = filetype(buf.st_mode);
        affiche_infos(&buf, type, argv[1]);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_FAILURE);
}
