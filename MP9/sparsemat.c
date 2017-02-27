/*
    Name: Rohan Mathur
    NetID: rmathur2

    This program stores a sparse matrix using the tuple data storage idea, stored in linked list nodes. It first loads the tuples from a file and sorts it into row major order. From there, several functions have been implemented that allow you to add and multiply these matricies together, get details about a specific row and column, and more. Another method, called save_tuples, is implemented to store a matrix from linked list format back to a stored file.
 */

#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

sp_tuples * load_tuples(char* input_file) {
    // make the new tuples structure
    sp_tuples * tuples = (sp_tuples *) malloc(sizeof(struct sp_tuples));

    // initialize the sizing variables
    int rows, cols;
    tuples->nz = 0;
    int row, col;
    double value;

    // open the file for reading
    FILE * fp;
    fp = fopen(input_file, "r");
    fscanf(fp, "%d %d", &rows, &cols);

    // assign the rows and cols number based on what we read in from the file
    tuples->m = rows;
    tuples->n = cols;

    // make pointers for keeping track of list
    sp_tuples_node * new_node, * head;
    head = NULL;

    // read the file line by line and store it in the values specified
    while(fscanf(fp, "%d %d %lf", &row, &col, &value) != EOF) {
        if (value != 0) {
            // make a new node and add it to the chain
            new_node = (sp_tuples_node *) malloc(sizeof(struct sp_tuples_node));
            new_node->row = row;
            new_node->col = col;
            new_node->value = value;
            new_node->next = head;

            // update the length
            tuples->nz++;

            // update the head
            head = new_node;
        }
    }

    // stop writing to file
    fclose(fp);
    tuples->tuples_head = head;

    // make pointers
    sp_tuples_node *target, *prev, *curr, *new_head, *currPrev;
    new_head = NULL;

    // sort by finding the least element on criteria (row or column) and then building a new linked list based off of that
    int count = 0;
    while (count<tuples->nz) {
        prev = NULL;
        currPrev = NULL;
        curr = head;
        target = curr;

        // loop till the end in the linked list repeatedly within and find the valute matching criteria
        while(curr != NULL) {
            // if it matches, store it to add later
            if (curr->row * tuples->m + curr->col > target->row * tuples->m + target->col) {
                prev   = currPrev;
                target = curr;
            }
            currPrev = curr;
            curr = curr->next;
        }

        if (target == head) {
            head = head->next;
        }
        if (prev != NULL ) {
            prev->next = target->next;
        }

        // add the new item
        target->next = new_head;

        // iterate
        new_head = target;
        count++;
    }

    // update the header to point to that
    tuples->tuples_head = new_head;

    return tuples;
}

double gv_tuples(sp_tuples * mat_t, int row, int col) {
    // make a curr pointer and assign to top of chain
    sp_tuples_node * curr;
    curr = mat_t->tuples_head;

    // loop through chain until end
    while(curr->next != NULL) {
        // if found, return the value
        if((curr->row == row) && (curr->col == col)) {
            return curr->value;
        }

        // iterate
        curr = curr->next;
    }

    // return 0 if not found
    return 0;
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value) {
    // initialize varialbes
    int wasFound = 0;
    sp_tuples_node * prevNode = NULL;

    // initialize current stuff
    sp_tuples_node * curr;
    curr = mat_t->tuples_head;

    // loop through entire linked list
    while(curr->next != NULL) {
        // if we skipped it, add the node in
         if(curr->row >= row && curr->col >= col && !wasFound){
            sp_tuples_node * new_node = (sp_tuples_node *) malloc(sizeof(struct sp_tuples_node));
            new_node->row = row;
            new_node->col = col;
            new_node->value = value;

            new_node->next = curr;
            prevNode->next = new_node;
        }

        // if we found it, do something with it...
        if((curr->row == row) && (curr->col == col)) {
            wasFound = 1;

            // if the value was 0, delete it by skipping the node and freeing its memory
            if(value == 0) {
                prevNode->next = curr->next;
                free(curr);
            } else {
                // if found and we arent supposed to delete, update the value to the new one
                curr->value = value;
            }
        }
        // iterate and update the pointers
        prevNode = curr;
        curr = curr->next;
    }

    return;
}

void save_tuples(char * file_name, sp_tuples * mat_t) {
    // check if matrix input is null (needed for unimplemented lil methods)
    if(mat_t != NULL) {
        // open a file for writing
        FILE * fp;
        fp = fopen(file_name, "w");
        // write the row and column information to the file at the top
        fprintf(fp, "%d %d\n", mat_t->m, mat_t->n);

        // get a pointer to the head of the linked list
        sp_tuples_node * curr_node = mat_t->tuples_head;

        // loop through the entire linked list and print out the values properly
        while(curr_node != NULL) {
            int row = curr_node->row;
            int col = curr_node->col;
            double value = curr_node->value;

            // print the values from the current node
            fprintf(fp, "%d %d %lf\n", row, col, value);

            // iterate
            curr_node = curr_node->next;
        }

        // close the file for writing
        fclose(fp);
    }

    return;
}

sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB) {
    // return null if invalid data is provided
    if(matA->m != matB->m || matA->n != matB->n || matA == NULL || matB == NULL) {
        return NULL;
    }

    // assign space for a new matrix
    sp_tuples * matC = (sp_tuples *) malloc(sizeof(struct sp_tuples));

    // get the size of the new array
    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;

    // set pointers to top of matrix linked lists
    sp_tuples_node * curr_a_node = matA->tuples_head;
    sp_tuples_node * curr_b_node = matB->tuples_head;

    // set whether its the first or not to default true
    int isFirst = 1;

    while(curr_a_node != NULL || curr_b_node != NULL) {
        // allocate memory for a new node
        sp_tuples_node * new_node = (sp_tuples_node *) malloc(sizeof(struct sp_tuples_node));
        sp_tuples_node * prev_node;

        // check if a is done, then use b if so
        if(curr_a_node == NULL) {
            // use b
            // copy over row and col values and actual value
            new_node->row = curr_b_node->row;
            new_node->col = curr_b_node->col;
            new_node->value = curr_b_node->value;

            // set default next to null
            new_node->next = NULL;

            // set previous next to the current node if its not null (first run)
            if(prev_node != NULL) {
                prev_node->next = new_node;
            }
            prev_node = new_node;
            curr_b_node = curr_b_node->next;
        } else if (curr_b_node == NULL) {
            // else, use a if b is done
            // copy over row and col values and actual value
            new_node->row = curr_a_node->row;
            new_node->col = curr_a_node->col;
            new_node->value = curr_a_node->value;

            // set default next to null
            new_node->next = NULL;

            // set previous next to the current node if its not null (first run)
            if(prev_node != NULL) {
                prev_node->next = new_node;
            }
            prev_node = new_node;
            curr_a_node = curr_a_node->next;
        } else if(curr_a_node->row < curr_b_node->row) {
            // use a node if it comes first in row-major order
            // copy over row and col values and actual value
            new_node->row = curr_a_node->row;
            new_node->col = curr_a_node->col;
            new_node->value = curr_a_node->value;

            // set default next to null
            new_node->next = NULL;

            // set previous next to the current node if its not null (first run)
            if(prev_node != NULL) {
                prev_node->next = new_node;
            }
            prev_node = new_node;
            curr_a_node = curr_a_node->next;
        } else if (curr_b_node->row < curr_a_node->row) {
            // use b node if it comes first in row-major order
            new_node->row = curr_b_node->row;
            new_node->col = curr_b_node->col;
            new_node->value = curr_b_node->value;
            new_node->next = NULL;
            if(prev_node != NULL) {
                prev_node->next = new_node;
            }
            prev_node = new_node;
            curr_b_node = curr_b_node->next;
        } else {
            // means the rows are equal, so check columns
            if(curr_a_node->col < curr_b_node->col) {
                // use a node if it comes first in row-major order
                new_node->row = curr_a_node->row;
                new_node->col = curr_a_node->col;
                new_node->value = curr_a_node->value;
                new_node->next = NULL;
                if(prev_node != NULL) {
                    prev_node->next = new_node;
                }
                prev_node = new_node;
                curr_a_node = curr_a_node->next;
            } else if(curr_b_node->col < curr_a_node->col) {
                // use b node if it comes first in row-major order
                new_node->row = curr_b_node->row;
                new_node->col = curr_b_node->col;
                new_node->value = curr_b_node->value;
                new_node->next = NULL;
                if(prev_node != NULL) {
                    prev_node->next = new_node;
                }
                prev_node = new_node;
                curr_b_node = curr_b_node->next;
            } else {
                // both row and col are equal, so add the values and increment both
                new_node->row = curr_a_node->row;
                new_node->col = curr_a_node->col;
                new_node->value = curr_a_node->value + curr_b_node->value;
                new_node->next = NULL;
                if(prev_node != NULL) {
                    prev_node->next = new_node;
                }
                prev_node = new_node;
                curr_a_node = curr_a_node->next;
                curr_b_node = curr_b_node->next;
            }
        }

        // incremenet the size as we have added a new nonzero node
        matC->nz++;

        // if its first, assign the top of the tuple list to the new node and then turn off the switch for later iterations
        if(isFirst) {
            matC->tuples_head = new_node;
            isFirst = 0;
        }
    }

    return matC;
}

double ** linkedListToArray(sp_tuples * tuples) {
    int nz, row, col, i;
    // assign rows and cols based off of proper values
    int rows = tuples->m;
    int cols = tuples->n;
    // make 2d array to load into
    double** array;

    //allocate space for it
    array = (double**) malloc(rows*sizeof(double*));
    for (i = 0; i < rows; i++)
        // allocate space for rows
       array[i] = (double*) malloc(cols*sizeof(double));

   // find head
    sp_tuples_node *curr = tuples->tuples_head;

    // loop through array and zero it out initially
    for (row = 0; row < tuples->m; row++) {
        for (col = 0; col < tuples->n; col++) {
            array[row][col] = 0;
        }
    }
    // loop through tuples and add data to array based on what the tuples have
    for (nz = 0; nz < tuples->nz; nz++) {
        array[curr->row][curr->col] = curr->value;
        curr = curr->next;
    }

    return array;
}

sp_tuples * arrayToLinkedList(double ** array, int rows, int cols) {
    // allocate space for tuples
    sp_tuples * tuples = (sp_tuples *) malloc(sizeof(struct sp_tuples));
    sp_tuples_node *prev, *new_node;
    // allocate member varaibles for new tuples variable
    tuples->m = rows;
    tuples->n = cols;
    tuples->nz = 0;
    tuples->tuples_head = NULL;

    // track if its the first one needing the head
    int isFirst=1;
    int row, col;

    // loop through entire array
    for (row = 0; row < tuples->m; row++) {
        for (col = 0; col < tuples->n; col++) {
            // if its not equal to zero, create a new tuple
            if (array[row][col] != 0) {
                tuples->nz++;
                new_node = (sp_tuples_node *) malloc(sizeof(struct sp_tuples_node));
                new_node->row = row;
                new_node->col = col;
                new_node->value = array[row][col];
                new_node->next  = NULL;
                // set that as head if its the first one and reset isFirst to 0
                if (isFirst) {
                    tuples->tuples_head = new_node;
                    isFirst = 0;
                } else {
                    // set prev-next to the new node if its not the first iteration when its null
                    prev->next = new_node;
                }
                prev = new_node;
            }
        }
    }
    return tuples;
}

sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB) {
    if(matA->n != matB->m || matA == NULL || matB == NULL) {
        return NULL;
    }
    sp_tuples * matC = (sp_tuples *) malloc(sizeof(struct sp_tuples));
    matC->m = matA->m;
    matC->n = matB->n;
    matC->nz = 0;

    //Convert to Array
    double sum;
    int i, j, k;
    double** arrayA;
    arrayA = (double**) malloc(matA->m*sizeof(double*));
    for (i = 0; i < matA->m; i++)
       arrayA[i] = (double*) malloc(matA->n*sizeof(double));
    arrayA = linkedListToArray(matA);

    //Convert to Array
    double** arrayB;
    arrayB = (double**) malloc(matB->m*sizeof(double*));
    for (i = 0; i < matB->m; i++)
       arrayB[i] = (double*) malloc(matB->n*sizeof(double));
    arrayB = linkedListToArray(matB);

    //Create Array based off the two arrays
    double** arrayC;
    arrayC = (double**) malloc(matC->m*sizeof(double*));
    for (i = 0; i < matC->m; i++)
       arrayC[i] = (double*) malloc(matC->n*sizeof(double));

   // zero out the new array with the new dimensions
    for (i = 0; i <matC->m; i++ ) {
        for (j = 0; j<matC->n; j++) {
            arrayC[i][j] = 0;
        }
    }

    // multiply the two arrays together
    for (i = 0; i < matA->m; i++) {
        for (j = 0; j < matB->n; j++) {
            sum = 0;
            for (k = 0; k < matA->n; k++) {
                sum += arrayA[i][k] * arrayB[k][j];
            }
            arrayC[i][j] = sum;

            if (sum !=0) {
                matC->nz++;
            }
        }
    }

    // Convert to Linked list
    matC = arrayToLinkedList(arrayC, matC->m, matC->n);

    // free the space we allocated for arrayA and arrayB
    free(arrayA);
    free(arrayB);
    return matC;
}

void destroy_tuples(sp_tuples * mat_t) {
    // only clear if its not null
    if(mat_t != NULL) {
        // get a pointer to the top of the list
        sp_tuples_node * curr = mat_t->tuples_head;
        // get a pointer to the one that we should free
        sp_tuples_node * toBeFreed = NULL;

        // loop through entire list
        while(curr != NULL) {
            // set the current node to be freed
            toBeFreed = curr;

            // iterate current
            curr = curr->next;

            // free the curr memory
            free(toBeFreed);
        }

        // free the memory to the pointer to the head of the list
        free(mat_t->tuples_head);
    }

    return;
}

sp_lils * load_lils(char* input_file) {
    return NULL;
}

double gv_lils(sp_lils * mat_l,int row,int col) {
    return 0;
}

void set_lils(sp_lils * mat_l, int row, int col, double value) {
    return;
}

void save_lils(char * file_name,sp_lils * mat_l) {
    return;
}

sp_lils * add_lils(sp_lils * matA, sp_lils * matB) {
    return NULL;
    //return retmat;
}

sp_lils * mult_lils(sp_lils * matA, sp_lils * matB) {
    return NULL;
    //return retmat;
}

void destroy_lils(sp_lils * mat_l) {
    return;
}

sp_lils * tuples2lil(sp_tuples * input_mat_t) {
    return NULL;
    //return new_mat_l;
}

sp_tuples * lil2tuples(sp_lils * input_mat_l) {
    return NULL;
    //return new_mat_t;
}
