// Template to create C libraries.
// Author: Josue Mosiah Contreras Rocha
// File: training.h
// Date: 17/02/20

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
    size_t totalAffinity;    // Total of elements for the affinity array
    unsigned int *watchedMovies;
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

/* Global variables */

/* Function prototypes */

/**
 * Function's documentation.
 */

#endif
