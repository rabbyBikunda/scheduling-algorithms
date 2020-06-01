#include <stdio.h>
#include <string.h>

//code taken from notes
void clear_stdin() {

	int c;
	//put value from getchar into c and check if value is not equal to a new line
	while((c = getchar()) != '\n');
}

void fgets_str_stdin(char* dest, size_t max) {

	fgets(dest, max, stdin);

	char* first_newline = strchr(dest, '\n');

	//if the newline is not found
	if(first_newline == NULL){
		//clear the buffer
		clear_stdin();

	}
	else {
  	*first_newline = '\0';
	}

}
