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
#include "functions.h"

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

	switch(mode)
	{
	case 1:
		for(i=0; i<problemAmount; i++)
		{
			printf("PROBLEM %d: ", i+1);
			addAndSub(difficulty);
		}
		break;

	case 2:
		for(i=0; i<problemAmount; i++)
		{
			printf("PROBLEM %d: ", i+1);
			multAndDiv(difficulty);
		}
		break;

	default:
		for(i=0; i<problemAmount; i++)
		{
			printf("PROBLEM: %d ", i+1);
			if(rand()%2)
				addAndSub(difficulty);
			else
				multAndDiv(difficulty);
		}
	}

	return 0;
}

