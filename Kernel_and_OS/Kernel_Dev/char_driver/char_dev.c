/*
 * Program: Linux Kernel Module for Character Device Management (char_kernel.c)
 * 
 * Description: This module demonstrates the creation and handling of a character device
 * 		with basic file operations such as open, read, and write. The device supports
 * 		multiple instances (up to 5 devices) and showcases dynamic major number
 * 		allocation along with proper error handling and cleanup procedures.
 *
 * 		The module uses kernel facilities such as cdev for character devices, kmalloc for
 * 		memory allocation, and copy_to/from_user for safe data transfer between user space
 * 		and kernel space. It also exemplifies the use of module parameters that can be set at load time,
 * 		with one parameter visible in sysfs allowing read/write access from user space.
 *
 * 		This code serves as an educational tool for understanding the essentials of character
 * 		device interaction in the Linux kernel environment, providing a basis for further expansion
 * 		and customization in more complex kernel module development tasks.
 *
 * Edited by: Wa'el AL KALBANI
 * Course: ECE 373 - Embedded Operating Systems & Device Drivers
 * Date modified: 04/22/2024
 *
 * Source: PJ Waskiewicz 
 *
 */


#include <linux/module.h>    // Essential for all kernel modules
#include <linux/types.h>     // Includes data types used in kernel
#include <linux/kdev_t.h>    // Definitions for major/minor numbers
#include <linux/fs.h>        // File-system support
#include <linux/cdev.h>      // Character device definitions
#include <linux/slab.h>      // kmalloc/kfree functions
#include <linux/uaccess.h>   // Copy to/from user functions
#include <linux/device.h>    // Provides definitions for device classes and functions


#define DEVCNT 1            // Number of devices to create
#define DEVNAME "char1"     // Name of the device


/* Global variables for class and device */
static struct class *char1_class = NULL;
static struct device *char1_device = NULL;

static struct mydev_dev {
	struct cdev my_cdev;
	/* more stuff will go in here later... */
	int syscall_val;
} mydev;

static dev_t mydev_node;

/* this shows up under /sys/modules/char1/parameters */
static int initial_val = 42;	//User parameter input
module_param(initial_val, int, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(initial_val, "Initial value for the character device");


/* this doesn't appear in /sys/modules */
// static int exam_nosysfs = 25;
// module_param(exam_nosysfs, int, 0);

static int char1_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "successfully opened!\n");

	mydev.syscall_val = initial_val;

	return 0;
}

static ssize_t char1_read(struct file *file, char __user *buf, size_t len, loff_t *offset)
{
	/* Get a local kernel buffer set aside */
	int ret;

	/* Check offset size */
	if (*offset >= sizeof(int)) {
		return 0;
	}
		
	/* Make sure our user wasn't bad... */
	if (!buf) {
		ret = -EINVAL;
		goto out;
	}
	printk(KERN_INFO "In the raed() system call");
	
	if (copy_to_user(buf, &mydev.syscall_val, sizeof(int))) {
		ret = -EFAULT;
		goto out;
	}
	ret = sizeof(int);
	*offset += sizeof(int);
	
	/* Good to go, so printk the thingy */
	printk(KERN_INFO "User got from us %d\n", mydev.syscall_val);

out:
	return ret;
}

static ssize_t char1_write(struct file *file, const char __user *buf, size_t len, loff_t *offset)
{
	/* Have local kernel memory ready */
	char *kern_buf;
	int ret;

	printk(KERN_INFO "In the write() system call");
	
	/* Make sure our user isn't bad... */
	if (!buf) {
		ret = -EINVAL;
		goto out;
	}

	/* Get some memory to copy into... */
	kern_buf = kmalloc(len, GFP_KERNEL);

	/* ...and make sure it's good to go */
	if (!kern_buf) {
		ret = -ENOMEM;
		goto out;
	}

	/* Copy from the user-provided buffer */
	if (copy_from_user(kern_buf, buf, len)) {
		/* uh-oh... */
		ret = -EFAULT;
		goto mem_out;
	}

	ret = len;
	
	mydev.syscall_val = *kern_buf;
	/* print what userspace gave us */
	printk(KERN_INFO "Userspace wrote \"%s\" to us\n", kern_buf);

mem_out:
	kfree(kern_buf);
out:
	return ret;
}

/* File operations for our device */
static struct file_operations mydev_fops = {
	.owner = THIS_MODULE,
	.open = char1_open,
	.read = char1_read,
	.write = char1_write,
};

static int __init char1_init(void)
{
    printk(KERN_INFO "char1 module loading... initial_val=%d\n", initial_val);

    if (alloc_chrdev_region(&mydev_node, 0, DEVCNT, DEVNAME)) {
        printk(KERN_ERR "alloc_chrdev_region() failed!\n");
        return -1;
    }

    /* Create a class */
    char1_class = class_create(THIS_MODULE, "charclass");
    if (IS_ERR(char1_class)) {
        unregister_chrdev_region(mydev_node, DEVCNT);
        return PTR_ERR(char1_class);
    }

    /* Initialize the character device and add it to the kernel */
    cdev_init(&mydev.my_cdev, &mydev_fops);
    mydev.my_cdev.owner = THIS_MODULE;

    if (cdev_add(&mydev.my_cdev, mydev_node, DEVCNT)) {
        printk(KERN_ERR "cdev_add() failed!\n");
        class_destroy(char1_class);
        unregister_chrdev_region(mydev_node, DEVCNT);
        return -1;
    }

    /* Create the device */
    char1_device = device_create(char1_class, NULL, mydev_node, NULL, DEVNAME);
    if (IS_ERR(char1_device)) {
        cdev_del(&mydev.my_cdev);
        class_destroy(char1_class);
        unregister_chrdev_region(mydev_node, DEVCNT);
        return PTR_ERR(char1_device);
    }

    return 0;
}


static void __exit char1_exit(void)
{
    device_destroy(char1_class, mydev_node);
    cdev_del(&mydev.my_cdev);
    class_destroy(char1_class);
    unregister_chrdev_region(mydev_node, DEVCNT);
    printk(KERN_INFO "char1 module unloaded!\n");
}



MODULE_AUTHOR("Wa'el AL KALBANI");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.2");
module_init(char1_init);
module_exit(char1_exit);

