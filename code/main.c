// File: main.c
// Date: 13/05/20

// ------------------------------------------
// System and application specific headers
// ------------------------------------------
#include "view.h"
#include "suggestions.h"
#include "reports.h"

int main( void ) {
	// Load data
	int op, id;
	initialGuide();
	Data_t *initialData = loadCSVFile();
	Data_t *trainedData = start_training(initialData);
	// createGraph();

	// Display data
	displayUsers(trainedData);
	displayMovies(initialData);

	// Display menu
	do {
		op = SuggestionsOptions();
		switch ( op ) {
		case 1:
			id = movieSuggestionUser(trainedData); 
			printf("Deberias ver ->   %s\n", trainedData->movies[id]->name);
			break;
		case 2:
			id = friendsSuggestions(trainedData); 
			printf("Deberias conocer a ->   %s\n", trainedData->users[id]->name);
			break;
		case 3:
			id = movieSuggestionMovie(trainedData); 
			printf("Te podria gustar ->   %s\n", trainedData->movies[id]->name);
			break;
		}
	} while( op != 4 );

	// Print in report
	print_in_file(REPORTS_FILE, trainedData);
	return 0;
}
