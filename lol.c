case UPDATE:
    {
      // Traite la commande 'update': Permet à l'utilisateur de modifier un enregistrement existant.
      char lastName[50];
      char stringId[100];
      uint count;
      uint id;

      // Demande à l'utilisateur de saisir le nom de famille pour la modification
      printf("Saisissez le nom de fammille de la personne dont vous souhaitez modifier les données :");
      scanf("%s", lastName);
      // Nettoie le buffer d'entrée
      while (getchar() != '\n')
        ;
      csv_printTable(inputFile);
      // Affiche les doublons pour aider l'utilisateur à choisir le bon enregistrement
      printf("Veuillez rentrer l'identifiant de la personne dont vous voulez modifier les données : ");
      scanf(" %d", &id);
      // Convertit l'ID en chaîne pour utilisation ultérieure
      sprintf(stringId, "%d", id);
      // Récupère la ligne correspondante à partir de l'ID
      char *line = csv_readLinebyId(inputFile, stringId);

      // Vérifie si la ligne a été trouvée
      if (line == NULL)
      {
        // Affiche un message d'erreur si aucun enregistrement correspondant n'a été trouvé
        fprintf(stderr, "Le nom de famille %s que vous avez saisi ne correspond à aucun membre.\n", lastName);
      }
      else
      {
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
        csv_updateLine(inputFile, modifiedRow, stringId, 1);
        // Affiche un message de confirmation de la modification.
        printf("La ligne avec le nom de famille %s a été modifie avec succès\n", lastName);
        // free(row);
      }
      // free(line);
    }