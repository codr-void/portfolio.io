/**
*   TEAM 4
*   Names:  Mohammad Hasan
*           Wa'el Alkalbani
*           Mohamed Gnedi
*           Yousef Alothman
*
*   Project: ECE 585 Final Cache Project
*   File: cache.c
*
*   Description: This file contains the implementation of cache operations and statistics.
*/


#include "cache.h"	// Include the header file for cache simulation
#include <stdio.h>	// Include standard libraries for input/output
#include <stdlib.h>
#include <string.h>

// Define global cache arrays for data and instruction caches
CACHE data_cache[8];
CACHE instruction_cache[4];

// Define global statistics structure to track cache performance
STATISTICS statistics;

// Define a global variable to store the chosen mode for cache operation
unsigned int chosen_mode = 2;

// Function to find a matching data tag in the cache
int find_DataTag(unsigned int tag_bits) {
	int i = 0;
    // Check for matching tags
    while (data_cache[i].tag_bits != tag_bits) {
		i++;
    	if (i > 7)
    	    	// Return -1 if no matching tag is found
		return -1;
    }
    
    // Return the index of the matching tag
    return i;
}

// Function to find a matching instruction tag in the cache
int find_InstructionTag(unsigned int tag_bits) {
    	int i = 0;
    // Check for matching tags
    while (instruction_cache[i].tag_bits != tag_bits) {
	i++;
    	if (i > 3)
    	    	// Return -1 if no matching tag is found
		return -1;
    }
    
    // Return the index of the matching tag
    return i;
}

// Function to locate the Least Recently Used (LRU) data entry in the cache
int locateLRU_Data(void) {
    	 for (int i = 0; i < 8; ++i) {
    	if (data_cache[i].LRU_bits == 0x7)
    	    // Return the index of the LRU entry
            return i;
    }
    // Return -1 if no LRU entry is found
    return -1;
}

// Function to locate the Least Recently Used (LRU) instruction entry in the cache
int locateLRU_Instruction(void) {
    	for (int i = 0; i < 4; ++i) {
    	if (instruction_cache[i].LRU_bits == 0x3)
    	    // Return the index of the LRU entry
            return i;
    }
    // Return -1 if no matching tag is found
    return -1;
}

// Function to find an entry with an invalid MESI state in the data cache
int findInvalid_Data_MESIState(void) {
    	for (int i = 0; i < 8; ++i){
	if (data_cache[i].MESI_state == 'I')
	    // Return the index of the entry with an invalid MESI state
	    return i;
    }
    // Return -1 if no entry with an invalid MESI state is found
    return -1;
}

// Function to find an entry with an invalid MESI state in the instruction cache
int findInvalid_Instruction_MESIState(void) {
    	for (int i = 0; i < 4; ++i) {
	if (instruction_cache[i].MESI_state == 'I')
	    // Return the index of the entry with an invalid MESI state
	    return i;
    }
    // Return -1 if no entry with an invalid MESI state is found
    return -1;
}

// Function to update the LRU bits for the instruction cache after accessing a specific entry
void updateLRU_Instruction(unsigned int way) {
    	// Store the current LRU value of the accessed entry
    	int current_LRU = instruction_cache[way].LRU_bits;
    for (int i = 0; i < 4; ++i) {
	if (instruction_cache[i].LRU_bits <= current_LRU)
	    instruction_cache[i].LRU_bits++;
    }
    // Set the LRU bits of the accessed entry to 0
    instruction_cache[way].LRU_bits = 0;
    return;
}

// Function to update the LRU bits for the data cache after accessing a specific entry
void updateLRU_Data(unsigned int way) {
    	// Store the current LRU value of the accessed entry
    	int current_LRU = data_cache[way].LRU_bits;
    	// Increment the LRU bits for all entries with LRU value less than or equal to the
    	// accessed entry
    for (int i = 0; i < 8; ++i) 
	{
		if (data_cache[i].LRU_bits <= current_LRU)
			data_cache[i].LRU_bits++;
    }
    // Set the LRU bits of the accessed entry to 0
    data_cache[way].LRU_bits = 0;
    return;
}

// Function to read data from the L1 cache
int readData_L1Cache(unsigned int hex_value) {
    	// update the statisitics
	statistics.data_cache_read++; 
	
	// this does the masking of the hex value givern from text file 
	uint32_t byte_select_bits = hex_value & 0x3F ;
	uint32_t address_bits = (hex_value >> 6) & 0x3FFF ; 
	uint32_t tag_bits = hex_value >> (INDEX + BYTE_SELECT);
	
	// this represents which way it is in the cache
	int way = -1; 
	
	
	// Check if a set is empty is available
	int i = 0;
	for (i = 0; i < 8 && way < 0; ++i) 
	{
		// Check if a set is empty 
		if (data_cache[i].tag_bits == 0)
		{
			way = i;
		}		
    }
	
	// Place the empty position 
    if (way >= 0) 
	{
		// There is an empty set in the cache
		// it is also a cache miss
		statistics.data_cache_miss++;
		
		// assign the tag and mesi state
		data_cache[way].tag_bits = tag_bits;
		data_cache[way].MESI_state = 'E';
		
		// update the LRU bits
		updateLRU_Data(way);

		// assign the address
		data_cache[way].address = hex_value;
		
		
		// Simulate L2 cache read
		if (chosen_mode == 1)
		{
			printf("\n\tRead from L2 %x [data]", hex_value);
		}
    }
    else 
	{  
		// the cache is no longer empty 
		
		// Search for a matching tag first
		way = find_DataTag(tag_bits);

		// if way is -1 , then it is a cache miss 
		// if it is another positive number then it is 
		// a cache hit
		if (way < 0) //CACHE MISS 
		{	 
			// Miss
			statistics.data_cache_miss++;
			
			// Check for a line with an invalid state to evict
			way = findInvalid_Data_MESIState();
			if (way < 0) 
			{ 	// If no invalid states, evict LRU
				way = locateLRU_Data();
				if (way >= 0) {	
					// Assign the new tag and MESI state to the evicted entry
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'E';
					// Update the LRU bits for the cache
					updateLRU_Data(way);
					// Assign the address to the cache entry
					data_cache[way].address = hex_value;
				}
				else {
					// If the LRU data is invalid, return an error
					printf("LRU data is invalid");
					return -1;
				}
			}
			else {
			// If an invalid MESI state is found, evict that entry
			data_cache[way].tag_bits = tag_bits;
			data_cache[way].MESI_state = 'E';
			// Update the LRU bits for the cache
			updateLRU_Data(way);
			// Assign the address to the cache entry  
			data_cache[way].address = hex_value;
			}
			// Simulate L2 cache read
			if (chosen_mode == 1)
				printf("\n\tRead from L2 %x [data]", hex_value);
		}
		else 
		{
			// If a matching tag is found, it is a cache hit
			statistics.data_cache_hit++;
			// Update the MESI state based on the current state
			switch (data_cache[way].MESI_state) 
			{
				case 'M':
					// If the current state is Modified (M),
					// keep it as is
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'M';
					updateLRU_Data(way);
					data_cache[way].address = hex_value;
					break;
				
				case 'E':
					// If the current state is Exclusive (E),
					// change it to Shared (S)
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'S';
					updateLRU_Data(way);
					data_cache[way].address = hex_value;
					break;
				  
				case 'S':
					// If the current state is Shared (S),
					// keep it as is
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'S';
					updateLRU_Data(way);
					data_cache[way].address = hex_value;
					break;
				
				case 'I':
					// If the current state is Invalid (I),
					// change it to Shared (S)
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'S';
					updateLRU_Data(way);
					data_cache[way].address = hex_value;
					break;
			}
		}
	}
	return 0;
}

// Function to write data to the L1 cache
int writeData_L1Cache(unsigned int hex_value) {
	// Extract the byte select, address, and tag bits from the hex value
    	uint32_t byte_select_bits = hex_value & 0x3F ;
	uint32_t address_bits = (hex_value >> 6) & 0x3FFF ; 
	uint32_t tag_bits = hex_value >> (INDEX + BYTE_SELECT);
	
	// Initialize the way index to an invalid value
	int way = -1;		
    	int i = 0;
    	// Update the statistics for cache writes
	statistics.data_cache_write++;
	
	// Check for an empty set in the cache
    for (i = 0; way < 0 && i < 8; ++i) 
	{
		if (data_cache[i].tag_bits == 0)
			// Assign the empty way index
			way = i;
	}
	
    // Place the empty position 
    if (way >= 0) 
	{
		// Assign the tag and MESI state to the empty way
		data_cache[way].tag_bits = tag_bits;
		data_cache[way].MESI_state = 'M';
		data_cache[way].address=hex_value;
		statistics.data_cache_miss++;
		
		// Update the LRU bits for the cache
		updateLRU_Data(way);
	
		// Simulate L2 cache write-through
		if (chosen_mode == 1)
			printf("\n\tWrite to L2 %x [write-through]", hex_value);
    }
    else 
    {		// no gap then search for hit/miss
		way = find_DataTag(tag_bits);	// Search for a matching tag first
		if (way < 0) {  // Miss
			statistics.data_cache_miss++;
			
			//Simulate L2 cache RFO
			if (chosen_mode == 1)
			printf("\n\tRead for Ownership from L2 %x", hex_value);

			way = findInvalid_Data_MESIState();
			
			// If no invalid states, evict LRU
			if (way < 0) { 			
			way = locateLRU_Data();
				if (way >= 0) {
				
				//Simulate L2 cache write-back
				if (chosen_mode == 1)
				printf("\n\tWrite to L2 %x [write-back]", hex_value);

				data_cache[way].tag_bits = tag_bits;
				data_cache[way].MESI_state = 'M';
				data_cache[way].address=hex_value;
				updateLRU_Data(way);
			}
			else {
				printf("ERROR: LRU data is invalid");
				return -1;
			}
			}
		
			// Else, evict the invalid member
			else {			
			data_cache[way].tag_bits = tag_bits;
			data_cache[way].MESI_state = 'M';
			data_cache[way].address = hex_value;
			updateLRU_Data(way);        	
			}
		}
		else 
		{	// Hit
			statistics.data_cache_hit++;
			switch (data_cache[way].MESI_state) 
			{
				case 'M':
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'M';
					data_cache[way].address = hex_value;
					updateLRU_Data(way);
					break;
				
				case 'E':
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'M';
					data_cache[way].address = hex_value;
					updateLRU_Data(way);
				break;
				  
				case 'S':
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'E';
					data_cache[way].address = hex_value;
					updateLRU_Data(way);
				break;
				
				case 'I':
					data_cache[way].tag_bits = tag_bits;
					data_cache[way].MESI_state = 'E';
					data_cache[way].address = hex_value;
					updateLRU_Data(way);
				break;
			}
			
		}
	
	
	}

	
	return 0;
}

int fetchInstruction_L1Cache(unsigned int hex_value) {
    	uint32_t byte_select_bits = hex_value & 0x3F ;
	uint32_t address_bits = (hex_value >> 6) & 0x3FFF ; 
	uint32_t tag_bits = hex_value >> (INDEX + BYTE_SELECT);
	
    int way = -1;	// Way in the cache set. start with invalid state
	
    int i = 0;
	
	statistics.instruction_cache_read++;
	
	// Check for an empty set
	for (i = 0; i < 8 && way < 0; ++i) 
	{
		// Check if a set is empty 
		if (data_cache[i].tag_bits == 0)
		{
			way = i;
		}
			
    }
	
	 // Place the empty position 
    if (way >= 0) 
	{
		instruction_cache[way].tag_bits = tag_bits;
		instruction_cache[way].MESI_state = 'E';
		instruction_cache[way].address=hex_value;
		updateLRU_Instruction(way);
		statistics.instruction_cache_miss++;
		
		// Simulate L2 cache read
		if (chosen_mode == 1)
			printf("\n\tRead from L2 %x [Instruction]", hex_value);
    }
    else 
	{ // no gap then search for hit/miss
		way = find_InstructionTag(tag_bits);
		if (way < 0) {  	// Miss
			statistics.instruction_cache_miss++;

			// Check for a line with an invalid state to evict
			way = findInvalid_Instruction_MESIState();
			
			if (way < 0) 
			{ 	// No invalid states, evict LRU
				way = locateLRU_Instruction();
				instruction_cache[way].tag_bits = tag_bits;
				instruction_cache[way].MESI_state = 'E';
				instruction_cache[way].address=hex_value;
				updateLRU_Instruction(way);
			}
			else 
			{	// Evict the invalid member
				instruction_cache[way].tag_bits = tag_bits;
				instruction_cache[way].MESI_state = 'E';
				instruction_cache[way].address=hex_value;
				updateLRU_Instruction(way);        	
			}
			
			// Simulate L2 cache read
			if (chosen_mode == 1)
				printf("\n\tRead from L2 %x [Instruction]", hex_value);
		}
		else 
		{				// Else, there was a hit
		
			statistics.instruction_cache_hit++;
			
			switch (instruction_cache[way].MESI_state) 
			{
				case 'M':
					instruction_cache[way].tag_bits = tag_bits;
					instruction_cache[way].MESI_state = 'M';
					instruction_cache[way].address=hex_value;
					updateLRU_Instruction(way);
					break;

				case 'E':
					instruction_cache[way].tag_bits = tag_bits;
					instruction_cache[way].MESI_state = 'S';
					instruction_cache[way].address=hex_value;  
					updateLRU_Instruction(way);
					break;

				case 'S':instruction_cache[way].tag_bits = tag_bits;
					instruction_cache[way].MESI_state = 'S';
					instruction_cache[way].address=hex_value;
					updateLRU_Instruction(way);
					break;

				case 'I':instruction_cache[way].tag_bits = tag_bits;
					instruction_cache[way].MESI_state = 'S';
					instruction_cache[way].address=hex_value;
					updateLRU_Instruction(way);
					break;
			}
			
		}
    }
    return 0;
}

int invalidate_L2CacheEntry(unsigned int hex_value) {
    	uint32_t byte_select_bits = hex_value & 0x3F ;
	uint32_t address_bits = (hex_value >> 6) & 0x3FFF ; 
	uint32_t tag_bits = hex_value >> (INDEX + BYTE_SELECT);

	int i;
    // Search data cache for a matching tag
    for (i = 0; i < 8; ++i) 
	{
		if (data_cache[i].tag_bits == tag_bits) 
		{
			switch (data_cache[i].MESI_state) 
			{
				case 'M': 
					data_cache[i].MESI_state = 'I';	// Changes MESI bit set to invalidate
					break;
			
				case 'E': 
					data_cache[i].MESI_state = 'I';	// Changes MESI bit set to invalidate
					break;

				case 'S': 
					data_cache[i].MESI_state = 'I';	// Changes MESI bit set to invalidate
					break;

				case 'I': 
					return 0;			// Do nothing, already invalid
					
				default:
					return -1;			// Non-MESI state
			} 
		}	
    }
	
	
    return 0;
}

int snoopData_L2Cache(unsigned int hex_value) {
	unsigned int tag_bits = hex_value >> (BYTE_SELECT + INDEX);  // Extract tag bits from hex value
    int i = 0;

    // Iterate over data cache of other processors to find matching tags
    for (i = 0; i < 8; ++i) 
	{
        if (data_cache[i].tag_bits == tag_bits) 
		{  // If tag bits match
            
			if
			(
				(data_cache[i].MESI_state == 'M') ||
				(data_cache[i].MESI_state == 'E') ||
				(data_cache[i].MESI_state == 'S')
			)
			{
				data_cache[i].MESI_state = 'I';
			}
			else
			{
				return 0;
			}

            // If in chosen mode, simulate data return to L2 cache
            if (chosen_mode == 1)
                printf("\n\tL2 Cache Receives Data: %x", hex_value); // Display the hex value sent back to L2 cache

        }
    }
    return 0;
}

void reset_AllCacheAndStats(void) {
    	 int i;
    printf("\n\t Resetting Cache data...\n\n");
    // Clear the instruction cache
    for (i = 0; i < 4; ++i) 
	{
    	instruction_cache[i].tag_bits = 0;
	instruction_cache[i].LRU_bits = 0;
	instruction_cache[i].MESI_state = 'I';
    }

    // Clear the data cache
    for (i = 0; i < 8; ++i) 
	{
    	data_cache[i].tag_bits = 0;
	data_cache[i].LRU_bits = 0;
	data_cache[i].MESI_state = 'I';
        data_cache[i].address = 0;
    }
     
    // Reset all statistics
    printf("\n\t Resetting statistics...\n\n");
    statistics.data_cache_hit = 0;
    statistics.data_cache_miss = 0;
    statistics.data_cache_read = 0;
    statistics.data_cache_write = 0;
    statistics.data_cache_hit_ratio = 0.0;
    statistics.instruction_cache_hit = 0;
    statistics.instruction_cache_miss = 0;
    statistics.instruction_cache_read = 0;
    statistics.instruction_cache_hit_ratio = 0.0;

    return;
}

void display_AllCacheContents(void) {
    int i;

    printf("\n\n\t Preparing content tables...\n\n");
    printf("-----------------MESI States key----------------\n");
    printf("Modified(M), Exclusive(E), Shared(S), Invalid(I)\n");
    printf("------------------------------------------------\n\n");

    printf("Table 1: Data Cache Content\n");
    printf("------------------------------------------------\n");
    printf(" Way |   Address   |   Tag   | LRU | MESI State \n");
    printf("------------------------------------------------\n");
    for (i = 0; i < 8; ++i) {
        printf("  %d  |  0x%08x |  0x%03x  |  %u  |     %c      \n", 
               i + 1, data_cache[i].address, data_cache[i].tag_bits, data_cache[i].LRU_bits, data_cache[i].MESI_state);
        printf("------------------------------------------------\n");
    }

    printf("\nTable 2: Instruction Cache Content\n");
    printf("------------------------------------------------\n");
    printf(" Way |   Address   |   Tag   | LRU | MESI State \n");
    printf("------------------------------------------------\n");
    for (i = 0; i < 4; ++i) {
        printf("  %d  |  0x%08x |  0x%03x  |  %u  |     %c      \n", 
               i + 1, instruction_cache[i].address, instruction_cache[i].tag_bits, instruction_cache[i].LRU_bits, instruction_cache[i].MESI_state);
        printf("------------------------------------------------\n");
    }

    unsigned int total_data_accesses = statistics.data_cache_hit + statistics.data_cache_miss;
    if (total_data_accesses > 0) {
        statistics.data_cache_hit_ratio = ((float)statistics.data_cache_hit / total_data_accesses) * 100;
    } else {
        statistics.data_cache_hit_ratio = 0.0;
    }

    unsigned int total_instruction_accesses = statistics.instruction_cache_hit + statistics.instruction_cache_miss;
    if (total_instruction_accesses > 0) {
        statistics.instruction_cache_hit_ratio = ((float)statistics.instruction_cache_hit / total_instruction_accesses) * 100;
    } else {
        statistics.instruction_cache_hit_ratio = 0.0;
    }

    printf("\nTable 3: Cache Statistics\n");
    printf("------------------------------------------------\n");
    printf(" Metric                     |       Value      \n");
    printf("------------------------------------------------\n");
    printf(" Data Cache Reads           |         %u        \n", statistics.data_cache_read);
    printf(" Data Cache Writes          |         %u        \n", statistics.data_cache_write);
    printf(" Data Cache Hits            |         %u        \n", statistics.data_cache_hit);
    printf(" Data Cache Misses          |         %u        \n", statistics.data_cache_miss);
    printf(" Data Cache Hit/Miss Ratio  |        %.2f%%       \n", statistics.data_cache_hit_ratio);
    printf("------------------------------------------------\n");

    printf("\nTable 4: Instruction Cache Statistics\n");
    printf("------------------------------------------------\n");
    printf(" Metric                           |    Value      \n");
    printf("------------------------------------------------\n");
    printf(" Instruction Cache Reads          |      %u      \n", statistics.instruction_cache_read);
    printf(" Instruction Cache Hits           |      %u      \n", statistics.instruction_cache_hit);
    printf(" Instruction Cache Misses         |      %u      \n", statistics.instruction_cache_miss);
    printf(" Instruction Cache Hit/Miss Ratio |     %.2f%%     \n", statistics.instruction_cache_hit_ratio);
    printf("------------------------------------------------\n");
}
