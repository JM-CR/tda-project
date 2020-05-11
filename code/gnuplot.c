// See gnuplot.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: gnuplot.c
// Date: 17/02/20

// ------------------------------------------
// System and application specific headers
// ------------------------------------------
#include <stdio.h>
#include <stdbool.h>
#include "gnuplot.h"


// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

bool removeFile( const char *file ) {
    if ( file != NULL && remove(file) == 0 )
        return true;
    else
        return false;
}

void saveState( const char *file, double data[], size_t size ) {
    // Append data
    FILE *fp = fopen(file, "a");
    for ( unsigned int i = 0; i < size; ++i )
        fprintf(fp, "%lf ", data[i]);

    // Close
    fprintf(fp, "\n");
    fclose(fp);
}

void plot( char *commands[], size_t size ) {
    // Open stream
    FILE *pipe;
    if ( (pipe = popen("gnuplot -persistent", "w")) == NULL )
        return;

    // Read commands
    if ( commands != NULL )
        for ( unsigned int i = 0; i < size; ++i )
            fprintf(pipe, "%s\n", commands[i]);

    // Close stream
    pclose(pipe);
}
