//rows and columns should be zero indexed!!

typedef struct sp_tuples_node
{
    double value;
    int row;
    int col;
    struct sp_tuples_node * next;

} sp_tuples_node;

typedef struct sp_lils_col_node //a node in the list of columns in a row list.
{
	int idx_c;	//the current column
    double value;	//the element value at the current row and column
    struct sp_lils_col_node * next; 

} sp_lils_col_node;

typedef struct sp_lils_row_node //a node in the row list of sp_lils
{
    int idx_r; //the current row
    sp_lils_col_node * col_list_head; //list of columns in current row
    struct sp_lils_row_node * next; 

} sp_lils_row_node;

typedef struct sp_tuples //list of coordinate format - each node is a tuple containing row col and value.
{
    int m; //# of rows
    int n; //# of cols
    int nz;//# of non-zero entries in matrix

    sp_tuples_node * tuples_head;
} sp_tuples;

typedef struct sp_lils // list of lists format - stores a list of rows, each of which contains a list of columns.
{
    int m; //# of rows
    int n; //# of cols
    int nz; //# of non-zero entries in matrix

    sp_lils_row_node * row_list_head; //list of rows

} sp_lils;

// Read an input file and return a matrix
sp_tuples * load_tuples(char* input_file);
sp_lils * load_lils(char* input_file);

//helper functions
double ** linkedListToArray(sp_tuples * tuples); 
sp_tuples * arrayToLinkedList(double ** array, int rows, int cols); 

//given a matrix, return the value of the element in the matrix that corresponds to the given coordinates. coordinates are 0 indexed.
double gv_lils(sp_lils * mat_l,int row,int col);
double gv_tuples(sp_tuples * mat_t,int row,int col);

//given a matrix, set the value of the element that corresponds to the given coordinates.
void set_lils(sp_lils * mat_l, int row, int col, double value); 
void set_tuples(sp_tuples * mat_t, int row, int col, double value);

//Save the matrix to a text file.
void save_tuples(char * file_name, sp_tuples * mat_t);
void save_lils(char * file_name,sp_lils * mat_l);

//return a matrix that is the sum of matA and matB.
sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB);
sp_lils * add_lils(sp_lils * matA, sp_lils * matB);

//return a matrix that is the product of matA and matB. Beware that matrix multiplication is not commutative e.g. matA*matB != matB*matA
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB);
sp_lils * mult_lils(sp_lils * matA, sp_lils * matB);

//free any and all allocated space associated with the given matrix.
void destroy_tuples(sp_tuples * mat_t);
void destroy_lils(sp_lils * mat_l);


//convert a matrix from lists of lists to tuple format or vice-versa. Don't use these functions in any of your other functions.
sp_lils * tuples2lil(sp_tuples * input_mat_t); 
sp_tuples * lil2tuples(sp_lils * input_mat_l);
