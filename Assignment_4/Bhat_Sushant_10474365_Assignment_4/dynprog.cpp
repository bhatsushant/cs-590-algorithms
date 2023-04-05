#include <cstring>
#include <iostream>
#include <limits.h>

#include "dynprog.h"

using namespace std;

/*
 * Bottom up implementation of Smith-Waterman algorithm
 */
void SW_bottomUp(char *X, char *Y, char **P, int **H, int n, int m)
{
    int s1, s2, s3;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (i == 0 || j == 0)
                P[i][j] = H[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                s1 = H[i - 1][j - 1] + 2;
            }
            else
            {
                s1 = H[i - 1][j - 1] - 1;
            }
            s2 = H[i - 1][j] - 1;
            s3 = H[i][j - 1] - 1;

            if (s1 >= s2 && s1 >= s3)
                H[i][j] = s1;
            else
            {
                if (s2 >= s1 && s2 >= s3)
                    H[i][j] = s2;
                else
                    H[i][j] = s3;
            }

            if (H[i][j] == s1)
            {
                P[i][j] = 'd';
            }
            else
            {
                if (H[i][j] == s2)
                {
                    P[i][j] = 'u';
                }
                else
                {
                    P[i][j] = 'l';
                }
            }
        }
    }

    return;
}

/*
 * Top-down with memoization implementation of Smith-Waterman algorithm
 */
void memoized_SW(char *X, char *Y, char **P, int **H, int n, int m)
{
    int s1, s2, s3;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            H[i][j] = 0;
            P[i][j] = '-';
        }
    }
    memoized_SW_AUX(X, Y, P, H, n, m);

    // if (m == 0 || n == 0)
    //         return ;

    // if (H[n][m] != 0){
    //    H[n][m] = H[n][m] ;
    // }
    // else{
    //        H[n][m] = memoized_SW_AUX(X, Y, P, H,n, m );
    // }

    return;

    // cout<< H[n][m] << endl;
    // }
}

/*
 * Auxilary recursive function of top-down with memoization implementation of Smith-Waterman algorithm
 */
int memoized_SW_AUX(char *X, char *Y, char **P, int **H, int n, int m)
{
    int s1, s2, s3;
    if (m == 0 || n == 0)
        return 0;

    if (H[n][m] != 0)
    {
        return H[n][m];
    }
    if (X[n - 1] == Y[m - 1])
    {
        s1 = memoized_SW_AUX(X, Y, P, H, n - 1, m - 1) + 2;
    }
    else
    {
        s1 = memoized_SW_AUX(X, Y, P, H, n - 1, m - 1) - 1;
    }
    s2 = memoized_SW_AUX(X, Y, P, H, n - 1, m) - 1;
    s3 = memoized_SW_AUX(X, Y, P, H, n, m - 1) - 1;

    if (s1 >= s2 && s1 >= s3)
    {
        H[n][m] = s1;
    }
    else
    {
        if (s2 >= s1 && s2 >= s3)
            H[n][m] = s2;
        else
            H[n][m] = s3;
    }

    if (H[n][m] == s1)
    {
        P[n][m] = 'd';
    }
    else
    {
        if (H[n][m] == s2)
        {
            P[n][m] = 'u';
        }
        else
        {
            P[n][m] = 'l';
        }
    }

    return H[n][m];
}

/*
 * Print X'
 */

void print_Seq_Align_X(char *X, char **P, int n, int m)
{
    if (m < 0 || n < 0)
    {
        // reverseStr(newX);
        // cout<X[n-1]<<endl;
        return;
    }
    if (P[n][m] == 'd')
    {
        // newX += X[n-1];
        print_Seq_Align_X(X, P, n - 1, m - 1);
        // cout<<X[n-1] << endl;
        cout << X[n - 1];
    }
    if (P[n][m] == 'l')
    {
        // newX += '-';

        print_Seq_Align_X(X, P, n, m - 1);
        // cout<<"-"<< endl;
        cout << "-";
    }
    if (P[n][m] == 'u')
    {
        // newX += X[n-1];
        print_Seq_Align_X(X, P, n - 1, m);
        // cout<<X[n-1] << endl;
        cout << X[n - 1];
    }
}

/*
 * Print Y'
 */
void print_Seq_Align_Y(char *Y, char **P, int n, int m)
{
    if (m < 0 || n < 0)
    {
        return;
    }
    if (P[n][m] == 'd')
    {
        print_Seq_Align_Y(Y, P, n - 1, m - 1);
        // cout<<Y[m-1] << endl;
        cout << Y[m - 1];
    }
    if (P[n][m] == 'l')
    {
        print_Seq_Align_Y(Y, P, n, m - 1);
        // cout<<Y[m-1] << endl;
        cout << Y[m - 1];
    }
    if (P[n][m] == 'u')
    {
        print_Seq_Align_Y(Y, P, n - 1, m);
        // cout<<"-"<< endl;
        cout << "-";
    }
}
