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
* information struct and allocates the memory using malloc and
* proceeds to populate its values, following this the program
* creates andn allocates memory for a character buffer which
* will be populated with strings and committed once full until
* no values are left to be comitted, this will then lead to the
* calling a check function and returning its value upon exit
* which will display a hexdump for analysis upon termination
*
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assignment2.h"

int main(int argc, char* argv[])
{
    // instance of personalInfo struct allocated using malloc
    personalInfo* pi = malloc(sizeof(struct personalInfo));

    // populates the values of pi using command line arguements
    // for the name and message, and uses predetermind values
    // for studentID, level, and languages
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

    // write the info prior to pi being deallocated
    writePersonalInfo(pi);

    free(pi);

    // buffer is allocated using malloc and specified size and spaceUsed
    // is set to 0 due to the buffer being empty
    char* buffer = malloc(BLOCK_SIZE);
    int spaceUsed = 0;

    // initializes the value of iterator i with the first getNext value
    const char* i = getNext();

    // while will loop until the return value of getNext() is null and
    // will also prevent the loop from running if getNext() returns a
    // null immediately
    while(i != NULL)
    {
        // length of the current value of i to be used for condition checks
        // and to properly copy strings into the buffer
        int spaceNeeded = strlen(i);

        // if the buffer is about to be or is full it will then copy to its
        // available space and then be committed using commitBuffer and reset
        // i, spaceNeeded, and spaceUsed for future use
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
        memcpy(buffer + spaceUsed, i, spaceNeeded);
        spaceUsed += spaceNeeded;

        // iterator i will be assigned the next value returned by getNext()
        // and if NULL will be caught ending the loop
        i = getNext();
    }

    // if any values are leftover in the buffer they will be commited prior
    // to deallocating the buffer
    if(spaceUsed > 0)
    {
        commitBlock(buffer);
    }

    free(buffer);

    return checkIt();
}