#ifndef ASSEMBLY_INLINE_FUNCTIONS_H
#define ASSEMBLY_INLINE_FUNCTIONS_H

int Add(int a, int b);
int Sub(int a, int b);
__int64 Mul(int a, int b);
int Div(__int64 a, int b);
bool Equal(int a, int b);
bool Greater(int a, int b);
bool GreaterEqual(int a, int b);
bool Lower(int a, int b);
bool LowerEqual(int a, int b);
bool Not(bool a);
bool And(bool a, bool b);
bool Or(bool a, bool b);
bool Xor(bool a, bool b);
int Index(int* arr, int i);
int LLShift(int a, __int8 i);
int RLShift(int a, __int8 i);
int LCShift(int a, __int8 i);
int RCShift(int a, __int8 i);

#endif