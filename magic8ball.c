/*
project: 03
author: Hasnain Ali
email: hali6@umbc.edu
student id: jl69013
github username: hali0860
description: Displays a random phrase to userspace, supposed to represent the response
of a magic eight ball to a question the user thinks of. The user does not actually type
in their question anywhere, the drivers "reads" the mind of the question posed by the
user. See the README on how to run it
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/random.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("GPL");

#define DEVICE_NAME "magic8ball"

// A list of magic 8 ball phrases
static const char *phrases[] = {
    "It is certain.",
    "It is decidedly so.",
    "Without a doubt.",
    "Yes definitely.",
    "You may rely on it.",
    "As I see it, yes.",
    "Most Likely.",
    "Outlook good.",
    "Yes.",
    "Signs point to yes.",
    "Reply hazy, try again.",
    "Ask again later.",
    "Better not tell you now.",
    "Cannot predict now.",
    "Concentrate and ask again.",
    "Don't count on it.",
    "My reply is no.",
    "My sources say no.",
    "Outlook not so good.",
    "Very doubtful."
};

// Code for open operation
static int magic8ball_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "magic8ball opened\n");
    return 0;
}

// Code for read operation
// Copies a random phrase to user space
static ssize_t magic8ball_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    const char *selectedPhrase;        // Will be the phrase that gets printed
    size_t arraySize;                  // Will contain the size of the array
    unsigned int randomIndex;          // Will contain the random index
    size_t bytesRead;
    // Check if we've already provided a response
    if (*offset > 0) {
        // If yes, signal EOF
        return 0;
    }
    arraySize = sizeof(phrases) / sizeof(phrases[0]);
    // Get a random index
    get_random_bytes(&randomIndex, sizeof(randomIndex));
    // Ensure the random index is within bounds
    randomIndex %= arraySize;
    // Get the random phrase
    selectedPhrase = phrases[randomIndex];
    // Copy the phrase to the user buffer
    bytesRead = 0;
    while (length && *selectedPhrase != '\0') {
        put_user(*(selectedPhrase++), buffer++);
        bytesRead++;
        length--;
    }
    // Add a newline character at the end of the response for better readability
    if (bytesRead > 0) {
        put_user('\n', buffer++);
        bytesRead++;
    }
    // Update the offset to signal that we've provided a response
    *offset += bytesRead;
    return bytesRead;
}

// Code for write operation
static ssize_t magic8ball_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset) {
    return -EPERM;
}

// Code for relase operation
static int magic8ball_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "magic8ball released\n");
    return 0;
}

// Code for the file operations
static struct file_operations magic8ball_fops = {
    .owner = THIS_MODULE,
    .open = magic8ball_open,
    .read = magic8ball_read,
    .write = magic8ball_write,
    .release = magic8ball_release,
};

// Misc device structure code, sets read only permissions
static struct miscdevice magic8ball_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &magic8ball_fops,
    .mode = 0444,
};

// Code for loading the kernel
static int __init magic8ball_init(void) {
    int returnValue;
    // Register the misc device
    returnValue = misc_register(&magic8ball_misc_device);
    if (returnValue) {
        printk(KERN_ERR "Failed to register misc device\n");
        return returnValue;
    }
    printk(KERN_INFO "magic8ball successfully loaded\n");
    return 0;
}

// Code for unloading the kernel
static void __exit magic8ball_exit(void) {
    // Deregister the misc device
    misc_deregister(&magic8ball_misc_device);
    printk(KERN_INFO "unloading magic8ball\n");
}

module_init(magic8ball_init);
module_exit(magic8ball_exit);
