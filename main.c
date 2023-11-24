// Inclut les bibliothèques nécessaires pour la manipulation des CSV, des tables, les fonctions d'entrée-sortie standard
#include "lib/csv.h"
#include "lib/table.h"
#include <stdio.h>
#include <locale.h>
#include <conio.h>

/*
Cet énumérateur permet de lister toutes les commandes qui sont possibles
en utilisant le programme.

Le dernier élément permet de connaître combien d'éléments il y a en tout,
puisque chaque élément est assigné une valeur entière qui s'incrémente à
partir de zéro.
*/
enum Command
{
  HELP = 0,   // Commande pour afficher l'aide.
  PRINT,      // Commande pour imprimer les données.
  ADD,        // Commande pour ajouter une entrée.
  UPDATE,     // Commande pour mettre à jour une entrée.
  REMOVE,     // Commande pour supprimer une entrée.
  QUIT,       // Commande pour quitter le programme.
  UNKNOWN,    // Commande inconnue, utilisée pour la gestion d'erreurs.
  CLEAR,      // commande pour effacer l'écran de la console
  NUM_COMMAND // Nombre total de commandes.
};

/*
Entrée: input (chaîne de caractères)
Retourne: un énumérateur Command (entier).

Cette fonction a pour but de prendre une chaîne de caractères quelconque
et de retourner une Command si la chaîne de caractère correspond à une
commande existante.
*/
enum Command getCommand(char *input)
{
  if (strcmp(input, "help") == 0)
    return HELP;
  else if (strcmp(input, "print") == 0)
    return PRINT;
  else if (strcmp(input, "add") == 0)
    return ADD;
  else if (strcmp(input, "update") == 0)
    return UPDATE;
  else if (strcmp(input, "remove") == 0)
    return REMOVE;
  else if (strcmp(input, "quit") == 0)
    return QUIT;
  else if (strcmp(input, "clear") == 0)
    return CLEAR;
  return UNKNOWN;
}

/*
Entrée: argc (entier); argv (liste de chaînes de caractères)
Retourne: un code erreur ou succès (entier)

Algorithme principal qui sert d'interface avec l'utilisateur.

Utilisation: <fichier d'execution> -i <fichier de données CSV>
*/
int main(int argc, char *argv[])
{
  // Définit le point d'entrée principal du programme. Configure le locale pour utiliser le français.
  setlocale(LC_ALL, "fr_FR.UTF-8");
  setlocale(LC_NUMERIC, "C");
  // Analyse les arguments donnés au lancer de l'application
  // et vérifie si l'argument suivant l'argument "-i" existe
  // et le stocke dans la varible inputFile ci dessous.
  char inputFile[256];
  for (int i = 0; i < argc; i++)
  {
    if (strcmp(argv[i], "-i") == 0)
    {
      if (argc > 2)
        strcpy(inputFile, argv[++i]);
      else
      {
        fprintf(stderr, "Aucun chemin n'est fourni");
        exit(1);
      }
    }
  }

  // Si le fichier CSV en argument n'exite pas on quitte le programme
  // et on renvoie le code erreur 1;
  if (!csv_fileExists(inputFile))
  {
    fprintf(stderr, "Impossible d'ouvrir le fichier %s", inputFile);
    return 1;
  }

  bool run = true;

  // Boucle qui se termine quand la variable run devient fausse.
  // Cela a pour but de se comporter comme un genre de shell où
  // l'utilisateur peut rentrer des commandes prédéfinies
  //
  // help: affiche à l'utilisateur toutes les commandes qui lui sont disponibles.
  // print: Permet d'afficher de manière formatée le fichier CSV sous la forme d'un tableau.
  // add: Permet à l'utilisateur d'ajouter un enregistrement dans le fichier CSV.
  // update: Permet à l'utilisteur de mofifier un enregistrement.
  // remove: Permet à l'utilisateur d'enlever un enregistrement.
  // quit: Permet à l'utilisateur de quitter l'application.
  //
  // Quand une commande est inconnue, cela écrit un message d'erreur.
  printf("Bonjour.\nVeuillez entrer la commande qui correspond à l'opération que vous souhaitez effectuer\n");
  printf("\tprint: Affiche l'ensemble des fiches dans le fichier.\n\tquit: Quitte l'application.\n\tadd: Ajoute un nouveau membre.\n\tremove: Suppression d'une fiche membre.\n\tupdate: Modification d'une fiche membre.\n");
  while (run)
  {
    char command[10]; // Enregistre la commande dans une chaîne de caractères.
    printf("> ");     // Indique à l'utilisateur qu'il peut écrire.
    scanf("%s", command);
    // Supprime tout de l'entrée standard pour éviter d'avoir des caractères
    // indésirables à la suite des prochaines entrées.
    // Selon la commande entrée on éxécute des blocks de programmes différents.
    switch (getCommand(command))
    {
      // Traite la commande 'help': Affiche les informations d'aide.
    case HELP:
      printf("[AIDE]:\n\tprint: Affiche l'ensemble des fiches dans le fichier.\n\tquit: Quitte l'application.\n\tadd: Ajout d'un nouveau membre.\n\tremove: Suppression d'une fiche membre.\n\tupdate: Modification d'une fiche membre.\n");
      break;
    case PRINT:
      // Traite la commande 'print': Affiche le contenu du fichier CSV sous forme de tableau.
      csv_printTable(inputFile);
      break;
    case ADD:
    {
      // Traite la commande 'add': Permet à l'utilisateur d'ajouter un nouvel enregistrement
      // Demande à l'utilisateur d'entrer le [nom de famille, prénom, etc.].
      // Vérifie la validité du numéro de téléphone. Affiche une erreur si le format n'est pas correct.
      TableRow row;

      printf("Entrez un nom de famille : ");
      fgets(row.lastName, sizeof(row.lastName), stdin);
      row.lastName[strcspn(row.lastName, "\n")] = 0;
      printf("Entrez un prénom: ");
      fgets(row.firstName, sizeof(row.firstName), stdin);
      row.firstName[strcspn(row.firstName, "\n")] = 0;
      // Lit l'adresse de l'utilisateur et supprime le retour à la ligne final"\n".
      printf("Entrez une adresse: ");
      fgets(row.address, sizeof(row.address), stdin);
      row.address[strcspn(row.address, "\n")] = 0;
      printf("Entrez un numéro de téléphone: ");
      scanf("%10s", row.phoneNumber);
      while (getchar() != '\n')
        ;
      if (!table_checkPhoneNumber(row.phoneNumber))
      {
        fprintf(stderr, "Le numéro %s est incorrete.\nUn muméro de téléphone doit contenir 10 chiffre.\n", row.phoneNumber);
        continue;
      }
      printf("Entrez un âge: ");
      scanf("%d", &row.age);
      while (getchar() != '\n')
        ;
      printf("Entrez une taille en cm: ");
      scanf("%d", &row.heightInCm);
      while (getchar() != '\n')
        ;
      printf("Entrez un poids en kg: ");
      scanf("%d", &row.weightInKg);
      while (getchar() != '\n')
        ;
      printf("Entrez son meilleur temps en s: ");
      scanf("%f", &row.bestTimeInS);
      while (getchar() != '\n')
        ;
      // Analyse et sauvegarde la ligne saisie dans le fichier CSV.
      row.id = csv_getId(inputFile);

      char *line = table_parseRow(&row, true);
      bool success = csv_writeLine(inputFile, line);
      // Gère les erreurs de formatage et d'enregistrement des informations.
      if (success == 0)
      {
        fprintf(stderr, "Un problème est survenue lors du formatage de vos informations sur le fichier.\nVeuillez ressayer s'il vous plaît.\n");
        continue;
      }
      else
      {
        // Affiche un message de confirmation de l'enregistrement des informations.
        fprintf(stdout, "Vos informations sont bien prises en compte %s.\n", row.firstName);
      }

      free(line);
    }
    break;
    case UPDATE:
    {
      char lastName[50]; // déclare une variable pour stocker le nom de famille saisi par l'utilisateur
      uint id;
      // Invite l'utilisateur a saisir le nom de famille de la personne à modifier
      printf("Saisissez le nom de fammille de la personne dont vous souhaitez modifier les données :");
      scanf("%s", lastName);
      // Nettoie le buffer d'entrée
      while (getchar() != '\n')
        ;
      csv_findLastname(inputFile, lastName);
      printf("Veuillez rentrer l'identifiant de la personne dont vous voulez supprimer : ");
      scanf(" %d", &id);
      char stringId[5];
      sprintf(stringId, "%d", id);
      char *line = csv_readLinebyId(inputFile, stringId);
      printf("%s\n", line);
      TableRow *row = table_parseString(line);
      // Propose des options à l'utilisateur pour choisir l'information à modifier.
      printf("Quel information souhaiteriez-vous modifier ?\n");
      printf("1: nom, 2: prenom, 3: adresse, 4: numero de tel, 5: age, 6: taille, 7: poids, 8: meilleur temps\n");
      printf("Entrez le numero correspondant a l'information a modifier: ");
      int choice;
      scanf("%d", &choice);
      while (getchar() != '\n')
        ;
      switch (choice)
      {
      case 1:
        // Modifie le nom de famille de l'enregistrement.
        printf("Entrez le nouveau nom de famille: ");
        fgets(row->lastName, sizeof(row->lastName), stdin);
        row->lastName[strcspn(row->lastName, "\n")] = 0;
        break;
      case 2:
        // Modifie le prénom de l'enregistrement.
        printf("Entrez le nouveau prenom: ");
        fgets(row->firstName, sizeof(row->firstName), stdin);
        row->firstName[strcspn(row->firstName, "\n")] = 0;
        break;
      case 3:
        // Modifie l'adresse de l'enregistrement.
        printf("Entrez le nouveau adresse: ");
        fgets(row->address, sizeof(row->address), stdin);
        row->address[strcspn(row->address, "\n")] = 0;
        break;
      case 4:
        // Modifie le numéro de téléphone de l'enregistrement.
        printf("Entrez le nouveau numéro de tel(ex : 0654378231) ");
        fgets(row->phoneNumber, sizeof(row->phoneNumber), stdin);
        row->phoneNumber[strcspn(row->phoneNumber, "\n")] = 0;
        break;
      case 5:
        // Modifie l'âge de l'enregistrement.
        printf("Entrez le nouveau age: ");
        scanf("%d", &(row->age));
        while (getchar() != '\n')
          ;
        break;
      case 6:
        // Modifie la taille en cm de l'enregistrement.
        printf("Entrez la nouvelle taille(en cm): ");
        scanf("%d", &(row->heightInCm));
        while (getchar() != '\n')
          ;
        break;
      case 7:
        // Modifie le poids en Kg de l'enregistrement.
        printf("Entrez le nouveau poids(en Kg): ");
        scanf("%d", &(row->weightInKg));
        while (getchar() != '\n')
          ;
        break;

      case 8:
        // Modifie le meilleur temps en ms de l'enregistrement.
        printf("Entrez le nouveau meilleur temps (en secondes): ");
        scanf("%f", &(row->bestTimeInS));
        while (getchar() != '\n')
          ;
        break;
      default:
        // Gère les entrées non valides pour la sélection de l'information à modifier.
        printf("Le numero que vous avez saisi ne correspond a aucune information a modifier.\n");
        break;
      }
      // Sauvegarde les modifications apportées à l'enregistrement.
      char *modifiedRow = table_parseRow(row, true);
      printf("%s", modifiedRow);
      csv_updateLine(inputFile, modifiedRow, stringId, 1);
      // printf("%s", modifiedRow);
      //  Affiche un message de confirmation de la modification.
      printf("La ligne avec le nom de famille %s a été modifie avec succès\n", lastName);
      free(row);
      free(line);
    }
    break;
    // Cas pour la commande REMOVE : Supprimer un enregistrement spécifique.
    case REMOVE:
    {
      // Déclare une variable pour stocker le nom de famille entré par l'utilisateur
      char lastName[50];
      uint id;
      // Invite l'utilisateur à saisir le nom de famille de la personne à supprimer
      printf("Saisissez le nom de fammille de la personne dont vous souhaitez supprimer les données :");
      scanf("%s", lastName);
      // Nettoie le buffer d'entrée
      while (getchar() != '\n')
        ;
      bool hasBeenRemoved = false; // variable pour stocker l'état de la fonction csv_removeLine
      csv_findLastname(inputFile, lastName);
      printf("Veuillez rentrer l'identifiant de la personne dont vous voulez supprimer : ");
      scanf(" %d", &id);
      char stringId[100];
      // Convertit l'ID en chaîne de caractères pour la suppression
      sprintf(stringId, "%d", id);
      hasBeenRemoved = csv_removeLineById(inputFile, stringId);
      // Affiche un message pour informer l'utilisateur du résultat de la suppression
      if (hasBeenRemoved)
      {
        printf("La ligne avec le nom de famille %s a été supprimée.\n", lastName);
      }
      else
      {
        printf("Aucune ligne avec le nom de famille %s n'a été trouvée.\n", lastName);
      }
    }
    break;
    // Traite la commande 'quit': Termine l'exécution du programme et affiche un message d'adieu.
    case QUIT:
      printf("Au revoir...\n");
      run = false;
      break;
    // Gère le cas d'une commande inconnue en informant l'utilisateur.
    case CLEAR:
      system("cls");
      break;
    case UNKNOWN:
    default:
      printf("Commande inconnue.\n");
    }
  }
  // Retourne 0 pour indiquer une fin d'exécution réussie du programme.
  return 0;
}
