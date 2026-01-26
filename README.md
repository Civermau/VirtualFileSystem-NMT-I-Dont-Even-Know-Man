# About
This project is a virtual file system simulator inspired by Linux console commands. The purpose is to practice the use and integration of smart pointers in a hierarchical structure.
All file and folders exist only in memory and does not access the real file system.

## Goal
The project was created specifically to understand:
- **shared_ptr** ownership
- **weak_ptr** for parent references
- prevention of reference cycles
- **lifetime control** in tree structures
- safe navigation through hierarchical data
- usage of **std::enable_shared_from_this**

## Command List
- clear
- ls
- tree
- close
- rm **file**
- cd **file**
- cd ..
- cd ~
- mkdir **folder**
- touch **file**

## Design
- Parent → child relationship
  - shared_ptr<Node>

- Child → parent relationship
  - weak_ptr<Node>

This design prevents circular references while allowing full bidirectional navigation.

Folders and files inherit from a common base:

`class Folder : public Node, public std::enable_shared_from_this<Folder>`


## Notes
- This project prioritizes understanding ownership and lifetime over performance or completeness.
- This project was bult before learning Cmake so it uses a Visual Studio .sln project.

Check Example.txt To Get The Next Example tree

![image](https://github.com/user-attachments/assets/cacd465c-4888-4bba-9299-7a06d7085cf2)
