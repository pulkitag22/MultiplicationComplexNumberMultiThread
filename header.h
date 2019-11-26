#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct complexNumber {
	int a;
	int b;
};

void * multiplyTwoComplexNumber (void * inputPtr);
