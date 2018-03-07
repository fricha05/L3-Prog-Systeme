#ifndef DISPLAY_FILES_H_INCLUDED
#define DISPLAY_FILES_H_INCLUDED

/*
 * Retourne 1 si le type la chaîne passée en argument correspond à "d",
 *  0 sinon.
 * Permet de savoir si un chemin correspond à un dossier ou non.
 */
extern int is_dir(const char type);

/*
 * Permet d'afficher le type d'un chemin passé en argument
 */
extern int display(const char * path, int mode);

/*
 * Permet d'afficher les informations sur le chemin passé en argument 
 * si c'est un fichier, 
 * et de dire si c'est un lien vers un autre fichier
 */ 
extern int display_file(const char * path, int mode);

/*
 * Affiche les dossier contenus dans le dossier passer en argument 
 */
extern int display_dir(const char * path, int mode);

/*
 * Permet de parcourir le contenu d'un dossier et de ses sous-dossiers
 * de façon récursive, et d'afficher tout les dossiers et fichiers 
 * trouvés
 * Affiche les éléments spécifiés en option grâce au paramètre mode
 */
extern int display_rec(const char * path, int recur, int mode);

/*
 * Permet de parcourir les sous dossiers d'un dossier de manière
 * récursive et d'afficher les chemin de ces sous dossiers grâce à
 * l'option -R récupérée avec getopt dans le main de exo5.c
 */
extern int display_dir_rec(const char * path, int recur, int mode);

#endif // DISPLAY_FILES_H_INCLUDED
