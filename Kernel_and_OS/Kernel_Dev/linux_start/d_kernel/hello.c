/*
 * 
 * This is a simple kernel module for the ECE373 course.
 * It demonstrates the basics of creating a kernel module,
 * including initialization and cleanup functions.
 * When loaded, it prints "Hello, Kernel" to the kernel log,
 * and when unloaded, it prints "Goodbye, Kernel".
 * 
 * Author: Wa'el AL KALBANI
 * Course: ECE 373 - Embedded Operating Systems & Device Drivers
 * 
 */


#include <linux/module.h>   // "module.h" Needed for all kernel modules
#include <linux/version.h>  // "version.h" Needed for version checking
#include <linux/kernel.h>   // "kernal.h" Needed for kernel functions



// Initialization function
// __init to indicate that it is only used at initialization time.
static int __init init_HelloLinux(void){
    printk(KERN_INFO "Hello, Kernel \n");  // Print "Hello, Kernel" to the log
    return 0;                              // Return 0 to indicate successful initialization
}


// Cleanup function
// __exit to indicate that it is only used at cleanup time.
static void __exit exit_HelloLinux(void){
    printk(KERN_INFO "Goodbye, Kernel \n");  // Print "Goodbye, Kernel" to the log
}



module_init(init_HelloLinux);  // Register initialization function
module_exit(exit_HelloLinux);  // Register cleanup function


MODULE_LICENSE("GPL");	// License "GPL" which stands for GNU General Public License
MODULE_AUTHOR("Wa'el AL KALBANI");  // Author declaration
MODULE_DESCRIPTION("ECE373 1st Assignment");  // Module description
