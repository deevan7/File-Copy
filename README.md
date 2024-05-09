
# flame_cp

## Assignment

Deevankumar Gaddala

This repository contains the necessary files to create a copy of a given file using a C program (`my_copy.c`) and a Bash script (`error.sh`) for error handling.

## Dependencies

- Standard C library
- Bash

## Building the Program

1. Compile the C program using a C compiler like GCC:
   ```bash
   gcc my_copy.c 
   created a object file a.out then 
   gcc my_copy.c -o flame_cp
   created a obj file with flame_cp
  
   created/copied a new file by ./flame_cp -i my_copy.c -o abc

## Usage

1. Execute the Bash script, providing the C program as an argument:
   ```bash error.sh $?
   ./run_flame_cp.sh ./flame_cp -i <source_file> -o <destination_file>


## Description

- my_copy.c:The C program handles file copying and returns error codes.
- error.sh The Bash script interprets error codes and displays user-friendly messages.

## Error Handling

- The C program returns exit codes to signal errors.
- The Bash script provides detailed error messages based on these codes.

## Common Exit Codes

- 0: No Errors/OK
- 147: Wrong arguments
- 148: File not found
- 149: Opening failed
- Others: System-specific errors (explained by `perror`)

## Screenshots

**Example of error handling:**

Screenshot sample shared in zip file

## Additional Notes

- The C program uses a buffer size of 4096 bytes for file I/O.
- The destination file is created exclusively, preventing overwriting existing files.

##usage
**gcc my_copy.c -o flame_cp**
creates a object file 
**./flame_cp -i my_copy.c -o testing**
copies contents from my_copy.c to testing file(plain text)

**./flame_cp -i copy -o testing**
says that **File not found** (error.sh) user friendly command which is in the bash script
