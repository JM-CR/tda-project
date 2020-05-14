// See model.h for more info
// Author: Josue Mosiah Contreras Rocha
// File: suggestions.c
// Date: 17/02/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "suggestions.h"
#include "view.h"

// -----------------------------
// Private elements
// -----------------------------

/* Private macros and constants */

/* Private types */

/* Private global variables */

/* Private functions */

int movieSuggestionUser(Data_t *data )
{		
	int i,j, user, mayor=0;
	double total[data->totalMovies], add, temp;
	
	user = askMenuValue("Inserta el ID del Usuario: ", 1, data->totalUsers);
	//printf("Inserta el ID del Usuario : ");

	for(i=0; i<(data->totalMovies); i++)
	{
		for(j=0; j<(data->movies[0]->totalAffinity); j++)
		{
			temp = data->users[user-1]->affinity[j] * data->movies[i]->affinity[j];
			add = add + temp;
			//printf("%f ", data->movies[i]->affinity[j]);
		}
		total[i]= add;
		//printf("%f\n", total[i]);
		//printf("%d\n", data->users[user-1]->watchedMovies[j]);
		add=0;
	}
	for (int i = 0; i < data->totalMovies ; ++i)
	{
		if (total[i] > mayor) mayor = i;
	}


	return mayor;
}

int friendsSuggestions(Data_t *data)
{	
	int i,j, user, mayor=0;
	double total[data->totalUsers], add, temp;

	user = askMenuValue("Inserta el ID del Usuario: ", 1, data->totalUsers);


	for(i=0; i<(data->totalUsers); i++)
	{
		for(j=0; j<(data->users[0]->totalAffinity); j++)
		{	
			if(data->users[i]->id != (user))
			{
				temp = data->users[user-1]->affinity[j] * data->users[i]->affinity[j];
				add = add + temp;
				//printf("%f ", data->movies[i]->affinity[j]);
			
			}

		}
		total[i]= add;
		//printf("%f\n", total[i]);
		add=0;
	}

	for (int i = 0; i < data->totalUsers ; ++i)
	{
		if (total[i] > mayor) mayor = i;
	}
	return mayor;
}

int movieSuggestionMovie(Data_t *data)
{
	int i,j, movieID, mayor=0;
	double total[data->totalMovies], add, temp;
	

	movieID = askMenuValue("Inserta el ID de la pelicula: ", 1, data->totalMovies);


	for(i=0; i<(data->totalMovies); i++)
	{
		for(j=0; j<(data->movies[0]->totalAffinity); j++)
		{
			if(data->movies[i]->id != (movieID))
			{
				temp = data->movies[movieID-1]->affinity[j] * data->movies[i]->affinity[j];
				add = add + temp;
				//printf("%f ", data->movies[i]->affinity[j]);
			}
		}
		total[i]= add;
		//printf("%f\n", total[i]);
		add=0;
	}

	for (int i = 0; i < data->totalMovies ; ++i)
	{
		if (total[i] > mayor) mayor = i;
	}
	return mayor;
}

// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

