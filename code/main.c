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
	Data_t *data = start_training();
	createGraph();

	op = SuggestionsOptions();
	if(op==1) 
    {
        id = movieSuggestionUser(data); 
		printf("Deberias ver ->   %s\n", data->movies[id]->name);
    }
	if(op==2) 
    {
        id = friendsSuggestions(data); 
		printf("Deberias conocer a ->   %s\n", data->users[id]->name);
    }
	if(op==3) 
    {
        id = movieSuggestionMovie(data); 
		printf("Te podria gustar ->   %s\n", data->movies[id]->name);
    }

	// Print in report
	print_in_file(REPORTS_FILE, data);
	return 0;
}
