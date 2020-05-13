// Functions to load data and train the recommendations app.
// Author: Josue Mosiah Contreras Rocha
// File: training.h
// Date: 11/05/20

#ifndef TRAINING_H
#define TRAINING_H

// -----------------------------
// System headers
// -----------------------------
#include <stddef.h>
#include "gnuplot.h"


// -----------------------------
// Public interface
// -----------------------------

/* Constants */

#define MAX_USERS 30       // Maximum number of users
#define MAX_MOVIES 100     // Maximum number of movies
#define MAX_WATCHED 20     // Maximum number of watched movies
#define TOTAL_FEATURES 9   // Size for the affinity vector

#define TRAINING_FILE "training_files/data.csv"

/* Types declarations */

struct movie {
    unsigned int id;
    char *name;
    double *affinity;
    size_t totalAffinity;    // Total of elements for the affinity array
};

typedef struct movie Movie_t;

struct user {
    unsigned int id;
    char *name;
    double *affinity;
    unsigned int *watchedMovies;
    unsigned int *ratings;
    size_t totalAffinity;    // Total of elements in the affinity array
    size_t watchTotal;       // Number of watched movies
};

typedef struct user User_t;

struct data {
    Movie_t **movies;
    User_t **users;
    size_t totalMovies;
    size_t totalUsers;
};

typedef struct data Data_t;

/* Function prototypes */

/**
 * Loads the "TRAINING_FILE" and initializes objects for the app.
 *
 * @return A data object with every value initialized.
 */
Data_t *loadCSVFile( void );

/**
 * Trains the data object to use in the recommendations system.
 *
 * @return Trained object.
 */
Data_t *start_training(void);

#endif
