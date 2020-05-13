// Library to do reports at the end of the execution.
// Author: Elena Ginebra Zarandona
// File: reports.h
// Date: 11/05/20

#ifndef REPORTS_H
#define REPORTS_H

// -----------------------------
// System headers
// -----------------------------
#include "training.h"


// -----------------------------
// Public interface
// -----------------------------

/* Constants */
#define REPORTS_FILE "training_files/report.txt"

/* Types declarations */

/* Global variables */

/* Function prototypes */

/**
 * Function's documentation.
 */
void print_in_file(char filename[50], Data_t *data);

#endif
