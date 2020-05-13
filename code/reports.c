// See reports.h for more info
// Author: Elena Ginebra Zarandona
// File: reports.h
// Date: 11/05/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include "reports.h"

// -----------------------------
// Private elements
// -----------------------------

/* Private macros and constants */

/* Private types */

/* Private global variables */

/* Private functions */

/**
 * Generates a line in file for table rows.
 * @param file pointer
 * @return void.
 */
static void print_table_line(FILE *fp)
{
    fprintf(fp, " ____________________________________________________________\n");
}

/**
 * Generates a line in file for table rows.
 * @param file pointer
 * @return void.
 */
static void print_welcome(FILE *fp)
{
    print_table_line(fp);
    fprintf(fp, "|%-60s|\n", " ");
    fprintf(fp, "|%-60s|\n", "               Welcome to your training reports");
    print_table_line(fp);
    fprintf(fp, "\n");
}

// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */
/**
 * Prints report in given file with table columns.
 * @param fp 
 * @param data_t 
 * @return void.
 */
void print_in_file(char filename[50], Data_t *data)
{
    User_t *data_usr;
    Movie_t *data_movie;

    FILE *fp;
    fp = fopen(filename, "wt");

    print_welcome(fp);
    print_table_line(fp);
    fprintf(fp, "| %-19s| %-18s| %-18s|\n", "User", "Affinity", "Ranking");
    print_table_line(fp);
    for (int i = 0; i < data->totalUsers; i++)
    {
        data_usr = data->users[i];
        data_movie = data->movies[i];
        for (int j = 0; j < data_usr->totalAffinity; j++)
        {
            if (j == 0)
            {
                fprintf(fp, "| %-19s| %-18s| %-18zu|\n", data_usr->name, data_movie->name, data_usr->watchTotal);
            } else
            {
                fprintf(fp, "| %-19s| %-18s| %-18zu|\n", "", data_movie->name, data_usr->watchTotal);
            }
            
        }
        print_table_line(fp);
    }

    fclose(fp);
}
