# Assembly Inline Functions and Sorting Algorithms

Note: This *library* was made as a part of lab assignments on the subject of System Programming in Tomsk State University. The dev enviroment of this library was Visual Studio 2017 and it's Windows compatable only. 

*Maybe* I'll rewrite it for Linux in the future.

## Table of Contents
- [Assembly Inline Functions and Sorting Algorithms](#assembly-inline-functions-and-sorting-algorithms)
  - [Table of Contents](#table-of-contents)
  - [TL;DR](#tldr)
- [Assembly Inline Functions](#assembly-inline-functions)
  - [Functions](#functions)
  - [Usage](#usage)
- [Assembly Bubble Sort and Selection Sort](#assembly-bubble-sort-and-selection-sort)
  - [Bubble Sort](#bubble-sort)
  - [Selection Sort](#selection-sort)
  - [Usage](#usage-1)


## TL;DR
This readme provides an overview and usage instructions for two components: 

Assembly Inline Functions: A collection of inline assembly functions that perform various mathematical and logical operations.

Assembly Bubble Sort and Selection Sort: Implementation of Bubble Sort and Selection Sort sorting algorithms using inline assembly in a C++ program.

# Assembly Inline Functions

This code implements a collection of inline assembly functions that perform various mathematical and logical operations. The functions are implemented using inline assembly in a C++ program.

## Functions
- `Add`: Performs addition of two integers.
- `Sub`: Performs subtraction of two integers.
- `Mul`: Performs multiplication of two integers and returns the result as a 64-bit integer.
- `Div`: Performs division of a 64-bit integer by an integer and returns the result as an integer.
- `Equal`: Checks if two integers are equal.
- `Greater`: Checks if the first integer is greater than the second integer.
- `GreaterEqual`: Checks if the first integer is greater than or equal to the second integer.
- `Lower`: Checks if the first integer is lower than the second integer.
- `LowerEqual`: Checks if the first integer is lower than or equal to the second integer.
- `Not`: Performs bitwise NOT operation on a boolean value.
- `And`: Performs bitwise AND operation on two boolean values.
- `Or`: Performs bitwise OR operation on two boolean values.
- `Xor`: Performs bitwise XOR operation on two boolean values.
- `Index`: Accesses an element in an integer array at the specified index.
- `LLShift`: Performs logical left shift operation on an integer.
- `RLShift`: Performs logical right shift operation on an integer.
- `LCShift`: Performs circular left shift operation on an integer.
- `RCShift`: Performs circular right shift operation on an integer.

## Usage
1. Include the header file containing the inline assembly functions in your code.
2. Use the desired function to perform the desired operation.
3. Provide the necessary parameters to the function.
4. Handle the return value as needed in your program.

Note: These inline assembly functions are implemented using Intel x86 assembly syntax and may not be portable to other architectures or compilers.

# Assembly Bubble Sort and Selection Sort

This code implements two sorting algorithms, Bubble Sort and Selection Sort, using inline assembly in a C++ program.

## Bubble Sort
The `AssemblerBubbleSort` function sorts an array of integers in ascending order using the Bubble Sort algorithm. It takes two arguments: a pointer to the array and the total number of elements in the array.

## Selection Sort
The `AssemblerSelectionSort` function sorts an array of integers in ascending order using the Selection Sort algorithm. It takes two arguments: a pointer to the array and the total number of elements in the array.

## Usage
1. Modify the value of `arr_size` if a different size of the array is desired.
2. Run the program.
3. The original arrays and the sorted arrays will be printed to the console.

Note: The implementation of these sorting algorithms using assembly is not considered the most efficient or optimized approach. The purpose is to demonstrate the use of inline assembly within a C++ program.