# Protocole de Test pour SAE-EXTRANAT

## Introduction

Ce document décrit les étapes à suivre pour utiliser le programme **_SAE-EXTRANAT_**, qui permet la gestion d'un fichier CSV contenant des informations personnelles et des performances sportives.

## Prérequis

Assurez-vous que le dossier SAE-EXTRANAT est téléchargé sur votre système.
Avoir un fichier CSV prêt à être utilisé par le programme.

## Construction du Projet

Avant de lancer le programme, vous devez construire le projet avec **make.py**.
Pour cela, suivez les instructions ci-dessous :
Ouvrez le terminal ou l'invite de commande.
Naviguez jusqu'au répertoire racine de **SAE-EXTRANAT**.
Exécutez **_python make.py_** pour construire le projet. Les fichiers exécutables seront générés dans le dossier approprié.

## Démarrage rapide

Ouvrez votre terminal ou invite de commande.
Naviguez jusqu'au dossier contenant SAE-EXTRANAT.
Exécutez le programme en tapant **_"./main.exe -i" suivi du nom de votre fichier CSV_**.

## Utilisation détaillée

#### Lecture d'un fichier CSV :

Pour lire et afficher le contenu du fichier CSV, utilisez la commande **_print_** après avoir démarré le programme.

### Ajout d'un enregistrement :

Pour ajouter une ligne, utilisez la commande **_add_** et suivez les instructions à l'écran pour entrer les données.

### Mise à jour d'un enregistrement :

Utilisez la commande **_update_**, suivez les prompts pour sélectionner un enregistrement par numéro de téléphone et modifiez les champs souhaités.

### Suppression d'un enregistrement :

Pour supprimer une ligne, tapez **_remove_** et entrez le numéro de téléphone de l'enregistrement à supprimer.

### Impression en format tableau :

La commande **_print_** affichera les données dans un format de tableau aligné, en tenant compte des caractères français.

### Traitement des erreurs

Si vous rencontrez des messages d'erreur, vérifiez que le format de vos données correspond aux attentes du programme et que le fichier CSV est accessible et correctement formaté.
