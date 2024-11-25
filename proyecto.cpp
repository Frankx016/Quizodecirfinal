
#include <stdio.h>
#include <string.h>

int main()
{
    FILE* fp;
    char buffer[300];
    char palabra[300];
    char diccionario[100][300];
    int estadistica[100];
    int conta;
    int iNumPalabras;
    for (conta = 0; conta < 100; conta++)
        estadistica[conta] = 0;
    fopen_s(&fp, "anita.txt", "r");
    if (fp != NULL)
    {
        iNumPalabras = 0;
        while (!feof(fp))
        {
            fgets(buffer, 300, fp);
            printf("::%s\n", buffer);
            conta = 0;
            int contaPalabra = 0;
            
            while (buffer[conta] != '\0')
            {
                //printf("%c", buffer[conta]);
                if (buffer[conta] == '\0' || buffer[conta] == ' ')
                {
                    palabra[contaPalabra] = '\0';
                    contaPalabra = 0;
                    strcpy_s(diccionario[iNumPalabras],300, palabra);
                    estadistica[iNumPalabras++]++;
                    //printf("%s\n", palabra);
                }
                else
                {
                    palabra[contaPalabra++] = buffer[conta];
                }
                conta++;

            }
        
        }
        printf("\nDiccionario completo\n");
        for (conta = 0; conta < iNumPalabras; conta++)
            printf("%s %i\n", diccionario[conta], estadistica[conta]);
        fclose(fp);
    }
}
