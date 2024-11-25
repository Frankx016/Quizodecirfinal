#include <stdio.h>
#include <string.h>
void main(void) 
{
    int iNumSugeridas = 1;							


    char palabra[3000];
    int i, j;
    gets_s(palabra);

    int numerodeletras = strlen(palabra);
    int contadorpalabras = 0;
    int contadorpalabras2 = 0;
    for (i = 0; i < numerodeletras; i++)
    {

        for (j = 0; j < numerodeletras; j++)
        {
            if (j != i)
            {
                printf("%c", palabra[j]);

            }
        }
        contadorpalabras++;
        printf("\n");
    }
}
