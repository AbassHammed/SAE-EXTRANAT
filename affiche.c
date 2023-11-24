void displaySwimmers(Swimmer records[], int numRecords)
/*
    Procédure displaySwimmers(Swimmer records[], int numRecords)
        Affiche les détails des nageurs stockés dans le tableau de structures 'records'.
*/
{
    printf("+----+----------------------+----------------------+------------------------------------+--------------------------+-----+---------+--------+-------------------------------+\n");
    printf("| ID |          Nom         |        Prenom        |              Adresse               |   Numero de telephone    | Age | Taille  |  Poids |  Meilleur temps sur 50 metres |\n");
    printf("+----+----------------------+----------------------+------------------------------------+--------------------------+-----+---------+--------+-------------------------------+\n");

    // Parcours de tous les enregistrements de nageurs pour les afficher
    for (int i = 0; i < numRecords; i++)
    {
        printf("| %-2d | %-20s | %-20s | %-34s | %-24s | %-3d | %-7d | %-6d | %-28.2f  |\n",
               i, records[i].lastName, records[i].firstName, records[i].address, records[i].phoneNumber, records[i].age,
               records[i].height, records[i].weight, records[i].best50mPerformance);
    }

    // Vérification s'il n'y a aucun enregistrement à afficher.
    if (numRecords <= 0)
    {
        printf("Aucun enregistrement trouve.\n");
    }
    else
    {
        printf("+----+----------------------+----------------------+------------------------------------+--------------------------+-----+---------+--------+-------------------------------+\n");
    }
}