#!/bin/bash

# Define the compiler
COMPILER="g++"

# Define the source file
SOURCE_FILE="./src/main.cpp"

# Define the target executable name
TARGET="./target/main"

# Define flags
FLAGS="-std=c++20 -Werror"

# Compile the source file
$COMPILER $(pkg-config --libs --cflags raylib) $FLAGS -o $TARGET $SOURCE_FILE

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable '$TARGET' created."
else
    echo "Compilation failed. Please check your code and try again."
fi