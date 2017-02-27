#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void freeMaze(char ** maze, int height);
 
int main(int argc, char **argv)
{
    int width, height;
    FILE *in;
    // attempt to open input file
    if (argc < 3)
    {
        printf("You need an input file and algorithm.\n");
        return -1;
    }
    in = fopen(argv[1], "r");
    if (in == NULL)
    {
        printf("Could not open file: %s\n", argv[1]);
        return -1;
    }
    // get ManhattanDFS/BFS from command line argument
    int mode = atoi(argv[2]);
    // read height and width from file
    fscanf(in, "%d", &width);
    fscanf(in, "%d", &height);
    fgetc(in);
    // allocate memory for 2D array maze
    char ** maze = (char **) malloc(height * sizeof(char*));
    int i;
    for(i = 0; i < height; i++)
    {
        maze[i] = (char *) malloc(width * sizeof(char));
    }
    // read contents of input file into maze
    char c;
    int x = 0, y = 0;
    while ((c = fgetc(in)) != EOF)
    {
        if (c == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        else
        {
            maze[y][x] = c;
            x++;
        }
    }
    fclose(in);
 
    int yStart, xStart, yEnd, xEnd;
    // get the start of the maze
    findStartEnd(maze, width, height, &xStart, &yStart, &xEnd, &yEnd);
    if (xStart == -1 || yStart == -1)
    {
        printf("Could not find start of maze\n");
        freeMaze(maze, height);
        return -1;
    }
    printf("Start of maze at (%d, %d)\n", xStart, yStart);

    // solve the maze using ManhattanDFS or BFS depending on what mode is
    int solved;
    if (mode == 0)
        solved = solveMazeManhattanDFS(maze, width, height, xStart, yStart, xEnd, yEnd);
    else
        solved = solveMazeBFS(maze, width, height, xStart, yStart);

    // if the maze is unsolvable print the maze and exit
    if (solved == 0)
    {
        printMaze(maze, width, height);
        printf("Maze is unsolvable\n");
    }
    // else print the maze and check that it's correct
    else
    {
        printMaze(maze, width, height);
        if(checkMaze(maze, width, height, xStart, yStart))
            printf("Maze is correct!\n");
        else
            printf("Maze is incorrect!\n");
    }

    // free the memory allocated for the maze
    freeMaze(maze, height); 
    return 0;
}

// Frees the memory allocated for maze
void freeMaze(char ** maze, int height)
{
    int i;
    for(i = 0; i < height; i++)
    {
        free(maze[i]);
    }
    free(maze);
}
