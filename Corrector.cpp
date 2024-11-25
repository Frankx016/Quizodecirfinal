/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion.
	(c) Ponga su nombre y numero de cuenta aqui.

	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{

    //Sustituya estas lineas por su código
    iNumElementos = 1;
    strcpy_s(szPalabras[0], "AquiVaElDiccionario");
    iEstadisticas[0] = 1; // la primer palabra aparece solo una vez.
    FILE* fp;
    char buffer[300];
    char palabra[300];
    iNumElementos = 0;
    int i;
    int k;
    int j;
   
    fopen_s(&fp, szNombre, "r");
    if (fp == NULL) 
    {
        printf("Error: No se pudo abrir el archivo %s\n", szNombre);
        return;
    }

    
    while (fgets(buffer, 300, fp) != NULL)
    {
        int conta = 0;
        int contaPalabra = 0;

        while (buffer[conta] != '\0') {
            if (buffer[conta] == ' ' || buffer[conta] == '\n') 
            {
                palabra[contaPalabra] = '\0';
                contaPalabra = 0;

                if (strlen(palabra) > 0) 
                {
                   
                    int encontrada = 0;
                    for (i = 0; i < iNumElementos && !encontrada; i++)
                    {
                        if (strcmp(szPalabras[i], palabra) == 0)
                        {
                            iEstadisticas[i]++;
                            encontrada = 1;
                        }
                    }

                   
                    if (!encontrada && iNumElementos < 100) 
                    {
                        strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabra);
                        iEstadisticas[iNumElementos] = 1;
                        iNumElementos++;
                    }
                }
            }
            else 
            {
                palabra[contaPalabra++] = buffer[conta];
            }
            conta++;
        }
    }

    fclose(fp);

    
    for (i = 0; i < iNumElementos - 1; i++)
    {
        for (j = 0; j < iNumElementos - i - 1; j++) 
        {
            if (iEstadisticas[j] < iEstadisticas[j + 1]) 
            {
               
                int tempEstadistica = iEstadisticas[j];
                iEstadisticas[j] = iEstadisticas[j + 1];
                iEstadisticas[j + 1] = tempEstadistica;

               
                char tempPalabra[TAMTOKEN];
                for (k = 0; k < TAMTOKEN; k++) 
                {
                    tempPalabra[k] = szPalabras[j][k];
                    szPalabras[j][k] = szPalabras[j + 1][k];
                    szPalabras[j + 1][k] = tempPalabra[k];
                }
            }
        }
    }

    
   
    for ( i = 0; i < iNumElementos; i++)
    {
        printf("%s %d\n", szPalabras[i], iEstadisticas[i]);
    }
    printf("Numero de elemntos en la lista: %i", iNumElementos);
}
 


   
       


/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código
	strcpy_s(szListaFinal[0], szPalabrasSugeridas[0]); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata

	iNumLista = 1;							//Una sola palabra candidata
    int f = 0;
    int duplicado;

    for (int i = 0; i < iNumSugeridas; i++) 
    {
        duplicado = 0;
       
        for (int j = 0; j < iNumLista; j++) 
        {
            if (strcmp(szPalabrasSugeridas[i], szListaFinal[j]) == 0) {
                duplicado = 1;
            }
        }

        if (duplicado == 0) {
            strcpy_s(szListaFinal[iNumLista], TAMTOKEN, szPalabrasSugeridas[i]);
            
            for (int k = 0; k < iNumElementos; k++) 
            {
                if (strcmp(szPalabrasSugeridas[i], szPalabras[k]) == 0) 
                {
                    iPeso[iNumLista] = iEstadisticas[k];
                }
            }
            iNumLista++;
        }
    }

    for (int i = 0; i < iNumLista; i++)
    {
        if (szListaFinal[i][0] != '\0')
        {
            printf("%s %d\n", szListaFinal[i], iPeso[i]);
        }
    }
}



/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	strcpy_s(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
    char palabra[300];
    fgets(palabra, sizeof(palabra), stdin);  // Usa fgets en lugar de gets_s para evitar errores

    int numerodeletras = strlen(palabra);
    char tpala[TAMTOKEN];  
    int temp;

    for (int i = 0; i < numerodeletras; i++) 
    {
        temp = 0;

        
        for (int j = 0; j < numerodeletras; j++)
        {
            if (j != i) 
            {
                tpala[temp++] = palabra[j];
            }
        }
        tpala[temp] = '\0';  
        strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, tpala);
        iNumSugeridas++;
    }

    const char abecedario[] = "abcdefjhijklmnñopqrstuvwxyzáéíóú";
    for (int i = 0; i <= numerodeletras; i++)
    {
        int temp = 0;
        int j = 0;
        while (abecedario[j] != '\0')
        {
           
            for (int k = 0; k < i; k++) 
            {
                tpala[temp++] = palabra[k];
            }

            tpala[temp++] = abecedario[j];

            for (int k = i; k < numerodeletras; k++)
            {
                tpala[temp++] = palabra[k];
            }
            tpala[temp] = '\0'; 
            strcpy_s(szPalabrasSugeridas[iNumSugeridas], TAMTOKEN, tpala);
            iNumSugeridas++;
            j++;
        }
    }

   
    printf("\nPalabras generadas:\n");
    for (int i = 0; i < iNumSugeridas; i++)
    {
        printf("%s\n", szPalabrasSugeridas[i]);
    }
    printf("\nTotal de sugerencias: %d\n", iNumSugeridas);
}