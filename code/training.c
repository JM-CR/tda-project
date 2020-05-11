// See training.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: training.c
// Date: 17/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "training.h"


// -----------------------------
// Private elements
// -----------------------------

/* Private macros and constants */

/* Private types */

/* Private global variables */

/* Private functions */

/**
 * Creates a new user object.
 *
 * @param id Unique id.
 * @param name Name of the user.
 * @param sizeAffinity Size of the features' vector.
 * @return User object.
 */
static User_t *newUser( unsigned int id, char *name, size_t totalAffinity ) {
    return NULL;
}

/**
 * Creates a new movie object.
 *
 * @param id Unique id.
 * @param name Name of the movie.
 * @param sizeAffinity Size of the features' vector.
 * @return Movie object.
 */
static Movie_t *newMovie( unsigned int id, char *name, size_t totalAffinity ) {
    return NULL;
}

/**
 * Creates a new data object.
 *
 * @param totalMovies Total of movies.
 * @param totalUsers Total of users.
 * @return Data object.
 */
static Data_t *newData( size_t totalMovies, size_t totalUsers ) {
    Data_t *data = malloc(sizeof(Data_t));
    data->movies = calloc(totalMovies, sizeof(Movie_t));
    data->users = calloc(totalUsers, sizeof(User_t));
    data->totalMovies = totalMovies;
    data->totalUsers = totalUsers;
    return data;
}

/**
 * Loads a CSV file to use as initial values for the app.
 *
 * @return A data object with every value initialized.
 */
Data_t *loadCSVFile( void ) {
    // Open file
    FILE *fp = fopen("training_files/data.csv", "r");
    if ( fp == NULL ) {
        fprintf(stderr, "\nError leyendo archivo de entrenamiento.\n");
        exit(EXIT_FAILURE);
    }

    // Read file
    int userID = 1, movieID = 1;
    char line[100], *token;
    while ( fgets(line, sizeof line, fp) != NULL ) {
        // Process user name
        token = strtok(line, ",");

        // Process movie name
        puts(token);
        token = strtok(NULL, ",");

        // Process ranking
        puts(token);
        token = strtok(NULL, ",");

        // Process features
        while ( token ) {
            puts(token);
            token = strtok(NULL, ",");
        }
    }

    fclose(fp);
    Data_t *data = newData(10, 10);
    return data;
}

// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */
