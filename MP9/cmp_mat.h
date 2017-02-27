#pragma once

#include <stdlib.h>
#include <stdio.h>

#ifndef SP_MAT
#define SP_MAT
#include "sparsemat.h"
#endif

void printl(sp_lils * mat); //print matrix in list of list format to terminal
void printt(sp_tuples * mat); // print matrix in tuples format to terminal

int matcmpl(sp_lils * matA, sp_lils *matB); //not implemented
int matcmpt(sp_tuples * matA, sp_tuples * matB); //not implemented

