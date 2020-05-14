// See view.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: view.c
// Date: 17/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <limits.h>
#include "view.h"


// -----------------------------
// Private elements
// -----------------------------

/* Private functions */

/**
 * Reads an integer from the console and saves the result.
 *
 * @param state Location for the result.
 * @param lower Minimum value.
 * @param upper Maximum value.
 */
static void readOption( int *state, int lower, int upper ) {
    // Read
    int option = INT_MAX;
    printf("-> ");
    do {
        scanf("%d", &option);
        setbuf(stdin, NULL);
    } while ( option < lower || option > upper );

    // Save
    *state = option;
}


// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

void clearScreen( void ) {
    printf("\e[2J\e[H");
}

void initialGuide( void ) {
    printf(
        "\nSistema de recomendaciones.\n"
        "\nEquipo:\n"
        "\t- Josue Mosiah Contreras Rocha\n"
        "\t- Elena Ginebra Zarandona\n"
        "\t- Mariana Abigail Carmona Guzman\n"
        "\t- Ivan Josue Guzman Felix\n\n"
    );
}

unsigned int askMenuValue( char *text, int lower, int upper ) {
    // Display
    printf("\n%s", text);
    int value;
    readOption(&value, lower, upper);

    // Translate
    return value;
}

unsigned int SuggestionsOptions()
{   
    printf(
        "\n------------------------\n\n"
        "Que quieres que te sugiramos?:\n"
        "\t1. Peliculas\n"
        "\t2. Amigos\n"
        "\t3. Peliculas Similares\n"
        "\t4. Salir\n"
    );

    int op;
    op = askMenuValue("", 1, 4);
    return op;
}

void displayUsers( Data_t *data ) {
    printf(
        "\n------------------------\n\n"
        "Usuarios actuales:\n"
    );
    for ( int i = 0; i < data->totalUsers; ++i ) {
        printf("\t%d. %s\n", i + 1, data->users[i]->name);
    }
}

void displayMovies( Data_t *data ) {
    printf(
        "\n------------------------\n\n"
        "Películas actuales:\n"
    );
    for ( int i = 0; i < data->totalMovies; ++i ) {
        printf("\t%2d. %s\n", i + 1, data->movies[i]->name);
    }
}
