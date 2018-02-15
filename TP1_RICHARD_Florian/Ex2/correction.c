#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

extern char filetype(mode_t st_mode);
extern void affiche_infos(const struct stat * buf, char type, const char * s);
extern void affiche_inode(const struct stat * buf);
extern void affiche_link(const char * progname, const char * filename);

extern int is_link(const char type);

char filetype(mode_t st_mode) {
    short i;

    struct _typemap {
        char type;
        short macro;
    } typemap[] = {
        {'f', S_ISREG(st_mode)},
        {'d', S_ISDIR(st_mode)},
        {'l', S_ISLNK(st_mode)}
    };

    for (i = 0; i < 2; ++i)
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

void affiche_link(const char * progname, const char * filename) {
    char link_buf[BUFSIZ]; //BUFSIZ prédéfini
    ssize_t size;

    if ((size = readlink(filename, link_buf, BUFSIZ)) == -1) {
        perror(progname);
       exit(EXIT_FAILURE);
    }
    char * link_str = NULL;
    link_str = malloc(size + 1);
    if (NULL == link_str) {
        exit(EXIT_FAILURE);
    }

    snprintf(link_str, size + 1, "%s", link_str);
    printf(" -> %s", link_buf);

    free(link_str);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        struct stat buf;

        if (lstat(argv[1], &buf) == -1) {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }

        char type = filetype(buf.st_mode);
        affiche_infos(&buf, type, argv[1]);

        if (is_link(type)) {
           affiche_link(argv[0], argv[1]);
        }
        printf("\n");
    }
    exit(EXIT_SUCCESS);
}
