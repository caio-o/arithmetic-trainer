#include <stdio.h> 
#include <stdlib.h>

//Function that generates problems consisting only of addition and subtraction
//e.g.: 123 + 323 - 45
void addAndSub(int difficulty)
{
	int* nums;  //Vector of the numbers used in the problem
	int length;  //Amount of numbers in the problem
	int maxValue, minValue;  //Greatest and smallest numbers possible
	int input, res = 0;
	int i;

	if(difficulty == 4)
	{
		// Difficulty 4: 2 very large numbers
		length = 2;
		minValue = 100000;
		maxValue = RAND_MAX/2; //4: 2*2*2*2*2*2
	}
	else
	{
		maxValue = 1;
		minValue = 1;

		// Diff.: problem length
		//     1: 3 numbers
		//     2: 5 numbers
		//     3: 6 numbers
		length = (difficulty*3)/2 + 2;
		
		// Diff.:  [min,max]
		//     1:   [20,90]
		//     2:  [400,8100]
		//     3: [8000,729000]
		for(i=0; i<difficulty; i++)
		{
			maxValue *= 90;
			minValue *= 20;
		}
	}

	nums = (int*)malloc(length*sizeof(int));

	//The first number is set here so that it is allways positive (cf. the loop below)
	nums[0] = rand()%(maxValue-minValue+1) + minValue;
	printf("%d ", nums[0]);

	res = nums[0];

	for(i=1; i<length; i++)
	{
		
		nums[i] = rand()%(maxValue-minValue+1) + minValue;
		
		if(rand()%2)  //Randomly generates either 1 or 0. If it is 1, it makes the number negative
		{
			printf("- %d ", nums[i]);
			nums[i] *= -1;
		}
		else
			printf("+ %d ", nums[i]);

		res += nums[i]; //  The result is the sum of all the numbers
	}

	printf("\nANSWER: ");
	scanf("%d", &input);
	
	while(input != res)
	{
		printf("\nWRONG\nANSWER: ");
		scanf("%d", &input);
	}
	printf("\nCORRECT!\n");
}


//Function that generates a problem of which the opperations are multiplication and division,
//e.g.: 836 * 921/10 
void multAndDiv(int difficulty)
{
	long resInt, minValue=1, maxValue=1;
	int exponent, length, i;
	int *nums;
	char *opperations;

	switch(difficulty)
	{
	case 1:
		length = 2;
		minValue = 20;
		maxValue = 100;
		break;
	
	case 2:
		length = 4;
		minValue = 20;
		maxValue = 1000;
		break;
	
	case 3: 
		length = 4;
		minValue = 100;
		maxValue = 100000;
		break;

	default:
		length = 2;
		minValue = 1000;
		maxValue = 100000;
		break;
	}

	// length-1 here because there are only opperations between numbers: 
	// a * b + c --> 3 numbers, 2 opperations
	opperations = (char*)malloc(sizeof(char)*(length-1));
	
	for(i=0; i<length-1; i++)
		opperations[i] = '*'; // the default opperation is multiplication
	
	if(length > 2) // If there is room for it, randomply places divisions, but not in place of the first opperation
	{
		opperations [rand()%(length-2) + 1] = '/';
	}
}

//Function that swaps the content of two integers
void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
