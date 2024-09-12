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

    // pi values are populated prior to writing the instance
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

    free(pi);

    // buffer is created and allocated using BLOCK_SIZE
    char* buffer = malloc(BLOCK_SIZE);
    int spaceUsed = 0;

    // initialize the value of character pointer temp with getNext
    const char* temp = getNext();

    // while temp is not NULL the temp is copied to the buffer
    while(temp != NULL)
    {
        // spaceNeeded is set to the length of temp
        int spaceNeeded = strlen(temp);

        // if buffer is near capacity  
        if(spaceUsed + spaceNeeded >= BLOCK_SIZE)
        {
            // as much of temp is copied and the buffer is commited
            memcpy(buffer + spaceUsed, temp, (BLOCK_SIZE - spaceUsed));
            commitBlock(buffer);

            // temp is moved ahead after the copied contents
            temp += (BLOCK_SIZE - spaceUsed);

            // spaceNeeded and spaceNeed are updated
            spaceNeeded -= (BLOCK_SIZE - spaceUsed);
            spaceUsed = 0;
        }

        // contents of temp are copied and spaceUsed is updated
        memcpy(buffer + spaceUsed, temp, spaceNeeded);
        spaceUsed += spaceNeeded;

        // temp is set to the next string returned by getNext()
        temp = getNext();
    }

    // if any strings are leftover the buffer will be commited
    if(spaceUsed > 0)
    {
        commitBlock(buffer);
    }

    // buffer is deallocated
    free(buffer);

    // checkIt is called and it's return value is returned upon exit
    return checkIt();
}