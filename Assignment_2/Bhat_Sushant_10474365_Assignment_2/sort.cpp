#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "sort.h"

using namespace std;

/* 
 * HW 2 part
 */
int string_compare(char *s1, char *s2)
{
  /*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
  {
    if (s1[i] < s2[i])
      return -1;
    else
      return 1;
  }
} /*>>>*/

void insertion_sort(char **A, int l, int r)
{
  int i;
  char *key;

  for (int j = l + 1; j <= r; j++)
  {
    key = A[j];
    i = j - 1;

    while ((i >= l) && (string_compare(A[i], key) > 0))
    {
      A[i + 1] = A[i];
      i = i - 1;
    }

    A[i + 1] = key;
  }
}

void insertion_sort_digit(char **A, int *A_len, int l, int r, int d)
{
  int i;
  char *tempKey;
  int tempKey_len;
  char A_i_d;
  char key_d;
  for (int j = 1; j <= r; j++)
  {
    tempKey = A[j];
    tempKey_len = A_len[j];
    i = j - 1;
    if (A_i_d == (A_len[i] < d))
    {
      A_i_d = 0;
    }
    else
    {
      A_i_d = A[i][d];
    }
    A_i_d = (A_len[i] < d) ? 0 : A[i][d];
    key_d = (tempKey_len < d) ? 0 : tempKey[d];
    while ((i >= l) && (A_i_d > key_d))
    {
      A_len[i + 1] = A_len[i];
      A[i + 1] = A[i];
      i = i - 1;
      if (i >= l)
      {
        if (A_i_d == (A_len[i] < d))
        {
          A_i_d = 0;
        }
        else
        {
          A_i_d = A[i][d];
        }
      }
    }
    A_len[i + 1] = tempKey_len;
    A[i + 1] = tempKey;
  }
}

void counting_sort_digit(char **A, int *A_len, char **B, int *B_len, int n, int d)
{

  int *c = new int[256];
  for (int i = 0; i < 256; i++)
  {
    c[i] = 0;
  }

  for (int i = 0; i < n; i++)
  {
    if (A_len[i] - 1 >= d)
    {
      ++c[A[i][d]];
    }
    else
    {
      ++c[0];
    }
  }
  for (int i = 1; i < 255; i++)
  {
    c[i] += c[i - 1];
  }

  for (int j = n - 1; j >= 0; --j)
  {
    if (A_len[j] - 1 >= d)
    {
      B[c[A[j][d]] - 1] = A[j];
      B_len[c[A[j][d]] - 1] = A_len[j];
      --c[A[j][d]];
    }
    else
    {
      B[c[0] - 1] = A[j];
      B_len[c[0] - 1] = A_len[j];
      c[0]--;
    }
  }
  for (int i = 0; i < n; i++)
  {
    A[i] = B[i];
    A_len[i] = B_len[i];
  }
  delete[] c;
}

void radix_sort_is(char **A, int *A_len, int n, int m)
{
  for (int i = m - 1; i >= 0; i--)
  {
    insertion_sort_digit(A, A_len, 0, n - 1, i);
  }
}

void radix_sort_cs(char **A, int *A_len, int n, int m)
{
  char **B, **currentA, **currentB;
  int *B_len, *currentA_len, *currentB_len;
  B = new char *[n];
  B_len = new int[n];
  currentA = A;
  currentB = B;
  currentA_len = A_len;
  currentB_len = B_len;

  for (int i = m - 1; i >= 0; i--)
  {
    //counting_sort_digit(currentA, currentA_len, currentB, currentB_len, n, i);
    counting_sort_digit(currentA, currentA_len, currentB, currentB_len, n - 1, i);
  }
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char **A, int l, int r)
{
  for (int i = l + 1; i < r; i++)
    if (string_compare(A[i - 1], A[i]) > 0)
      return false;
  return true;
}
