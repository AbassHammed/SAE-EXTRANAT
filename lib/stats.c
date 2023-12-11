// Veuillez vous référer au fichier stats.h pour les détails des commentaires.
#include "stats.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>

float iaverage(const int *array, const uint length)
{
  float res = 0;
  for (int i = 0; i < length; i++)
  {
    res += array[i];
  }
  return res / length;
}

float faverage(const float *array, const uint length)
{
  float res = 0;
  for (int i = 0; i < length; i++)
  {
    res += array[i];
  }
  return res / length;
}

float istdDeviation(const int *array, const uint length)
{
  float res = 0;
  float avg = iaverage(array, length);
  for (int i = 0; i < length; i++)
    res += pow(array[i] - avg, 2);

  return sqrt(res / length);
}

float fstdDeviation(const float *array, const uint length)
{
  float res = 0;
  float avg = faverage(array, length);
  for (int i = 0; i < length; i++)
    res += pow(array[i] - avg, 2);

  return sqrt(res / length);
}

int imax(const int *array, const uint length)
{
  int max = array[0];
  int maxIndex = 0;
  for (int i = 1; i < length; i++)
  {
    if (max < array[i])
    {
      maxIndex = i;
      max = array[i];
    }
  }
  return max;
}

int fmaxIndex(const float *array, const uint length)
{
  float max = array[0];
  int maxIndex = 0;
  for (int i = 1; i < length; i++)
  {
    if (max < array[i])
    {
      maxIndex = i;
      max = array[i];
    }
  }
  return maxIndex;
}

int imin(const int *array, const uint length)
{
  int min = array[0];
  int minIndex = 0;
  for (int i = 1; i < length; i++)
  {
    if (min > array[i])
    {
      minIndex = i;
      min = array[i];
    }
  }
  return min;
}

int fminIndex(const float *array, const uint length)
{
  float min = array[0];
  int minIndex = 0;
  for (int i = 1; i < length; i++)
  {
    if (min > array[i])
    {
      minIndex = i;
      min = array[i];
    }
  }
  return minIndex;
}

void ibubblesort(int *array, const uint length)
{
  bool hasPermuted = true;
  while (hasPermuted)
  {
    hasPermuted = false;
    for (int i = 0; i < length - 1; i++)
    {
      if (array[i] > array[i + 1])
      {
        int c = array[i];
        array[i] = array[i + 1];
        array[i + 1] = c;
        hasPermuted = true;
      }
    }
  }
}

void cbubbleSort(char arr[][MAX], const uint length)
{
  char temp[MAX];
  bool hasPermuted;

  for (int i = 0; i < length - 1; i++)
  {
    hasPermuted = false;
    for (int j = 0; j < length - 1 - i; j++)
    {
      if (strcmp(arr[j], arr[j + 1]) > 0)
      {
        strcpy(temp, arr[j]);
        strcpy(arr[j], arr[j + 1]);
        strcpy(arr[j + 1], temp);
        hasPermuted = true;
      }
    }
    if (!hasPermuted)
      break;
  }
}

void fbubblesort(float *array, const uint length)
{
  bool hasPermuted = true;
  while (hasPermuted)
  {
    hasPermuted = false;
    for (int i = 0; i < length - 1; i++)
    {
      if (array[i] > array[i + 1])
      {
        float c = array[i];
        array[i] = array[i + 1];
        array[i + 1] = c;
        hasPermuted = true;
      }
    }
  }
}

int _ipartition(int *array, const int low, const int high)
{
  int pivot = array[high];
  int i = low - 1;
  for (int j = low; j < high; j++)
  {
    if (array[j] <= pivot)
    {
      int copy = array[++i];
      array[i] = array[j];
      array[j] = copy;
    }
  }
  int copy = array[i + 1];
  array[i + 1] = array[high];
  array[high] = copy;

  return i + 1;
}

void _iquicksort(int *array, const int low, const int high)
{
  if (low < high)
  {
    int pivot = _ipartition(array, low, high);
    _iquicksort(array, low, pivot - 1);
    _iquicksort(array, pivot + 1, high);
  }
}

void iquicksort(int *array, const uint length)
{
  _iquicksort(array, 0, length - 1);
}

int _fpartition(float *array, const int low, const int high)
{
  float pivot = array[high];
  int i = low - 1;
  for (int j = low; j < high; j++)
  {
    if (array[j] <= pivot)
    {
      float copy = array[++i];
      array[i] = array[j];
      array[j] = copy;
    }
  }
  float copy = array[i + 1];
  array[i + 1] = array[high];
  array[high] = copy;

  return i + 1;
}

void _fquicksort(float *array, const int low, const int high)
{
  if (low < high)
  {
    int pivot = _fpartition(array, low, high);
    _fquicksort(array, low, pivot - 1);
    _fquicksort(array, pivot + 1, high);
  }
}

void fquicksort(float *array, const uint length)
{
  _fquicksort(array, 0, length - 1);
}
