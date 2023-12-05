/**********************************************************************/
/*                                                                    */
/* Definitions of all the functions of the program, which are         */
/* all declared in functions.h, and whose purpose is to generate      */
/* the expressions to be evaluated by the user.                       */
/*                                                                    */
/**********************************************************************/

#include <stdio.h> 
#include <stdlib.h>

// Macro to be used in the function randomDenominator
#define N_DIVISORS 7

//For ignoring possible floating point precision errors when evaluating the user's answer
#define MAX_ERROR 0.00003

// A function that returns a random divisor within a list.
// The possible divisors are controlled in order to avoid periodical numbers, e.g. 4/3 = 1,333... 
int randomDenominator()
{
	int nums[] = {2, 4, 5, 10, 20, 100, 200}; // List of possible divisors

	return nums[rand()%N_DIVISORS];
}

//Function that generates problems consisting only of addition and subtraction
//e.g.: 123 + 323 - 45
void addAndSub(int difficulty)
{
	int *nums;  //Vector of the numbers used in the problem
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

	free(nums);
}

//Function that generates a problem of which the opperations are multiplication and division,
//e.g.: 836 * 921/10 
void multAndDiv(int difficulty)
{
	int minValue=1, maxValue=1;
	int length, i, j;
	float *nums;
	char *opperations;

	float input;
	float res = 1.0;

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

	nums = (float*)malloc(sizeof(float)*(length));

	// length-1 here because there are only opperations BETWEEN 2 numbers: 
	// a * b/c --> 3 numbers, 2 opperations
	opperations = (char*)malloc(sizeof(char)*(length-1));

	for(i=0; i<length-1; i++)
		opperations[i] = '*'; // the default opperation is multiplication

	// Randomly places a division
	if(rand()%(length+10) > 5)
		opperations [rand()%(length-1)] = '/';
	
	nums[0] = rand()%(maxValue - minValue) + minValue;
	printf("%.0f", nums[0]);

	//Fill in the vector with the numbers and print the problem as it is generated
	for(i=1; i<length; i++)
	{
		if(opperations[i-1] == '/')
		{
			nums[i] = randomDenominator();
			printf("/%.0f", nums[i]);
		}
		else 
		{
			nums[i] = rand()%(maxValue - minValue) + minValue; 
			printf(" * %.0f", nums[i]);
		}
	}

	// Calculate result
	for(i=0; i<length-1; i++)
	{
		if(opperations[i] == '/')
		{
			nums[i] = nums[i]/nums[i+1];

			for(j=i+1; j<length-1; j++)
				nums[j] = nums[j+1];

			length--;
		}
	}

	for(i=0; i<length; i++)
		res *= nums[i];

	free(nums);
	free(opperations);

	printf("\n\tANSWER:");
	scanf("%f", &input);
	while(input > res+MAX_ERROR || input < res-MAX_ERROR)
	{
		printf("\tWRONG!\n\n\tANSWER: ");
		scanf("%f", &input);
	}

	printf("\tCORRECT!\n\n");
}
