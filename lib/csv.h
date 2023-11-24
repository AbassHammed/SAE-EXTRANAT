/*
 Ce module a pour objectif d'être une interface avec les fichiers CSV.
 */

// Ici on défini une variable avec le pré-processeur C
// afin d'éviter que les fonctions ou "objets" soient définies plusieurs fois
// s'ils existent déjà.
#ifndef __CSV_HEADER
#define __CSV_HEADER

#define MAX_LINE 1024
#define MAX_BUFFER 2048

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

// Ceci est un entier positif.
typedef unsigned int uint;

/*
Cette énumération permet de lister toutes les différentes manières d'ouvrir un fichier.
Que ce soit pour écrire dedans, le lire, etc.

Le dernier élément permet de connaître combien d'éléments il y a en tout,
puisque chaque élément est assigné une valeur entière qui s'incrémente à
partir de zéro.
*/
typedef enum
{
  READ = 0,
  WRITE,
  WRITE_READ,
  NUM_OPENTYPE
} CSV_OpenType;

/*
Entrée: path (chaîne de caractères, chemin du fichier csv)
Retourne: un booléen

Cette fonction permet de savoir si un fichier existe.
*/
bool csv_fileExists(char *path);

/*
Entrée: opentype (enum CSV_OpenType)
Retoune: Une chaîne de caractère:
  "w" pour write
  "r" pour read

Cette fonction permet selon un enum CSV_OpenType de retourner une chaîne de caractères
qui sera utilisé avec la fonction fopen()
*/
char *csv_openType(CSV_OpenType opentype);

/*
Entrée: path (chaîne de caractères, chemin du fichier CSV); opentype (enum CSV_OpenType, manière d'ouvrir le fichier).
Retourne: un fichier s'il existe.

S'il n'existe pas, le prorgramme affiche un message d'erreur, et se ferme.

Cette fonction permet de réduire la répétition tidieuse lors des ouvertures de fichiers,
lorsque l'on vérifie si le fichier existe ou pas.
*/
FILE *csv_open(const char *path, CSV_OpenType opentype);

/* Lit une ligne spécifique d'un fichier CSV en se basant sur un identifiant unique
@param path: Chemin du fichier CSV.
@param id: Identifiant unique pour identifier la ligne spécifique.
@return: La ligne correspondant à l'identifiant ou NULL si non trouvée.*/

char *csv_readLinebyId(const char *path, const char *id);
/*
Entrée: path (chaîne de caractères, chemin du fichier CSV); line (chaîne de caractères à ajouter);
Retourne le statut de l'opération

Cette procédure permet de rajouter un enregistrement dans le fichier CSV.
*/
int csv_writeLine(char *path, const char *line);
/* Met à jour une ligne spécifique dans un fichier CSV.
@param path: Chemin du fichier CSV.
@param modifiedRow: La ligne modifiée à écrire dans le fichier.
@param value: La valeur unique utilisée pour identifier la ligne à mettre à jour.
@param columnIndex: L'indice de la colonne où rechercher la valeur.
Cette procédure permet de mettre à jour un enregistrement dans le fichier CSV.
*/
void csv_updateLine(char *path, const char *modifiedRow, const char *value, uint columnIndex);

/*
Recherche et extrait les lignes d'un fichier CSV où la seconde colonne correspond à une valeur spécifiée.
Crée un fichier temporaire contenant uniquement ces lignes. Le fichier original n'est pas modifié.
@param path Chemin du fichier CSV source.
@param value Valeur à rechercher dans la seconde colonne du fichier CSV.
@return Chemin du fichier temporaire contenant les lignes correspondantes. La libération de la mémoire allouée est à la charge de l'utilisateur.
 */
void csv_findLastname(char *path, const char *value);

/*
Cette fonction parcourt un fichier CSV et supprime la ligne où une colonne spécifique
contient l'id donnée. Elle crée un fichier temporaire pour stocker toutes les lignes sauf celle
à supprimer, puis remplace le fichier original par ce fichier temporaire si une ligne est effectivement supprimée.

@param path Chemin du fichier CSV source.
@param value Numéro de téléphone à rechercher pour identifier la ligne à supprimer.
@return Booléen indiquant si une ligne a été supprimée (true) ou non (false).
*/
bool csv_removeLineById(char *path, const char *value);

/*
Entrée: path (chaîne de caractères, chemin du fichier csv)
Retourne: rien

Cette procédure permet d'afficher dans le shell un tableau contenant toutes les informations dans le fichier CSV
*/
void csv_printTable(char *path);

/*Extrait l'identifiant (ID) d'une ligne de fichier CSV.
@param line: La ligne du fichier CSV à partir de laquelle extraire l'ID.
@return: L'ID extrait sous forme d'entier.*/
int csv_extractId(const char *line);

/*Trouve l'ID le plus élevé dans un fichier CSV et retourne l'ID suivant.
@param path: Chemin du fichier CSV.
@return: Le prochain ID disponible (le plus élevé trouvé dans le fichier + 1).
*/
int csv_getId(const char *path);

#endif // !__CSV_HEADER
