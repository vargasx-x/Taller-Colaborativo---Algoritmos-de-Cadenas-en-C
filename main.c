#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Prototipos de funciones
int buscar_ultima_ocurrencia(char cadena[], char subcadena[]);
void capitalizar_cadena(char cadena[]);
char** dividir_cadena(char cadena[], int* numPalabras);
void unir_cadena(char* resultado, char** arreglo, int numPalabras, char separador);
int verificar_final_cadena(char cadena[], char subcadena[]);
void formatear_valor_numerico(int valor, char* resultado);
int es_palindromo(char cadena[]);
int validar_parentesis(char cadena[]);
void mostrar_menu();

// Función principal
int main()
{
    int opcion;
    do
    {
        mostrar_menu();
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada

        switch (opcion)
        {
        case 1:
            {
                char cadena[100], subcadena[50];
                printf("Ingrese la cadena principal: ");
                fgets(cadena, 100, stdin);
                printf("Ingrese la subcadena a buscar: ");
                fgets(subcadena, 50, stdin);
                int posicion = buscar_ultima_ocurrencia(cadena, subcadena);
                if (posicion > 0)
                    printf("La ultima ocurrencia comienza en la posicion %d\n", posicion);
                else
                    printf("Subcadena no encontrada\n");
                break;
            }
        case 2:
            {
                char cadena[100];
                printf("Ingrese una cadena para capitalizar: ");
                fgets(cadena, 100, stdin);
                capitalizar_cadena(cadena);
                printf("Cadena capitalizada: %s\n", cadena);
                break;
            }
        // Aquí irían los demás casos del menú, llamando las otras funciones.
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción no válida\n");
        }
    }
    while (opcion != 0);

    return 0;
}

// Función para mostrar el menú
void mostrar_menu()
{
    printf("\n--- Menu de Opciones ---\n");
    printf("1. Buscar la ultima ocurrencia de una subcadena\n");
    printf("2. Capitalizar una cadena de texto\n");
    // Más opciones del menú
    printf("0. Salir\n");
    printf("Elija una opcion: ");
}

// Buscar la última ocurrencia de una subcadena
int buscar_ultima_ocurrencia(char cadena[], char subcadena[])
{
    int ultima_pos = -1;
    char* ptr = strstr(cadena, subcadena);
    while (ptr != NULL)
    {
        ultima_pos = ptr - cadena;
        ptr = strstr(ptr + 1, subcadena);
    }
    return ultima_pos;
}

// Capitalizar una cadena de texto
void capitalizar_cadena(char cadena[])
{
    int capitalizar = 1;
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (isspace(cadena[i]))
        {
            capitalizar = 1;
        }
        else if (capitalizar && isalpha(cadena[i]))
        {
            cadena[i] = toupper(cadena[i]);
            capitalizar = 0;
        }
    }
}
