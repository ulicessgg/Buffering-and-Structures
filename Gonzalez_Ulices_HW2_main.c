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
    // instance of personalInfo struct is created and allocated
    personalInfo* pi = malloc(sizeof(struct personalInfo));

    // pi values are populated using command line arguements
    // for the first name, last name and message
    // studentID, level, and languages are initialized with
    // predetermined values
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

    // writePersonalInfo is called to write the pi instance
    writePersonalInfo(pi);

    // pi instance is deallocated
    free(pi);

    // c string buffer is created and allocated using BLOCK_SIZE
    // spaceUsed counter is created and set to 0 since buffer is
    // empty
    char* buffer = malloc(BLOCK_SIZE);
    int spaceUsed = 0;

    // initializes the value of c string i with the first getNext value
    const char* i = getNext();

    // while the value of i is not NULL the contents of i are copied to
    // the buffer, if the first getNext value is NULL the while will not
    // be executed and will be skipped
    while(i != NULL)
    {
        // spaceNeeded is set to the length of current string stored in i
        int spaceNeeded = strlen(i);

        // if buffer is about to be full it will then copy to as much of the
        // current string to its availabe space leading to commitBlock being
        // called to commit the buffer to the BLOCK_SIZE buffer
        if(spaceUsed + spaceNeeded >= BLOCK_SIZE)
        {
            // contents of i are copied to the buffer
            memcpy(buffer + spaceUsed, i, (BLOCK_SIZE - spaceUsed));
            // buffer is commited after its pointer is passed to commitBlock 
            commitBlock(buffer);

            // i, spaceNeeded, and spaceUsed are reset for future use
            i += (BLOCK_SIZE - spaceUsed);
            spaceNeeded -= (BLOCK_SIZE - spaceUsed);
            spaceUsed = 0;
        }

        // contents of i are copied to the buffer
        memcpy(buffer + spaceUsed, i, spaceNeeded);
        // spaceUsed is updated after new string is copied
        spaceUsed += spaceNeeded;

        // i is set to the next string returned by getNext()
        i = getNext();
    }

    // spaceUsed is checked and if greater than 0 any strings left in
    // buffer will be commited
    if(spaceUsed > 0)
    {
        commitBlock(buffer);
    }

    // buffer is deallocated
    free(buffer);

    // checkIt is called and it's return value is returned upon exit
    return checkIt();
}