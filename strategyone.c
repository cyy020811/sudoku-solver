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