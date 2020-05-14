// File: main.c
// Date: 10/05/20

// ------------------------------------------
// System and application specific headers
// ------------------------------------------
#include "view.h"
#include "suggestions.h"
#include "reports.h"

int main( void ) {
	// Load data
	initialGuide();
	Data_t *data = start_training();
	createGraph();

	// Print report
	print_in_file(REPORTS_FILE, data);
	return 0;
}
