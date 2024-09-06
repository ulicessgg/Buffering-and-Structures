/**************************************************************
* Class::  CSC-415-01 Fall 2024
* Name:: Ulices Gonzalez
* Student ID:: 923328897
* GitHub-Name:: ulicessgg
* Project:: Assignment 2 – Stucture in Memory and Buffering
*
* File:: Gonzalez_Ulices_HW2_main.c
*
* Description::
*
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment2.h"

int main(int argc, char* argv[])
{
    // malloc allocates the memory for pi by returning a pointer of the
    // size of the personalInfo struct or null if it is unable to allocate
    personalInfo* pi = malloc(sizeof(struct personalInfo));

    //testing pi to make sure it isnt null
    if(pi == NULL)
    {
        printf("\nmalloc failed to allocate pi\n");
        return 0;
    }

    // sets the values of the pi values using the first two command line arguements
    // and with hardcoded values
    pi->firstName = argv[1];
    pi->lastName = argv[2];
    pi->studentID = 923328897;
    pi->level = SENIOR;
    pi->languages = KNOWLEDGE_OF_C && KNOWLEDGE_OF_JAVA &&
                    KNOWLEDGE_OF_JAVASCRIPT && KNOWLEDGE_OF_PYTHON &&
                    KNOWLEDGE_OF_CPLUSPLUS && KNOWLEDGE_OF_SQL &&
                    KNOWLEDGE_OF_HTML && KNOWLEDGE_OF_MIPS_ASSEMBLER &&
                    KNOWLEDGE_OF_R && KNOWLEDGE_OF_BASIC;
    strncpy(pi->message, argv[3], sizeof(pi->message));

    // testing writePersonalInfo with pi to make sure it runs sucessfully
    if(writePersonalInfo(pi) != 0)
    {
        printf("\nwrite personal failed to write pi and did not return 0\n");
        return 0;
    }

    free(pi);

    return 0;
}