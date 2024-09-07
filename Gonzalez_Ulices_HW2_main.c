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

    // sets the values of the pi using the first two command line arguements
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

    // deallocates the memory being taken up by the pi instance
    free(pi);

    // char pointer is allocated to the size of 256 and spaceUsed is set to 0  
    // since the buffer is empty
    char* buffer = malloc(BLOCK_SIZE);
    int spaceUsed= 0;

    // testing writePersonalInfo with pi to make sure it runs sucessfully
    if(buffer == NULL)
    {
        printf("\nmalloc failed to allocate the buffer\n");
        return 0;
    }

    // initializes the value of i with the first getNext value
    const char* i = getNext();
    
    // while loop will iterates using the getNext value assigned to iterator i
    // once the getNext function returns a NULL sucessfully this will signal  
    // the end of the strings
    // if getNext returns a null to i prior to the while it will not allow for
    // the loop to execute avoiding any unnecassru processes from occuring
    while(i != NULL)
    {
        int spaceNeeded = strlen(i);

        if(spaceUsed + spaceNeeded >= BLOCK_SIZE)
        {
            memcpy(buffer + spaceUsed, i, BLOCK_SIZE - spaceUsed);
            commitBlock(buffer);

            printf("\nbuffer being filled and reaches the commit portion\n");
            return 0;
        }

        memcpy(buffer + spaceUsed, i, spaceUsed);
        spaceUsed += spaceNeeded;
    }

    return 0;
}