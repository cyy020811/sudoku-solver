/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Chi-Yuan Yang 1169908
   Dated:     2021/09/16

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/


/****************************************************************/
/* read the input file into an one-dimensional array
*/
void
readsudoku(int* sudoku);

/* print the sudoku out into grid format
*/
void
printsudoku(int* sudoku);

/* check if the input file has mistakes
*/
int
checksudoku(int* sudoku);

/*solve the sudoku using strategy one
*/
int
strategyone(int* sudoku);

/*check the number of unknown cells in the sudoku
*/
int
checkunknown(int* sudoku);

/*copy the value of a sudoku to a new sudoku
*/
void
copysudoku(int* sudoku, int* newsudoku);
/****************************************************************/

/* main program controls all the action
*/
int
main(int argc, char* argv[]) {
	int sudoku[NCLL], cansolve = 1, isfirst = 1;
	fill_c2s();
	readsudoku(sudoku);
	int unknown = checkunknown(sudoku);
	printsudoku(sudoku);
	if (checksudoku(sudoku)) {
		while (cansolve) {
			if (!isfirst) {
				if (unknown == checkunknown(sudoku)) {
					break;
				} 				else {
					unknown = checkunknown(sudoku);
					strategyone(sudoku);
				}
			} 			else {
				strategyone(sudoku);
				isfirst = 0;
			}
		}
		printsudoku(sudoku);
	}
	if (unknown == 0) printf("\nta daa!!!\n");
	return 0;
}

void
readsudoku(int* sudoku) {
	int i, cell;
	for (i = 0; i < NCLL; i++) {
		scanf("%d", &cell);
		sudoku[i] = cell;
	}
}

void
printsudoku(int* sudoku) {
	int i, unknown = 0;
	printf("\n");
	/*count the number of unknown cells and transfer 0 to . as output*/
	for (i = 1; i <= NCLL; i++) {
		if (sudoku[i - 1] == 0) {
			if (i % NDIG == 0) printf(".");
			else printf(". ");
			unknown++;
		} 		else {
			if (i % NDIG == 0) printf("%d", sudoku[i - 1]);
			else printf("%d ", sudoku[i - 1]);
		}
		if (i % NDIG != 0) {
			if (i % NDIM == 0) printf("| ");
		} 		else if (i % (NDIG * NDIM) == 0 && i % NCLL != 0) {
			printf("\n------+-------+------\n");
		} 		else printf("\n");
	}
	/*show the number or unknown cells*/
	printf("\n");
	if (unknown == 1) printf("%2d cell is unknown\n", unknown);
	else printf("%2d cells are unknown\n", unknown);
}

int
checksudoku(int* sudoku) {
	int i, j, k, setviol = 0, totalviol = 0;
	for (i = 0; i < NSET; i++) {
		int issetviol = 0;
		for (j = 1; j <= NDIG; j++) {
			int instance = 0, violnum;
			for (k = 0; k < NDIG; k++) {
				if (sudoku[s2c[i][k]] == j) {
					instance++;
					violnum = j;
				}
			}
			if (instance > 1) {
				/*print the instances of each number that violated the
				sudoku format*/
				if (i < NDIG) printf("\nset %2d (row %d): %d instances of %d", i, i + 1, instance, violnum);
				else if (i < 2 * NDIG && i >= NDIG) printf("\nset %2d (col %d): %d instances of %d", i, i + 1 - NDIG, instance, violnum);
				else printf("\nset %2d (sqr %d): %d instances of %d", i, i + 1 - NDIG * 2, instance, violnum);
				totalviol++;
				issetviol = 1;
			}
		}
		if (issetviol) {
			setviol++;
		}
	}
	if (setviol > 0) {
		/*print the number of different sets that have violations*/
		if (setviol == 1) printf("\n\n%d set has violations\n", setviol);
		else printf("\n\n%d different sets have violations\n", setviol);
	}
	if (totalviol > 0) {
		/*print the total number of sets that have violations*/
		if (totalviol == 1) printf("%d violation in total\n", totalviol);
		else printf("%d violations in total\n", totalviol);
		return 0;
	}
	return 1;
}

int strategyone(int* sudoku) {
	int i, j, k, l, newsudoku[NCLL];
	int ischanged = 0;
	copysudoku(sudoku, newsudoku);
	for (i = 0; i < NCLL; i++) {
		if (sudoku[i] == 0) {
			int ans, anssum = 0;
			for (j = 1; j <= NDIM * NDIM; j++) {
				int isans = 1;
				for (k = 0; k < NGRP; k++) {
					for (l = 0; l < NDIM * NDIM; l++) {
						if (sudoku[s2c[c2s[i][k]][l]] == j) {
							isans = 0;
						}
					}
				}
				if (isans) {
					anssum++;
					ans = j;
				}
			}
			if (anssum == 1) {
				if (!ischanged) {
					printf("\nstrategy one\n");
					ischanged = 1;
				}
				newsudoku[i] = ans;
				printf("row %d col %d must be %d\n", c2s[i][0] + 1, c2s[i][1] + 1 - 9, ans);
			}
		}
	}
	copysudoku(newsudoku, sudoku);
	return 0;
}

int
checkunknown(int* sudoku) {
	int i, unknown = 0;
	for (i = 0; i < NCLL; i++) {
		if (sudoku[i] == 0) unknown++;
	}
	return unknown;
}

void
copysudoku(int* sudoku, int* newsudoku) {
	int i;
	for (i = 0; i < NCLL; i++) newsudoku[i] = sudoku[i];
}
/****************************************************************/
/*Algorithms are fun!*/