
#include <stdio.h>


#include "cmp_mat.h"
#ifndef SP_MAT
#define SP_MAT
#include "sparsemat.h"
#endif

int main(int argc, char *argv[]){

    if(argc > 2){
        printf("Too many arguments.\n");
        return 0;
    }
    
    if (argc == 2){
        int s = atoi(argv[1]);
        switch (s){
            case 1:
                printf("Test 1: tuple functions\n");
                goto TEST_1;
                break;
            case 2:
                printf("Test 2: lil functions\n");
                goto TEST_2;
                break;
            case 3:
                printf("Test 3: conversion functions\n");
                goto TEST_3;
                break;
            default:
                printf("Error: Valid arguments are 1-3");
                return 0;
        }        
        printf("%s\n",argv[1]);
    }


	TEST_1:printf("calling load_tuples on \"matrices/input_mats/scrambled_rows.txt\":\n");
	sp_tuples * unscrambledrowst = load_tuples("matrices/input_mats/scrambled_rows.txt");
	printt(unscrambledrowst);
	
	printf("calling load_tuples on \"matrices/input_mats/withZeroes.txt\":\n");
	sp_tuples * withZeroest = load_tuples("matrices/input_mats/withZeroes.txt");
	printt(withZeroest);
	
	sp_tuples * a_At = load_tuples("matrices/input_mats/a_A.txt");
	sp_tuples * a_Bt = load_tuples("matrices/input_mats/a_B.txt");
	printf("a_Ct = a_A+a_B addition in tuples:\n");
	sp_tuples * a_Ct = add_tuples(a_At,a_Bt);
	printt(a_Ct);
	
	sp_tuples * sa_At = load_tuples("matrices/input_mats/sa_A.txt");
	sp_tuples * sa_Bt = load_tuples("matrices/input_mats/sa_B.txt");
	printf("sa_Ct = sa_A+sa_B sparse addition in tuples:\n");
	sp_tuples * sa_Ct = add_tuples(sa_At,sa_Bt);
	printt(sa_Ct);
	
	sp_tuples * m_At = load_tuples("matrices/input_mats/m_A.txt");
	sp_tuples * m_Bt = load_tuples("matrices/input_mats/m_B.txt");
	printf("m_Ct = m_A*m_B multiplication in tuples:\n");
	sp_tuples * m_Ct = mult_tuples(m_At,m_Bt);
	printt(m_Ct);
	
	sp_tuples * sm_At = load_tuples("matrices/input_mats/sm_A.txt");
	sp_tuples * sm_Bt = load_tuples("matrices/input_mats/sm_B.txt");
	printf("sm_Ct = sm_A*sm_B sparse multiplication in tuples:\n");
	sp_tuples * sm_Ct = mult_tuples(sm_At,sm_Bt);
	printt(sm_Ct);
	
	printf("Saving output matrices... \n");
	
	save_tuples("matrices/output_mats/withZeroest.txt",withZeroest);
	save_tuples("matrices/output_mats/unscrambled.txt",unscrambledrowst);
	save_tuples("matrices/output_mats/a_Ct.txt",a_Ct);
	save_tuples("matrices/output_mats/sa_Ct.txt",sa_Ct);
	save_tuples("matrices/output_mats/m_Ct.txt",m_Ct);
	save_tuples("matrices/output_mats/sm_Ct.txt",sm_Ct);
	
    printf("freeing matrices from memory..\n");
	destroy_tuples(withZeroest);
	destroy_tuples(unscrambledrowst);
	destroy_tuples(a_At);
	destroy_tuples(sa_At);
	destroy_tuples(m_At);
	destroy_tuples(sm_At);
	
	
	destroy_tuples(a_Bt);
	destroy_tuples(sa_Bt);
	destroy_tuples(m_Bt);
	destroy_tuples(sm_Bt);
	
	destroy_tuples(a_Ct);
	destroy_tuples(sa_Ct);
	destroy_tuples(m_Ct);
	destroy_tuples(sm_Ct);
	
    if(argc == 2)
        return 0;
	// LIL STUFF
	TEST_2: printf("calling load_lils on \"matrices/input_mats/scrambled_rows2.txt\":\n");
	sp_lils * unscrambledrows2l = load_lils("matrices/input_mats/scrambled_rows2.txt");
	printl(unscrambledrows2l);
	
	printf("calling load_lils on \"matrices/input_mats/withZeroes.txt\":\n");
	sp_lils * withZeroesl = load_lils("matrices/input_mats/withZeroes.txt");
	printl(withZeroesl);
	
	sp_lils * a_Al = load_lils("matrices/input_mats/a_A.txt");
	sp_lils * a_Bl = load_lils("matrices/input_mats/a_B.txt");
	printf("a_Cl = a_A+a_B addition in LIL:\n");
	sp_lils * a_Cl = add_lils(a_Al,a_Bl);
	printl(a_Cl);
	
	sp_lils * sa_Al = load_lils("matrices/input_mats/sa_A.txt");
	sp_lils * sa_Bl = load_lils("matrices/input_mats/sa_B.txt");
	printf("sa_Cl = sa_A+sa_B sparse addition in LIL:\n");
	sp_lils * sa_Cl = add_lils(sa_Al,sa_Bl);
	printl(sa_Cl);
	
	sp_lils * m_Al = load_lils("matrices/input_mats/m_A.txt");
	sp_lils * m_Bl = load_lils("matrices/input_mats/m_B.txt");
	printf("m_Cl = m_A*m_B multiplication in LIL:\n");
	sp_lils * m_Cl = mult_lils(m_Al,m_Bl);
	printl(m_Cl);
	
	sp_lils * sm_Al = load_lils("matrices/input_mats/sm_A.txt");
	sp_lils * sm_Bl = load_lils("matrices/input_mats/sm_B.txt");
	printf("sm_Cl = sm_A*sm_B sparse multiplication in LIL:\n");
	sp_lils * sm_Cl = mult_lils(sm_Al,sm_Bl);
	printl(sm_Cl);
	
    printf("saving output matrices..\n");
	save_lils("matrices/output_mats/withZeroesl.txt",withZeroesl);
	save_lils("matrices/output_mats/unscrambled2.txt",unscrambledrows2l);
	save_lils("matrices/output_mats/a_Cl.txt",a_Cl);
	save_lils("matrices/output_mats/sa_Cl.txt",sa_Cl);
	save_lils("matrices/output_mats/m_Cl.txt",m_Cl);
	save_lils("matrices/output_mats/sm_Cl.txt",sm_Cl);
	
    printf("freeing matrices from memory..\n");
	destroy_lils(withZeroesl);
	destroy_lils(unscrambledrows2l);
	destroy_lils(a_Al);
	destroy_lils(sa_Al);
	destroy_lils(m_Al);
	destroy_lils(sm_Al);
	
	destroy_lils(a_Bl);
	destroy_lils(sa_Bl);
	destroy_lils(m_Bl);
	destroy_lils(sm_Bl);
	
	destroy_lils(a_Cl);
	destroy_lils(sa_Cl);
	destroy_lils(m_Cl);
	destroy_lils(sm_Cl);

    if(argc == 2) 
        return 0;

	TEST_3: printf("loading a_A as tuples: \n");
    sp_tuples * a_Ato = load_tuples("matrices/input_mats/a_A.txt");
    printt(a_Ato);
    printf("Testing tuples2lil:\n");
    sp_lils * a_At2l = tuples2lil(a_Ato);

    printl(a_At2l);

    destroy_tuples(a_Ato);
    destroy_lils(a_At2l);

    printf("Testing lil2tuples:\n");
    sp_lils * a_Alo = load_lils("matrices/input_mats/a_B.txt");
    printl(a_Alo);
    sp_tuples * a_Al2t = lil2tuples(a_Alo);
    printt(a_Al2t);
    
    printf("freeing matrices from memory..\n");
    destroy_tuples(a_Al2t);
    destroy_lils(a_Alo);    


    return 0;
}
