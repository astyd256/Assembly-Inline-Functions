#include <assembly_inline_functions.h>

int Add(int a, int b)
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

int Sub(int a, int b)
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

__int64 Mul(int a, int b)
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

int Div(__int64 a, int b)
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

bool Equal(int a, int b)
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

bool Greater(int a, int b)
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

bool GreaterEqual(int a, int b)
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

bool Lower(int a, int b)
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

bool LowerEqual(int a, int b)
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

bool Not(bool a)
    {
        _asm
        {
            not a
        }
        if (a & 1) return true;
        return false;
    }

bool And(bool a, bool b)
    {
        _asm
        {
            mov al, a
            and al, b
            mov a, al
        }
        return a;
    }

bool Or(bool a, bool b)
    {
        _asm
        {
            mov al, a
            or al, b
            mov a, al
        }
        return a;
    }

bool Xor(bool a, bool b)
    {
        _asm
        {
            mov al, a
            xor al, b
            mov a, al
        }
        return a;
    }

int Index(int* arr, int i)
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

int LLShift(int a, __int8 i)
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

int RLShift(int a, __int8 i)
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

int LCShift(int a, __int8 i)
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

int RCShift(int a, __int8 i)
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

int IterLambdaFunc(int(*func)(int, int), int a)
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

