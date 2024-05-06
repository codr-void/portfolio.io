/**
*   TEAM 4
*   Names:  Mohammad Hasan
*           Wa'el Alkalbani
*           Mohamed Gnedi
*           Yousef Alothman
*
*   Project: ECE 585 Final Cache Project
*   File: main.c
*
*   Description: This file contains the main function that drives the cache simulation.
*                It reads trace values from a file and performs corresponding cache operations.
*/

#include "cache.h"	// Include the cache header file for cache
#include <stdio.h>	// Include standard input/output library 
#include <stdlib.h>	// Include standard library for general functions


int main() {
    // Define variables to hold trace values and parsed hex values from the input file
    unsigned int trace_value = 0;
    char char_value_from_text_file[32];
    uint32_t hex_value_from_text_file = 0x0;
    uint32_t byte_select_bits = 0x0;
    uint32_t address_bits = 0x0;
    uint32_t tag_bits = 0x0;

    // Specify the filename from which to read the trace values
    char *filename = "test_cache.txt";
    // Open the file for reading
    FILE *fp = fopen(filename, "r");

    // Define a buffer to hold each line read from the file
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    // Check if the file was successfully opened
    if (fp == NULL) {
        // Print an error message if the file could not be opened
        printf("Error: could not open file %s", filename);
        // Return with an error code
        return 1;
    }

// Prompt the user to select a mode for the simulation
// The mode determines how the cache behaves in certain scenarios
do {
    // Welcome message with fancy design, project description, and author names
    printf("-------------------------------🌟 Welcome to the Cache Simulation Program 🌟-------------------------------\n");
    printf("Simulates various cache operations based on input hex trace .txt data file located within program directory\n");
    printf("-----------------------------------------------------------------------------------------------------------\n\n");
    // Display the mode instructions
    printf("---------------------------Please select an operation mode (enter the number)------------------------------\n");
    printf("0: Simulation displays only the required summary of usage statistics and responses to 9s in the trace file.\n");
    printf("1: Simulation displays everything from  mode 0  but also includes  communication  messages to the L2 cache.\n");
    printf("2: Close the program.\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("Enter simulation mode number: ");
    // Read the mode selected by the user
    scanf("%u", &chosen_mode);

    // Check if the user selected mode 2 to close the program
    if (chosen_mode == 2) {
        printf("👋 Closing the program. Thank you for using our cache simulation.\n");
        return 0; // Exit the program gracefully
    }
    // Repeat the prompt if the input mode is invalid
    } while (chosen_mode > 2);


    // Main loop to read and process each line from the input file
    while (fgets(buffer, MAX_LENGTH, fp)) {
        // Extract the trace value (the first character of the line) from the buffer
        trace_value = buffer[0] - '0';

        // Extract the hex value (the rest of the line) from the buffer
        sscanf(buffer, "%*d %s", char_value_from_text_file);
        // Convert the hex string to an integer value
        hex_value_from_text_file = (uint32_t)strtoul(char_value_from_text_file, NULL, 16);

        // Extract the byte select bits from the hex value
        byte_select_bits = hex_value_from_text_file & 0x3F;
        // Extract the address bits from the hex value
        address_bits = (hex_value_from_text_file >> 6) & 0x3FFF;
        // Extract the tag bits from the hex value
        tag_bits = hex_value_from_text_file >> 20;

        // Switch statement to handle different trace values and perform corresponding cache operations
        switch(trace_value) {
            // Case for L1 cache read operation
            case L1_READ:
                // Perform the read operation and check for errors
                if (readData_L1Cache(hex_value_from_text_file))
                    // Print an error message if the operation fails
                    printf("\n\tERROR: L1 data cache read");
                break;
            // Case for L1 cache write operation
            case L1_WRITE:
                // Perform the write operation and check for errors
                if (writeData_L1Cache(hex_value_from_text_file))
                    // Print an error message if the operation fails
                    printf("\n\tERROR: L1 data cache write");
                break;
            // Case for L1 instruction fetch operation
            case L1_FETCH_INSTRUCTION:
                // Perform the instruction fetch operation and check for errors
                if (fetchInstruction_L1Cache(hex_value_from_text_file))
                    // Print an error message if the operation fails
                    printf("\n\tERROR: L1 instruction cache fetch");
                break;
            // Case for invalidating L2 cache entry
            case INVALIDATE_L2:
                // Perform the invalidate operation and check for errors
                if (invalidate_L2CacheEntry(hex_value_from_text_file))
                    // Print an error message if the operation fails
                    printf("\n\tERROR: L2 cache invalidate");
                break;
            // Case for snooping L2 cache
            case SNOOP_L2_CACHE:
                // Perform the snoop operation and check for errors
                if (snoopData_L2Cache(hex_value_from_text_file))
                    // Print an error message if the operation fails
                    printf("\n\tERROR: L2 data request from snoop");
                break;
            // Case for resetting the cache and statistics
            case RESET_CACHE:
                // Reset all cache entries and statistics
                reset_AllCacheAndStats();
                break;
            // Case for printing all cache contents
            case PRINT_ALL_CACHE:
                // Display the contents of the cache
                display_AllCacheContents();
                break;
            // Default case for handling invalid trace values
            default:
                // Print an error message for invalid trace numbers
                printf("\n\tERROR: invalid trace number\n");
                // Return with an error code
                return -1;
        }
    }

    // Print a newline for formatting
    printf("\n");

    // Close the input file after processing all lines
    fclose(fp);
    
    
    // end the program.
    return 0;
}
