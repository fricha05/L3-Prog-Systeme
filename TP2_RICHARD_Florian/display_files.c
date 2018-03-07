#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <ftw.h>

#include "stat.h"
#include "display_files.h"

int is_dir(const char type) {
    return type == 'd' ? 1 : 0;
}

/**********************************************************************
PARCOURS NON RECURSIF D'UNE ARBORESCENCE
**********************************************************************/

int display(const char * path, int mode) {
    struct stat buf;
    char type;
    int r;

    if (lstat(path, &buf) == -1)
        return -1;

    type = filetype(buf.st_mode);
    if (is_dir(type))
        r = display_dir(path, mode);
    else
        r = display_file(path, mode);

    return r;
}
/**********************************************************************/
int display_file(const char * path, int mode) {
    struct stat buf;
    char type;

    if (lstat(path, &buf) == -1)
        return -1;

    type = filetype(buf.st_mode);
    affiche_infos(&buf, type, path, mode);

    if (is_link(type)) {
        affiche_link(path);
    }
    printf("\n");
    return 0;
}
/**********************************************************************/
int display_dir(const char * path, int mode) {
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    while (n--) {
        size_t size = strlen(path) + strlen(namelist[n]->d_name) + 2;

        char fullpath[BUFSIZ];

        snprintf(fullpath, size, "%s/%s", path, namelist[n]->d_name);

        if (display_file(fullpath, mode) == -1)
            return -1;
    }
    free(namelist);
    printf("\n");

    return 0;
}


/**********************************************************************
PARCOURS RECURSIF D'UNE ARBORESCENCE
**********************************************************************/
int display_rec(const char * path, int recur, int mode) {
    struct stat buf;
    char type;
    int r;

    if (lstat(path, &buf) == -1)
        return -1;

    type = filetype(buf.st_mode);
    if (is_dir(type))
        r = display_dir_rec(path, recur, mode);
    else
        r = display_file(path, mode);

    return r;
}

/**********************************************************************/
int display_dir_rec(const char * path, int recur, int mode) {
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    while (n--) {
        struct stat buf;
        char type;

        size_t size = strlen(path) + strlen(namelist[n]->d_name) + 2;

        char fullpath[BUFSIZ];
        snprintf(fullpath, size, "%s/%s", path, namelist[n]->d_name);

        if (lstat(fullpath, &buf) == -1)
            return -1;

        type = filetype(buf.st_mode);
        /** si c'est un répertoire != "." ou ".." et c'est récursif */
        if (is_dir(type) && recur == 1 &&
                strcmp(namelist[n]->d_name, ".") && strcmp(namelist[n]->d_name, "..")) {
            if (display_dir_rec(fullpath, recur, mode) == -1)
                return -1;
        } else {
            if (display_file(fullpath, mode) == -1)
                return -1;
        }
    }
    free(namelist);

    return 0;
}


