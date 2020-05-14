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
    fprintf(fp, " ________________________________________________________________________________________ \n");
}

/**
 * Generates a line in file for table rows.
 * @param file pointer
 * @return void.
 */
static void print_table_line_end(FILE *fp)
{
    fprintf(fp, "|________________________________________________________________________________________|\n");
}

/**
 * Generates a column name with strings.
 * @param file pointer, msg1, msg2, msg3
 * @return void.
 */
static void print_table_column_name(FILE *fp, char msg1[128], char msg2[128], char msg3[128])
{
    fprintf(fp, "| %-35s| %-32s| %-15s |\n", msg1, msg2, msg3);
    print_table_line_end(fp);
}

/**
 * Generates a message between tables.
 * @param file pointer
 * @return void.
 */
static void print_welcome(FILE *fp, char message[128])
{
    print_table_line(fp);
    fprintf(fp, "|%-88s|\n", " ");
    fprintf(fp, "|                            %-60s|\n", message);
    print_table_line_end(fp);
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
    unsigned int movieID;
    char affinityNames[9][50] = {
        "Acción",
        "Terror",
        "Thrillers",
        "Comedias",
        "Ciencia Ficción y Fantasía",
        "Documentales",
        "Infantiles",
        "Romance",
        "Dramas"};

    FILE *fp;
    fp = fopen(filename, "wt");

    print_welcome(fp, "Welcome to your training reports");
    fprintf(fp, "\n");
    print_table_line(fp);
    print_table_column_name(fp, "User", "Category", "Affinity");
    for (int i = 0; i < data->totalUsers; i++)
    {
        data_usr = data->users[i];
        for (int j = 0; j < data_usr->totalAffinity; j++)
        {
            if (j == 0)
            {
                fprintf(fp, "| %-35s|%-33s | %16.2f|\n", data_usr->name, affinityNames[j], data_usr->affinity[j] * 10);
            }
            else
            {
                fprintf(fp, "| %-35s|%-33s| %16.2f|\n", " ", affinityNames[j], data_usr->affinity[j] * 10);
            }
        }
        print_table_line_end(fp);
    }

    fprintf(fp, "\n\n");
    print_welcome(fp, "Favourite categories by user");
    print_table_line(fp);
    print_table_column_name(fp, "Movie", "Category", "Affinity");
    for (int i = 0; i < data->totalMovies; i++)
    {
        data_movie = data->movies[i];
        for (int j = 0; j < data_movie->totalAffinity; j++)
        {

            if (j == 0)
            {
                fprintf(fp, "| %-35s|%-33s |%17.2f|\n", data_movie->name, affinityNames[j], data_movie->affinity[j] * 10);
            }
            else
            {
                fprintf(fp, "| %-35s|%-33s|%17.2f|\n", " ", affinityNames[j], data_movie->affinity[j] * 10);
            }
        }
        print_table_line_end(fp);
    }

    fprintf(fp, "\n\n");
    print_welcome(fp, "Ratings by user");
    print_table_line(fp);
    print_table_column_name(fp, "User", "Movie", "Calc ★ | User ★");
    for (int i = 0; i < data->totalUsers; i++)
    {

        data_usr = data->users[i];
        for (int j = 0; j < data_usr->watchTotal; j++)
        {
            movieID = data_usr->watchedMovies[j] - 1;
            data_movie = data->movies[movieID];
            if (j == 0)
            {
                fprintf(fp, "| %-35s|%-33s| %-8.0f | %-4.lf |\n", data_usr->name, data_movie->name, dot_product(data_usr->totalAffinity, data_usr->affinity, data_movie->affinity), (double)data_usr->ratings[j]);
            }
            else
            {
                fprintf(fp, "| %-35s|%-33s| %-8.2f | %-4.lf |\n", " ", data_movie->name, dot_product(data_usr->totalAffinity, data_usr->affinity, data_movie->affinity), (double)data_usr->ratings[j]);
            }
        }
        print_table_line_end(fp);
    }
    fclose(fp);
}
