#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void gauss(float**matr,float **matr_obr, int n)
{
    int k = 0, ind;
    while (k < n)
    {
        float t = matr[k][k];
        if(t == 0)
        {
            for(int i = 0; i < n; i++)
                if(matr[i][k] != 0)
                {
                    ind = i;
                    break;
                }
            for(int i = 0; i < n; i++)
            {
                float t = matr[k][i], t1 = matr_obr[k][i];
                matr[k][i] = matr[ind][i], matr_obr[k][i] = matr[ind][i];
                matr[ind][i] = t, matr_obr[ind][i] = t1;
            }
            t = matr[k][k];
        }
        for (int i = 0; i < n; i++)
        {
            matr[k][i] /= t;
            matr_obr[k][i] /= t;
        }
        for (int i = k + 1; i < n; i++)
        {
            float t = matr[i][k];
            for (int j = 0; j < n; j++)
            {
                matr[i][j] -= matr[k][j] * t;
                matr_obr[i][j] -= matr_obr[k][j] * t;
            }
        }
        k++;
    }
    for (k = n - 1; k > 0; k--)
    {
        for(int j = k - 1; j >= 0; j--)
        {
            float t = matr[j][k];
            matr[j][k] -= matr[k][k] * t;
            for(int i = n-1; i >= 0; i--)
            {
                matr_obr[j][i] -= matr_obr[k][i] * t;
            }
        }
    }
}
int main()
{
    setlocale(LC_ALL, "Rus");
    int n;
    float **matr, **matr_obr, **copy_m;

    printf("Введите размер матрицы m*m: ");
    scanf("%d", &n);

    matr = (float**) malloc(n*sizeof(float*));
    matr_obr = (float**) malloc(n*sizeof(float*));
    copy_m = (float**) malloc(n*sizeof(float*));


    for (int i = 0; i < n; ++i){
        matr[i] = (float*) malloc(n*sizeof(float));
        matr_obr[i] = (float*) malloc(n*sizeof(float));
        copy_m[i] = (float*) malloc(n*sizeof(float));
    }
    printf("Введите элементы матрицы\n");

    for (int i = 0; i < n; i++)

        for (int j = 0; j < n; j++)

        {
            if(i == j)
                matr_obr[i][j] = 1;
                  else matr_obr[i][j] = 0;

            scanf("%f", &matr[i][j]);
            copy_m[i][j] = matr[i][j];
        }

    gauss(matr, matr_obr, n);
    printf("Обратная матрица\n");

     for(int i = 0; i < n; i++)
      {
        for(int j = 0; j < n; j++)
            printf("%f ", matr_obr[i][j]);
        printf("\n");
      }

    float**p = (float**) malloc(n*sizeof(float*));

    for (int i = 0; i < n; i++)
    {
        p[i] = (float*) malloc(n*sizeof(float));

        for (int j = 0; j < n; j++)

        {
            p[i][j] = 0;

            for (int k = 0; k < n; k++)
                p[i][j] += copy_m[i][k] * matr_obr[k][j];

            if (fabs(p[i][j]) < 0.000001)
                p[i][j] = 0;
        }

    }
    printf("Матрица-произведение для проверки\n");
    for(int i = 0; i < n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%f ", p[i][j]);
        }
        printf("\n");
    }
return 0;
}
