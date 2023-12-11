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
#define ARRAY_SIZE 100

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

// Ceci est un entier positif.
typedef unsigned int uint;

typedef struct
{
  int *values;
  uint size;
} IntArray;

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
Recherche et extrait les lignes d'un fichier CSV où le now de famille correspond à valeur spécifiée.
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

/*Extrait d'une colonne spécifique d'une ligne de fichier CSV.
@param line: La ligne du fichier CSV à partir de laquelle extraire l'ID.
@return: L'ID extrait sous forme d'entier.*/
int csv_extractValue(const char *line, uint columnIndex);

/*Trouve l'ID le plus élevé dans un fichier CSV et retourne l'ID suivant.
@param path: Chemin du fichier CSV.
@return: Le prochain ID disponible (le plus élevé trouvé dans le fichier + 1).
*/
int csv_getId(const char *path);

/*Filtre les lignes d'un fichier CSV en fonction d'une valeur spécifique dans une colonne donnée.(ex: la colonne 2 pour les noms de famille)
@param path: Le chemin du fichier CSV à filtrer.
@param value: La valeur à rechercher dans la colonne spécifiée.
@param columnIndex: L'index de la colonne où la recherche doit être effectuée (commence à 0).
Le programme crée un fichier temporaire pour stocker les lignes correspondantes. Si des correspondances sont trouvées, il les affiche à partir du fichier temporaire. Si aucune correspondance n'est trouvée, un message est affiché indiquant l'absence de données correspondantes, et le fichier temporaire est supprimé.
*/
void csv_findUser(const char *path, const char *value, int columnIndex);

/* Cette fonction extrait les valeurs d'une colonne spécifique d'un fichier CSV et les stocke dans un tableau puis l'appliquer un algorithme de tri.
@param path: Le chemin du fichier CSV.
@param columnIndex: L'index de la colonne à partir de laquelle les valeurs doivent être extraites.
@return: Un tableau de type IntArray contenant les valeurs extraites de la colonne spécifiée.
La fonction ouvre le fichier CSV, lit chaque ligne, et extrait la valeur de la colonne spécifiée. Ces valeurs sont ensuite stockées dans un tableau dynamique, dont la taille est augmentée au besoin. La fonction retourne ce tableau avec les valeurs extraites.
*/
IntArray csv_extractIntArray(const char *path, uint columnIndex);

/* Permet d'afficher les contenus d'un fichier CSV trié.
@param path: Le chemin du fichier CSV à trier.
@param sortedArray: Un tableau d'entiers représentant les valeurs triées sur lesquelles le tri doit être basé.
@param sortedSize: La taille du tableau sortedArray.
@param columnIndex: L'index de la colonne du fichier CSV à utiliser pour le tri.
La fonction crée un fichier temporaire pour stocker les lignes triées. Elle parcourt ensuite le tableau sortedArray, recherche chaque valeur dans le fichier CSV et écrit la ligne correspondante dans le fichier temporaire si elle correspond à la valeur triée et n'a pas encore été écrite. Après avoir trié toutes les lignes, elle affiche le contenu du fichier temporaire et le supprime.
*/
void csv_sortedCSV(const char *path, const int *sortedArray, uint sortedSize, uint columnIndex);

/* Filtre les lignes d'un fichier CSV pour ne conserver que celles dont la valeur dans une colonne spécifique correspond à une valeur donnée et les écrit dans un fichier temporaire.
@param path: Le chemin du fichier CSV à filtrer.
@param valueToMatch: La valeur à rechercher dans la colonne spécifiée.
@param columnIndex: L'index de la colonne à partir de laquelle la comparaison doit être effectuée.
La fonction commence par créer un fichier temporaire. Elle parcourt ensuite le fichier CSV original, extrait la valeur de la colonne spécifiée pour chaque ligne et vérifie si cette valeur correspond à valueToMatch. Si c'est le cas, et que la ligne n'a pas encore été écrite, elle l'écrit dans le fichier temporaire. Une fois toutes les lignes pertinentes écrites, la fonction affiche le contenu du fichier temporaire et le supprime.
*/
void csv_sortedCSVInt(const char *path, int valueToMatch, uint columnIndex);

#endif // !__CSV_HEADER
