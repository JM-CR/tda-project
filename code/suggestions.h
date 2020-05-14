// Template to create C libraries.
// Author: Ivan Josue Guzman Felix
// File: suggestions.h
// Date: 17/02/20

#ifndef SUGGESTIONS_H
#define SUGGESTIONS_H

// -----------------------------
// System headers
// -----------------------------
#include "training.h"


// -----------------------------
// Public interface
// -----------------------------

/* Constants */

/* Types declarations */

/* Global variables */

/* Function prototypes */

/**
*This funcion puts a movie suggestion according to a user´s affinities
*
*@Trained database
*@return a movie suggestion
*
*/
int movieSuggestionUser(Data_t *data );

/**
*This funcion puts a friend suggestion according to a user´s affinities
*
*@Trained database
*@return a friend suggestion
*
*/
int friendsSuggestions(Data_t *data);

/**
*This funcion puts a movie suggestion according to a other movie´s affinities
*
*@Trained database
*@return a friend suggestion
*
*/
int movieSuggestionMovie(Data_t *data);


/**
 * Function's documentation.
 */

#endif
