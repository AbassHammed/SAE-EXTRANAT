#ifndef __STATS_HEADER

#define MAX 128

typedef unsigned int uint;
/* Calcule la moyenne des valeurs d'un tableau d'entiers.
@param array: Le tableau
@param length: La taille du tableau.
@return: La moyenne des valeurs du tableau sous forme de flottant.
La fonction itère sur le tableau, somme toutes les valeurs, puis divise cette somme par la taille du tableau pour obtenir la moyenne.
*/
float iaverage(const int *array, const uint length);
float faverage(const float *array, const uint length);

/* Calcule l'écart-type des valeurs d'un tableau d'entiers.
@param array: Le tableau
@param length: La taille du tableau.
@return: L'écart-type des valeurs du tableau sous forme de flottant.
La fonction commence par calculer la moyenne des valeurs du tableau, puis itère sur chaque élément pour calculer la somme des carrés des écarts par rapport à cette moyenne. L'écart-type est la racine carrée de cette somme divisée par la taille du tableau.
*/
float istdDeviation(const int *array, const uint length);
float fstdDeviation(const float *array, const uint length);

/* Trouve la valeur maximale dans un tableau d'entiers.
@param array: Le tableau
@param length: La taille du tableau.
@return: La valeur maximale trouvée dans le tableau.
La fonction itère sur le tableau, en maintenant une trace de la valeur maximale trouvée jusqu'à présent. Elle retourne cette valeur maximale une fois toute la liste parcourue.
*/
int imax(const int *array, const uint length);
int fmaxIndex(const float *array, const uint length);

/* Trouve la valeur minimale dans un tableau d'entiers.
@param array: Le tableau
@param length: La taille du tableau.
@return: La valeur minimale trouvée dans le tableau.
Cette fonction parcourt le tableau, compare chaque élément avec la valeur minimale actuelle et met à jour cette valeur si un élément plus petit est trouvé.
*/
int imin(const int *array, const uint length);
int fminIndex(const float *array, const uint length);

/* Trie un tableau d'entiers en utilisant l'algorithme de tri à bulles.
@param array: Le tableau
@param length: La taille du tableau.
La fonction utilise le tri à bulles, en parcourant le tableau et en échangeant les éléments adjacents si nécessaire, jusqu'à ce que le tableau soit entièrement trié.
*/
void ibubblesort(int *array, const uint length);
void fbubblesort(float *array, const uint length);
void cbubbleSort(char arr[][MAX], const uint length);

/* Trie un tableau d'entiers en utilisant l'algorithme de tri rapide (QuickSort).
@param array: Le tableau
@param length: La taille du tableau.
La fonction principale `iquicksort` initialise le processus en appelant `_iquicksort`, qui effectue le tri récursivement en divisant le tableau en sous-tableaux autour d'un pivot choisi par `_ipartition`. `_ipartition` organise les éléments de manière à ce que ceux plus petits que le pivot soient à gauche, et ceux plus grands à droite.
*/
void iquicksort(int *array, const uint length);
void fquicksort(float *array, const uint length);

#endif // !__STATS_HEADER
