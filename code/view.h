// Library that facilitates the use of the recommendations system.
// Author: Josue Mosiah Contreras Rocha
// File: view.h
// Date: 13/05/20

#ifndef VIEW_H
#define VIEW_H

// -----------------------------
// System headers
// -----------------------------
#include "suggestions.h"
#include "reports.h"


// -----------------------------
// Public interface
// -----------------------------

/* Function prototypes */

/**
 * Clears the current window.
 */
void clearScreen( void );

/**
 * A little description about the program's behaviour.
 */
void initialGuide( void );

/**
 * Allows the user to choose an option from a menu.
 *
 * @param text Instructions.
 * @param lower Minimum value.
 * @param upper Maximum value.
 * @return Chosen option.
 */
unsigned int askMenuValue( char *text, int lower, int upper );

/**
* Movies or friends suggesion view menu 
*/
unsigned int SuggestionsOptions();

/**
 * Displays all the available users.
 */
void displayUsers( Data_t *data );

/**
 * Displays all the available movies.
 */
void displayMovies( Data_t *data );

#endif
