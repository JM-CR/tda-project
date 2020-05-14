// See training.h for more info
// Author: Josue Mosiah Contreras Rocha
// Author: Mariana Abigail Carmona Guzman
// File: training.c
// Date: 11/05/20

// ------------------------------------------
// System and application specific headers
// ------------------------------------------
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "training.h"


// -----------------------------
// Private elements
// -----------------------------

/* Private macros and constants */

#define PLOT_FILE "training_files/plot.dat"

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
static User_t *createUser( char *name ) {
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
static Movie_t *createMovie( char *name ) {
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
        data->users[0] = createUser(username);
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
        match = data->users[index] = createUser(username);
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
        data->movies[0] = createMovie(name);
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
        match = data->movies[index] = createMovie(name);
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

/**
 * Calculates the dot product between to vectors.
 *
 * @param size_vector Number of elements.
 * @param aff_usr Vector from the user.
 * @param aff_movie Vector from the movies.
 * @return Result.
 */
static double dot_product(int size_vector, double *aff_usr, double *aff_movie) {
    double res=0;
    for (int i = 0; i < size_vector; i++) {
       res += aff_usr[i] * aff_movie[i];
    }
    return res;
}

/**
 * Calculates the error for the training algorithm.
 *
 * @param error Variable where the results will be saved.
 * @param newValue New value to add.
 */
static void squareError( double *error, double newValue ) {
    *error += pow(newValue, 2);
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

Data_t *start_training(void){
    // Initialize
    Data_t *data = loadCSVFile();
    User_t *data_usr;
    Movie_t *data_movie;
    double res_dot_product=0, nu=0.01, nm = 0.001;
    double plotValues[2], error=0, newError = 0;  /* GNUlot */

    // Algorithm
    removeFile(PLOT_FILE);
    int flag=0,count_flag=0, currentCycle = 1;
     while (flag != 1){
        for (int i = 0; i < data->totalUsers; i++){
            data_usr = data->users[i];
            for (int j = 0; j < data_usr->watchTotal; j++) {
                data_movie = data->movies[j];
                //User dot priduct with Movie
                if (data_usr->totalAffinity == data_movie->totalAffinity) {
                    res_dot_product = dot_product(data_usr->totalAffinity, data_usr->affinity, data_movie->affinity);
                    //calculate error in training algorithm
                    newError = (double)data_usr->ratings[j] - res_dot_product;
                    squareError(&error, newError);
                    //calculate new values in affinity.
                    for (int count=0; count < data_usr->totalAffinity; count++) {
                        data_usr->affinity[count] = data_usr->affinity[count] + (nu * newError * data_movie->affinity[count]);
                        data_movie->affinity[count] = data_movie->affinity[count] + (nm * newError * data_usr->affinity[count]);
                    }
                    data->users[i] = data_usr;
                    data->movies[j] = data_movie;
                    //GNU Plot
                    if(newError<0.1 && newError>-0.1){
                        count_flag++;
                    }
                } else {
                    exit(EXIT_FAILURE);
                }
            }
        }

        // GNUplot graph
        plotValues[0] = currentCycle++;
        plotValues[1] = sqrt(error);
        saveState(PLOT_FILE, plotValues, 2);
        error = 0;

        // Exit condition
        if (count_flag == (data_usr->watchTotal * data->totalUsers)){
            flag = 1;
        } else {
            count_flag=0;
        }
    }
    return data;
}

void createGraph( void ) {
    char *commands[] = {
        "set title 'Training Error'",
        "set xlabel 'Cycles'",
        "set ylabel 'Error",
        "plot 'training_files/plot.dat' u 1:2 title '' with lines"
    };
    int length = sizeof(commands) / sizeof(char *);
    plot(commands, length);
}
