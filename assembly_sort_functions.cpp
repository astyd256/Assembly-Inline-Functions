#include <assembly_sort_functions.h>

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
