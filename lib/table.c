// Inclut le fichier d'en-tête 'table.h' pour la structure TableRow et les fonctions associées, et la bibliothèque standard pour la gestion de la mémoire.
#include "table.h"
#include <stdlib.h>

/*
Entrée: row (pointeur vers un TableRow); value (chaîne de caractères); column (entier)
Retourne: rien

Cette procédure privée a pour objectif d'assigner à chaque attribut du TableRow
la valeur correspondante trouvée dans le fichier CSV, en respectant les types.
*/
void set(TableRow *row, const char *value, const uint column)
{
  switch (column)
  {
  case 0:
    row->id = (uint)atoi(value);
    break;
  case 1:
    strncpy(row->lastName, value, sizeof(row->lastName)); // Copie la chaîne de caractères dans le champ 'lastName'.
    break;
  case 2:
    strncpy(row->firstName, value, sizeof(row->firstName));
    break;
  case 3:
    strncpy(row->address, value, sizeof(row->address));
    break;
  case 4:
    strncpy(row->phoneNumber, value, sizeof(row->phoneNumber));
    break;
  case 5:
    row->age = (uint)atoi(value); // Convertit la chaîne de caractères en entier pour 'age'.
    break;
  case 6:
    row->heightInCm = (uint)atoi(value);
    break;
  case 7:
    row->weightInKg = (uint)atoi(value);
    break;
  case 8:
    row->bestTimeInS = atof(value); // Convertit la chaîne de caractères en réel pour 'bestTimeInS'.
    break;
  }
}

/* Pour let détails sur l'objectif de la fonction, cf. table.h */
// Fonction pour analyser une chaîne représentant une ligne d'un tableau et la convertir en structure TableRow
TableRow *table_parseString(const char *line)
{
  // Allocation dynamique de mémoire pour une nouvelle structure TableRow
  TableRow *parsed = malloc(sizeof(TableRow));
  if (parsed == NULL)
  {
    printf("Problème de gestion de la mémoire.\n");
    return NULL;
  }

  // Initialisation des variables pour suivre les indices dans la ligne et la valeur en cours de traitement
  uint lineIndex = 0, valueIndex = 0, column = 0;
  char value[50] = ""; // Tableau pour stocker temporairement chaque valeur

  // Boucle pour parcourir chaque caractère de la ligne
  while (line[lineIndex] != '\0' && line[lineIndex] != '\n')
  {
    // Si on trouve une virgule, cela signifie la fin d'une valeur
    if (line[lineIndex] == ',')
    {
      value[valueIndex] = '\0';   // Fin de la chaîne de caractères
      set(parsed, value, column); // Enregistrement de la valeur dans la structure TableRow

      // Réinitialisation de valueIndex pour la prochaine valeur et avance au prochain colonne
      valueIndex = 0;
      column++;
    }
    else if (valueIndex < sizeof(value) - 1) // Ajoute le caractère actuel à la valeur en cours si dans les limites du tableau
    {
      value[valueIndex++] = line[lineIndex];
    }

    lineIndex++; // Avance au prochain caractère de la ligne
  }
  // Traitement de la dernière valeur de la ligne si elle existe
  if (valueIndex > 0)
  {
    value[valueIndex] = '\0';
    set(parsed, value, column); // Enregistrement de la dernière valeur dans la structure TableRow
  }

  return parsed; // Retourne la structure TableRow remplie
}

/* Pour let détails sur l'objectif de la fonction, cf. table.h */
char *table_parseRow(const TableRow *row, bool newLine)
{
  // On crée une chaîne de caractères dans le heap avec malloc.
  char *parsed = malloc(256);
  if (parsed == NULL)
  {
    printf("problème gestion de la mémoire.\n");
    return NULL;
  }

  char n = newLine ? '\n' : '\0';
  // Utilisation de sprintf pour formatter la nouvelle chaîne de caractères
  // %2.f pour limiter le réel à deux décimales.
  sprintf(parsed, "%d,%s,%s,%s,%s,%d,%d,%d,%.2f%c",
          row->id,
          row->lastName,
          row->firstName,
          row->address,
          row->phoneNumber,
          row->age,
          row->heightInCm,
          row->weightInKg,
          row->bestTimeInS,
          n);

  return parsed;
}
// Définit la fonction 'table_checkPhoneNumber' pour vérifier la longueur du numéro de téléphone. Retourne false si la longueur n'est pas de 10 caractères.
/* Pour let détails sur l'objectif de la fonction, cf. table.h */
bool table_checkPhoneNumber(const char *phoneNumber)
{
  if (strlen(phoneNumber) != 10)
    return false;
  unsigned int i = 0;
  // Vérifie si chaque caractère du numéro de téléphone est un chiffre. Retourne false si un caractère non numérique est trouvé ou si la longueur n'est pas exactement de 10.
  while (('0' >= phoneNumber[i++] <= '9') && i < 10)
    ;
  if (i != 10)
    return false;
  return true;
}
