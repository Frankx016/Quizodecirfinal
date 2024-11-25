#include <stdio.h>
#include <string.h>
void main(void)
{
    
    int iNumLista = 1;	//Una sola palabra candidata
    int sugeridas = 0;
    int elementos;
    char sugeridas;
    char palabras;
    char lista;
    int peso;
    int estadistica;
    for (i = 0; i < sugeridas; i++)
    {
        for (j = 0; j < elementos; j++)
        {
            if (strcmp(sugeridas[i], palabras[j]) == 0)
            {

                strcpy_s(lista[iNumLista]);
                Peso[iNumLista] = Estadistica[j];
                iNumLista++;
            }
        }
    }
    int temppeso;
    char temppalabra;
    for (i = 0; i < iNumLista - 1; i++)

    {
        for (j = 0; j < iNumLista - i - 1; j++)
        {
            if (peso[j] < peso[j + 1])
            {

                temppeso = peso[j];
                peso[j] = peso[j + 1];
                peso[j + 1] = temppeso;



                strcpy_s(temppalabra, lista[j]);
                strcpy_s(lista[j], lista[j + 1]);
                strcpy_s(lista[j + 1], temppalabra);
            }
        }
    }
}
