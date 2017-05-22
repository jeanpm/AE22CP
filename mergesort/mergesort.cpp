#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <time.h>



void printVector(int* vetor, int from, int to)
{
	for (int i = 0; i < to-from; ++i)
		fprintf(stderr, "%d ", vetor[from+i]);
	fprintf(stderr, "\n");
}

void merge(int* vetor, int afrom, int ato, int bfrom, int bto)
{
	int lsize = (ato-afrom) + 1;
	int rsize = (bto-bfrom) + 1; 

	int* left  = (int*) malloc(sizeof(int) * lsize);
	int* right = (int*) malloc(sizeof(int) * rsize);
	
	left[lsize-1]  = INT_MAX;
	right[rsize-1] = INT_MAX;
	
	memcpy(left,  vetor+afrom, (lsize-1) * sizeof(int));
	memcpy(right, vetor+bfrom, (rsize-1) * sizeof(int));
	
	int posL = 0;
	int posR = 0;
	
	for (int posV = afrom; posV < bto; ++posV)
	{
		if (left[posL] < right[posR]) {
			vetor[posV] = left[posL];
			posL++;
		} else {
			vetor[posV] = right[posR];
			posR++;
		}
	}
	
	free(left);
	free(right);
}

void mergesort(int* vetor, int from, int to)
{
	if (to - from > 1)
	{
		int middle = from + (to - from)/2;

		mergesort(vetor, from, middle);
		mergesort(vetor, middle, to);
		
		merge(vetor, from, middle, middle, to);
	}
}
 

int main(int args, char** argv)
{
	srand(time(NULL));
	int vsize = 2;
	int* vetor = (int*) malloc(sizeof(int)* vsize);


	for (int i = 0; i < vsize; ++i)
		vetor[i] = rand()%500;
	
//	printVector(vetor, 0, vsize);
	
	mergesort(vetor, 0, vsize);
	
	printVector(vetor, 0, vsize);
	
	free(vetor);

	return 1;
}
