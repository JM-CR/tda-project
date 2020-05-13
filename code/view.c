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
        "\nCorrecto uso del programa:\n"
        "\t1. \n"
        "\t2. \n"
        "\t3. \n\n"
    );
}

void printMenu( void ) {
    printf(
        "\n------------------------\n\n"
        "Operaciones disponibles:\n"
        "\t1. \n"
        "\t2. \n"
        "\t3. \n"
        "\t4. \n"
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
