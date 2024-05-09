#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define E_OK                 0
#define E_WRONG_ARGNUMS      147
#define E_INVALID_ARGS       145
#define E_EMPTY_SOURCE_FILE  146
#define E_FILE_NOT_FOUND     148
#define E_OPEN_FAILED        149

#define BUFFER_SIZE 4096  

int main(int argc, char *argv[]) {
    int ec = E_OK;
    struct stat file_stats;
    int stat_status = E_OK;

    // Check for correct number of arguments
    if (argc != 5) {
        char error_msg[] = "Usage: flame_cp -i <source file> -o <destination file>\n";
        write(STDERR_FILENO, error_msg, sizeof(error_msg) - 1);
        return E_WRONG_ARGNUMS;
    }

    // Parse command-line arguments
    char source[500] = "";
    char dest[500] = "";
    int source_fd = 0; // Default to stdin
    int dest_fd = 1;   // Default to stdout

    for (int i = 1; i < 4; i = i + 2) {
        if (strcmp(argv[i], "-i") == 0) {
            strcat(source, argv[i + 1]);
            if (strcmp(source, "-") != 0) {
                // Open source file for reading
                source_fd = open(source, O_RDONLY);
                if (source_fd == -1) {
                    ec = E_FILE_NOT_FOUND;
                    return ec;
                }
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            strcat(dest, argv[i + 1]);
            if (strcmp(dest, "-") != 0) {
                // Create/open destination file
                dest_fd = open(dest, O_CREAT | O_WRONLY | O_EXCL, S_IRWXU | S_IRGRP);
                if (dest_fd == -1) {
                    ec = E_OPEN_FAILED;
                    return ec;
                }
            }
        } else {
            ec = E_INVALID_ARGS;
            return ec;
        }
    }

    // Check if both source and destination are specified
    if (strcmp(source, "") != 0 && strcmp(dest, "") != 0) {
        // Check if source file is empty
        if (source_fd != 0) {
            stat_status = stat(source, &file_stats);
            if (stat_status == -1) {
                ec = errno;
                return ec;
            } else if (file_stats.st_size == 0) {
                ec = E_EMPTY_SOURCE_FILE;
                return ec;
            }
        }

        // Copy data from source to destination
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
            if (write(dest_fd, buffer, bytes_read) != bytes_read) {
                ec = errno;
                close(source_fd);
                close(dest_fd);
                return ec;
            }
        }

        if (bytes_read == -1) {
            ec = errno;
            close(source_fd);
            close(dest_fd);
            return ec;
        }
    } else {
        ec = E_INVALID_ARGS;
        return ec;
    }

    close(source_fd);
    close(dest_fd);
    return ec;
}

