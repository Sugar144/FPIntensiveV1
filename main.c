#include <stdio.h>      // Funciones de entrada y salida estándar (printf, scanf, fopen, etc.)
#include <string.h>     // Funciones básicas para trabajar con texto (strlen, strcpy)
#include <stdbool.h>    // Tipo booleano (true / false)


/* Tamaño máximo de una línea de texto que se leerá del fichero */
#define MAX_LINE 514+1

/* Tamaño máximo del nombre del fichero del tema */
#define MAX_FILENAME 25+1

/* 
 * Enumerado que representa las opciones del menú principal.
 * Cada valor corresponde a una opción que el usuario puede seleccionar.
 */
typedef enum {
    TOPIC_TYPES = 1,
    TOPIC_VARIABLES,
    TOPIC_ENUMS,
    TOPIC_EXPRESSIONS,
    EXIT 
} tMainOption;


int main(int argc, char **argv)
{
    /* Variable para leer la opción introducida por el usuario (como número) */
    int optionInt;

    /* Variable del tipo enumerado para trabajar con opciones de forma más clara */
    tMainOption option;
    
    /* Nombre del fichero que contiene el contenido del tema seleccionado */
    char fileName[MAX_FILENAME];

    /* Buffer de texto donde se guardará la línea leída del fichero */
    char line[MAX_LINE];

    /* Puntero a fichero para acceder al archivo de texto */
    FILE *fin;

    /* 
     * Variables de control del flujo del programa.
     * Se utilizan para evitar múltiples puntos de salida (return).
     */
    bool validOption;     // Indica si la opción introducida es válida
    bool mustLoadFile;   // Indica si se debe cargar un fichero o no

    /* Estado inicial del programa */
    validOption = true;
    mustLoadFile = false;
    
    
    /* 1) Mostrar el menú principal */
    printf("==== LEARNING MOTOR (Sprint 1) ====\n");
    printf("1) Primitive data types\n");
    printf("2) Variables and constants\n");
    printf("3) Enumerated types\n");
    printf("4) Expressions\n");
    printf("5) Exit\n");
    printf("Select option >> \n");
    
    scanf("%d", &optionInt);
    
    /* Leer la opción introducida por el usuario */
    if ( optionInt < 1 || optionInt > 5) {
        
        /* Si la lectura falla, se marca la opción como no válida */
        printf("Invalid input\n");
        validOption = false;
        
     } else {

        /* Consumir el salto de línea que queda en el buffer de entrada.
           Esto evita problemas en lecturas posteriores.*/
        getchar();

        /* Convertir el número leído a una opción del enumerado */
        option = (tMainOption)optionInt;
        
        
        /* 2) Decidir qué hacer según la opción seleccionada */
        switch (option) {

            case TOPIC_TYPES:
                /* Asociar la opción con el fichero del tema correspondiente */
                strcpy(fileName, "topic_1_types.txt");
                mustLoadFile = true;   // Se deberá cargar el fichero
                break;

            case TOPIC_VARIABLES:
                strcpy(fileName, "topic_2_variables.txt");
                mustLoadFile = true;
                break;

            case TOPIC_ENUMS:
                strcpy(fileName, "topic_3_enums.txt");
                mustLoadFile = true;
                break;

            case TOPIC_EXPRESSIONS:
                strcpy(fileName, "topic_4_expressions.txt");
                mustLoadFile = true;
                break;

            case EXIT:
                /* Si el usuario elige salir, no se carga ningún fichero */
                printf("Bye!\n");
                mustLoadFile = false;
                break;

            default:
                /* Opción no válida */
                printf("Invalid option\n");
                validOption = false;
                mustLoadFile = false;
                break;
        }
        
     }
     
     /* 3) Cargar el contenido del fichero y mostrarlo */
    /* Solo se entra aquí si la opción es válida y hay que cargar fichero */
    if (validOption == true && mustLoadFile == true) {

        /* Abrir el fichero en modo lectura */
        fin = fopen(fileName, "r");

        if (fin == NULL) {
            /* Si el fichero no se puede abrir, se muestra un error */
            printf("ERROR: unable to open topic file\n");
        } else {

            /* 
             * Leer una única línea del fichero.
             * En Sprint 1 NO se usan bucles, por lo que solo se realiza una lectura.
             */
            line[0] = '\0';                  // Inicializar el buffer como cadena vacía
            fgets(line, MAX_LINE - 1, fin);  // Leer una línea del fichero
            line[MAX_LINE - 1] = '\0';       // Garantizar fin de cadena

            /* Cerrar el fichero */
            fclose(fin);

            /* Comprobar si se ha leído contenido */
            if (strlen(line) > 0) {
                /* Mostrar el contenido leído */
                printf("\n---- CONTENT ----\n");
                printf("%s", line);
                printf("\n-----------------\n");
            } else {
                /* El fichero estaba vacío */
                printf("ERROR: empty topic file\n");
            }
        }
    }
     
    
	return 0;
}