// See training.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: training.c
// Date: 17/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "training.h"


// -----------------------------
// Private elements
// -----------------------------

/* Private macros and constants */

/* Private types */

/* Private global variables */

/* Private functions */

/**
 * Generates a random number.
 *
 * @return The number.
 */
static double randomNumber( void ) {
    // Initial set up
	static bool firstRun = true;
	if ( firstRun ) {
		firstRun = false;
		srand(time(0));
	}

    // Get random
    return (double)rand() / (double)RAND_MAX;
}

/**
 * Creates random vector for the user's affinities.
 *
 * @return Array of affinities.
 */
static double *randomAffinities( void ) {
    double *vector = calloc(TOTAL_FEATURES, sizeof(double));
    for ( int i = 0; i < TOTAL_FEATURES; ++i ) {
        vector[i] = randomNumber();
    }
    return vector;
}

/**
 * Creates a new user object.
 *
 * @param name Name of the user.
 * @return User object.
 */
static User_t *newUser( char *name ) {
    // Status variables
    static int lastID = 1;

    // Set values
    User_t *user = malloc(sizeof(User_t));
    user->id = lastID++;
    user->name = name;
    user->affinity = randomAffinities();
    user->totalAffinity = TOTAL_FEATURES;
    user->watchedMovies = calloc(MAX_WATCHED, sizeof(int));
    user->watchTotal = 0;
    return user;
}

/**
 * Creates a new movie object.
 *
 * @param name Name of the movie.
 * @return Movie object.
 */
static Movie_t *newMovie( char *name ) {
    return NULL;
}

/**
 * Creates a new data object with an empty set of users and movies.
 *
 * @return Data object.
 */
static Data_t *newData( void ) {
    Data_t *data = malloc(sizeof(Data_t));
    data->users = calloc(MAX_USERS, sizeof(User_t));
    data->movies = calloc(MAX_MOVIES, sizeof(Movie_t));
    data->totalMovies = 0;
    data->totalUsers = 0;
    return data;
}

/**
 * Seeks a user in the data struct. If it doesn't exist a new one is created.
 *
 * @param username Name of the user.
 * @return Found user; NULL if no more users can be created.
 */
static User_t *findUser( char *username, Data_t *data ) {
    // Guards
    if ( data->totalUsers == 0 ) {
        data->users[0] = newUser(username);
        data->totalUsers++;
        return data->users[0];
    } else if ( data->totalUsers == MAX_USERS ) {
        return NULL;
    }

    // Seek
    User_t *match = NULL;
    for ( int i = 0; i < data->totalUsers; ++i ) {
        if ( strcmp(data->users[i]->name, username) == 0 ) {
            match = data->users[i];
            break;
        }
    }

    // Create if not exists
    if ( match == NULL ) {
        size_t index = data->totalUsers++;
        match = data->users[index] = newUser(username);
    }
    return match;
}

/**
 * Loads a CSV file to use as initial values for the app.
 *
 * @return A data object with every value initialized.
 */
Data_t *loadCSVFile( void ) {
    // Open file
    FILE *fp = fopen(TRAINING_FILE, "r");
    if ( fp == NULL ) {
        fprintf(stderr, "\nError leyendo archivo de entrenamiento.\n");
        exit(EXIT_FAILURE);
    }

    // Initial setup
    Data_t *data = newData();

    // Read file
    char line[100], *token;
    while ( fgets(line, sizeof line, fp) != NULL ) {
        // Process user
        token = strtok(line, ",");
        User_t *user = findUser(token, data);

        // Process movie name
        token = strtok(NULL, ",");

        // Process ranking
        token = strtok(NULL, ",");

        // Process features
        while ( token ) {
            token = strtok(NULL, ",");
        }
    }
    fclose(fp);

    return data;
}

// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */
