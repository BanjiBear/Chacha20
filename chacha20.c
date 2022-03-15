#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>                              // For tolower()
#include <time.h>                               // For srand()


// CHEN Yi pu
// 19084858d
// Assignment 1 Question 5

// I managed to make all of the important variables to be global
const char Scheme[128] = "Chacha20 Encryption Scheme";
char * the512BitBlock[17] = {"65787061", "6e642033", "322d6279", "7465206b"};
char key[33] = {0}, nonce[9] = {0}, input[1024];
int plaintext[1024], textLength = 0, counter = 1;

void settings(int mode);                        // Initialize the system
int checkInputFormat(char str[1024]);           // Check input format: only letters and spaces are allowed
void keyGenerator();                            // Generate the key and print in hex-format using %x
void nonceGenerator();                          // Generate the nonce and print in hex-format using %x
void inputBlockConstruction();                  // Construct the 512-bit block -> Calls toHex()
void toHex(char block[4], int n);
void Chacha20();                                // The implementation of Chacha20
void QUARTERROUND(char blockA[8], char blockB[8], char blockC[8], char blockD[8]);

int main(){

	settings(0);
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
	//printf("%lu\n", strlen(input));           // For Debugging
	for(int i = 0; i < strlen(input) - 1; i++){
		input[i] = tolower(input[i]);
	}
	//printf("%s\n", input);                    // For Debugging
	while(1){
		system("clear");
		keyGenerator();
		nonceGenerator();
		settings(1);
		inputBlockConstruction();
		Chacha20();

		counter++;                              // Next Encryption
		break;
	}
}

void settings(int mode){
	switch(mode){
		case 0:
			system("python3 terminalSize.py");  // Use the embedded python file to re-size the terminal window
			system("clear");
			break;
		case 1:
			printf("%s\n", Scheme);
			//printf("%x\n", 10);               // Testing
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
			break;
	}
}

int checkInputFormat(char str[1024]){
	//printf("%lu\n", strlen(str));             // For Debugging
	//printf("%d\n", (int)(str[2]));            // For Debugging
	int length = 0;
	for(int i = 0; i < strlen(str) - 1; i++){
		//printf("%d\n", (int)(str[i]));        // For Debugging
		if((int)(str[i]) == 32){length++;}      // space
		else if((int)(str[i]) > 64 && (int)(str[i]) < 91){length++;}        // A to Z
		else if((int)(str[i]) > 96 && (int)(str[i]) < 123){length++;}       // a to z
	}
	//printf("length = %d\n", length);          // For Debugging
	return length;
}

void keyGenerator(){
	srand (time(0));
	for(int i = 0; i < 32; i++){
		key[i] = 'a' + (rand() % 26);
	}
}

void nonceGenerator(){
	srand (rand());
	for(int i = 0; i < 8; i++){
		nonce[i] = 'a' + (rand() % 26);
	}
}

void inputBlockConstruction(){
	char buffer[5] = {0};
	int index = 0;
	/*
	for(int i = 0; i < 16; i++){
		printf("the512BitBlock[%d] = %s\n", i, the512BitBlock[i]);
	}
	*/
	for(int i = 4; i < 12; i++){                                            // block 4 to 11, 8 key block
		for(int j = 0; j < 4; j++){
			buffer[j] = key[index];
			index++;
		}
		the512BitBlock[i] = strdup(buffer);                                 // https://stackoverflow.com/questions/3972453/array-of-strings-overwriting-each-other
	}
	index = 0;
	for(int i = 14; i < 16; i++){                                           // block 14 and 15, 2 nonce block
		for(int j = 0; j < 4; j++){
			buffer[j] = nonce[index];
			index++;
		}
		//printf("buffer = %s\n", buffer);                                  // For Debugging
		the512BitBlock[i] = strdup(buffer);                                 // https://stackoverflow.com/questions/3972453/array-of-strings-overwriting-each-other
		//printf("the512BitBlock = %s\n", the512BitBlock[i]);               // For Debugging
	}
	the512BitBlock[12] = "00000000";
	the512BitBlock[13] = "00000001";
	//printf("%d\n", atoi(the512BitBlock[13]));                             // Testing
	for(int i = 4; i < 16; i++){
		if(i == 12 || i == 13) continue;
		toHex(the512BitBlock[i], i);
	}
}

void toHex(char block[4], int n){
	char buffer[9] = {0};
	int index = 0;
	for(int i = 0; i < 4; i++){
		if(block[i] == 'a'){buffer[index] = '6'; buffer[index + 1] = '1';}
		else if(block[i] == 'a'){buffer[index] = '6'; buffer[index + 1] = '1';}
		else if(block[i] == 'b'){buffer[index] = '6'; buffer[index + 1] = '2';}
		else if(block[i] == 'c'){buffer[index] = '6'; buffer[index + 1] = '3';}
		else if(block[i] == 'd'){buffer[index] = '6'; buffer[index + 1] = '4';}
		else if(block[i] == 'e'){buffer[index] = '6'; buffer[index + 1] = '5';}
		else if(block[i] == 'f'){buffer[index] = '6'; buffer[index + 1] = '6';}
		else if(block[i] == 'g'){buffer[index] = '6'; buffer[index + 1] = '7';}
		else if(block[i] == 'h'){buffer[index] = '6'; buffer[index + 1] = '8';}
		else if(block[i] == 'i'){buffer[index] = '6'; buffer[index + 1] = '9';}
		else if(block[i] == 'j'){buffer[index] = '6'; buffer[index + 1] = 'A';}
		else if(block[i] == 'k'){buffer[index] = '6'; buffer[index + 1] = 'B';}
		else if(block[i] == 'l'){buffer[index] = '6'; buffer[index + 1] = 'C';}
		else if(block[i] == 'm'){buffer[index] = '6'; buffer[index + 1] = 'D';}
		else if(block[i] == 'n'){buffer[index] = '6'; buffer[index + 1] = 'E';}
		else if(block[i] == 'o'){buffer[index] = '6'; buffer[index + 1] = 'F';}
		else if(block[i] == 'p'){buffer[index] = '7'; buffer[index + 1] = '0';}
		else if(block[i] == 'q'){buffer[index] = '7'; buffer[index + 1] = '1';}
		else if(block[i] == 'r'){buffer[index] = '7'; buffer[index + 1] = '2';}
		else if(block[i] == 's'){buffer[index] = '7'; buffer[index + 1] = '3';}
		else if(block[i] == 't'){buffer[index] = '7'; buffer[index + 1] = '4';}
		else if(block[i] == 'u'){buffer[index] = '7'; buffer[index + 1] = '5';}
		else if(block[i] == 'v'){buffer[index] = '7'; buffer[index + 1] = '6';}
		else if(block[i] == 'w'){buffer[index] = '7'; buffer[index + 1] = '7';}
		else if(block[i] == 'x'){buffer[index] = '7'; buffer[index + 1] = '8';}
		else if(block[i] == 'y'){buffer[index] = '7'; buffer[index + 1] = '9';}
		else if(block[i] == 'z'){buffer[index] = '7'; buffer[index + 1] = 'A';}
		index = index + 2;
	}
	the512BitBlock[n] = strdup(buffer);
}

void Chacha20(){
	// 20 rounds, 2 rounds per loop
	// column
	//printf("%c\n", the512BitBlock[0][1]);                                 // Testing
	QUARTERROUND(the512BitBlock[0], the512BitBlock[4], the512BitBlock[8], the512BitBlock[12]);
	//QUARTERROUND(the512BitBlock[1], the512BitBlock[5], the512BitBlock[9], the512BitBlock[13]);
	//QUARTERROUND(the512BitBlock[2], the512BitBlock[6], the512BitBlock[10], the512BitBlock[14]);
	//QUARTERROUND(the512BitBlock[3], the512BitBlock[7], the512BitBlock[11], the512BitBlock[15]);
	// diagonal
	//QUARTERROUND(the512BitBlock[0], the512BitBlock[5], the512BitBlock[10], the512BitBlock[15]);
	//QUARTERROUND(the512BitBlock[1], the512BitBlock[6], the512BitBlock[11], the512BitBlock[12]);
	//QUARTERROUND(the512BitBlock[2], the512BitBlock[7], the512BitBlock[8], the512BitBlock[13]);
	//QUARTERROUND(the512BitBlock[3], the512BitBlock[4], the512BitBlock[9], the512BitBlock[14]);
}

void QUARTERROUND(char blockA[8], char blockB[8], char blockC[8], char blockD[8]){
	char buffer[9] = {0};
	//printf("%s %s %s %s\n", blockA, blockB, blockC, blockD);              // Testing
	//printf("%c\n", (char)(23));                                           // Testing

	/*
		Not Used now!!
		https://stackoverflow.com/questions/7863499/conversion-of-char-to-binary-in-c
		https://www.geeksforgeeks.org/putchar-function-in-c/
	*/

	//a += b;
	//printf("%s ", blockA);                                                // For debugging
	for(int i = 7; i > -1; i--){
		//printf("%c ", blockA[i]);                                         // For debugging
	}
}







