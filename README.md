# Student Management System

## Overview

The **Student Management System** is a C-based application designed to efficiently manage student records using a binary search tree (BST). The system allows users to perform various operations such as adding, updating, deleting, searching, and listing student information. With additional features like sorting students by name, searching by city, and grouping by class, this program is a comprehensive solution for managing student data.

---

## Table of Contents

1. [Features](#features)
2. [How It Works](#how-it-works)
    - [Core Data Structures](#core-data-structures)
    - [Supported Operations](#supported-operations)
3. [File Structure](#file-structure)
4. [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Steps to Run the Program](#steps-to-run-the-program)
5. [Menu Options](#menu-options)
6. [Example Output](#example-output)
7. [Conclusion](#conclusion)

---

## Features

- **Student Record Management**:
  - Add, update, delete, and search student records.
  - Save student data to a file for persistence.

- **Sorting and Searching**:
  - List all students in lexicographic order of their names.
  - Search for students based on their city.
  - Group students by their class.

- **User-Friendly Interface**:
  - Interactive menu for performing various operations.
  - Clear error messages and validation for invalid inputs.

- **File I/O**:
  - Load student data from a file (`studentsData.txt`).
  - Save updated records to the same file.

---

## How It Works

### Core Data Structures

1. **Binary Search Tree (BST)**:
   - Used to store and manage student records.
   - Enables efficient searching, insertion, and deletion operations.

2. **Student Node**:
   - Contains the following information:
     - `Student ID`
     - `Student Name`
     - `City`
     - `Class ID`
     - `Enrollment Date`

### Supported Operations

- **Insert**: Add a new student to the tree.
- **Search**: Find a student by their ID or city.
- **Update**: Modify a student's information.
- **Delete**: Remove a student using their ID.
- **Sort**: Display students in lexicographic order of their names.
- **Group**: Organize students by their class.
- **Save**: Persist student data to a file.

---

## File Structure

### Input File (`studentsData.txt`)

The input file stores student data in the following format:
    ```
    StudentID StudentName City EnrollmentDate ClassID
        
    Example: 101 John Seattle 2022-09-01 CS101 102 Alice Boston 2023-01-15 CS102 103 Bob Denver 2022-07-20 CS101


---

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC).
- Basic knowledge of file handling and data structures.

### Steps to Run the Program

1. Clone the repository:
   ```bash
   git clone https://github.com/Lanamahd/Student-Management-System.git
   cd Student-Management-System

2. Compile the program:
   ```bash
    gcc main.c -o student_management_system

3. Run the executable:
    ```bash
    ./student_management_system

4. Follow the menu options to interact with the system.

---

## Menu Options
The program provides the following menu for user interaction:

1. **Insert a Student**:
  - Add a new student with their associated data.

2. **Find a Student by ID**:

  - Locate a student by their unique ID.
  - Optionally update their information.
    
3. **List All Students**:

  - Display all students sorted by their names.

4. **Search Students by City**:

  -Find all students from a specific city.

5. **Group Students by Class**:
  - Display students grouped by their class.

6. **Delete a Student**:

  -Remove a student by their ID.

7. **Save Students to File**:

  - Persist the current student records to studentsData.txt.

8. **Exit**:

  - Exit the program.

---

## Example Output

### Case 1: Insert a Student

    ```
    ENTER STUDENT ID: 104
    ENTER STUDENT NAME: Charlie
    ENTER STUDENT CITY: Austin
    ENTER STUDENT ENROLLMENT DATE: 2023-03-10
    ENTER CURRENT CLASS ID: CS103
    
    STUDENT ADDED SUCCESSFULLY!

### Case 2: Search for a Student by ID
    ```
    ENTER STUDENT ID: 102
    STUDENT IS FOUND!
    STUDENT NAME: Alice
    STUDENT CITY: Boston
    CURRENT CLASS ID: CS102
    ENROLLMENT DATE: 2023-01-15

### Case 3: List All Students

    ```
    STUDENTS BY LEXICOGRAPHIC ORDER OF THEIR NAMES:
    STUDENT NAME: Alice
    STUDENT ID: 102
    STUDENT CITY: Boston
    CURRENT CLASS ID: CS102
    ENROLLMENT DATE: 2023-01-15
    
    STUDENT NAME: Bob
    STUDENT ID: 103
    STUDENT CITY: Denver
    CURRENT CLASS ID: CS101
    ENROLLMENT DATE: 2022-07-20
    
    STUDENT NAME: John
    STUDENT ID: 101
    STUDENT CITY: Seattle
    CURRENT CLASS ID: CS101
    ENROLLMENT DATE: 2022-09-01

---

## Conclusion
The Student Management System is a robust and efficient application for managing student records. By leveraging binary search trees, the program ensures fast and reliable operations for inserting, searching, deleting, and listing students. The interactive menu and file-based persistence make it user-friendly and practical for real-world use cases.

This project demonstrates the effective use of data structures, algorithms, and file handling in C. It can serve as a foundation for further enhancements, such as adding graphical user interfaces (GUI) or integrating database systems. 
