// See training.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: training.c
// Date: 11/05/20

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
    char *copy = calloc(strlen(name) + 1, sizeof(char));
    strcpy(copy, name);

    // Set values
    User_t *user = malloc(sizeof(User_t));
    user->id = lastID++;
    user->name = copy;
    user->affinity = randomAffinities();
    user->watchedMovies = calloc(MAX_WATCHED, sizeof(int));
    user->ratings = calloc(MAX_WATCHED, sizeof(int));
    user->totalAffinity = TOTAL_FEATURES;
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
    // Status variables
    static int lastID = 1;
    char *copy = calloc(strlen(name) + 1, sizeof(char));
    strcpy(copy, name);

    // Set values
    Movie_t *movie = malloc(sizeof(Movie_t));
    movie->id = lastID++;
    movie->name = copy;
    movie->affinity = NULL;
    movie->totalAffinity = TOTAL_FEATURES;
    return movie;
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
 * Seeks a movie in the data struct. If it doesn't exist a new one is created.
 *
 * @param name Name of the movie.
 * @return Found movie; NULL if no more movies can be created.
 */
static Movie_t *findMovie( char *name, Data_t *data ) {
    // Guards
    if ( data->totalMovies == 0 ) {
        data->movies[0] = newMovie(name);
        data->totalMovies++;
        return data->movies[0];
    } else if ( data->totalMovies == MAX_MOVIES ) {
        return NULL;
    }

    // Seek
    Movie_t *match = NULL;
    for ( int i = 0; i < data->totalMovies; ++i ) {
        if ( strcmp(data->movies[i]->name, name) == 0 ) {
            match = data->movies[i];
            break;
        }
    }

    // Create if not exists
    if ( match == NULL ) {
        size_t index = data->totalMovies++;
        match = data->movies[index] = newMovie(name);
    }
    return match;
}

/**
 * Appends a movie to a user if it hasn't been loaded before.
 *
 * @param user User where the movie will be appended.
 * @param movie Movie to append.
 * @param rating User's rating for the movie.
 */
static void appendMovie( User_t *user, Movie_t *movie, char *rating ) {
    // Guards
    if ( user == NULL || movie == NULL ) {
        return;
    }

    // Seek
    bool found = false;
    for ( int i = 0; i < user->watchTotal; ++i ) {
        if ( user->watchedMovies[i] == movie->id ) {
            found = true;
            break;
        }
    }

    // Add if not exists
    if ( !found && user->watchTotal < MAX_WATCHED ) {
        size_t index = user->watchTotal++;
        user->watchedMovies[index] = movie->id;
        user->ratings[index] = strtod(rating, NULL);
    }
}

/**
 * Sets the affinities for a movie.
 *
 * @param features Affinities to set.
 * @param movie Movie where the affinities will be set.
 */
static void setFeatures( char *features[], Movie_t *movie ) {
    // Guard
    if ( movie->affinity != NULL || movie == NULL ) {
        return;
    }

    // Set
    movie->affinity = calloc(TOTAL_FEATURES, sizeof(double));
    for ( int i = 0; i < TOTAL_FEATURES; ++i ) {
        movie->affinity[i] = strtod(features[i], NULL);
    }
}


// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

Data_t *loadCSVFile( void ) {
    // Open file
    FILE *fp = fopen(TRAINING_FILE, "r");
    if ( fp == NULL ) {
        fprintf(stderr, "\nError leyendo archivo de entrenamiento.\n");
        exit(EXIT_FAILURE);
    }

    // Read file
    Data_t *data = newData();
    char line[100], *token;
    while ( fgets(line, sizeof line, fp) != NULL ) {
        // Process user
        token = strtok(line, ",");  /* Username */
        User_t *user = findUser(token, data);

        // Process movie
        token = strtok(NULL, ",");  /* Movie name */
        Movie_t *movie = findMovie(token, data);
        token = strtok(NULL, ",");  /* Rating */
        appendMovie(user, movie, token);

        // Process features
        int index = 0;
        char *features[TOTAL_FEATURES];
        while ( token ) {
            features[index++] = token = strtok(NULL, ",");  /* Features */
        }
        setFeatures(features, movie);
    }

    // Clean up
    fclose(fp);
    return data;
}
