// File: main.c
// Date: 11/04/20

// ------------------------------------------
// System and aplication specific headers
// ------------------------------------------
#include "view.h"
#include "model.h"

int main( void ) {
	//Print report
	print_in_file(REPORTS_FILE, loadCSVFile());
	return 0;
}
