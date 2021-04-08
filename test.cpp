#include "test.h"


Complex::Complex::Complex() {
    if (str) free(str);
    str = (char*)malloc(sizeof(char)*128);
}

Complex::Complex::~Complx() {
    if (str) free(str);
}
