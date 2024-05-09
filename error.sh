#!/bin/bash

# Capture the exit code from the previous command
exit_code=$?

if [ "$1" == 0 ]; then
  echo "Error: Invalid usage. Please use the correct syntax: flame_cp -i <source file> -o <destination file>"
elif [ "$1" == 147 ]; then
  echo "Wrong Arguments"
elif [ "$1" == 148 ]; then
  echo "File not found"
elif [ "$1" == 149 ]; then
  echo "Opening failed"
else

  perror $1
fi

exit $exit_code

