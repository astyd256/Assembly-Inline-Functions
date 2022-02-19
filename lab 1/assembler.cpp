// assembler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

static class AssemblerWrapper
{
public:
    AssemblerWrapper();
    ~AssemblerWrapper();

    static int Add(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            add eax, b
            mov c, eax
        }
        return c;
    }

    static int Sub(int a, int b)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            sub eax, b
            mov c, eax
        }
        return c;
    }

    static __int64 Mul(int a, int b)
    {
        int c = 0;
        int d = 0;
        int e = 0;
        _asm
        {
            mov eax, a
            mul b
            mov c, edx
            mov d, eax
        }
        for (int n = 32; n < 64; n++)
            if (c & (1 << n)) e += pow(2, n);

        return d * 1LL + e;
    }

    static int Div(__int64 a, int b)
    {
        int c = 0;
        int a1 = 0, a2 = 0;
        for (int n = 0; n < 64;n++)
        {
            if (a & (1LL << n))
                (n < 32) ? a1 += pow(2, n) : a2 += pow(2, n);
        }
        _asm
        {
            mov edx, a2
            mov eax, a1
            div b
            mov c, eax
        }

        return c;
    }

    static bool Equal(int a, int b)
    {
        bool c = 0;
        _asm
        {
            mov eax, a
            cmp eax, b
            jne L
            mov c, 1
            L:
        }
        return c;
    }

    static bool Greater(int a, int b)
    {
        bool c = 0;
        _asm
        {
            mov eax, a
            cmp eax, b
            jng L
            mov c, 1
            L:
        }
        return c;
    }

    static bool GreaterEqual(int a, int b)
    {
        bool c = 0;
        _asm
        {
            mov eax, a
            cmp eax, b
            jnge L
            mov c, 1
            L:
        }
        return c;
    }

    static bool Lower(int a, int b)
    {
        bool c = 0;
        _asm
        {
            mov eax, a
            cmp eax, b
            jnl L
            mov c, 1
            L:
        }
        return c;
    }

    static bool LowerEqual(int a, int b)
    {
        bool c = 0;
        _asm
        {
            mov eax, a
            cmp eax, b
            jnle L
            mov c, 1
            L:
        }
        bool d = c;
        return c;
    }

    static bool Not(bool a)
    {
        _asm
        {
            not a
        }
        if (a & 1) return true;
        return false;
    }

    static bool And(bool a, bool b)
    {
        _asm
        {
            mov al, a
            and al, b
            mov a, al
        }
        return a;
    }

    static bool Or(bool a, bool b)
    {
        _asm
        {
            mov al, a
            or al, b
            mov a, al
        }
        return a;
    }

    static bool Xor(bool a, bool b)
    {
        _asm
        {
            mov al, a
            xor al, b
            mov a, al
        }
        return a;
    }

    static int Index(int* arr, int i)
    {
        _asm
        {
            mov eax, i
            mov ebx, arr
            mov eax, [ebx + eax * 4]
            mov i, eax
        }
        return i;
    }

    static int LLShift(int a, __int8 i)
    {
        _asm
        {
            mov eax, a
            mov cl, i
            shl eax, cl
            mov a, eax
        }
        return a;
    }

    static int RLShift(int a, __int8 i)
    {
        _asm
        {
            mov eax, a
            mov cl, i
            shr eax, cl
            mov a, eax
        }
        return a;
    }

    static int LCShift(int a, __int8 i)
    {
        _asm
        {
            mov eax, a
            mov cl, i
            rol eax, cl
            mov a, eax
        }
        return a;
    }

    static int RCShift(int a, __int8 i)
    {
        _asm
        {
            mov eax, a
            mov cl, i
            ror eax, cl
            mov a, eax
        }
        return a;
    }

    static int IterLambdaFunc(int(*func)(int, int), int a)
    {
        int c = 0;
        _asm
        {
            mov eax, a
            L:
            push eax
            push eax
            call func
            add esp, 8

            add c, 1
            mov edx, a
            cmp c, edx

            je ESCAPE
            jne L
                ESCAPE:
            mov a, eax
        }
        return a;
    }
};


int main()
{   
    std::cout << "Add(8,24): " << AssemblerWrapper::Add(8, 24) << std::endl; 
    std::cout << "Sub(8, 24): " << AssemblerWrapper::Sub(8, 24) << std::endl;
    std::cout << "Mul(8, 24): " << AssemblerWrapper::Mul(8, 24) << std::endl;
    std::cout << "Div(24, 8): " << AssemblerWrapper::Div(24, 8) << std::endl;

    std::cout << "Equal(24, 8): " << AssemblerWrapper::Equal(24, 8) << std::endl;
    std::cout << "Equal(24, 24): " << AssemblerWrapper::Equal(24, 24) << std::endl;
    std::cout << "Greater(24, 8): " << AssemblerWrapper::Greater(24, 8) << std::endl;
    std::cout << "Greater(24, 24): " << AssemblerWrapper::Greater(24, 24) << std::endl;
    std::cout << "GreaterEqual(24, 8): " << AssemblerWrapper::GreaterEqual(24, 8) << std::endl;
    std::cout << "GreaterEqual(24, 24): " << AssemblerWrapper::GreaterEqual(24, 24) << std::endl;
    std::cout << "Lower(8, 24): " << AssemblerWrapper::Lower(8, 24) << std::endl;
    std::cout << "Lower(24, 24): " << AssemblerWrapper::Lower(24, 24) << std::endl;
    std::cout << "LowerEqual(24, 8): " << AssemblerWrapper::LowerEqual(24, 8) << std::endl;
    std::cout << "LowerEqual(24, 24): " << AssemblerWrapper::LowerEqual(24, 24) << std::endl;
    
    std::cout << "Not(true): " << AssemblerWrapper::Not(true) << std::endl;
    std::cout << "Not(false): " << AssemblerWrapper::Not(false) << std::endl;
    std::cout << "And(true, false): " << AssemblerWrapper::And(true, false) << std::endl;
    std::cout << "And(true, true): " << AssemblerWrapper::And(true, true) << std::endl;
    std::cout << "Or(true, false): " << AssemblerWrapper::Or(true, false) << std::endl;
    std::cout << "Or(false, false): " << AssemblerWrapper::Or(false, false) << std::endl;
    std::cout << "Xor(true, true): " << AssemblerWrapper::Xor(true, true) << std::endl;
    std::cout << "Xor(false, false): " << AssemblerWrapper::Xor(false, false) << std::endl;
    std::cout << "Xor(true, false): " << AssemblerWrapper::Xor(true, false) << std::endl;

    int arr[5] = {0, 0, 0, 3, 0 };
    std::cout << "arr[3] = " << arr[3] << std::endl;
    std::cout << "Index(arr, 3): " << AssemblerWrapper::Index(arr, 3) << std::endl;

    std::cout << "LLShift(4294967296, 1): " << AssemblerWrapper::LLShift(64, 1) << std::endl;
    std::cout << "RLShift(1, 1): " << AssemblerWrapper::RLShift(64, 1) << std::endl;
    std::cout << "LCShift(4294967296, 1): " << AssemblerWrapper::LCShift(64, 1) << std::endl;
    std::cout << "RCShift(1, 1): " << AssemblerWrapper::RCShift(64, 1) << std::endl;

    std::cout << "IterLambdaFunc([](int a, int b) {return a + b;}, 10): " << AssemblerWrapper::IterLambdaFunc([](int a, int b) -> int {return a + b;}, 10);

}