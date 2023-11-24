/*
Ce module a pour objectif de stocker les colones d'une ligne
dans des attributs dans la structure TableRow.
*/

// Ici on défini une variable avec le pré-processeur C
// afin d'éviter que les fonctions ou "objets" soient définies plusieurs fois
// s'ils existent déjà.
#ifndef __TABLE_HEADER
#define __TABLE_HEADER

// Ceci est un entier positif.
typedef unsigned int uint;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
  uint id;
  char lastName[50];  // Nom de famille de l'individu.
  char firstName[50]; // Prénom de l'individu.
  char address[50];   // Son adresse de domicile.
  // Son numéro de téléphone, stocker dans une chaîne de caractères
  // et non un entier pour éviter que les 0 du début soient ignorés.
  char phoneNumber[12];
  uint age;          // Son âge.
  uint heightInCm;   // Sa taille en centimètre
  uint weightInKg;   // Son poids en kilos.
  float bestTimeInS; // Son meilleur temps.
} TableRow;

/*
Entrée: line (chaîne de caractères, enregistrement du fichier CSV); lineNumber (entier, numéro de la ligne auquel l'enregistrement appartient)
Retourne: Un pointeur d'une structure TableRow définie avec malloc

IMPORTANT: Ne pas oublier de `free` le pointeur une fois qu'on a plus utilité de ce dernier.

Cette fonction permet de prendre un enregistrement donné en paramètre et de le transformet en TableRow.
*/
TableRow *table_parseString(const char *line);

/*
Entrée: row (pointeur vers un TableRow); newLine (booléen, ajoute un caratère de nouvel ligne à la fin)
Retourne: Un pointeur d'une chaîne de caractères définie avec malloc

IMPORTANT: Ne pas oublier de `free` le pointeur une fois qu'on a plus utilité de ce dernier.

Cette fonction permet de prendre les valeurs d'un TableRow et de les transformer
en une chaîne de caractères prête à être insérer dans un fichier CSV.
*/
char *table_parseRow(const TableRow *row, bool newLine);

/*
Entrée: phoneNumber (pointeur vers une chaîne de caractères représentant le numéro de téléphone)
Retourne: booléen (true si le numéro est valide, false sinon)

Cette fonction a pour but de vérifier la validité d'un numéro de téléphone.
Un numéro de téléphone est considéré comme valide s'il est composé exactement de 10 chiffres numériques.
La fonction parcourt chaque caractère du numéro et vérifie qu'il s'agit bien d'un chiffre.
Si un caractère n'est pas un chiffre ou si la longueur du numéro est différente de 10, la fonction retourne false.
Dans le cas contraire, elle retourne true, indiquant que le numéro est valide.
*/

bool table_checkPhoneNumber(const char *phoneNumber);

#endif // !__TABLE_HEADER
