/**
 * Program: Char Device Interactor (userspace.c)
 * Description: This program demonstrates opening, reading from, writing to,
 *              and reading again from a character device. It's designed to
 *              interact with a Linux kernel module for a character device named 'char1'.
 *              The program reads an initial value from the device, writes a new value,
 *              then reads back the updated value to confirm the write operation.
 *              It's useful for testing and verifying the functionality of the kernel module.
 *
 * Author: Wa'el AL KALBANI
 * Course: ECE 373 - Embedded Operating Systems & Device Drivers
 * Created on: 04/22/2024
 * 
 * This program is part of an educational project to understand device driver
 * interactions within Linux. It opens the character device '/dev/char1', manipulates
 * data by interfacing directly with the kernel through standard system calls, and
 * ensures proper resource management by closing the device after operations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define PATH_DEVICE "/dev/char1"

int main() {
    int fd_device; // File descriptor for the device
    int input_val = 0; // Buffer for reading values from the device
    int new_val; // New value to write to the device

    // Open the device file
    fd_device = open(PATH_DEVICE, O_RDWR);
    if (fd_device < 0) {
        perror("Failed to open the device");
        return errno;
    }

    // Read the initial value from the device
    if (read(fd_device, &input_val, sizeof(input_val)) < 0) {
        perror("Failed to read from device");
        close(fd_device);
        return errno;
    }
    printf("Initial value read from device: %d\n", input_val);

    // Prompt user for a new value to write
    printf("Enter new value to write to device: ");
    scanf("%d", &new_val);

    // Write the new value to the device
    if (write(fd_device, &new_val, sizeof(new_val)) < 0) {
        perror("Failed to write to device");
        close(fd_device);
        return errno;
    }
    printf("New value written to device: %d\n", new_val);

    // Read back the value from the device to confirm the write
    if (read(fd_device, &input_val, sizeof(input_val)) < 0) {
        perror("Failed to read from device after write");
        close(fd_device);
        return errno;
    }
    printf("Value read from device after write: %d\n", input_val);

    // Clean up and close the device file
    close(fd_device);

    return 0;
}

