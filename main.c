#define DELIMITADOR " " // Definir el delimitador para la separación (en este caso, espacios)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Prototipos de funciones

int findLastOccurrence(char cadena[], char subcadena[]);

void capitalizeString(char cadena[]);

int verifyStringEnd(char cadena[], char subcadena[]);

void formatNumericValue(int valor);

int validate_parentheses(char cadena[]);

char **splitString(const char *str, const char *delimitador, int *numTokens);

char *joinString(char *string, char separator);

int isPalindrome(char cadena[]);

// Función para mostrar el menú
void mostrar_menu();

// Definición de errores para paréntesis
#define ERROR_PARANTESIS_APERTURA_SIN_CIERRE -1
#define ERROR_PARANTESIS_CIERRE_SIN_APERTURA -2

int main()
{
    char *array = NULL;
    int opcion;

    do
    {
        mostrar_menu();
        if (scanf("%d", &opcion) != 1)
        {
            // Si scanf falla en leer un entero, limpiamos el buffer y mostramos error
            fprintf(stderr, "Entrada no válida. Intente de nuevo.\n");
            while (getchar() != '\n')
                ; // Limpiar buffer
            continue;
        }
        getchar(); // Consumir el salto de línea después de scanf

        switch (opcion)
        {
        case 1:
        {
            char cadena[100], subcadena[50];
            printf("Ingrese la cadena principal: ");
            fgets(cadena, 100, stdin);
            printf("Ingrese la subcadena a buscar: ");
            fgets(subcadena, 50, stdin);

            // Validar que las cadenas no estén vacías
            if (strlen(cadena) == 0 || strlen(subcadena) == 0)
            {
                fprintf(stderr, "Error: Las cadenas no pueden estar vacías.\n");
                break;
            }

            int posicion = findLastOccurrence(cadena, subcadena);
            if (posicion > 0)
                printf("La última ocurrencia comienza en la posición %d\n", posicion);
            else
                printf("Subcadena no encontrada\n");
            break;
        }
        case 2:
        {
            char cadena[100];
            printf("Ingrese una cadena para capitalizar: ");
            fgets(cadena, 100, stdin);

            if (strlen(cadena) == 0)
            {
                fprintf(stderr, "Error: La cadena no puede estar vacía.\n");
                break;
            }

            capitalizeString(cadena);
            printf("Cadena capitalizada: %s\n", cadena);
            break;
        }
        case 3:
        {
            char input[100];
            int numTokens;

            printf("Ingrese una cadena: ");
            fgets(input, sizeof(input), stdin);

            input[strcspn(input, "\n")] = '\0'; // Eliminar el salto de línea

            // Llamar a la función splitString
            char **array = splitString(input, DELIMITADOR, &numTokens);

            // Validar que la función retornó correctamente
            if (array != NULL)
            {
                printf("La cadena dividida es:\n");
                for (int i = 0; i < numTokens; i++)
                {
                    printf("%s\n", array[i]);
                    free(array[i]); // Liberar memoria de cada token
                }
                free(array); // Liberar memoria del arreglo de tokens
            }
            else
            {
                fprintf(stderr, "Error al dividir la cadena.\n");
            }
            break;
        }
        case 4:
        {
            char cadena[100], subcadena[50];
            printf("Ingrese la cadena a unir: ");
            fgets(cadena, 100, stdin);
            printf("Ingrese el separador: ");
            fgets(subcadena, 50, stdin);

            // Validar que las cadenas no estén vacías
            if (strlen(cadena) == 0 || strlen(subcadena) == 0)
            {
                fprintf(stderr, "Error: Las cadenas no pueden estar vacías.\n");
                break;
            }

            char *unionCadena = joinString(cadena, subcadena);

            printf("La union de la cadena es %s \n", unionCadena);
            break;
        }
        case 5:
        {
            char cadena[100], subcadena[50];
            printf("Ingrese la cadena principal: ");
            fgets(cadena, 100, stdin);
            printf("Ingrese la subcadena a verificar: ");
            fgets(subcadena, 50, stdin);

            // Validar que las cadenas no estén vacías
            if (strlen(cadena) == 0 || strlen(subcadena) == 0)
            {
                fprintf(stderr, "Error: Las cadenas no pueden estar vacías.\n");
                break;
            }

            int resultado = verifyStringEnd(cadena, subcadena);
            if (resultado)
                printf("La cadena termina con la subcadena.\n");
            else
                printf("La cadena no termina con la subcadena.\n");
            break;
        }
        case 6:
        {
            int valor;
            printf("Ingrese un valor numérico: ");
            if (scanf("%d", &valor) != 1)
            {
                fprintf(stderr, "Entrada no válida. Intente de nuevo.\n");
                while (getchar() != '\n')
                    ; // Limpiar buffer
                break;
            }

            formatNumericValue(valor);
            break;
        }
        case 7:
        {
            char cadena[100];
            printf("Ingrese una cadena para validar paréntesis: ");
            fgets(cadena, 100, stdin);

            // Validar que la cadena no esté vacía
            if (strlen(cadena) == 0)
            {
                fprintf(stderr, "Error: La cadena no puede estar vacía.\n");
                break;
            }

            int resultado = validate_parentheses(cadena);
            if (resultado == ERROR_PARANTESIS_APERTURA_SIN_CIERRE)
                printf("Error: Hay paréntesis de apertura sin cerrar.\n");
            else if (resultado == ERROR_PARANTESIS_CIERRE_SIN_APERTURA)
                printf("Error: Hay paréntesis de cierre sin apertura correspondiente.\n");
            else
                printf("Número de pares de paréntesis balanceados: %d\n", resultado);
            break;
        }
        case 8:
        {
            char cadena[100];
            printf("Ingrese una cadena para verificar si es palíndromo: ");
            fgets(cadena, 100, stdin);

            // Validar que la cadena no esté vacía
            if (strlen(cadena) == 0)
            {
                fprintf(stderr, "Error: La cadena no puede estar vacía.\n");
                break;
            }

            int resultado = isPalindrome(cadena);
            if (resultado)
                printf("La cadena es un palíndromo.\n");
            else
                printf("La cadena no es un palíndromo.\n");
            break;
        }
        case 9:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 8);

    return 0;
}

void mostrar_menu()
{
    printf("\nMenú de Opciones:\n");
    printf("1. Buscar última ocurrencia de una subcadena\n");
    printf("2. Capitalizar cadena\n");
    printf("3. Dividir cadena\n");
    printf("4. Unir cadena\n");
    printf("5. Verificar final de cadena\n");
    printf("6. Formatear valor numérico\n");
    printf("7. Validar paréntesis\n");
    printf("8. Verificar palíndromo\n");
    printf("9. Salir\n");
    printf("Seleccione una opción: ");
}
/**
 * @brief Verifica si una cadena es un palíndromo.
 *
 * Esta función determina si una cadena es un palíndromo, ignorando caracteres no alfanuméricos y considerando mayúsculas y minúsculas como equivalentes.
 * Ejemplo:
 * Para la cadena "A man a plan a canal Panama", la función devuelve 1.
 *
 * @param cadena La cadena de texto a verificar.
 * @return int 1 si la cadena es un palíndromo, 0 si no.
 */
int isPalindrome(char cadena[])
{
    int inicio = 0;
    int fin = strlen(cadena) - 1;

    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (isdigit(cadena[i]))
        {
            printf("Error: La cadena contiene valores numericos, solo se permiten letras.\n");
            return 0; // Si contiene números, no es válida.
        }
    }

    // Recorremos la cadena de extremo a extremo
    while (inicio < fin)
    {

        // Ignoramos los caracteres que no sean letras o dígitos numéricos
        if (!isalnum(cadena[inicio]))
        {
            inicio++;
        }
        else if (!isalnum(cadena[fin]))
        {
            fin--;
        }
        else
        {
            // Comparar los caracteres en minúsculas
            if (tolower(cadena[inicio]) != tolower(cadena[fin]))
            {
                return 0; // No es un palíndromo
            }
            inicio++;
            fin--;
        }
    }
    return 1; // Es un palíndromo
}

#define ERROR_PARANTESIS_APERTURA_SIN_CIERRE -1
#define ERROR_PARANTESIS_CIERRE_SIN_APERTURA -2
/**
 * @brief Valida los paréntesis en una cadena de texto.
 *
 * Esta función revisa una cadena para asegurar que todos los paréntesis de apertura '(' tienen un paréntesis de cierre correspondiente ')'.
 * Retorna diferentes códigos de error dependiendo del tipo de desbalance:
 *   - `ERROR_PARANTESIS_APERTURA_SIN_CIERRE` (-1): Hay paréntesis de apertura sin cerrar.
 *   - `ERROR_PARANTESIS_CIERRE_SIN_APERTURA` (-2): Hay paréntesis de cierre sin apertura correspondiente.
 *   - Número positivo: Cantidad de pares de paréntesis correctamente balanceados.
 *
 * @param cadena La cadena de texto a validar.
 * @return int Un código de error o el número de pares de paréntesis balanceados.
 */
int validate_parentheses(char cadena[])
{
    int apertura = 0;
    int pares = 0;

    for (int i = 0; cadena[i] != '\0'; i++)
    {
        if (cadena[i] == '(')
        {
            apertura++; // Encontrar paréntesis de apertura
        }
        else if (cadena[i] == ')')
        {
            if (apertura > 0)
            {
                apertura--; // Encontrar paréntesis de cierre que corresponde al de apertura
                pares++;    // Incrementamos el número de pares
            }
            else
            {
                // Si encontramos un paréntesis de cierre sin uno de apertura correspondiente
                return ERROR_PARANTESIS_CIERRE_SIN_APERTURA;
            }
        }
    }

    if (apertura == 0)
    {
        // Retorna el número de pares si todos los paréntesis están balanceados
        return pares;
    }
    else
    {
        // Si queda algún paréntesis de apertura sin cerrar
        return ERROR_PARANTESIS_APERTURA_SIN_CIERRE;
    }
}
/**
 * @brief Divide una cadena en un arreglo de tokens utilizando un delimitador.
 *
 * Esta función divide una cadena de texto en múltiples tokens basados en un delimitador específico y retorna un arreglo de punteros a estos tokens.
 * Ejemplo:
 * Si la entrada es "uno,dos,tres" y el delimitador es ",", el resultado será un arreglo de cadenas {"uno", "dos", "tres"}.
 *
 * @param str La cadena de texto que se va a dividir.
 * @param delimitador El delimitador que se utiliza para dividir la cadena.
 * @param numTokens Puntero a un entero que será actualizado con el número de tokens encontrados.
 * @return char** Un arreglo de punteros a los tokens, o NULL si ocurre un error.
 */
char **splitString(const char *str, const char *delimitador, int *numTokens)
{
    if (str == NULL || strlen(str) == 0)
    {
        fprintf(stderr, "Error: La cadena de entrada está vacía o es NULL.\n");
        *numTokens = 0;
        return NULL; // Retornar NULL si la cadena está vacía
    }

    // Hacer una copia de la cadena original ya que strtok modifica la cadena
    char *temp = strdup(str);
    if (temp == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para la copia de la cadena.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializar el número de tokens
    *numTokens = 0;

    // Usar strtok para contar cuántos tokens habrá
    char *token = strtok(temp, delimitador);
    while (token != NULL)
    {
        (*numTokens)++;
        token = strtok(NULL, delimitador);
    }

    // Asignar memoria para el arreglo de punteros a tokens
    char **tokens = (char **)malloc((*numTokens) * sizeof(char *));
    if (tokens == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para tokens.\n");
        free(temp); // Liberar la memoria de la copia temporal en caso de error
        exit(EXIT_FAILURE);
    }

    // Resetear temp para dividir la cadena de nuevo
    strcpy(temp, str);
    int index = 0;
    token = strtok(temp, delimitador);
    while (token != NULL)
    {
        tokens[index++] = strdup(token);
        token = strtok(NULL, delimitador);
    }

    // Liberar la memoria de la copia temporal
    free(temp);

    return tokens;
}
/**
 * @brief Une palabras en una cadena usando un separador específico.
 *
 * Esta función toma una cadena de texto en la que las palabras están separadas por espacios
 * y las une en una sola cadena utilizando un separador específico.
 * Ejemplo:
 * Si la entrada es "palabra1 palabra2 palabra3" y el separador es '-', la salida será "palabra1-palabra2-palabra3".
 *
 * @param string La cadena de texto que contiene las palabras a unir.
 * @param separator El carácter que se usará como separador entre las palabras.
 * @return char* La cadena resultante con las palabras unidas por el separador, o NULL si ocurre un error.
 */
// Función para unir palabras en una cadena usando un separador
char *joinString(char *string, char separator)
{
    // Verificar si la cadena de entrada es NULL
    if (string == NULL)
    {
        fprintf(stderr, "Error: La cadena de entrada es NULL.\n");
        return NULL;
    }

    // Calcular la longitud de la cadena de entrada
    int length = strlen(string);

    // Contar el número de palabras en la cadena (asumiendo que las palabras están separadas por espacios)
    int word_count = 1;
    for (int i = 0; i < length; i++)
    {
        if (string[i] == ' ')
        {
            word_count++;
        }
    }

    // Calcular la longitud total de la nueva cadena, considerando el separador
    // longitud original + (número de palabras - 1) + 1 (para el carácter nulo)
    int total_length = length + (word_count - 1) + 1;

    // Reservar memoria para la nueva cadena
    char *result = (char *)malloc(total_length * sizeof(char));
    if (result == NULL)
    {
        fprintf(stderr, "Error: No se pudo asignar memoria para el resultado.\n");
        return NULL; // Maneja el error de memoria
    }

    // Copiar la cadena original a la nueva cadena, reemplazando los espacios con el separador
    int j = 0;
    for (int i = 0; i < length; i++)
    {
        if (string[i] == ' ')
        {
            result[j++] = separator; // Reemplazar espacio con el separador
        }
        else
        {
            result[j++] = string[i]; // Copiar el carácter original
        }
    }
    result[j] = '\0'; // Añadir el carácter nulo al final de la nueva cadena

    return result;
}
/**
 * @brief Busca la última ocurrencia de una subcadena dentro de una cadena principal.
 *
 * Esta función recorre la cadena principal buscando la última aparición de la subcadena proporcionada.
 * Si la subcadena no se encuentra, devuelve 0. Si la subcadena es más larga que la cadena principal, también devuelve 0.
 *
 * @param cadena La cadena principal en la que se busca la subcadena.
 * @param subcadena La subcadena que se busca en la cadena principal.
 * @return int La posición de la última ocurrencia de la subcadena, o 0 si no se encuentra.
 */
// Función para buscar la última ocurrencia de una subcadena
int findLastOccurrence(char cadena[], char subcadena[])
{
    int i, j;
    int ultima_pos = -1;
    int len_cadena = strlen(cadena);
    int len_subcadena = strlen(subcadena);

    // Verificar si la subcadena es más larga que la cadena principal
    if (len_subcadena > len_cadena)
    {
        return 0; // La subcadena no puede encontrarse si es más larga que la cadena principal
    }

    // Eliminar el salto de línea final, si existe
    if (cadena[len_cadena - 1] == '\n')
    {
        cadena[len_cadena - 1] = '\0';
        len_cadena--;
    }
    if (subcadena[len_subcadena - 1] == '\n')
    {
        subcadena[len_subcadena - 1] = '\0';
        len_subcadena--;
    }

    for (i = 0; i <= len_cadena - len_subcadena; i++)
    {
        for (j = 0; j < len_subcadena; j++)
        {
            if (cadena[i + j] != subcadena[j])
            {
                break; // Salir del bucle si no coinciden los caracteres
            }
        }
        if (j == len_subcadena)
        {
            ultima_pos = i; // Actualizar la última posición encontrada
        }
    }

    return (ultima_pos >= 0) ? ultima_pos + 1 : 0; // Devolver la posición (1-indexada) o 0 si no se encuentra
}
/**
 * @brief Capitaliza la primera letra de cada palabra en una cadena.
 *
 * Esta función convierte la primera letra de cada palabra en una cadena a mayúscula. Las palabras están definidas por la presencia de espacios u otros caracteres de espacio.
 * Ejemplo:
 * Si la entrada es "hola mundo", la salida será "Hola Mundo".
 *
 * @param cadena La cadena de texto que se desea capitalizar.
 */
// Capitalizar una cadena de texto
void capitalizeString(char cadena[])
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

/**
 * @brief Verifica si una cadena termina con una subcadena específica.
 *
 * Esta función compara la parte final de una cadena con una subcadena dada para determinar si la cadena termina con la subcadena proporcionada.
 * Ejemplo:
 * Para la cadena "programacion en C" y la subcadena "en C", la función devuelve 1.
 *
 * @param cadena La cadena principal que se va a verificar.
 * @param subcadena La subcadena que se compara con el final de la cadena principal.
 * @return int 1 si la cadena termina con la subcadena, 0 si no.
 */
int verifyStringEnd(char cadena[], char subcadena[])
{
    int long_cadena = strlen(cadena); // Longitud de la cadena
    int long_subcadena = strlen(subcadena);

    // Verificar si la subcadena es más larga que la cadena principal
    if (long_subcadena > long_cadena)
    {
        return 0;
    }

    int pos_inicio_sub = long_cadena - long_subcadena;

    // Comparamos cada carácter de la subcadena con los caracteres finales de la cadena
    for (int i = 0; i < long_subcadena; i++)
    {
        char caracter_cadena = cadena[pos_inicio_sub + i];
        char caracter_subcadena = subcadena[i];

        if (caracter_cadena != caracter_subcadena)
        {
            return 0;
        }
    }

    return 1;
}
/**
 * @brief Formatea un valor numérico en formato de moneda.
 *
 * Esta función convierte un número entero a una cadena de texto con formato de moneda, incluyendo el signo de dólar '$' y separadores de miles ','.
 *
 * @param valor El número entero que se desea formatear.
 */
void formatNumericValue(int valor)
{
    char num[20];
    static char num_formateado[30]; // Usamos static para que la memoria se mantenga fuera de la función

    // Convertir el número a cadena de texto
    sprintf(num, "%d", valor);

    int len_num = strlen(num);
    int j = 0;

    num_formateado[j++] = '$'; // Añadir el signo de pesos

    // Calcular cuántos dígitos vienen antes del primer separador de miles
    int primeros_digitos = len_num % 3;
    if (primeros_digitos == 0)
    {
        primeros_digitos = 3;
    }

    // Copiar los primeros dígitos sin separador
    for (int i = 0; i < primeros_digitos; i++)
    {
        num_formateado[j++] = num[i];
    }

    // Añadir separadores de miles para el resto de los dígitos
    for (int i = primeros_digitos; i < len_num; i++)
    {
        if ((i - primeros_digitos) % 3 == 0)
        {
            num_formateado[j++] = ','; // Añadir el separador de miles
        }
        num_formateado[j++] = num[i]; // Añadir el siguiente dígito
    }

    num_formateado[j] = '\0'; // Terminar la cadena

    // Imprimir el número formateado
    printf("Valor formateado: %s\n", num_formateado);
}
