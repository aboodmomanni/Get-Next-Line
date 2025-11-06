Get Next Line
A C function that reads a line from a file descriptor, one line at a time.
Description
get_next_line is a function that returns a line read from a file descriptor. It handles multiple consecutive calls, reading the file line by line until the end. This project is a common assignment in the 42 programming curriculum that teaches file I/O, static variables, and memory management.
Features

Reads from any valid file descriptor (files, stdin, etc.)
Returns one line per call, including the newline character
Efficient buffer management
Handles multiple file descriptors simultaneously (bonus)
Customizable buffer size

Files
Mandatory Part

get_next_line.c - Main function implementation
get_next_line.h - Header file with function prototypes
get_next_line_utils.c - Helper functions

Bonus Part

get_next_line_bonus.c - Implementation with multi-fd support
get_next_line_bonus.h - Header file for bonus version
get_next_line_utils_bonus.c - Helper functions for bonus

Compilation
Mandatory
bashcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
Bonus (Multiple File Descriptors)
bashcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus
You can adjust the BUFFER_SIZE value to any positive integer.
Usage
c#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
Function Prototype
cchar *get_next_line(int fd);
Parameters

fd - File descriptor to read from

Return Value

Returns the line read from the file descriptor
Returns NULL if there's nothing more to read or if an error occurred

Helper Functions
f_strlen
Calculates the length of a string.
f_strchr
Finds the first occurrence of a character in a string, returns its index.
f_dup
Duplicates a string.
f_join
Concatenates two strings, freeing the first one.
f_ssubstr
Extracts a substring from a string.
Implementation Details
The function uses a static variable to maintain a buffer between calls, allowing it to:

Read chunks of data from the file descriptor
Store any leftover data for the next call
Return exactly one line per call

Bonus Features

Supports reading from multiple file descriptors simultaneously
Uses an array of static variables indexed by file descriptor
Maximum supported file descriptors: 1024 (configurable via MAX_FD)

Memory Management

All allocated memory is properly freed
No memory leaks in normal operation
Handles edge cases like read errors gracefully

Testing
Create a test file and run:
bashecho "Line 1\nLine 2\nLine 3" > test.txt
./gnl test.txt
For multiple file descriptors (bonus):
cint fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);
char *line3 = get_next_line(fd1);
// Can alternate between file descriptors
Notes

The function returns the line including the newline character \n (if present)
The last line might not have a newline character
Buffer size affects performance but not functionality
Typical buffer sizes range from 1 to 8192 bytes

Author
aalmoman (aalmoman@student.42.fr)
