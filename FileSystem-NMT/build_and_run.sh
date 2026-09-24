#!/bin/bash

# Compile the program
# Compile the source files using g++ compiler:
# -fdiagnostics-color=always                                                    : Enable colored compiler output messages
# -g                                                                            : Include debug information in the executable
# main.cpp, Folder.cpp, CommandHandler.cpp, SystemUtils.cpp                     : Source files to compile
# -o VirtualFileSystem                                                          : Name of the output executable
g++ -fdiagnostics-color=always -g main.cpp Folder.cpp CommandHandler.cpp SystemUtils.cpp -o VirtualFileSystem

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Running the program..."
    ./VirtualFileSystem
else
    echo "Compilation failed!"
fi