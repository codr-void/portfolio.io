
   TEAM 4                                                      
   Names:  Mohammad Hasan                                     
           Wa'el Alkalbani                                    
           Mohamed Gnedi                                      
           Yousef Alothman                                    
                                                               
   Project: ECE 585 Final Cache Project                       
   File: README.md                                               
                                                               
   Description: This program simulates a cache system using   
   the MESI protocol. It includes functionality to read       
   cache accesses/events from a text file, simulate cache     
   operations, and display cache contents and statistics.
   
   ---------------------------------------------------------     
                                                               
   Files:                                                      
   1. main.c: Contains the main function that orchestrates    
              the simulation process. It reads traces from a  
              file, processes them, and interacts with the    
              cache functions accordingly.                   
   2. ache.h: Header file containing function declarations   
              and data structures for the cache simulation.  
   3. cache.c: Contains the implementation of cache          
               functions such as read, write, invalidate,    
               and print operations. It also includes the     
               MESI protocol logic for cache coherence.       
   4. test_cache.txt: Sample text file containing traces     
                      for testing the cache simulation.      
   5. report.pdf: Contains detailing program design and       
                  assumptions.                                
                                                               
   Documentation:                                             
   report.pdf: Contains detailing program design and          
               assumptions. 
                                                 
   ---------------------------------------------------------
                                                                    
   To compile the program, use the following command to toggle the Makefile:
   How to Compile and generate executables:                  
   make all                                                  
                                                               
   How to Run:                                               
   To run the program, use the following command:            
   make run                                                  
                                                               
   How to Remove executables:                                
   To remove executable file, use the following command:     
   make clean                                                
   
   --------------------------------------------------------- 
                                                                  
   New trace file?                                           
   to use a deferent trace file, make sure to store it within 
   the program directory, then replace `test_cache.txt` in   
   Makefile with the name of your trace file.                
                                                               
   Trace File Format:                                        
   The trace file should contain lines with the format:      
   n address                                                 
                                                               
   Where `n` is the operation type (0 for read, 1 for write, 
   2 for instruction fetch, 3 for invalidate, 4 for data     
   request from L2, 8 for cache reset, 9 for cache print),   
   and `address` is the memory address in hexadecimal format.
   
   ---------------------------------------------------------
                                                           
   Output:                                                   
   The program will output the simulation results, including  
   cache contents, statistics, and coherence actions based   
   on the MESI protocol.                                     
                                                               
   Note:                                                     
   - This program assumes that memory references do not span  
     cache line boundaries.                                  
   - The MESI protocol is used for cache coherence, where:    
     - Modified (M): Data is present and modified in this    
       cache only.                                           
     - Exclusive (E): Data is present in this cache only,    
       but not modified.                                     
     - Shared (S): Data is present in this cache and         
       possibly in others, not modified.                     
     - Invalid (I): Data is not present in this cache.       
                                                               
   Example Usage:                                            
   Suppose the trace file contains the following traces:     
   0 10019d94                                                
   1 10019d88                                                
   2 408edc                                                  
                                                               
   - Trace 0: Read from address `0x10019d94` (Data Cache Read).
   - Trace 1: Write to address `0x10019d88` (Data Cache Write).
   - Trace 2: Instruction fetch from address `0x408edc`.     
                                                               
   The program will simulate these operations and display the 
   cache contents and statistics accordingly.                
   
   --------------------------------------------------------- 
                                                       
   For further details, refer to the source code and comments 
   in the files.                                            
