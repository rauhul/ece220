#include "sudoku.h"

/*
 * Rauhul Varma
 * netID: rvarma2
 *
 * This program recursively solves a sudoku. At every node it checks if the sudoku is filled;
 * if the sudoku is filled the program will pop off the node with a success. If the node is 
 * not filled, the program will find the first empty entry and find a value for the entry 
 * (determined using helper functions). If there is no valid value for the entry the program 
 * will pop off the node with a failure. If there is a valid value for the entry the program
 * will branch and begin again with a new node where the entry has this value.
 *
 */

// procedure: print_sudoku
void print_sudoku(int sudoku[9][9]) {
	int i, j;
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			printf("%2d", sudoku[i][j]);
		}
		printf("\n");
	}
}

// procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
	FILE *reader = fopen(fpath, "r");
	assert(reader != NULL);
	int i, j;
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			fscanf(reader, "%d", &sudoku[i][j]);
		}
	}
	fclose(reader);
}

//-------------------------------------------------------------------------------------------------
// start coding your MP here.
// ------------------------------------------------------------------------------------------------

// function: is_val_in_row
// return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
	// abort if invalid inputs
	assert(i>=0 && i<9);

	// declare column counter
	int col;
	// iterate through the columns in row i
	for(col=0; col<9; col++) {
		// check if the sudoku at this column contains the value
		if (val == sudoku[i][col]) {
			// value already exits: return success
			return 1;
		}
	}
	// default, return failture
	return 0;
}

// function: is_val_in_col
// return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
	// abort if invalid inputs
	assert(j>=0 && j<9);

	// declare row counter
	int row;
	// iterate through the rows in column j
	for(row=0; row<9; row++) {
		// check if the sudoku at this row contains the value
		if (val == sudoku[row][j]) {
			// value already exits: return success
			return 1;
		}
	}
	// default, return failture
	return 0;
}

// function: is_val_in_3x3_zone
// return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
	// abort if invalid inputs
	assert(i>=0 && i<9);
	assert(j>=0 && j<9);

	// divide by 3 to get the zone indices, decimal value is automatically truncated
	// multiply by 3 to get the zone's starting index
	int zoneRowStart = (i/3)*3;
	int zoneColStart = (j/3)*3;

	// declare row and column counters
	int row, col;
	// iterate through the indices in one zone
	for(row=0; row<=2; row++) {
		for(col=0; col<=2; col++) {
			// check if the sudoku in this position of the zone contains the value
			// offset using the zoneRowStart and zoneColStart indices caluated earlier
			if (val == sudoku[zoneRowStart+row][zoneColStart+col]) {
				// value already exits: return success
				return 1;
			}
		}
	}
	// default, return failture
	return 0;
}

// function: is_val_valid
// return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
	// for clarity, check each of the sudoku validity conditions and store them in a boolean
	int val_in_row = is_val_in_row(val, i, sudoku);
	int val_in_col = is_val_in_col(val, j, sudoku);
	int val_in_3x3 = is_val_in_3x3_zone(val, i, j, sudoku);
	
	// check if any of the conditions fail
	if (val_in_row || val_in_col || val_in_3x3) {
		// failed a condition, return failure
		return 0;
	}
	
	// default, return success
	return 1;
}

// function: is_in_diag
// return true if the val is in one of the diagonals.
int is_in_diag(const int val, const int i, const int j, const int sudoku[9][9]) {
	// abort if invalid inputs
	assert(i>=0 && i<9);
	assert(j>=0 && j<9);

	// declare diagonal counters
	int k;
	// check validity if the index is in the forward diagonal 
	if (i == j) {
		for(k=0; k<9; k++) {
			// check if the sudoku at this index of the diagonal contains the value
			if (val == sudoku[k][k]) {
				// value already exits: return success
				return 1;
			}
		}
	}

	// check validity if the index is in the backward diagonal 
	// dont use 'else if' in the case (4,4) where the index is in both diagonals
	if (i == 8-j) {
		for(k=0; k<9; k++) {
			// check if the sudoku at this index of the diagonal contains the value
			if (val == sudoku[k][8-k]) {
				// value already exits: return success
				return 1;
			}
		}
	}

	// default, return failure
	return 0;
}

// procedure: solve_sudoku
// solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
	// look for an empty cell by iterating through the array
	// declare row and column counters
	int i, j;
	for(i=0; i<9; i++) {
		for(j=0; j<9; j++) {
			if (sudoku[i][j] == 0) {
				// stop looking for an empty cell after one is found
				goto findValueForCell;
			}
		}
	}
	// no cells are empty, pop the node with success
	return 1;

	// find a possible value for the cell
	findValueForCell: int val;
	for(val=1; val<=9; val++) {
		// check value validity with both the original and challenege conditions
		if (is_val_valid(val, i, j, sudoku) && !is_in_diag(val, i, j, sudoku)) {
			// fill sudoku with this value
			sudoku[i][j] = val;
			// push new node onto the tree and check validity
			if (solve_sudoku(sudoku)) {
				// branch is valid, pop node with success
				return 1;
			}
			// reset if branch failed to find a solution
			sudoku[i][j] = 0; 
		}
	}

	// node has an empty cell with no possible values, pop node with failure
	return 0;
}