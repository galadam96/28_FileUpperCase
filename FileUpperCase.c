//Date: 2023.10.24
//Purpose: Converts all characters of a file to uppercase and writes the result out to a temprary file. 
//Then renames the temp file to the original file and temove the temp file.
//TL;DR: Uppercase convert overwrite old lowercase file.

#include <stdio.h>
#include <ctype.h> // for islower()

int main() {
	FILE* fp = fopen("myfile.txt","r");
	FILE* pTemp = fopen("temp.txt", "w");
	int c;

	//Error handling
	if (fp == NULL) {
		perror("There was an error opening the file");
		fclose(pTemp);
		return 1;
	}

	if (pTemp == NULL) {
		perror("There was an error opening the file");
		fclose(fp);
		return 1;
	}
	//iterate through the characters until EOF
	while ((c = fgetc(fp)) != EOF) {
		//check for lowercase, convert them to uppercase
		if (islower(c) != 0) { 
			c = c - 32; // same as toupper()
		}
		 
		fputc(c, pTemp);
		
	}

	fclose(fp);

	//removing original file
	if (remove("myfile.txt") != 0) {
		perror("Error removing original file");
		return 1;
	}
	fclose(pTemp);

	if (rename("temp.txt", "myfile.txt") != 0) {
		perror("Error renaming temporary file");
		return 1;
	}

	//open for printing the result to console

	fp = fopen("myfile.txt", "r");
	if (fp == NULL) {
		perror("There was an error opening the file");
		return 1;
	}

	while ((c = fgetc(fp)) != EOF) {
		printf("%c", c);
	}

	fclose(fp);

	fp = NULL;
	pTemp = NULL;

	return 0;
}