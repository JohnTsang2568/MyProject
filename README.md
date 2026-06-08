# Project Portfolio

This repository contains a collection of independent projects demonstrating proficiency in C++ programming, data structures, modern C++ features, GUI development, computer vision, and game design.

---

## Project 1: BigDecimal — Arbitrary-Precision Arithmetic Using Linked List

**Description:** Implements arithmetic operations for arbitrarily large integers and decimals using a doubly linked circular list. Each node holds a single digit, and the list structure allows natural propagation of carries and borrows during addition and subtraction.

**Features:**

- Full support for addition and subtraction of integers and decimals
- Sign handling and decimal point alignment
- Manual memory management following the Rule of Three
- Qt-based GUI calculator (optional frontend)

**Key Learning Outcomes:**

- Deep understanding of pointer manipulation and dynamic memory
- Experience with linked list traversal, insertion, and deletion
- Ability to design a non-trivial class with proper resource management

---

## Project 2: Stanford CS106L Assignments (Full Set)

**Description:** Complete implementation of all seven assignments from Stanford CS106L, a course on modern Standard C++ programming.

**Assignment 1: Course Scheduler**
Reads courses from a CSV file, filters by user availability, and outputs results. Practices file I/O and STL containers (`std::vector`, `std::string`).

**Assignment 2: Best Match**
Matching algorithm using field-wise comparison. Practices STL algorithms (`std::sort`, `std::find_if`), custom comparators, and string manipulation.

**Assignment 3: Custom Class Design**
Designing classes with proper encapsulation, constructors, and operator overloading. Practices OOP design, inheritance, and RAII principles.

**Assignment 4: Spell Checker**
Implements a spell checker using a custom hash table and dictionary lookup. Practices templates, hash tables, `std::unordered_set`, and file processing.

**Assignment 5: Treebook**
Implements a `User` class for a fictional social media platform with full special member functions (SMFs), operator overloading (`operator<<`, `operator+=`, `operator<`), and friend functions. Practices copy/move semantics, raw pointer array management, and symmetric friend relationships.

**Assignment 6: Explore Courses**
Uses `std::optional` and monadic operations (`and_then`, `transform`, `or_else`) to build a course lookup system without conditional branching. Practices functional-style C++23 features and the `std::optional` API.

**Assignment 7: Unique Pointer**
Implements a custom `unique_ptr` from scratch with full RAII semantics, including constructors, destructor, dereference operators, move semantics, and deleted copy operations. Practices templates, operator overloading, move semantics, and smart pointer design. Also implements a singly-linked list backed by `unique_ptr`.

**Key Learning Outcomes:**

- Mastery of C++ standard library containers and algorithms
- Deep understanding of RAII, smart pointers, and move semantics
- Experience with operator overloading, special member functions, and friend functions
- Functional-style programming with `std::optional` monadic operations
- File processing, text parsing, and data-driven design

---

## Project 3: ToDo List Application

**Description:** A feature-rich console-based ToDo list application written in C++.

**Features:**

- Add, delete, and view tasks
- Sort tasks by priority and date
- Edit task attributes (date, importance, dependencies)
- Import and export task lists
- Search tasks by keyword
- Built-in help system

**Key Learning Outcomes:**

- Modular class design (TODO, TODOlist, Command, TODOmanager)
- File I/O for data persistence
- Command parsing and interactive CLI design

---

## Project 4: LKA — Lane Keeping Assistant

**Description:** A traditional computer vision prototype for lane detection and lane keeping using Python and OpenCV.

**Features:**

- Lane detection via threshold binarization and Canny edge detection
- Pixel offset calculation between lane center and image center
- PID steering control to simulate lane keeping
- Visualization with ROI overlay, lane centerline, and steering arrow
- Video file processing for frame-by-frame lane following

**Tech Stack:** Python, OpenCV, NumPy, Matplotlib

---

## Project 5: Senren Banka Tribute — Visual Novel

**Description:** A visual novel application built with Qt, inspired by *Senren Banka*.

**Features:**

- Character-by-character text display with typewriter effect
- Customizable backgrounds and character sprites
- Background music and sound effects
- Automated UI management and scene transitions
- Keyboard interaction support

**Key Learning Outcomes:**

- Event-driven programming and Qt signal-slot mechanism
- Graphics rendering with QGraphicsScene and QGraphicsView
- Multimedia integration with QMediaPlayer

---

## Project 6: Slay the Stone — Rogue-like Card Game

**Description:** A unique blend of Hearthstone, Slay the Spire, Yu-Gi-Oh, and Shadowverse, built with Qt and C++.

**Features:**

- JSON-driven card data system with an effect factory
- Player and enemy entities with battlefield management
- Card types: Act, Power, Attack
- Player classes: Warrior, Warlock, Robot, Neutral
- Deck, hand, graveyard, and vanishyard zones
- Extensible effect system via `IEffect` interface

**Key Learning Outcomes:**

- Game architecture design with entity-component patterns
- Factory pattern for card effects
- JSON parsing and data-driven design

---

Each project contains its own source code and a detailed README inside its respective subdirectory.

Thank you for reviewing my work.
