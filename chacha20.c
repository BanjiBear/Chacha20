#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>								// For tolower()


// CHEN Yi pu
// 19084858d
// Assignment 1 Question 5

// I managed to make all of the important variables to be global
const char Scheme[128] = "Chacha20 Encryption Scheme";
char the512BitBlock[17][5];
char key[33] = {0}, nonce[9] = {0}, input[1024];;
int plaintext[1024], textLength = 0, counter = 1;

void settings();								// Initialize the system
int checkInputFormat(char str[1024]);			// Check input format: only letters and spaces are allowed
void keyGeneration();							// Generate the key and print in hex-format using %x
void nonceGeneration();							// Generate the nonce and print in hex-format using %x
void inputBlockConstruction();					// Construct the 512-bit block
void Chacha20();								// The implementation of Chacha20

int main(){

	printf("Please type in the plaintext to be encrypted\n(only letters and spaces are allowed, both uppercase and lowercase are fine): \n");
	while(1){
		fgets(input, 1024, stdin);
		if(checkInputFormat(input) == (strlen(input) - 1)){
			break;
		}
		else{
			printf("Only letters and spaces are allowed in the plaintext: \n");
		}
	}
	input[strlen(input) - 1] = 0;
	textLength = strlen(input);
	//printf("%lu\n", strlen(input));			// For Debugging
	for(int i = 0; i < strlen(input) - 1; i++){
		input[i] = tolower(input[i]);
	}
	//printf("%s\n", input);					// For Debugging
	while(1){
		system("clear");
		keyGeneration();
		nonceGeneration();
		printf("%s\n", Scheme);
		//printf("%x\n", 10);					// Testing
		printf("Input                   : %s\n\n", input);
		printf("------ Encryption ------\n");
		printf("Input              (hex): ");
		for(int i = 0; i < textLength; i++){
			printf("%x", (int)(input[i]));
			if(i == textLength - 1) printf("\n");
		}
		printf("Key                (hex): ");
		for(int i = 0; i < 32; i++){
			printf("%x", (int)(key[i]));
			if(i == 31) printf("\n");
		}
		printf("nonce              (hex): ");
		for(int i = 0; i < 8; i++){
			printf("%x", (int)(nonce[i]));
			if(i == 7) printf("\n");
		}
		printf("counter            (hex): %x\n", counter);

		Chacha20();

		counter++;								// Next Encryption
		main();
	}
}

void settings(){
	system("python3 terminalSize.py");			// Use the embedded python file to re-size the terminal window
	system("clear");
	for(int i = 0; i < 4; i++){
		switch(i){
			case 0:
				the512BitBlock[i] = "expa";
				break;
			case 1:
				the512BitBlock[i] = "nd 3";
				break;
			case 2:
				the512BitBlock[i] = "2-by";
				break;
			case 3:
				the512BitBlock[i] = "te k";
				break;
		}
	}
}

int checkInputFormat(char str[1024]){
	//printf("%lu\n", strlen(str));				// For Debugging
	//printf("%d\n", (int)(str[2]));			// For Debugging
	int length = 0;
	for(int i = 0; i < strlen(str) - 1; i++){
		//printf("%d\n", (int)(str[i]));		// For Debugging
		if((int)(str[i]) == 32){length++;}		// space
		else if((int)(str[i]) > 64 && (int)(str[i]) < 91){length++;}		// A to Z
		else if((int)(str[i]) > 96 && (int)(str[i]) < 123){length++;}		// a to z
	}
	//printf("length = %d\n", length);			// For Debugging
	return length;
}

void keyGeneration(){
	for(int i = 0; i < 32; i++){
		key[i] = 'a' + (random() % 26);
	}
}

void nonceGeneration(){
	for(int i = 0; i < 8; i++){
		nonce[i] = 'a' + (random() % 26);
	}
}

void inputBlockConstruction(){
}





