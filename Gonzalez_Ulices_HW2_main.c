/**************************************************************
* Class::  CSC-415-01 Fall 2024
* Name:: Ulices Gonzalez
* Student ID:: 923328897
* GitHub-Name:: ulicessgg
* Project:: Assignment 2 – Stucture in Memory and Buffering
*
* File:: Gonzalez_Ulices_HW2_main.c
*
* Description:: This file creates an instance of the personal
* information struct provided in the assignment2.h file and
* allocates the memory for the instance using malloc and then
* proceeds to assign values to each variable in the struct
* after this is completed the following portion of the program
* allocates memory for a character buffer that is then filled
* with string values and then committed once full and repreated
* until no values are left to be comitted, this will then lead
* to the program returning a value to check the success of the
* processes that have been completed and will display a hexdump
* generated over the course of the program being executed
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
    }

    // sets the values of the pi using the first two command line arguements
    // and with hardcoded values
    pi->firstName = argv[1];
    pi->lastName = argv[2];
    pi->studentID = 923328897;
    pi->level = SENIOR;
    pi->languages = KNOWLEDGE_OF_C | KNOWLEDGE_OF_JAVA |
                    KNOWLEDGE_OF_JAVASCRIPT | KNOWLEDGE_OF_PYTHON |
                    KNOWLEDGE_OF_CPLUSPLUS | KNOWLEDGE_OF_SQL |
                    KNOWLEDGE_OF_HTML | KNOWLEDGE_OF_MIPS_ASSEMBLER |
                    KNOWLEDGE_OF_R | KNOWLEDGE_OF_BASIC;
    strncpy(pi->message, argv[3], sizeof(pi->message));

    // testing writePersonalInfo with pi to make sure it runs sucessfully
    if(writePersonalInfo(pi) != 0)
    {
        printf("\nwrite personal failed to write pi and did not return 0\n");
    }

    // deallocates the memory being taken up by the pi instance
    free(pi);

    // char pointer is allocated to the size of 256 and spaceUsed is set to 0  
    // since the buffer is empty
    char* buffer = malloc(BLOCK_SIZE);
    int spaceUsed = 0;

    // testing writePersonalInfo with pi to make sure it runs sucessfully
    if(buffer == NULL)
    {
        printf("\nmalloc failed to allocate the buffer\n");
    }

    // initializes the value of i with the first getNext value
    const char* i = getNext();
    
    // the while loop will iterates using the getNext value assigned to iterator
    // i once the getNext function returns a NULL sucessfully this will signal  
    // the end of the strings
    while(i != NULL)
    {
        // the returned strlen value will be saved and used for copying strings
        // into the buffer and also checking if the buffer is in need of being
        // committed
        int spaceNeeded = strlen(i);

        // if the buffer is about to be or is full it will then copy to its
        // available space and then be committed using commitBuffer which
        // will then be followed by resetting the spacedNeeded and spaceUsed
        // variables as well as moving the iterator along to the postion after
        // the now truncated string
        if(spaceUsed + spaceNeeded >= BLOCK_SIZE)
        {
            memcpy(buffer + spaceUsed, i, (BLOCK_SIZE - spaceUsed));
            commitBlock(buffer);

            i += (BLOCK_SIZE - spaceUsed);
            spaceNeeded -= (BLOCK_SIZE - spaceUsed);
            spaceUsed = 0;
        }

        // the current iterator value will be stored into the buffer using
        // spaceUsed to set the position and spaceNeeded to define the end
        // of the string being copied which will be followed by updating
        // spaceUsed and getting the next string from getNext before looping
        memcpy(buffer + spaceUsed, i, spaceNeeded);
        spaceUsed += spaceNeeded;
        i = getNext();
    }

    // in the case that there is still left over strings in the buffer they will
    // be commited prior to the buffer being deallocated
    if(spaceUsed > 0)
    {
        printf("Theres still items in the buffer");
        commitBlock(buffer);
    }

    free(buffer);

    return checkIt();
}