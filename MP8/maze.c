/*
    Name: Rohan Mathur
    NetID: rmathur2

    This program accepts mazes via text file input, and then attempts to solve them using the DFS algorithm (depth first search). It does this by first identifying the start and end points, and then applying the DFS algorithm to navigate through the maze finding a path to the end. It then prints the maze and checks to confirm that the solution found is indeed a correct solution.
 */


#include <stdio.h>
#include "maze.h"

/*
 * findStartEnd -- finds the x and y location of the start and end of the  maze
 *                 if the end or start does not exist should output (-1, -1) as the location
 * INPUTS:         maze -- 2D char array that holds the contents of the maze
 *                 width -- width of the maze
 *                 height -- height of the maze
 *                 xStart -- pointer to where x start location should be stored
 *                 yStart -- pointer to where y start location should be stored
 *                 xEnd -- pointer to where x end location should be stored
 *                 yEnd -- pointer to where y end location should be stored
 * OUTPUTS: xStart, yStart, xEnd, and yEnd set to corresponding locations
 * RETURN: none
 * SIDE EFFECTS: none
 */
void findStartEnd(char ** maze, int width, int height, int * xStart, int * yStart, int * xEnd, int * yEnd)
{
    // initialize start and end values to those if not found
    *xStart = -1;
    *yStart = -1;
    *xEnd = -1;
    *yEnd = -1;

    // try and find start and end and replace values if found
    int x, y;
    for(y = 0; y < height; y++){
        for(x = 0; x < width; x++){
            // check for the start character
            if (maze[x][y] == 'S'){
                *xStart = x;
                *yStart = y;
            }

            // check for the end character
            if(maze[x][y] == 'E'){
                *xEnd = x;
                *yEnd = y;
            }
        }
    }
    return;
}

/*
 * printMaze -- prints out the maze in a human readable format (should look like examples)
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 * OUTPUTS:     none
 * RETURN:      none
 * SIDE EFFECTS: prints the maze to the console
 */
void printMaze(char ** maze, int width, int height)
{
    // loop through whole maze and print the proper character
    int x, y;
    for(y = 0; y < height; y++){
        for(x = 0; x < width; x++){
            // print the character
            printf("%c", maze[y][x]);
        }
        // print a new line when the row is finished
        printf("\n");
    }
}


 void sorter(int *manhattanDistance, char *manhattanDirections, int length){ //Sorts the distances by the optimal manhattan heuristic. This is how we determine which direction to try first.
    int s = 1;
    int i = 9;
    while(s) {
        s = 0;
        for (i = 1; i < length; i++){
            if(manhattanDistance[i] < manhattanDistance[i-1]){
                int t = manhattanDistance [i];
                manhattanDistance[i] = manhattanDistance[i-1];
                manhattanDistance[i-1] = t;
                char tc = manhattanDirections [i];
                manhattanDirections[i] = manhattanDirections[i-1];
                manhattanDirections[i-1] = tc;
                s = 1;
            }
        }
    }
}

/*
    Function that returns the absolute value of the number provided
 */
int absolute(int num){
    // return the number * -1 if its below 0, or return the number if its already positive
    if(num < 0) {
        return num * -1;
    }
    else {
        return num;
    }
}

/*
    Calculate the manhattand distance and return it using the formula provided
 */
int manhattanCalculation (int xPos, int xEnd, int yPos, int yEnd){
    return absolute((yEnd - yPos))+ absolute((xEnd - xPos));
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:                  maze -- 2D char array that holds the contents of the maze
 *                          width -- the width of the maze
 *                          height -- the height of the maze
 *                          xPos -- the current x position within the maze
 *                          yPos -- the current y position within the maze
 *                          xEnd -- the x position of the end of the maze
 *                          yEnd -- the y position of the end of the maze
 * OUTPUTS:                 updates maze with the solution path ('.') and visited nodes ('~')
 * RETURNS:                 0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:            none
 */



int solveMazeManhattanDFS(char ** maze, int width, int height, int xPos, int yPos, int xEnd, int yEnd)
{
    if(xPos == xEnd && yPos == yEnd){ //Checks if we have completed
        return 1;
    }
    if(xPos < 0 || xPos >= width || yPos < 0 || yPos >= height){
        return 0;
    }
    if(maze[xPos][yPos] == '%' || maze[xPos][yPos] == '.' || maze[xPos][yPos] == '~'){ //Drop a ~ whenever we hit a wall and realize that we are following the wrong path
        return 0;
    }
    if(maze[xPos][yPos] != 'S'){
        maze[xPos][yPos] = '.';
    }
    int manhattanDistance[4]; //4 for each direction
    manhattanDistance[0] = manhattanCalculation(xPos, xEnd, yPos - 1, yEnd); //fill an array with the different manhattan heuristics
    manhattanDistance[1] = manhattanCalculation(xPos, xEnd, yPos + 1, yEnd);
    manhattanDistance[2] = manhattanCalculation(xPos - 1,xEnd, yPos, yEnd);
    manhattanDistance[3] = manhattanCalculation(xPos + 1,xEnd, yPos, yEnd);
    char manhattanDirections[4] = {'u', 'd', 'l', 'r'}; //the characters have to do with the direction of the associated manhattan heuristic
    sorter(manhattanDistance, manhattanDirections, 4);

    int i;
    for (i = 0; i < 4; i++){
        if(manhattanDirections[i] == 'l'){
            if(solveMazeManhattanDFS(maze, width, height, xPos - 1, yPos, xEnd, yEnd)){//Check the manhattan heuristic up, down, left or right.
                return 1;
            }
        } else if(manhattanDirections[i] == 'd'){
            if(solveMazeManhattanDFS(maze, width, height, xPos, yPos+1, xEnd, yEnd)){
                return 1;
            }
        } else if(manhattanDirections[i] == 'r'){
            if(solveMazeManhattanDFS(maze, width, height, xPos+1, yPos, xEnd, yEnd)){
                return 1;
            }
        } else {
            if (solveMazeManhattanDFS(maze, width, height, xPos, yPos - 1, xEnd, yEnd)){
                return 1;
            }
        }
    }
    if(maze[xPos][yPos] != 'S'){
        maze[xPos][yPos] = '~';
    }
    return 0;
}

/*
 * checkMaze -- checks if a maze has a valid solution or not
 * INPUTS:      maze -- 2D char array that holds the contents of the maze
 *              width -- width of the maze
 *              height -- height of the maze
 *              x -- the starting x position in the maze
 *              y -- the starting y position in the maze
 * OUTPUTS:     none
 * RETURN:      1 if the maze has a valid solution, otherwise 0
 * SIDE EFFECTS: none
 */
int checkMaze(char ** maze, int width, int height, int x, int y)
{
    for (y=1; y< height-1; y++){
        for(x=1; x<width-1; x++){
            int count = 0;
            if (maze[x][y] == '.'){
                if(maze[x][y-1] == '.') count++;
                if (maze[x+1][y] == '.') count++;
                if (maze[x][y+1] == '.') count++;
                if (maze[x-1][y] == '.') count++;
                if (count > 2) return 0;
            }
        }
    }
    return 1;

}


/*
 * solveMazeBFS -- solves the maze using a breadth first search algorithm
 * INPUTS:         maze -- A 2D array that contains the contents of the maze
 *                 width -- the width of the maze
 *                 height -- the height of the maze
 *                 xPos -- the starting x position within the maze
 *                 yPos -- the starting y position within the maze
 * OUTPUTS:        none
 * RETURNS:        0 if the maze is unsolvable, else 1
 * SIDE EFFECTS:   marks the cells within the maze as visited or part of the solution path
 */



int solveMazeBFS(char ** maze, int width, int height, int xPos, int yPos)
{
    return 0;
}





/*
 * enqueue -- enqueues an integer onto the given queue
 * INPUTS:    queue -- a pointer to the array that will hold the contents of the queue
 *            value -- the value to  enqueue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   none
 * SIDE EFFECTS: adds an item to the queue
 */
void enqueue(int * queue, int value, int * head, int * tail, int maxSize)
{
    if ((*tail - maxSize) == *head)
    {
        printf("Queue is full\n");
        return;
    }
    *tail = *tail + 1;
    queue[*tail % maxSize] = value;
}

/* dequeue -- dequeues an item from the given queue
 * INPUTS:    queue -- a pointer to the array that holds the contents of the queue
 *            head -- a pointer to a variable that contains the head index in the queue
 *            tail -- a pointer to a variable that contains the tail index in the queue
 *            maxSize -- the maximum size of the queue (size of the array)
 * OUTPUTS:   none
 * RETURNS:   the value dequeued from the queue
 * SIDE EFFECTS: removes an item from the queue
 */
int dequeue(int * queue, int * head, int * tail, int maxSize)
{
    if (*head == *tail)
    {
        printf("Queue is empty\n");
        return -1;
    }
    *head = *head + 1;
    return queue[*head % maxSize];
}
