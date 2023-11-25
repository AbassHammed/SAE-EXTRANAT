#include "csv.h"
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <locale.h>

bool csv_fileExists(char *path)
{                                            /* Pour les détails sur l'objectif de la fonction, cf. csv.h */
  FILE *file = fopen(path, "r");             // Ouvre le fichier en lecture
  bool exists = file != NULL ? true : false; // Si le fichier est nul retourne vrai sinon faux.
  fclose(file);                              // Ferme le fichier.
  return exists;
}

char *csv_openType(CSV_OpenType opentype)
{ /* Pour les détails sur l'objectif de la fonction, cf. csv.h */
  // Retourne le mode d'ouverture de fichier approprié en fonction de l'énumération CSV_OpenType.
  switch (opentype)
  {
  case READ:
    return "r"; // On retourne r si READ, etc.
  case WRITE:
    return "w";
  case WRITE_READ:
    return "w+";
  default:
    return "";
  }
}

FILE *csv_open(const char *path, CSV_OpenType opentype)
{ /* Pour les détails sur l'objectif de la fonction, cf. csv.h */
  FILE *file = fopen(path, csv_openType(opentype));
  // Si nul, affiche un message d'erreur et quitte le programme.
  if (file == NULL)
  {
    fprintf(stderr, "Le fichier %s ne peut être ouvert.", path);
    exit(1);
  }

  // Sinon, on retourne le fichier.
  return file;
}

char *csv_readLinebyId(const char *path, const char *id)
{
  // Ouvre le fichier CSV en mode lecture
  FILE *file = csv_open(path, READ);
  char buffer[MAX_BUFFER];
  char lineCopy[MAX_BUFFER];
  char *line = NULL;

  // Parcourt chaque ligne du fichier CSV
  while (fgets(buffer, MAX_BUFFER, file) != NULL)
  {
    strcpy(lineCopy, buffer);
    // Utilise strtok pour diviser la ligne en tokens (valeurs) basées sur les virgules
    char *token = strtok(buffer, ",");
    // Parcourt les tokens (colonnes) de la ligne actuelle
    while (token != NULL)
    {
      if (strcmp(token, id) == 0)
      { // Compare le token actuel avec l'ID fourni
        // Si l'ID correspond, alloue de la mémoire pour la ligne et la copie
        line = malloc(strlen(lineCopy) + 1);
        if (line != NULL)
        {
          strcpy(line, lineCopy);
        }
        break; // Sortie anticipée de la boucle si l'ID correspond
      }
      // Passe au token suivant (prochaine colonne)
      token = strtok(NULL, ",");
    }
    if (line != NULL)
    {
      break; // Si une ligne correspondante a été trouvée, sort de la boucle principale
    }
  }
  // Ferme le fichier après la lecture
  fclose(file);
  return line; // Retourne la ligne trouvée ou NULL si aucune correspondance
}

int csv_writeLine(char *path, const char *line)
{
  // Crée des copies du chemin pour éviter la modification de l'original
  char *path1 = strdup(path);       // Duplique le chemin d'accès pour éviter de modifier l'original
  char *path2 = strdup(path);       // Duplique à nouveau le chemin d'accès pour une utilisation séparée
  char *filename = basename(path1); // Extrait le nom du fichier du chemin d'accès
  char *dir = dirname(path2);       // Extrait le répertoire (dossier) du chemin d'accès

  // Prépare le chemin du fichier temporaire
  char tmpFilePath[256];
  int success = 1; // Variable pour suivre le succès de l'opération

  // Formatte le chemin du fichier temporaire
  sprintf(tmpFilePath, "%s/temp____%s", dir, filename);

  // Ouvre les fichiers temporaire et original
  FILE *wFile = csv_open(tmpFilePath, WRITE); // Crée et ouvre le fichier temporaire en mode écriture
  FILE *rFile = csv_open(path, READ);         // Ouvre le fichier CSV original en mode lecture

  char buffer[MAX_BUFFER]; // Buffer pour stocker les lignes lues du fichier

  // Copie le contenu du fichier original dans le fichier temporaire
  while (fgets(buffer, MAX_BUFFER, rFile)) // Lit chaque ligne du fichier original
  {
    if (fputs(buffer, wFile) == EOF) // Écrit la ligne dans le fichier temporaire
    {
      success = 0; // En cas d'erreur, met à jour la variable de succès
      break;       // Interrompt la boucle en cas d'erreur
    }
  }

  // Ajoute la nouvelle ligne à la fin du fichier temporaire
  if (fputs(line, wFile) == EOF) // Écrit la nouvelle ligne
  {
    success = 0; // Met à jour la variable de succès en cas d'erreur
  }

  // Ferme les fichiers
  fclose(rFile); // Ferme le fichier original
  fclose(wFile); // Ferme le fichier temporaire

  // Remplace le fichier original par le fichier temporaire si tout s'est bien passé
  if (success)
  {
    remove(path);              // Supprime le fichier original
    rename(tmpFilePath, path); // Renomme le fichier temporaire en fichier original
  }
  else // Si une erreur s'est produite
  {
    remove(tmpFilePath); // Supprime le fichier temporaire
  }

  // Libère la mémoire allouée pour les chemins dupliqués
  free(path1);
  free(path2);

  return success; // Retourne le statut de l'opération
}

// Fonction pour mettre à jour une ligne spécifique dans un fichier CSV
void csv_updateLine(char *path, const char *modifiedRow, const char *value, uint columnIndex)
{
  // Duplique le chemin pour éviter de modifier le chemin original
  char *path1 = strdup(path);
  char *path2 = strdup(path);

  // Vérifie si la duplication a réussi pour les deux chemins
  if (!path1 || !path2)
  {
    perror("Erreur de duplication du chemin");
    return;
  }

  // Récupère le nom du fichier et le chemin du répertoire à partir du chemin dupliqué
  char *filename = basename(path1);
  char *dir = dirname(path2);

  // Construit le chemin du fichier temporaire
  char tmpFilePath[MAX_BUFFER];
  sprintf(tmpFilePath, "%s/temp____%s", dir, filename);

  // Ouvre le fichier temporaire en écriture et le fichier original en lecture
  FILE *wFile = csv_open(tmpFilePath, WRITE);
  FILE *rFile = csv_open(path, READ);

  // Déclare les buffers pour stocker les lignes lues et copiées
  char line[MAX_BUFFER], currentValue[MAX_BUFFER];
  bool lineUpdated = false;

  // Lit le fichier ligne par ligne

  while (fgets(line, sizeof(line), rFile))
  {
    uint currentColumnIndex = 1;
    int lineIndex = 0, valueIndex = 0;

    // Parcourt la ligne caractère par caractère
    while (line[lineIndex] != '\0' && line[lineIndex] != '\n')
    {
      // Si on trouve une virgule, on termine le token actuel
      if (line[lineIndex] == ',')
      {
        currentValue[valueIndex] = '\0';
        // Compare le token avec la valeur donnée
        if (currentColumnIndex == columnIndex && strcmp(currentValue, value) == 0)
        {
          // Si correspondance, écrit la ligne modifiée dans le fichier temporaire
          fputs(modifiedRow, wFile);
          lineUpdated = true;
          break;
        }
        // Réinitialise l'index pour le prochain token
        valueIndex = 0;
        currentColumnIndex++;
      }
      else if (valueIndex < sizeof(currentValue) - 1)
      {
        // Continue de construire le token actuel
        currentValue[valueIndex++] = line[lineIndex];
      }
      lineIndex++;
    }

    // Vérifie si le dernier token de la ligne correspond
    if (valueIndex > 0 && !lineUpdated)
    {
      currentValue[valueIndex] = '\0';
      if (currentColumnIndex == columnIndex && strcmp(currentValue, value) == 0)
      {
        fputs(modifiedRow, wFile);
        lineUpdated = true;
      }
    }

    // Si la ligne n'a pas été mise à jour, écrit la ligne originale
    if (!lineUpdated)
    {
      fputs(line, wFile);
    }
    // Réinitialise le flag pour la prochaine ligne
    lineUpdated = false;
  }

  // Ferme les fichiers ouverts
  fclose(rFile);
  fclose(wFile);

  // Supprime le fichier original et renomme le fichier temporaire
  remove(path);
  rename(tmpFilePath, path);

  // Libère la mémoire allouée pour les chemins dupliqués
  free(path1);
  free(path2);
}

void csv_findLastname(char *path, const char *value)
{
  // Duplique le chemin pour utiliser avec basename et dirname sans modifier l'original
  char *path1 = strdup(path);
  char *path2 = strdup(path);
  // Extrait le nom du fichier et le répertoire du chemin
  char *filename = basename(path1);
  char *dir = dirname(path2);

  // Alloue de la mémoire pour le chemin du fichier temporaire et construit ce chemin
  char *tmpFilePath = malloc(256 * sizeof(char));
  sprintf(tmpFilePath, "%s/temp____duplicates__%s", dir, filename);

  // Ouvre le fichier original en lecture et le fichier temporaire en écriture
  FILE *wFile = csv_open(tmpFilePath, WRITE);
  FILE *rFile = csv_open(path, READ);

  // Buffers pour stocker les lignes lues
  char buffer[MAX_BUFFER];
  char bufferCopy[MAX_BUFFER];

  // Parcourt chaque ligne du fichier
  while (fgets(buffer, sizeof(buffer), rFile))
  {
    // Copie la ligne pour la manipulation
    strcpy(bufferCopy, buffer);
    // Récupère le premier token (colonne)
    char *token = strtok(bufferCopy, ",");
    if (token != NULL)
    {
      // Passe à la seconde colonne
      token = strtok(NULL, ",");
      // Vérifie si la seconde colonne correspond à la valeur recherchée
      if (token != NULL && strcmp(token, value) == 0)
      {
        fputs(buffer, wFile);
      }
    }
  }

  // Ferme les fichiers ouverts
  fclose(rFile);
  fclose(wFile);

  // Libère la mémoire allouée pour les chemins
  free(path1);
  free(path2);

  // Retourne le chemin du fichier temporaire
  csv_printTable(tmpFilePath);
  remove(tmpFilePath);
  free(tmpFilePath);
}

// Fonction pour supprimer une ligne spécifique d'un fichier CSV basée sur un ID
bool csv_removeLineById(char *path, const char *value)
{
  // Duplication des chemins pour éviter la modification de l'original
  char *path1 = strdup(path);
  char *path2 = strdup(path);

  // Extraction du nom du fichier et du chemin du répertoire
  char *filename = basename(path1);
  char *dir = dirname(path2);

  char tmpFilePath[256];
  // Construction du chemin du fichier temporaire
  sprintf(tmpFilePath, "%s/temp____%s", dir, filename);

  // Ouverture des fichiers original et temporaire
  FILE *wFile = csv_open(tmpFilePath, WRITE);
  FILE *rFile = csv_open(path, READ);

  char buffer[MAX_BUFFER];
  char lineCopy[MAX_BUFFER];
  bool lineRemoved = false; // Indicateur de suppression de ligne

  // Parcours du fichier pour rechercher l'ID spécifié
  while (fgets(buffer, sizeof(buffer), rFile))
  {
    strcpy(lineCopy, buffer);
    // Séparation des colonnes de la ligne
    char *token = strtok(buffer, ",");
    // Vérification de la correspondance avec l'ID
    if (token != NULL && strcmp(token, value) == 0)
    {
      // Si l'ID correspond, marque la ligne pour suppression
      lineRemoved = true;
      continue;
    }
    // Copie de la ligne dans le fichier temporaire si l'ID ne correspond pas
    fputs(lineCopy, wFile);
  }

  fclose(rFile);
  fclose(wFile);

  // Remplacement du fichier original si une ligne a été supprimée
  if (lineRemoved)
  {
    remove(path);
    rename(tmpFilePath, path);
  }
  else // Suppression du fichier temporaire si aucune ligne n'a été supprimée
  {
    remove(tmpFilePath);
  }

  // Libérée la mémoire allouée pour les chemins
  free(path1);
  free(path2);

  return lineRemoved; // Retourne vrai si une ligne a été supprimée
}

void csv_printTable(char *path)
{
  // Ouvre le fichier CSV pour lecture
  FILE *read = csv_open(path, READ);

  char buffer[MAX_BUFFER];
  uint id;
  char lastName[50], firstName[50], address[150], phoneNumber[20];
  int age, heightInCm, weightInKg;
  float bestTimeInS;

  // Imprime les en-têtes du tableau
  printf("+-----+--------------------+--------------------+------------------------------------------+--------------+-----+----------------+----------------+-----------------------+\n");
  printf("| ID  | Nom de Famille     | Prénom             | Adresse                                  | Téléphone    | Âge | Taille (en cm) | Poids (en kg)  | Meilleur Temps (en s) |\n");
  printf("+-----+--------------------+--------------------+------------------------------------------+--------------+-----+----------------+----------------+-----------------------+\n");

  while (fgets(buffer, sizeof(buffer), read))
  {
    // Lis et affiche chaque ligne du fichier CSV
    if (sscanf(buffer, "%d,%49[^,],%49[^,],%149[^,],%19[^,],%d,%d,%d,%f",
               &id, lastName, firstName, address, phoneNumber, &age, &heightInCm, &weightInKg, &bestTimeInS) == 9)
    {
      printf("| %-3d | %-18s | %-18s | %-40s | %-12s | %3d | %14d | %14d | %21.2f |\n",
             id, lastName, firstName, address, phoneNumber, age, heightInCm, weightInKg, bestTimeInS);
    }
  }

  printf("+-----+--------------------+--------------------+------------------------------------------+--------------+-----+----------------+----------------+-----------------------+\n");

  // Ferme le fichier après impression
  fclose(read);
}

// Fonction pour extraire une valeur numérique d'une colonne spécifiée dans une ligne CSV
int csv_extractValue(const char *line, uint columnIndex)
{
  // Buffer pour stocker une copie de la ligne
  char buffer[MAX_BUFFER];
  // Copie la ligne dans le buffer en s'assurant de ne pas dépasser la taille maximale
  strncpy(buffer, line, MAX_BUFFER - 1);
  // Assure que le buffer est terminé par un caractère nul
  buffer[MAX_BUFFER - 1] = '\0';

  // Utilise strtok pour diviser la ligne en tokens basées sur les virgules
  char *token = strtok(buffer, ",");
  // Index pour suivre la colonne courante
  uint currentColumnIndex = 1;

  // Parcourt les tokens un par un
  while (token != NULL)
  {
    // Vérifie si l'index de la colonne courante correspond à l'index demandé
    if (currentColumnIndex == columnIndex)
    {
      // Variable pour stocker la valeur numérique convertie
      long value;
      char *stringId;
      // Convertit le token en valeur longue
      value = strtol(token, &stringId, 10);
      if (*stringId != '\0')
      {
        return -1;
      }
      return (int)value;
    }
    // Passe au token suivant (prochaine colonne)
    token = strtok(NULL, ",");
    currentColumnIndex++;
  }

  return -1;
}

int csv_getId(const char *path)
{
  // Ouvre le fichier CSV en mode lecture
  FILE *file = csv_open(path, READ);

  char line[MAX_LINE]; // Déclare un buffer pour stocker les lignes lues du fichier
  int lastId = 0, id;

  // Lire le fichier ligne par ligne pour trouver le dernier ID
  while (fgets(line, sizeof(line), file))
  {
    id = csv_extractValue(line, 1);
    if (id > lastId) // Met à jour lastId si l'ID courant est supérieur
    {
      lastId = id;
    }
  }

  fclose(file);
  return lastId + 1; // Retourne le prochain ID
}

void csv_filter(const char *path, const char *value, int columnIndex)
{
  // Duplique le chemin pour éviter de modifier le chemin original
  char *path1 = strdup(path);
  char *path2 = strdup(path);

  // Extrait le nom de fichier et le répertoire du chemin
  char *filename = basename(path1);
  char *dir = dirname(path2);

  // Construit le chemin du fichier temporaire
  char tmpFilePath[256];
  sprintf(tmpFilePath, "%s/temp____%s", dir, filename);

  // Ouvre le fichier temporaire en écriture et le fichier original en lecture
  FILE *wFile = csv_open(tmpFilePath, WRITE);
  FILE *rFile = csv_open(path, READ);

  columnIndex++;
  // Délimiteur pour séparer les valeurs dans une ligne CSV
  const char *delim = ",";
  char buffer[MAX_BUFFER];
  char lineCopy[MAX_BUFFER];

  // Lit chaque ligne du fichier CSV
  while (fgets(buffer, MAX_BUFFER, rFile))
  {
    // Copie la ligne pour la préserver
    strcpy(lineCopy, buffer);
    // Divise la ligne en valeurs
    char *token = strtok(buffer, delim);
    int currentColumn = 1;

    // Parcourt les colonnes
    while (token != NULL)
    {
      // Vérifie si la colonne actuelle est celle recherchée
      if (currentColumn == columnIndex)
      {
        // Compare la valeur du token avec la valeur recherchée
        if (strcmp(token, value) == 0)
        {
          // Si correspondance, écrit la ligne dans le fichier temporaires
          fputs(lineCopy, wFile);
          fflush(wFile);
          break;
        }
      }
      // Passe au token suivant
      token = strtok(NULL, delim);
      currentColumn++;
    }
  }
  // Se positionne à la fin du fichier pour obtenir la taille
  fseek(wFile, 0, SEEK_END);
  long filesize = ftell(wFile);
  // Remet le pointeur au début du fichier
  fseek(wFile, 0, SEEK_SET);

  // Ferme les fichiers
  fclose(rFile);
  fclose(wFile);

  // Libère la mémoire allouée pour les chemins
  free(path1);
  free(path2);

  // Vérifie si le fichier temporaire est vide
  if (filesize == 0)
  {
    // Affiche un message si aucune correspondance n'est trouvée
    printf("Aucune donnée dans la colonne selectionnée correspond à la valeur que vous recherchez.\n");
    remove(tmpFilePath);
  }
  else
  {
    // Sinon, affiche les données du fichier temporaire
    csv_printTable(tmpFilePath);
    remove(tmpFilePath);
  }
}