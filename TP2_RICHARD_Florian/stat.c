#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "stat.h"

char filetype(mode_t st_mode) {
    short i;

    /** pour �viter les suites de if ou les switch/case */
    struct _typemap {
        char type;
        short macro;
    } typemap[] = {
        {'f', S_ISREG(st_mode)},    /* fichier r�gulier*/
        {'d', S_ISDIR(st_mode)},    /* directory*/
        {'l', S_ISLNK(st_mode)}     /* lien*/
};

    for (i = 0; i < 3; ++i)
        if (typemap[i].macro == 1)
            return typemap[i].type;
    return '?';
}

void affiche_infos(const struct stat * buf, char type, const char * filename, int mode) {
    printf("%s ", filename);
    affiche_inode(buf);
    struct passwd* pwd;
    struct group* group;
    
    pwd = getpwuid(buf->st_uid);
    group = getgrgid(buf->st_gid);
    
    if(mode == 1){
		printf("%s ", pwd->pw_name);
		printf("%s ", group->gr_name);
	}
	if(mode == 2){
		printf("%d ", pwd->pw_uid);
		printf("%d ", group->gr_gid);
	}
    printf("%c ", type);
}

void affiche_inode(const struct stat * buf) {
    printf("%ld ", buf->st_ino);
    printf("%ld ", buf->st_size);
    printf("%s", ctime(&buf->st_mtime));
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

