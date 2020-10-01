
#include <iostream>
#include <stdio.h>
#include <malloc.h>

void func(_int8* a, _int8* b, _int8* c, _int16* d) {
    _int16 f[8] = {};
    _asm {
        mov       eax, a
        mov       ebx, b
        mov       ecx, c
        mov       edx, d


        movq      mm0, [eax]
        movq      mm1, [ebx]
        movq      mm2, [ecx]
        movq      mm3, [edx]

        punpcklbw mm0, mm0
        punpcklbw mm1, mm1
        punpcklbw mm2, mm2
        psraw     mm0, 8
        psraw     mm1, 8
        psraw     mm2, 8

        pmullw   mm1, mm2
        psubsw   mm0, mm1
        paddsw   mm0, mm3

        movq  qword ptr[f], mm0

        movq      mm0, [eax + 4]
        movq      mm1, [ebx + 4]
        movq      mm2, [ecx + 4]
        movq      mm3, [edx + 8]

        punpcklbw mm0, mm0
        punpcklbw mm1, mm1
        punpcklbw mm2, mm2
        psraw     mm0, 8
        psraw     mm1, 8
        psraw     mm2, 8

        pmullw   mm1, mm2
        psubsw   mm0, mm1
        paddsw   mm0, mm3
        movq  qword ptr[f + 8], mm0
    }
    for (int i = 0; i < 8; i++) {
        std::cout << f[i] << ",";
    }

}

void main() {
    _int8  a[8] = { 4,3,23,3,64,3,32,3 };
    _int8  b[8] = { 34,10,10,4,10,10,8,10 };
    _int8  c[8] = { 6,40,-10,10,23,10,10,10 };
    _int16 d[8] = { 1,5,3,-5,45,25,54,5 };

    func(*&a, *&b, *&c, *&d);
    std::cout << "\n";
    for (int i = 0; i < 8; i++) {
        std::cout << a[i] - b[i] * c[i] + d[i] << ",";
    }
    std::cout << "\n";
    _int8  a1[8] = { 4,3,3,31,4,13,2,31 };
    _int8  b1[8] = { 14,-10,8,7,13,12,18,10 };
    _int8  c1[8] = { 26,10,-10,10,13,10,10,10 };
    _int16 d1[8] = { 1,5,3,-5,-5,15,44,5 };
    func(*&a1, *&b1, *&c1, *&d1);
    std::cout << "\n";
    for (int i = 0; i < 8; i++) {
        std::cout << a1[i] - b1[i] * c1[i] + d1[i] << ",";
    }
    getchar();
}
