# Overview
The miniMATLAB program performs calculations on 1x3 vectors. The program has the following functions:

* Addition
* Subtraction
* Scalar Multiplication
* Dot Product
* Cross Product

Calculations can be performed via the program prompt line:
```
miniMATLAB>     // user input here
```

## Build Instructions
To compile the program, locate the cloned repository and run the command below in the wsl directory:
```
$ make
```
### To make clean
Run the command:
```
$ make clean
```

### To run
Run the command:
```
$ ./start.exe
```

## Supported Commands
Note: 
* All vector names must be one character
* All values must be floating point integers, or integers
* The must be spaces before and after any '=' or opperators 'op'
* Valid opperators are:
    - ' + ' Addition
    - ' - ' Subtraction
    - ' * ' Scalar Multiplication
    - ' . ' Dot Product
    - ' x ' Cross Product



```
miniMATLAB> <v_name> = val_1, val_2, val_3 // stores values 1-3 in vector v_name

miniMATLAB> <v_name>  // displays the value of the specified vector

miniMATLAB> <v_name> = <v_name1> op <v_name2>   // stores the result of v_name1 op v_name2 in v_name

miniMATLAB> <v_name1> op <v_name2>   // displays the result of v_name1 op v_name2

miniMATLAB> clear   // clears vector memory

miniMATLAB> list    // displays all the vectors in vector memory

miniMATLAB> save <filepath>    // saves vector memory to a .csv file

miniMATLAB> load <filepath>    // loads a .csv file

miniMATLAB> help               // displays the help menu
```

## Dynamic Memory
This program utilizes malloc() and realloc() in <stdlb.h> to allocate memory dynamically.

The program utilizes the realloc() function to resize the program's vector memory to store a large number of vectors if needed. The only limitation being if realloc() cannot find sufficient space in memory. **The program will display an error if there is insufficient memory and disallow the addition of new vectors.**