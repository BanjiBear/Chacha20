# Chacha20
This repository stores the code for Chacha20 implementation written in C.  
Chacha20 is a Encryption Scheme applying the concept of Stream Cipher. The implementation provide three modes to elaborate the encryption process as well as the Quarter Round Function.  
The 8-block key and the 2-block nonce are randomly generated, the counter increase for each encryption.

# Installation and Execution
The current version is only executable on Linux/MAC OS.  
To compile the Chacha20, open the terminal and type
```shell
cc chacha20.c -o chacha20 -std=c99 -w
```
Simply follow the instruction given on the screen!  
***NOTE: Please make sure that the chacha20.c file is in the same directory as the terminalSize.py file***

To execute the code, there are three modes:  
```shell
./chacha20 1
```
Mode 1 simply reads in user-typed in plaintext then encrypt it into ciphertext.  

```shell
./chacha20 2
```
Mode 2 server as a debug mode, it encrypts five test cases pre-defined in the code and encrypt the plaintexts.  

```shell
./chacha20 3
```
Mode 3 allows user input but print detailed encryption process, specifically, the output of the Quarter Round function (only the first round).  

# Sample Output
Mode 1 Input  
```
Please type in the plaintext to be encrypted
(only letters and spaces are allowed, both uppercase and lowercase are fine): 
THis is Tommy please meet me after five in the evening
```
Mode 1 Output  
```
Chacha20 Encryption Scheme
Input                   : this is tommy please meet me after five in the evening
------ Encryption ------
Input              (hex): 7468697320697320746f6d6d7920706c65617365206d656574206d65206166746572206669766520696e20746865206576656e696e67
Key                (hex): 7669656d71707371656f63636b6f6a7666627a6d7a657279656b61716765797a
nonce              (hex): 78646c796c696b7a
counter            (hex): 1
--Input 512-bit blocks--
block [0] to [15]  (hex): 65787061 6E642033 322D6279 7465206B 7669656D 71707371 656F6363 6B6F6A76 66627A6D 7A657279 656B6171 6765797A 00000000 00000001 78646C79 6C696B7A 
Cipher Sequence    (hex): 7B72077AF614B1F08824F2C4ED390FA8018CB0F42A0C2CC6B9FFFDCFBF000794DFBE812517523EBBB19FBF41D97F3583FDA5D5151789A904FC780107F5716FAA

Ciphertext         (hex): 7B72077AF614B1F0882486AC844A2FC172ACC49B476155E6C99398AECC6527F9BADBF5057A371EDAD7EBDA33F9195CF59885BC7B37FDC161DC1D77629B1801CD
------------------------
```

Mode 2 Output  
```
Chacha20 Encryption Scheme
Plaintext               : My name is Tommy and I am a year three student
Input                   : my name is tommy and i am a year three student
------ Encryption ------
Input              (hex): 6d79206e616d6520697320746f6d6d7920616e64206920616d206120796561722074687265652073747564656e74
Key                (hex): 7a6e7264746b746a7476796c6a756962747371786c7972706870666b717a7972
nonce              (hex): 716f7a6563786761
counter            (hex): 1
--Input 512-bit blocks--
block [0] to [15]  (hex): 65787061 6E642033 322D6279 7465206B 7A6E7264 746B746A 7476796C 6A756962 74737178 6C797270 6870666B 717A7972 00000000 00000001 716F7A65 63786761 
Cipher Sequence    (hex): 5CDAACA709C56B075C3108A5B59EF467F98D41AECDF08DE95073E7F094CB69A8D9C8E5670B4AC128EBF7F346C95E62B0C7BD36F968760945D9232EBF1F370DCD

Ciphertext         (hex): 5CDAACA709C56B075C3108A5B59EF467F98D2CD7ED9EEC8435538E83B4BF06C5B4B1C506652EE141CB969E66A87E1BD5A6CF168D00046C20F9505ACA7B5263B9
------------------------

Chacha20 Encryption Scheme
Plaintext               : Azamat can you please meet me after the lecture
Input                   : azamat can you please meet me after the lecture
------ Encryption ------
Input              (hex): 617a616d61742063616e20796f7520706c65617365206d656574206d6520616674657220746865206c656374757265
Key                (hex): 7679656163676873677473696c61626868657068796a73646974626d66707566
nonce              (hex): 6d786a6c6f66757a
counter            (hex): 2
--Input 512-bit blocks--
block [0] to [15]  (hex): 65787061 6E642033 322D6279 7465206B 76796561 63676873 67747369 6C616268 68657068 796A7364 6974626D 66707566 00000000 00000002 6D786A6C 6F66757A 
Cipher Sequence    (hex): EA91CAB65D7E9B789F3886865946097C1BAE2EE2480491D8C70957F7CB75DDCA19B4A9A4E01D06A587ACDA3B0A7532AF603F2ADB2F29F1EED8005977D20C91CC

Ciphertext         (hex): EA91CAB65D7E9B789F3886865946097C1BCF54832565E5F8A46839D7B21AA8EA69D8CCC5937826C8E2C9AE1B671012CE064B4FA90F5D998BF86C3C14A679E3A9
------------------------

Chacha20 Encryption Scheme
Plaintext               : Action Code AFXCS kill the man in black
Input                   : action code afxcs kill the man in black
------ Encryption ------
Input              (hex): 616374696f6e20636f6465206166786373206b696c6c20746865206d616e20696e20626c61636b
Key                (hex): 726775786c667665777270666e67726b73716f726c7577726d75786c75637171
nonce              (hex): 696a7776786e6c76
counter            (hex): 3
--Input 512-bit blocks--
block [0] to [15]  (hex): 65787061 6E642033 322D6279 7465206B 72677578 6C667665 77727066 6E67726B 73716F72 6C757772 6D75786C 75637171 00000000 00000003 696A7776 786E6C76 
Cipher Sequence    (hex): 51759618A50B100238BBC8EAE372478A9C8ADE304C3DD3868287D0E6D9527DD0B3948735D8185CD9210C643C38FBA68CC3D828B1BB7CB4546A823F7F3C48658F

Ciphertext         (hex): 51759618A50B100238BBC8EAE372478A9C8ADE304C3DD38682E6B392B03D13F0D0FBE350F8793AA1427F44575197CAACB7B04D91D61DDA7403EC1F1D502906E4
------------------------

Chacha20 Encryption Scheme
Plaintext               : ten tons of drugs have arrived at the harbor
Input                   : ten tons of drugs have arrived at the harbor
------ Encryption ------
Input              (hex): 74656e20746f6e73206f66206472756773206861766520617272697665642061742074686520686172626f72
Key                (hex): 6e6f687575626a6e6a706d636d6d686e64636e62796978637176746b6a706d65
nonce              (hex): 687367636a766375
counter            (hex): 4
--Input 512-bit blocks--
block [0] to [15]  (hex): 65787061 6E642033 322D6279 7465206B 6E6F6875 75626A6E 6A706D63 6D6D686E 64636E62 79697863 7176746B 6A706D65 00000000 00000004 68736763 6A766375 
Cipher Sequence    (hex): A032F80701E1EDD2BBC96FDCC71E8BD838F0B6FB1289DC3D6E3FA40A43274C9D9BF6F6CAEADEF01B87A51295379BC71DA70B49E2015890EA358E7DE139DCA100

Ciphertext         (hex): A032F80701E1EDD2BBC96FDCC71E8BD838F0B6FB66ECB21D1A50CA7963482ABDFF8483AD99FE987AF1C032F445E9AE6BC26F69837578E48250AE15804BBECE72
------------------------

Chacha20 Encryption Scheme
Plaintext               : Q is discovered kill him at all cost
Input                   : q is discovered kill him at all cost
------ Encryption ------
Input              (hex): 7120697320646973636f7665726564206b696c6c2068696d20617420616c6c20636f7374
Key                (hex): 6a77787264617877776e6a7a6f737871726f6a6f6c7479717277736a76666970
nonce              (hex): 6465746a73647471
counter            (hex): 5
--Input 512-bit blocks--
block [0] to [15]  (hex): 65787061 6E642033 322D6279 7465206B 6A777872 64617877 776E6A7A 6F737871 726F6A6F 6C747971 7277736A 76666970 00000000 00000005 6465746A 73647471 
Cipher Sequence    (hex): 1864E6E6C7DBAD7F44D309BF19D60AF2EC2EEB427C48F89A317A0F9345E62991D56D31FE50A82495E31E76A2F5E34B66D2ED5D5A2EF80EED93C85EE0F81F0E1E

Ciphertext         (hex): 1864E6E6C7DBAD7F44D309BF19D60AF2EC2EEB427C48F89A317A0F9334C640E2F509588D33C752F0917B12829E8A270AF28534370E997ACDF2A432C09B707D6A
------------------------2FC172ACC49B476155E6C99398AECC6527F9BADBF5057A371EDAD7EBDA33F9195CF59885BC7B37FDC161DC1D77629B1801CD
------------------------
```

Mode 3 Input  
```
Please type in the plaintext to be encrypted
(only letters and spaces are allowed, both uppercase and lowercase are fine): 
meet me after lunch under the bridge near harbor
```
Mode 3 Output  
```
Chacha20 Encryption Scheme
Input                   : meet me after lunch under the bridge near harbor
------ Encryption ------
Input              (hex): 6d656574206d65206166746572206c756e636820756e6465722074686520627269646765206e65617220686172626f72
Key                (hex): 69767177716f747778627467636a61697675717a76646c6966726d68706a7765
nonce              (hex): 6f71697178636661
counter            (hex): 1
--Input 512-bit blocks--
block [0] to [15]  (hex): 65787061 6E642033 322D6279 7465206B 69767177 716F7477 78627467 636A6169 7675717A 76646C69 66726D68 706A7765 00000000 00000001 6F716971 78636661 

-------- Round 1 --------
Binary Addition    (hex): CEEEE1D8 6E642033 322D6279 7465206B 69767177 716F7477 78627467 636A6169 7675717A 76646C69 66726D68 706A7765 00000000 00000001 6F716971 78636661 
XOR                (hex): CEEEE1D8 6E642033 322D6279 7465206B 69767177 716F7477 78627467 636A6169 7675717A 76646C69 66726D68 706A7765 CEEEE1D8 00000001 6F716971 78636661 
Bit Rotation       (hex): CEEEE1D8 6E642033 322D6279 7465206B 69767177 716F7477 78627467 636A6169 7675717A 76646C69 66726D68 706A7765 E1D8CEEE 00000001 6F716971 78636661 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Binary Addition    (hex): CEEEE1D8 6E642033 322D6279 7465206B 69767177 716F7477 78627467 636A6169 684E4068 76646C69 66726D68 706A7765 E1D8CEEE 00000001 6F716971 78636661 
XOR                (hex): CEEEE1D8 6E642033 322D6279 7465206B 0138311F 716F7477 78627467 636A6169 684E4068 76646C69 66726D68 706A7765 E1D8CEEE 00000001 6F716971 78636661 
Bit Rotation       (hex): CEEEE1D8 6E642033 322D6279 7465206B 8311F013 716F7477 78627467 636A6169 684E4068 76646C69 66726D68 706A7765 E1D8CEEE 00000001 6F716971 78636661 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Binary Addition    (hex): 5200D1EB 6E642033 322D6279 7465206B 8311F013 716F7477 78627467 636A6169 684E4068 76646C69 66726D68 706A7765 E1D8CEEE 00000001 6F716971 78636661 
XOR                (hex): 5200D1EB 6E642033 322D6279 7465206B 8311F013 716F7477 78627467 636A6169 684E4068 76646C69 66726D68 706A7765 B3D81F05 00000001 6F716971 78636661 
Bit Rotation       (hex): 5200D1EB 6E642033 322D6279 7465206B 8311F013 716F7477 78627467 636A6169 684E4068 76646C69 66726D68 706A7765 D81F05B3 00000001 6F716971 78636661 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Binary Addition    (hex): 5200D1EB 6E642033 322D6279 7465206B 8311F013 716F7477 78627467 636A6169 416E561B 76646C69 66726D68 706A7765 D81F05B3 00000001 6F716971 78636661 
XOR                (hex): 5200D1EB 6E642033 322D6279 7465206B C27FA608 716F7477 78627467 636A6169 416E561B 76646C69 66726D68 706A7765 D81F05B3 00000001 6F716971 78636661 
Bit Rotation       (hex): 5200D1EB 6E642033 322D6279 7465206B 3FD30461 716F7477 78627467 636A6169 416E561B 76646C69 66726D68 706A7765 D81F05B3 00000001 6F716971 78636661 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---- Round 1 results ----
block [0] to [15]  (hex): 5200D1EB 6E642033 322D6279 7465206B 3FD30461 716F7477 78627467 636A6169 416E561B 76646C69 66726D68 706A7765 D81F05B3 00000001 6F716971 78636661 

Cipher Sequence    (hex): 9D2F11CA97D9C9B4CC8ED7499426DABD3406270262F9318FC5A5EA0F89AF634ED18D1BC54714F5E5C8AB6D883675ED22B79E52112A3FCE55BC8A9983993900AA

Ciphertext         (hex): 9D2
```

# Author
[CHEN Yi pu(Tommy)](https://github.com/BanjiBear)

# Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change. Please make sure to update tests as appropriate.

# License
MIT