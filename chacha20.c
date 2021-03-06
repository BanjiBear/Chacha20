#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>                              // For tolower()
#include <time.h>                               // For srand()
#include <unistd.h>                             // For sleep()


// CHEN Yi pu
// 19084858d
// Assignment 1 Question 5

// I managed to make all of the important variables to be global
const char Scheme[128] = "Chacha20 Encryption Scheme";
const char * testCases[5] = {"My name is Tommy and I am a year three student", "Azamat can you please meet me after the lecture", "Action Code AFXCS kill the man in black", "ten tons of drugs have arrived at the harbor", "Q is discovered kill him at all cost"};
char key[33] = {0}, nonce[9] = {0}, input[1024], inputHex[2048] = {0};
char * the512BitBlock[17] = {"65787061", "6E642033", "322D6279", "7465206B"};
char cipherSequence[129] = "";
int textLength = 0, counter = 1, modeBit, printBit = 0;

void getInput();
void settings(int mode);                        // Initialize the system
int checkInputFormat(char str[1024]);           // Check input format: only letters and spaces are allowed
void keyGenerator();                            // Generate the key and print in hex-format using %x
void nonceGenerator();                          // Generate the nonce and print in hex-format using %x
void inputBlockConstruction();                  // Construct the 512-bit block -> Calls toHex()
void toHex(char block[4], int n);

void Chacha20();                                // The implementation of Chacha20
void QUARTERROUND(int A, int B, int C, int D);
void binaryAddition(char blockA[8], char blockB[8], int A);
void XOR(char blockD[8], char blockA[8], int D);
void bitRotation(char blockD[8], int rotation, int D);

void encryption();

void printDetailOutput(int A, int B, int mode);

int main(int argc, char *argv[]){

	modeBit = atoi(argv[1]);
	//printf("%d\n", modeBit);
	if(counter == 1) settings(0);
	
	while(counter < 6){
		
		if(modeBit == 1 || modeBit == 3){
			getInput();
			system("clear");
		}
		else if(modeBit == 2){
			strcpy(input, testCases[counter - 1]);
			textLength = strlen(input);
			//printf("%lu\n", strlen(input));           // For Debugging
			for(int i = 0; i < strlen(input) - 1; i++){
				input[i] = tolower(input[i]);
			}
		}
		else break;

		keyGenerator();
		nonceGenerator();
		settings(1);
		inputBlockConstruction();
		Chacha20();
		settings(2);

		encryption();
		settings(3);

		counter++;                              // Next Encryption
		if(modeBit == 1 || modeBit == 3) break;
		/*
		char iteration[9] = {0};
		strcpy(iteration, "00000001");
		binaryAddition(the512BitBlock[13], iteration, 13);
		*/
		for(int i = 0; i < 1024; i++){input[i] = 0;}
		for(int i = 0; i < 2048; i++){inputHex[i] = 0;}
		for(int i = 0; i < 129; i++){cipherSequence[i] = 0;}
		for(int i = 4; i < 16; i++){the512BitBlock[i] = 0;}
		the512BitBlock[0] = "65787061";
		the512BitBlock[1] = "6E642033";
		the512BitBlock[2] = "322D6279";
		the512BitBlock[3] = "7465206B";

		sleep(2);
	}
}

void getInput(){
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
	//system("clear");
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
			if(modeBit == 2) printf("Plaintext               : %s\n", testCases[counter - 1]);
			printf("Input                   : %s\n", input);
			printf("------ Encryption ------\n");
			printf("Input              (hex): ");
			for(int i = 0; i < textLength; i++){
				printf("%x", (int)(input[i]));
			}
			printf("\n");
			printf("Key                (hex): ");
			for(int i = 0; i < 32; i++){
				printf("%x", (int)(key[i]));
			}
			printf("\n");
			printf("nonce              (hex): ");
			for(int i = 0; i < 8; i++){
				printf("%x", (int)(nonce[i]));
			}
			printf("\n");
			printf("counter            (hex): %x\n", counter);
			break;
		case 2:
			printf("Cipher Sequence    (hex): ");
			for(int i = 0; i < 16; i++){
				printf("%s", the512BitBlock[i]);
			}
			printf("\n");
			break;
		case 3:
			printf("\n");
			printf("Ciphertext         (hex): ");
			printf("%s\n", cipherSequence);
			printf("------------------------\n\n");
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
	for(int i = 0; i < counter - 1; i++){
		binaryAddition(the512BitBlock[13], "00000001", 13);
	}
	/*
	for(int i = 0; i < 16; i++){
		printf("%s ", the512BitBlock[i]);
	}
	printf("\n");
	*/
	//printf("%d\n", atoi(the512BitBlock[13]));                             // Testing
	for(int i = 4; i < 16; i++){
		if(i == 12 || i == 13) continue;
		toHex(the512BitBlock[i], i);
	}
	
	printf("--Input 512-bit blocks--\n");
	printf("block [0] to [15]  (hex): ");
	for(int i = 0; i < 16; i++){
		printf("%s ", the512BitBlock[i]);
	}
	printf("\n");
	
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
	//printf("%c\n", the512BitBlock[0][1]);                                 // Testing
	for (int i = 0; i < 10; i++){
		if(modeBit == 3 && i == 0){
			printf("\n");
			printf("-------- Round %d --------\n", i + 1);
		}
		// 20 rounds, 2 rounds per loop
		// column
		QUARTERROUND(0, 4, 8, 12); printBit = 1;
		QUARTERROUND(1, 5, 9, 13);
		QUARTERROUND(2, 6, 10, 14);
		QUARTERROUND(3, 7, 11, 15);
		// diagonal
		QUARTERROUND(0, 5, 10, 15);
		QUARTERROUND(1, 6, 11, 12);
		QUARTERROUND(2, 7, 8, 13);
		QUARTERROUND(3, 4, 9, 14);
	}
}

void QUARTERROUND(int A, int B, int C, int D){
	
	//printf("%s %s %s %s\n", blockA, blockB, blockC, blockD);              // Testing
	//printf("%c\n", (char)(23));                                           // Testing

	//a += b;
	binaryAddition(the512BitBlock[A], the512BitBlock[B], A); if(modeBit == 3 && printBit == 0){printDetailOutput(A, B, 1);}
	/*
		Not Used now!!
		https://stackoverflow.com/questions/7863499/conversion-of-char-to-binary-in-c
		https://www.geeksforgeeks.org/putchar-function-in-c/
	*/

	//d ^= a;
	XOR(the512BitBlock[D], the512BitBlock[A], D); if(modeBit == 3 && printBit == 0){printDetailOutput(D, A, 2);}
	//ROT_L32(d, 16);
	bitRotation(the512BitBlock[D], 16, D); if(modeBit == 3 && printBit == 0){printDetailOutput(D, 16, 3); printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");}

	binaryAddition(the512BitBlock[C], the512BitBlock[D], C); if(modeBit == 3 && printBit == 0){printDetailOutput(C, D, 1);}
	XOR(the512BitBlock[B], the512BitBlock[C], B); if(modeBit == 3 && printBit == 0){printDetailOutput(B, C, 2);}
	bitRotation(the512BitBlock[B], 12, B); if(modeBit == 3 && printBit == 0){printDetailOutput(B, 12, 3); printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");}

	binaryAddition(the512BitBlock[A], the512BitBlock[B], A); if(modeBit == 3 && printBit == 0){printDetailOutput(A, B, 1);}
	XOR(the512BitBlock[D], the512BitBlock[A], D); if(modeBit == 3 && printBit == 0){printDetailOutput(D, A, 2);}
	bitRotation(the512BitBlock[D], 8, D); if(modeBit == 3 && printBit == 0){printDetailOutput(D, 8, 3); printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");}

	binaryAddition(the512BitBlock[C], the512BitBlock[D], C); if(modeBit == 3 && printBit == 0){printDetailOutput(C, D, 1);}
	XOR(the512BitBlock[B], the512BitBlock[C], B); if(modeBit == 3 && printBit == 0){printDetailOutput(B, C, 2);}
	bitRotation(the512BitBlock[B], 7, B); if(modeBit == 3 && printBit == 0){printDetailOutput(B, 7, 3); 	printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");}

	if(modeBit == 3 && printBit == 0){
		printf("---- Round 1 results ----\n");
		printf("block [0] to [15]  (hex): ");
		for(int i = 0; i < 16; i++){
			printf("%s ", the512BitBlock[i]);
		}
		printf("\n\n");
	}
}

void binaryAddition(char blockA[8], char blockB[8], int A){
	char buffer[9] = {0};
	int a = 0, b = 0, carry = 0;
	//a += b;
	//printf("blockA = %s\n", blockA);                                      // For debugging
	//printf("blockB = %s\n", blockB);                                      // For debugging
	for(int i = 7; i > -1; i--){
		//printf("%c\n", blockA[i]);                                        // For debugging
		if((int)(blockA[i]) > 47 && (int)(blockA[i]) < 58){/*printf("1\n");*/ a = blockA[i] - '0';} // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
		else if(blockA[i] == 'A'){/*printf("2\n");*/ a = 10;}
		else if(blockA[i] == 'B'){/*printf("3\n");*/ a = 11;}
		else if(blockA[i] == 'C'){/*printf("4\n");*/ a = 12;}
		else if(blockA[i] == 'D'){/*printf("5\n");*/ a = 13;}
		else if(blockA[i] == 'E'){/*printf("6\n");*/ a = 14;}
		else if(blockA[i] == 'F'){/*printf("7\n");*/ a = 15;}
		if((int)(blockB[i]) > 47 && (int)(blockB[i]) < 58){/*printf("8\n");*/ b = blockB[i] - '0';} // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
		else if(blockB[i] == 'A'){/*printf("9\n");*/ b = 10;}
		else if(blockB[i] == 'B'){/*printf("10\n");*/ b = 11;}
		else if(blockB[i] == 'C'){/*printf("11\n");*/ b = 12;}
		else if(blockB[i] == 'D'){/*printf("12\n");*/ b = 13;}
		else if(blockB[i] == 'E'){/*printf("13\n");*/ b = 14;}
		else if(blockB[i] == 'F'){/*printf("14\n");*/ b = 15;}

		a = a + b + carry;
		/*printf("15\n");*/
		if(a < 10){/*printf("16\n");*/ buffer[i] = a + '0';}                // https://www.delftstack.com/howto/c/convert-int-to-char/
		else{
			carry = a / 16;                                                 // For the next iteration
			if((a % 16) < 10){/*printf("17\n");*/ buffer[i] = (a % 16) + '0';}
			else if((a % 16) == 10){/*printf("18\n");*/ buffer[i] = 'A';}
			else if((a % 16) == 11){/*printf("19\n");*/ buffer[i] = 'B';}
			else if((a % 16) == 12){/*printf("20\n");*/ buffer[i] = 'C';}
			else if((a % 16) == 13){/*printf("21\n");*/ buffer[i] = 'D';}
			else if((a % 16) == 14){/*printf("22\n");*/ buffer[i] = 'E';}
			else if((a % 16) == 15){/*printf("23\n");*/ buffer[i] = 'F';}
		}
	}
	the512BitBlock[A] = strdup(buffer);
	//printf("buffer = %s\n", buffer);                                      // For debugging
	//printf("blockA = %s\n", blockA);                                      // For debugging (Not available now)
	//printf("blockB = %s\n", blockB);                                      // For debugging
}

void XOR(char blockD[8], char blockA[8], int D){
	char buffer[9] = {0};
	int d = 0, a = 0;
	//d ^= a;
	//printf("blockD = %s\n", blockD);                                      // For debugging
	//printf("blockA = %s\n", blockA);                                      // For debugging
	for(int i = 7; i > -1; i--){
		//printf("%c\n", blockD[i]);                                        // For debugging
		if((int)(blockD[i]) > 47 && (int)(blockD[i]) < 58){/*printf("1\n");*/ d = blockD[i] - '0';} // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
		else if(blockD[i] == 'A'){/*printf("2\n");*/ d = 10;}
		else if(blockD[i] == 'B'){/*printf("3\n");*/ d = 11;}
		else if(blockD[i] == 'C'){/*printf("4\n");*/ d = 12;}
		else if(blockD[i] == 'D'){/*printf("5\n");*/ d = 13;}
		else if(blockD[i] == 'E'){/*printf("6\n");*/ d = 14;}
		else if(blockD[i] == 'F'){/*printf("7\n");*/ d = 15;}
		if((int)(blockA[i]) > 47 && (int)(blockA[i]) < 58){/*printf("8\n");*/ a = blockA[i] - '0';} // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
		else if(blockA[i] == 'A'){/*printf("9\n");*/ a = 10;}
		else if(blockA[i] == 'B'){/*printf("10\n");*/ a = 11;}
		else if(blockA[i] == 'C'){/*printf("11\n");*/ a = 12;}
		else if(blockA[i] == 'D'){/*printf("12\n");*/ a = 13;}
		else if(blockA[i] == 'E'){/*printf("13\n");*/ a = 14;}
		else if(blockA[i] == 'F'){/*printf("14\n");*/ a = 15;}

		d = d ^ a;
		/*printf("15\n");*/
		if(d < 10){/*printf("16\n");*/ buffer[i] = d + '0';}                // https://www.delftstack.com/howto/c/convert-int-to-char/
		else{
			if(d == 10){/*printf("18\n");*/ buffer[i] = 'A';}
			else if(d == 11){/*printf("19\n");*/ buffer[i] = 'B';}
			else if(d == 12){/*printf("20\n");*/ buffer[i] = 'C';}
			else if(d == 13){/*printf("21\n");*/ buffer[i] = 'D';}
			else if(d == 14){/*printf("22\n");*/ buffer[i] = 'E';}
			else if(d == 15){/*printf("23\n");*/ buffer[i] = 'F';}
		}
	}
	the512BitBlock[D] = strdup(buffer);
	//printf("buffer = %s\n", buffer);                                      // For debugging
	//printf("blockD = %s\n", blockD);                                      // For debugging (Not available now)
	//printf("blockA = %s\n", blockA);                                      // For debugging
}

void bitRotation(char blockD[8], int rotation, int D){
	const char * hexToBinary[16] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
	const char hex[16] = {"0123456789ABCDEF"};
	char buffer[9] = {0};
	char binaryConversionBuffer[33] = "" /*For 0s and 1s*/, rotatedBuffer[33] = {0}; /*For rotation*/
	int lettersToBeMoved = 0, index = 0;
	if(rotation % 4 == 0){
		lettersToBeMoved = rotation / 4;
		//printf("lettersToBeMoved = %d\n", lettersToBeMoved);
		// e.g. CAE3D8CF, rotation = 16, lettersToBeMoved = 4
		for(int i = lettersToBeMoved; i < 8; i++){
			buffer[index] = blockD[i];
			index++;
		}
		for(int i = 0; i < lettersToBeMoved; i++){
			// !!!!! No need to re-initialize index to 0 --> THINK!!!!
			buffer[index] = blockD[i];
			index++;
		}
	}
	else{
		//printf("blockD = %s\n", blockD);
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 16; j++){
				if(blockD[i] == hex[j]){
					strcat(binaryConversionBuffer, hexToBinary[j]);
				}
			}
		}
		//printf("Binary Buffer = %s\n", binaryConversionBuffer);
		// Rotate
		// e.g. 01101111011001010111011001100101
		for(int i = rotation; i < 32; i++){
			rotatedBuffer[index] = binaryConversionBuffer[i];
			index++;
		}
		for(int i = 0; i < rotation; i++){
			// !!!!! No need to re-initialize index to 0 --> THINK!!!!
			rotatedBuffer[index] = binaryConversionBuffer[i];
			index++;
		}
		//printf("Rotated Buffer = %s\n", rotatedBuffer);
		char temp[5] = {0};
		index = 0;
		for(int i = 0; i < 8; i++){
			for(int j = 0; j < 4; j++){
				temp[j] = rotatedBuffer[index];
				index++;
			}
			//printf("temp = %s\n", temp);
			for(int p = 0; p < 16; p++){
				if(strcmp(temp, hexToBinary[p]) == 0){
					buffer[i] = hex[p];
					break;
				}
			}
		}
		//printf("buffer = %s\n", buffer);
	}
	the512BitBlock[D] = strdup(buffer);
	//printf("buffer = %s\n", buffer);
}

void encryption(){
	char buffer[9] = {0};
	int decimal, index = 0;
	for(int i = 0; i < textLength; i++){
		if(input[i] == ' '){
			inputHex[index] = '2';
			inputHex[index + 1] = '0';
			index = index + 2;
			continue;
		}
		decimal = (int)(input[i]);
		if(decimal > 111){
			inputHex[index] = '7';
			index++;
			//strcat(inputHex, "7");
			decimal = decimal - 112;
		}
		else{
			inputHex[index] = '6';
			index++;
			//strcat(inputHex, "6");
			decimal = decimal - 96;
		}

		if(decimal < 10){
			inputHex[index] = decimal + '0';
			index++;
			//strcat(inputHex, decimal + '0');
		}
		else{
			switch(decimal){
				case 10: inputHex[index] = 'A'; index++; break;
				case 11: inputHex[index] = 'B'; index++; break;
				case 12: inputHex[index] = 'C'; index++; break;
				case 13: inputHex[index] = 'D'; index++; break;
				case 14: inputHex[index] = 'E'; index++; break;
				case 15: inputHex[index] = 'F'; index++; break;
			}
		}
	}
	//printf("%s\n", inputHex);

	for(int i = 0; i < 16; i++){
		strcat(cipherSequence, the512BitBlock[i]);
	}
	//printf("%s\n", cipherSequence);

	index = strlen(cipherSequence) - 1;
	int p, q;
	for(int i = strlen(inputHex) - 1; i > -1; i--){
		if((int)(inputHex[i]) > 47 && (int)(inputHex[i]) < 58){/*printf("1\n");*/ p = inputHex[i] - '0';} // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
		else if(inputHex[i] == 'A'){/*printf("2\n");*/ p = 10;}
		else if(inputHex[i] == 'B'){/*printf("3\n");*/ p = 11;}
		else if(inputHex[i] == 'C'){/*printf("4\n");*/ p = 12;}
		else if(inputHex[i] == 'D'){/*printf("5\n");*/ p = 13;}
		else if(inputHex[i] == 'E'){/*printf("6\n");*/ p = 14;}
		else if(inputHex[i] == 'F'){/*printf("7\n");*/ p = 15;}
		if((int)(cipherSequence[index]) > 47 && (int)(cipherSequence[index]) < 58){/*printf("8\n");*/ q = cipherSequence[index] - '0';} // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
		else if(cipherSequence[index] == 'A'){/*printf("9\n");*/ q = 10;}
		else if(cipherSequence[index] == 'B'){/*printf("10\n");*/ q = 11;}
		else if(cipherSequence[index] == 'C'){/*printf("11\n");*/ q = 12;}
		else if(cipherSequence[index] == 'D'){/*printf("12\n");*/ q = 13;}
		else if(cipherSequence[index] == 'E'){/*printf("13\n");*/ q = 14;}
		else if(cipherSequence[index] == 'F'){/*printf("14\n");*/ q = 15;}
		//printf("%d\n", p);
		//printf("%d\n", q);
		q = p ^ q;
		//printf("%d\n", q);

		if(q < 10){/*printf("16\n");*/ cipherSequence[index] = q + '0';} // https://www.delftstack.com/howto/c/convert-int-to-char/
		else{
			if(q == 10){/*printf("18\n");*/ cipherSequence[index] = 'A';}
			else if(q == 11){/*printf("19\n");*/ cipherSequence[index] = 'B';}
			else if(q == 12){/*printf("20\n");*/ cipherSequence[index] = 'C';}
			else if(q == 13){/*printf("21\n");*/ cipherSequence[index] = 'D';}
			else if(q == 14){/*printf("22\n");*/ cipherSequence[index] = 'E';}
			else if(q == 15){/*printf("23\n");*/ cipherSequence[index] = 'F';}
		}
		index--;
	}
	//printf("%s\n", inputHex);
	//printf("%s\n", cipherSequence);
}

void printDetailOutput(int A, int B, int mode){

	switch(mode){
		case 1:
			printf("Binary Addition    (hex): ");
			for(int i = 0; i < 16; i++){
				printf("%s ", the512BitBlock[i]);
			}
			break;
		case 2:
			printf("XOR                (hex): ");
			for(int i = 0; i < 16; i++){
				printf("%s ", the512BitBlock[i]);
			}
			break;
		case 3:
			printf("Bit Rotation       (hex): ");
			for(int i = 0; i < 16; i++){
				printf("%s ", the512BitBlock[i]);
			}
			break;
	}

	printf("\n");
}





