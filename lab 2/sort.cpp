// lab 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>

void AssemblerBubbleSort(int* adress, int n)
{
    int arr_size = n;
    _asm
    {
        mov edx, [adress]
        CYCLE:
            cmp n, 0
            jle END
            mov eax, n
            mov ebx, [edx + 4 * eax - 8]; second val
            cmp [edx + 4*eax - 4], ebx    ; comparing values
            jl SWAP
            dec n
            jmp CYCLE
        SWAP:
            mov ebx, [edx + 4*eax - 4] ; swap
            mov ecx, [edx + 4*eax - 8] ; swap
            mov [edx + 4*eax - 8], ebx ; swap
            mov [edx + 4*eax - 4], ecx ; swap
            cmp eax, arr_size 
            jge CYCLE
            inc eax
            mov ecx, [edx + 4*eax - 8] ; second val
            cmp[edx + 4*eax - 4], ecx; comparing values
            jl SWAP
            jmp CYCLE
        END:
    }
}

void AssemblerSelectionSort(int* adress, int n)
{
    int temp, index;
    _asm // EAX - i; EBX - j; EDX - adress; ECX - temp.
    {
            mov edx, [adress]
            mov eax, n
            inc eax
        CYCLE:
            dec eax
            cmp eax, 0
            jle END
            mov ebx, eax    ; Copying start adress for SELECT
            mov index, ebx   ; Copying starting index
            mov ecx, [edx + 4*ebx - 4]
            mov temp, ecx   ; Copying starting value
            jmp SELECT
        SWAP:   ;EAX - i; EDX - adress; EBX, ECX - free here
            mov ebx, index
            mov ecx, [edx + 4 * eax - 4]
            mov [edx + 4*ebx - 4], ecx  ; eax adressed written into index
            mov ecx, temp   
            mov [edx + 4*eax - 4], ecx  ;temp written into eax adressed
            jmp CYCLE
        SELECT: ;EAX - i; EBX - j; EDX - adress; ECX - free here
            cmp ebx, 0  ; Cycle ended
            jle SWAP
            dec ebx
            mov ecx, temp
            cmp ecx, [edx + 4*ebx - 4]    ; Comparing current value to highest in a cycle
            jl SWAP_HIGHEST
            jmp SELECT
        SWAP_HIGHEST:
            mov index, ebx
            mov ecx, [edx + 4*ebx - 4]
            mov temp, ecx
            jmp SELECT
        END:
    }
}

int main()
{
    int arr_size = 100;
    int* array1 = new int[arr_size];
    int* array2 = new int[arr_size];
    srand(time(NULL));
    for (int i = 0; i < arr_size; i++)
    {
        array1[i] = rand() % arr_size * ((rand() % 2 == 0) ? 1: -1);
        array2[i] = array1[i];
        std::cout << array1[i] << '\t';
    }
    std::cout << '\n';

    _asm
    {
        push arr_size
        push [array1]
        call AssemblerBubbleSort
        add ESP, 8
    }

    std::cout << "Bubble assembler sort:\n";
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << array1[i] << '\t';
    }
    std::cout << '\n';
    _asm
    {
        push arr_size
        push[array2]
        call AssemblerSelectionSort
        add ESP, 8
    }

    std::cout << "Selection assembler sort:\n";
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << array2[i] << '\t';
    }



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
