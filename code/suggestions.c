// See suggestions.h for more info
// Author: Ivan Josue Guzman Felix
// File: suggestions.c
// Date: 10/05/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "suggestions.h"

// -----------------------------
// Private elements
// -----------------------------

/* Private macros and constants */

/* Private types */

/* Private global variables */

/* Private functions */

void movieSuggestionUser(Data_t *data )
{		
	int i,j, user;
	double total[data->totalMovies], add, temp;
	printf("Test movieSuggestionUser\n");
	

	printf("Insert User's ID: ");
	scanf("%d", &user);


	for(i=0; i<(data->totalMovies); i++)
	{
		for(j=0; j<(data->movies[0]->totalAffinity); j++)
		{
			temp = data->users[user-1]->affinity[j] * data->movies[i]->affinity[j];
			add = add + temp;
			//printf("%f ", data->movies[i]->affinity[j]);
		}
		total[i]= add;
		printf("%f\n", total[i]);
		add=0;
	}
	
}

void friendsSuggestions(Data_t *data)
{	
	int i,j, user;
	double total[data->totalUsers], add, temp;
	printf("Test friendsSuggestion\n");

	printf("Insert User's ID: ");
	scanf("%d", &user);


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
		printf("%f\n", total[i]);
		add=0;
	}

}

void movieSuggestionMovie(Data_t *data)
{
	int i,j, movieID;
	double total[data->totalMovies], add, temp;
	printf("Test movieSuggestionMovie\n");
	

	printf("Insert Movie's ID: ");
	scanf("%d", &movieID);


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
		printf("%f\n", total[i]);
		add=0;
	}
	
}

// -----------------------------
// Public elements
// -----------------------------

/* Implementation of the public functions */

