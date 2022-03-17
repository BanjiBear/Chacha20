# Chacha20
This repository stores the code for Chacha20 implementation written in C.  
The code is written for COMP3334 Computer System Security assignment 1 at Hong Kong Polytechnic University.  

# Installation and Execution
Though the code is not done yet, it can still be executed. The current version is only executable on MAC OS.  
To run the Chacha20, open the terminal and type
```shell
cc chacha20.c -o chacha20
./chacha20
```
Simply follow the instruction given on the screen!  
***NOTE: Please make sure that the chacha20.c file is in the same directory as the terminalSize.py file***

# Author
[CHEN Yi pu(Tommy)](https://github.com/BanjiBear)

# To-do
The assignment is still in the development phase
- [x] main two while-loop
- [x] int checkInputFormat(char str[1024]);
- [x] void keyGeneration();
- [x] void nonceGeneration();
- [x] ~~Errors in settings(): The i will be regard as the second integer of the 2D array~~
- [x] void inputBlockConstruction(); -> Then convert all char into decimal value
- [x] void Chacha20();
- [x] void quarterRound(A, B, C, D);
- [x] bitRotation() -> 7: Convert into binary, rotate and convert back (Think some better approach)
- [x] counter++
- [x] 5 test cases
- [ ] ~~detail output text file, input output text file~~

- [x] See if it is necessary to implement all trifle stuff in settings.

# Some websites for personal reference
- [ASCII Table](https://www.asciitable.com/)
- ~~[Convert an Integer to a String in C](https://www.delftstack.com/howto/c/how-to-convert-an-integer-to-a-string-in-c/) (Not used for now)~~
- ~~[Bit-wise Operation in C](https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/)~~
- ~~[Char to Binary(string format)](https://stackoverflow.com/questions/7863499/conversion-of-char-to-binary-in-c)~~
- [String to Bianry](https://www.rapidtables.com/convert/number/string-to-binary.html)
- [Hex to String](https://codebeautify.org/hex-string-converter)
# Tools
- [XOR Calculator](https://xor.pw/#)
- [Hex Calculator](https://www.calculator.net/hex-calculator.html?number1=79727269&c2op=%2B&number2=E0CCDBF2&calctype=op&x=76&y=29)
- [Binary to Hex converter](https://www.rapidtables.com/convert/number/binary-to-hex.html)
