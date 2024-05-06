/**
*   TEAM 4
*   Names:  Mohammad Hasan
*           Wa'el Alkalbani
*           Mohamed Gnedi
*           Yousef Alothman
*
*   Project: ECE 585 Final Cache Project
*   File: cache.h
*
*   Description: This header file contains the definitions of the cache structure,
*                statistics structure, operation enums, and function prototypes
*                used in the cache simulation.
*/

// Include guard to prevent multiple inclusions of this header file
#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>	// Include the standard integer library for fixed-width integer types

// Define constants for the cache configuration
#define TAG_BITS 12        // Number of bits used for the tag
#define INDEX 14           // Number of bits used for the index
#define BYTE_SELECT 6      // Number of bits used for byte selection

// Define a structure to hold cache statistics
typedef struct my_stat {
    unsigned int data_cache_hit;          // Number of data cache hits
    unsigned int data_cache_miss;         // Number of data cache misses
    unsigned int data_cache_read;         // Number of data cache reads
    unsigned int data_cache_write;        // Number of data cache writes
    float data_cache_hit_ratio;           // Ratio of data cache hits to misses
    unsigned int instruction_cache_hit;   // Number of instruction cache hits
    unsigned int instruction_cache_miss;  // Number of instruction cache misses
    unsigned int instruction_cache_read;  // Number of instruction cache reads
    float instruction_cache_hit_ratio;    // Ratio of instruction cache hits to misses
} STATISTICS;

// Define a structure to represent a cache line
typedef struct my_cache {
    unsigned int tag_bits;    // Tag bits of the cache line
    unsigned int LRU_bits;    // Least Recently Used bits for cache replacement
    char MESI_state;          // MESI state of the cache (Modified, Exclusive, Shared, Invalid)
    unsigned char data[64];   // Data stored in the cache line
    unsigned int address;     // Address of the cache line
} CACHE;

// Define an enumeration for cache operations
typedef enum ops {
    L1_READ = 0,              // Read from L1 cache
    L1_WRITE = 1,             // Write to L1 cache
    L1_FETCH_INSTRUCTION = 2, // Fetch instruction from L1 cache
    INVALIDATE_L2 = 3,        // Invalidate L2 cache entry
    SNOOP_L2_CACHE = 4,       // Snoop L2 cache
    RESET_CACHE = 8,          // Reset cache
    PRINT_ALL_CACHE = 9,      // Print all cache contents
} OPERATIONS;


// Declare external variables for cache arrays and statistics
extern CACHE data_cache[8];           // Array for data cache lines
extern CACHE instruction_cache[4];    // Array for instruction cache lines
extern STATISTICS statistics;         // Cache statistics
extern unsigned int chosen_mode;      // Mode chosen for cache operation


// Function prototypes for cache operations
int find_DataTag(unsigned int tag_bits);
int find_InstructionTag(unsigned int tag_bits);
int locateLRU_Data(void);
int locateLRU_Instruction(void);
int findInvalid_Data_MESIState(void);
int findInvalid_Instruction_MESIState(void);
void updateLRU_Instruction(unsigned int way);
void updateLRU_Data(unsigned int way);
int readData_L1Cache(unsigned int hex_value);
int writeData_L1Cache(unsigned int hex_value);
int fetchInstruction_L1Cache(unsigned int hex_value);
int invalidate_L2CacheEntry(unsigned int hex_value);
int snoopData_L2Cache(unsigned int hex_value);
void reset_AllCacheAndStats(void);
void display_AllCacheContents(void);


#endif // CACHE_H
