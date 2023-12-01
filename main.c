/*********************************************************************/
/*                                                                   */
/*   PROGRAM for arithmetic training, which generates random         */
/*   arithmetic/numerical calculus problems, based on user's choice  */
/*   of opperations, difficulty and session length.                  */
/*                                                                   */
/*********************************************************************/
/*                                                                   */
/*   Author: caio-o -- Caio Barbieri                                 */
/*                                                                   */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void addAndSub(int difficulty);
void multAndDiv(int difficulty);
void suddenDeath(int mode, int difficulty, int* hasMissed);
void swap(int *a, int *b);

int main(void)
{
	int i;
	int mode, difficulty, problemAmount;
	int hasMissed = 0;

	printf("\nWhat would you like to train?");
	printf("\n\t[1] Addition and subtraction");
	printf("\n\t[2] Multiplication");
	printf("\n\t[3] Both\n");

	scanf("%d", &mode);

	printf("\nWhat difficulty do you wish?");
	printf("\n\t[1] Easy");
	printf("\n\t[2] Medium");
	printf("\n\t[3] Hard");
	printf("\n\t[4] Absurd\n\n");

	scanf("%d", &difficulty);

	printf("\nHow many problems do you want to solve? Type 0 to play until you miss (sudden death).\n\n");

	scanf("%d", &problemAmount);

	srand(time(NULL));

	//TODO: (1) Calculate total time taken and also (2) the average time taken to solve each problem

	for(i=0; i<problemAmount; i++)
	{
		printf("PROBLEM %d: ", i+1);
		addAndSub(difficulty);
	}

	return 0;
}

//Function fo problems that consist only of addition and subtraction
//i.e.: 123 + 323 - 45
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

	//TODO: Count the time each problem takes, and print it

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
		printf("WRONG\nANSWER: ");
		scanf("%d", &input);
	}

	printf("CORRECT\n\n");

	free(nums);
}

//This function generates a problem of which the opperations are only multiplication and division,
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
	
	if(length > 2) // If there is room for it, randomply places subtracitons or divisions, but not in place of the first opperation
	{
		opperations [rand()%(length-2) + 1] = '-';
		opperations [rand()%(length-2) + 1] = '/';
	}
}

void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}
