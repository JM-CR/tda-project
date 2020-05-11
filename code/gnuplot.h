// Interaction with the GNUPlot utility.
// Author: Josue Mosiah Contreras Rocha
// File: gnuplot.h
// Date: 17/02/20

#ifndef GNUPLOT_H
#define GNUPLOT_H

// -----------------------------
// System headers
// -----------------------------
#include <stdio.h>
#include <stdbool.h>


// -----------------------------
// Public interface
// -----------------------------

/* Function prototypes */

/**
 * Used to delete a file created in the saveState function.
 *
 * @param file Filename.
 * @return True if the file was deleted.
 */
bool removeFile( const char *file );

/**
 * Appends data to a file using GNUPlot's format.
 *
 * @param file Filename.
 * @param data Values to write.
 * @param size Quantity of values.
 */
void saveState( const char *file, double data[], size_t size );

/**
 * Send commands to GNUPlot.
 *
 * @param commands Settings for the plot (One line per command).
 * @param size Number of commands.
 */
void plot( char *commands[], size_t size );

#endif
