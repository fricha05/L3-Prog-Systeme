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

int display(const char * path) {
    struct stat buf;
    char type;
    int r;

    if (lstat(path, &buf) == -1)
        return -1;

    type = filetype(buf.st_mode);
    if (is_dir(type))
        r = display_dir(path);
    else
        r = display_file(path);

    return r;
}
/**********************************************************************/
int display_file(const char * path) {
    struct stat buf;
    char type;

    if (lstat(path, &buf) == -1)
        return -1;

    type = filetype(buf.st_mode);
    affiche_infos(&buf, type, path);

    if (is_link(type)) {
        affiche_link(path);
    }
    printf("\n");
    return 0;
}
/**********************************************************************/
int display_dir(const char * path) {
    DIR * dir;
    struct dirent * dirent;

    if (NULL == (dir = opendir(path)))
        return -1;

    while (NULL != (dirent = readdir(dir))) {
        size_t size = strlen(path) + strlen(dirent->d_name) + 2;

        char fullpath[BUFSIZ];
        snprintf(fullpath, size, "%s/%s", path, dirent->d_name);

        if (display_file(fullpath) == -1)
            return -1;
    }
    printf("\n");

    closedir(dir);
    return 0;
}


/**********************************************************************
PARCOURS RECURSIF D'UNE ARBORESCENCE
**********************************************************************/
int display_rec(const char * path, int recur) {
    struct stat buf;
    char type;
    int r;

    if (lstat(path, &buf) == -1)
        return -1;

    type = filetype(buf.st_mode);
    if (is_dir(type))
        r = display_dir_rec(path, recur);
    else
        r = display_file(path);

    return r;
}

/**********************************************************************/
int display_dir_rec(const char * path, int recur) {
    DIR * dir;
    struct dirent * dirent;

    if (NULL == (dir = opendir(path)))
        return -1;

    while (NULL != (dirent = readdir(dir))) {
        struct stat buf;
        char type;

        size_t size = strlen(path) + strlen(dirent->d_name) + 2;

        char fullpath[BUFSIZ];
        snprintf(fullpath, size, "%s/%s", path, dirent->d_name);

        if (lstat(fullpath, &buf) == -1)
            return -1;

        type = filetype(buf.st_mode);
        /** si c'est un répertoire != "." ou ".." et c'est récursif */
        if (is_dir(type) && recur == 1 &&
                strcmp(dirent->d_name, ".") && strcmp(dirent->d_name, "..")) {
            if (display_dir_rec(fullpath, recur) == -1)
                return -1;
        } else {
            if (display_file(fullpath) == -1)
                return -1;
        }
    }

    closedir(dir);
    return 0;
}

/**********************************************************************
PARCOURS RECURSIF D'UNE ARBORESCENCE utilisant la fonction ftw
**********************************************************************/

int display_ftw(const char * path, int recur) {
    struct stat buf;
    char type;
    int r;

    if (lstat(path, &buf) == -1)
        return -1;

    type = filetype(buf.st_mode);
    if (is_dir(type))
        r = display_dir_ftw(path, recur);
    else
        r = display_file_ftw(path, &buf, FTW_F);

    return r;
}

/**********************************************************************/

int display_file_ftw(const char * path, const struct stat * buf, int recur) {
    char type;

    type = filetype(buf->st_mode);
    affiche_infos(buf, type, path);

    if (is_link(type)) {
        affiche_link(path);
    }
    printf("\n");
    return 0;
}


/**********************************************************************/

int display_dir_ftw(const char * path, int recur) {
    DIR * dir;
    struct dirent * dirent;
    int deep = 16;

    if (recur == 1) {
	if (ftw(path, display_file_ftw, deep) == -1)
		return -1;
	else
		return 0;
    }
 
    if (NULL == (dir = opendir(path)))
        return -1;

    while (NULL != (dirent = readdir(dir))) {
        struct stat buf;
        size_t size = strlen(path) + strlen(dirent->d_name) + 2;

        char fullpath[BUFSIZ];
        snprintf(fullpath, size, "%s/%s", path, dirent->d_name);

        if (lstat(fullpath, &buf) == -1)
            return -1;

        if (display_file_ftw(fullpath, &buf, 0) == -1)
            return -1;
    }
    printf("\n");

    closedir(dir);
    return 0;
}




