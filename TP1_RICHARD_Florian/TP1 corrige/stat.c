#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "stat.h"

char filetype(mode_t st_mode) {
    short i;

    /** pour éviter les suites de if ou les switch/case */
    struct _typemap {
        char type;
        short macro;
    } typemap[] = {
        {'f', S_ISREG(st_mode)},    /* fichier régulier*/
        {'d', S_ISDIR(st_mode)},    /* directory*/
        {'l', S_ISLNK(st_mode)}     /* lien*/
};

    for (i = 0; i < 3; ++i)
        if (typemap[i].macro == 1)
            return typemap[i].type;
    return '?';
}

void affiche_infos(const struct stat * buf, char type, const char * filename) {
    affiche_inode(buf);
    printf("%c ", type);
    printf("%s\n", filename);
}

void affiche_inode(const struct stat * buf) {
    printf("%ld ", buf->st_ino);
    printf("%ld ", buf->st_size);
    printf("%ld\n", buf->st_mtime);
}

int is_link(const char type) {
    return type == 'l' ? 1 : 0;
}

void affiche_link(const char * filename) {
    char link_buf[BUFSIZ];
    ssize_t size;

    if ((size = readlink(filename, link_buf, BUFSIZ)) == -1) {
        perror("PB lien");
        exit(EXIT_FAILURE);
    }

    char link_str[BUFSIZ];
    snprintf(link_str, size + 1, "%s", link_buf);
    printf("%s -> %s", filename, link_str);
}

