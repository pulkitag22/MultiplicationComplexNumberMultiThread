#include "definations.h"

int main (void) {
	FILE *fptr;
	char filename[] = "input.txt";
	int i;
	int numberOfInputs;//number of camplex (a + ib) passed. if it has value 5 then, there are 10 numbers in the input.
	
	fptr = fopen(filename, "r");
	if (fptr == NULL){
		printf ("Not able to open file.\n");
		exit(0);
	}
	
	fscanf (fptr, "%d", &numberOfInputs);
	struct complexNumber inputComplexNumber[numberOfInputs];

	for (i=0; i<2*numberOfInputs; i++){
		fscanf (fptr, "%d", &inputComplexNumber[i].a);
		fscanf (fptr, "%d", &inputComplexNumber[i].b);
	}
	
	for (i=0; i<numberOfInputs; i++){
		printf ("%d ", inputComplexNumber[i].a);
		printf (" %d\n", inputComplexNumber[i].b);
	}

	fclose(fptr);
	
	int currentIterationNumberOfComplexNumbers = numberOfInputs;
	int currentIterationNumber = 1;
	pthread_t threadMultiplyPair [numberOfInputs/2];
	void * temporaryResultStorageArrayPtr[numberOfInputs/2];			
	struct complexNumber temporaryResultStorageArray[numberOfInputs/2 + 1];
	
	while (currentIterationNumberOfComplexNumbers != 1){
		if (currentIterationNumberOfComplexNumbers%2 == 0){
			for (i=0; i<currentIterationNumberOfComplexNumbers/2; i++){
				if (currentIterationNumber == 1){
					if ((pthread_create(&threadMultiplyPair[i], NULL, multiplyTwoComplexNumber, &inputComplexNumber[2*i]) != 0)){
						fprintf(stderr, "Unabe to create new thread.");
						exit(1);
					}
				} else {
					if ((pthread_create(&threadMultiplyPair[i], NULL, multiplyTwoComplexNumber, &temporaryResultStorageArray[2*i]) != 0)){
						fprintf(stderr, "Unabe to create new thread.");
						exit(1);
					}
				}
				pthread_join (threadMultiplyPair[i], (void **)&temporaryResultStorageArrayPtr[i]);
				temporaryResultStorageArray[i] = *((struct complexNumber *)temporaryResultStorageArrayPtr[i]);
				printf("%d + i%d\n", temporaryResultStorageArray[i].a, temporaryResultStorageArray[i].b);
				free (temporaryResultStorageArrayPtr[i]);
			}
		} else {
			for (i=0; i<currentIterationNumberOfComplexNumbers/2; i++){
			if (currentIterationNumber == 1){
				if ((pthread_create(&threadMultiplyPair[i], NULL, multiplyTwoComplexNumber, &inputComplexNumber[2*i]) != 0)){
					fprintf(stderr, "Unabe to create new thread.");
					exit(1);
				}
			} else {
				if ((pthread_create(&threadMultiplyPair[i], NULL, multiplyTwoComplexNumber, &temporaryResultStorageArray[2*i]) != 0)){
					fprintf(stderr, "Unabe to create new thread.");
					exit(1);
				}
			}
			pthread_join (threadMultiplyPair[i], (void **)&temporaryResultStorageArrayPtr[i]);
			temporaryResultStorageArray[i] = *((struct complexNumber *)temporaryResultStorageArrayPtr[i]);
			printf("%d + i%d\n", temporaryResultStorageArray[i].a, temporaryResultStorageArray[i].b);
			free (temporaryResultStorageArrayPtr[i]);
			}

			if (currentIterationNumber == 1){
				temporaryResultStorageArray[currentIterationNumberOfComplexNumbers/2] = inputComplexNumber[numberOfInputs-1];
				printf("%d + i%d\n", temporaryResultStorageArray[currentIterationNumberOfComplexNumbers/2].a, temporaryResultStorageArray[currentIterationNumberOfComplexNumbers/2].b);
			} else {
				temporaryResultStorageArray[currentIterationNumberOfComplexNumbers/2] = temporaryResultStorageArray[currentIterationNumberOfComplexNumbers];
				printf("%d + i%d\n", temporaryResultStorageArray[currentIterationNumberOfComplexNumbers/2].a, temporaryResultStorageArray[currentIterationNumberOfComplexNumbers/2].b);
			}
			currentIterationNumberOfComplexNumbers++;
		}
		currentIterationNumberOfComplexNumbers = currentIterationNumberOfComplexNumbers/2;
		currentIterationNumber++;
	}

	printf("Main functing exiting.\n");

	return 0;
}


void * multiplyTwoComplexNumber (void * inputPtr){
	int * localIntAPtr = (int *) inputPtr;
	int localA = *localIntAPtr;
	int localB = *++localIntAPtr;
	int localC = *++localIntAPtr;
	int localD = *++localIntAPtr;

	printf ("\n%d %d %d %d\n", localA, localB, localC, localD);
	struct complexNumber * resultPtr = (struct complexNumber *) malloc(1*sizeof(struct complexNumber));
	resultPtr->a = (localA*localC)-(localB*localD);
	resultPtr->b = (localB*localC)+(localA*localD);
	pthread_exit((void *)resultPtr);
}
