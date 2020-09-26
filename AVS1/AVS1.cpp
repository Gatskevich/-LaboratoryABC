
#include <iostream>
#include <stdio.h>
#include <malloc.h>

void main() {
    _int8  a[8] = { 3,3,3,3,3,3,3,3 };
    _int8  b[8] = { 10,10,10,10,10,10,10,10 };
    _int8  c[8] = { 10,10,10,10,10,10,10,10 };
    _int16 d[8] = { 5,5,5,5,5,5,5,5 };
    _int16 f[8] = {};
    _asm{
        pushad
 
        movq      mm0, qword ptr[a]
        movq      mm1, qword ptr[b]
        movq      mm2, qword ptr[c]
        movq      mm3, [d]

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

        movq      mm0, qword ptr[a+4]
        movq      mm1, qword ptr[b+4]
        movq      mm2, qword ptr[c+4]
        movq      mm3, [d+8]

        punpcklbw mm0, mm0
        punpcklbw mm1, mm1
        punpcklbw mm2, mm2
        psraw     mm0, 8
        psraw     mm1, 8
        psraw     mm2, 8
        
        pmullw   mm1, mm2
        psubsw   mm0, mm1
        paddsw   mm0, mm3
        movq  qword ptr[f+8], mm0
    }
 
    printf("Result: {%i,%i,%i,%i,%i,%i,%i,%i}\n", f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
    getchar();
} 
