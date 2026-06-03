# Practice Problems: Structures and Multi-File Programming

This document contains a series of problems designed to help you master structures, arrays, and multi-file code organization in C.

---

## Concept Overview: Multi-File Sharing
To share a global variable (like an array of structures) across multiple files:
1.  **Define** the variable in **one** `.c` file (e.g., `main.c`).
2.  **Declare** it as `extern` in the other `.c` files that need to use it, OR include it in a header file as `extern`.
3.  **Include** the structure definition (the `struct` template) in a common `.h` file.

---

## Problem 1: The Shared Library (Printing)
**Goal:** Create a program where data is defined in `main.c` but printed by a function in `printer.c`.

- **`book.h`**: Define `struct Book { char title[50]; float price; };`.
- **`main.c`**: Define a global array `struct Book library[3]`.
- **`printer.c`**: Implement `void printLibrary()` which uses `extern struct Book library[3]` to print all books.

---

## Problem 2: Data Modification (Writing/Updating)
**Goal:** Modify data from a separate file.

- **Task:** Create `editor.c`.
- **Function:** `void updatePrice(int index, float newPrice)`.
- **Requirement:** This function should access the global `library` array (using `extern`) and update the price of the book at the given index.
- **Test:** Call `updatePrice` from `main.c` and then call the print function to verify the change.

---

## Problem 3: User Input (Reading)
**Goal:** Populate the structure using `scanf` from a separate file.

- **Task:** Create `input_handler.c`.
- **Function:** `void fillBookData()`.
- **Requirement:** Use a loop to ask the user for the title and price of each book in the shared `library` array.
- **Tip:** Use `fgets` for titles with spaces.

---

## Problem 4: The Student Management System (Mini-Project)
**Goal:** Combine everything into a modular system.

**Files:**
1.  `student.h`: Define `struct Student { int id; char name[50]; float gpa; };`.
2.  `database.c`: Define `struct Student db[5];`.
3.  `operations.c`: 
    - `void addStudent(int i, int id, char* name, float gpa)`
    - `void findTopStudent()` (Finds the student with the highest GPA).
4.  `main.c`: The menu system to call these functions.

---

## Compilation Guide
When working with multiple files, compile them all together:

```bash
gcc main.c printer.c editor.c input_handler.c -o my_program
./my_program
```
