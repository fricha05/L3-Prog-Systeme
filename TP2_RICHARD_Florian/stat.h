#ifndef STAT_H_INCLUDED
#define STAT_H_INCLUDED

/*
 * Permet de renvoyer une chaîne de caractères représentant le type de
 * fichier passé en argument 
 */
extern char filetype(mode_t st_mode);

/*
 * Affiche le numéro d'inode, le type et le nom du fichier de la 
 * structure stat passée en paramètre
 * Affiche les éléments supplémentaire spécifiés en option grâce au
 * paramètre mode
 */
extern void affiche_infos(const struct stat * buf, char type, const char * s, int mode);

/*
 * Affiche le numéro d'inode, la taille et la date de dernière 
 * modification d'une structure stat passée en paramètre
 */
extern void affiche_inode(const struct stat * buf);

/*
 * Affiche le fichier auquel le fichier link passé en argument est lié
 */
extern void affiche_link(const char * filename);

/*
 * retourne 1 si le fichier passé en argument par son chemin est un 
 * lien, 0 sinon.
 */
extern int is_link(const char type);

#endif /* STAT_H_INCLUDED*/
