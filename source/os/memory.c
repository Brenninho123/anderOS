#include "memory.h"

void* memset(void* ptr, int value, unsigned int num) {
    unsigned char* p = (unsigned char*)ptr;
    for (unsigned int i = 0; i < num; i++) p[i] = (unsigned char)value;
    return ptr;
}

void* memcpy(void* dest, const void* src, unsigned int num) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    for (unsigned int i = 0; i < num; i++) d[i] = s[i];
    return dest;
}