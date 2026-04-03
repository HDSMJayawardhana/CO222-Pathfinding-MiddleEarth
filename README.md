# 🧙 Optimal Path to Mount Doom
### CO222 – Programming Methodology | University of Peradeniya | 2023

![Language](https://img.shields.io/badge/Language-C-blue)
![Algorithm](https://img.shields.io/badge/Algorithm-BFS-green)
![Fibonacci](https://img.shields.io/badge/Math-Fibonacci-orange)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![University](https://img.shields.io/badge/University-Peradeniya-red)
![Year](https://img.shields.io/badge/Year-2023-yellow)

---

## 📖 Project Overview

A grid-based pathfinding simulation inspired by **Lord of the Rings**,
developed as a **Second Year Coursework Project** for CO222 -
Programming Methodology at the **Faculty of Engineering,
University of Peradeniya**.

The objective is to help **Frodo Baggins** find the **minimum distance
path** from a given starting point to **Mount Doom** across a
Middle-Earth map, subject to:
- **Altitude-based movement constraints**
- **Magical teleportation doors** identified using Fibonacci logic

---

## 🗺️ Problem Background

Frodo Baggins must carry the One Ring to Mount Doom in Mordor.
To navigate Middle-Earth safely, we need to find the **optimal
(minimum distance) path** on a character-based grid map.

Each cell on the map contains a capital letter **(A-Z)**, and the
**ASCII value** of the letter represents the **altitude** of that cell.

---

## 🏗️ Project Structure

    CO222-Pathfinding-MiddleEarth/
    │
    ├── README.md
    │
    ├── Milestone_01/
    │   └── co222-project-m1.c        <- Basic BFS Pathfinding
    │
    ├── Milestone_02/
    │   ├── task1_fibonacci.c          <- Fibonacci Matcher
    │   ├── task2_teleportation.c      <- Multi-point Distance Calculator
    │   └── task3_full_solution.c      <- Complete Solution
    │
    └── docs/
        ├── Milestone01_Brief.pdf
        └── Milestone02_Brief.pdf

---

## 📐 Map Representation

The map is given as a **string of H x W capital letters** which is
converted into a **2D character array**.

### Example Input String: ABCCDGLCKEZZBLFXYCMGDVEGH | Map Size: 5x5

    [ A  B  C  C  D ]
    [ G  L  C  K  E ]
    [ Z  Z  B  L  F ]
    [ X  Y  C  M  G ]
    [ D  V  E  G  H ]

- **Start:** (0,0) -> A
- **End:** (4,2) -> E
- **Minimum Distance:** 6 moves

---

## 🚶 Movement Rules

| Rule | Condition |
|------|-----------|
| ✅ Move Up/Down/Left/Right | Always allowed if altitude rule passes |
| ✅ Climbing | ASCII(Next) - ASCII(Current) <= 2 |
| ✅ Descending | ASCII(Current) - ASCII(Next) <= 3 |
| ❌ Diagonal moves | Never allowed |

### Altitude Examples

    Current cell = 'C' (ASCII 67)
    Next cell    = 'E' (ASCII 69)
    Difference   = 69 - 67 = 2  -> Climbing allowed ✅

    Current cell = 'E' (ASCII 69)
    Next cell    = 'B' (ASCII 66)
    Difference   = 69 - 66 = 3  -> Descending allowed ✅

    Current cell = 'A' (ASCII 65)
    Next cell    = 'Z' (ASCII 90)
    Difference   = 90 - 65 = 25 -> Too steep, not allowed ❌

---

## 📥 Input / Output Format

### Milestone 01 Input Format

    H W
    S1 S2       <- Start position (0-indexed)
    E1 E2       <- End position (0-indexed)
    [H x W character string]

### Sample Input

    5 5
    0 0
    4 2
    ABCCDGLCKEZZBLFXYCMGDVEGH

### Sample Output

    The minimum distance from A to E is 6

### No Path Output

    There is no possible path from A to E

---

## 🚪 Milestone 02 — Teleportation Doors

While travelling, Frodo discovers **magical teleportation doors**
on the map. Two special doors can **teleport bidirectionally**
with **zero distance** between them.

### How to Identify Teleportation Doors

    Calculated Number = Row Number x Map Width + Column Number
    Fibonacci(Calculated Number) == Given Magic Number
    -> That cell is a Teleportation Door ✅

### Teleportation Door Example

    Map Width = 5
    Cell C at [0,2] -> 0x5 + 2 = 1  -> Fib(1)  = 1   -> Door 1 ✅
    Cell B at [2,2] -> 2x5 + 2 = 12 -> Fib(12) = 144 -> Door 2 ✅

### Teleportation Path Example

    A -> C -> (teleport zero distance) -> B -> E
    Distance = 2 + 0 + 2 = 4

---

## 📋 Milestone 02 Tasks

### Task 01 — Fibonacci Matcher

    Input  : 3 integers (n, m1, m2)
    Task   : Calculate Fib(n), check if equals m1 or m2
    Output : TRUE or FALSE

    Sample Input  : 10 34 55
    Sample Output : TRUE
    Reason        : Fib(10) = 55, matches m2

### Task 02 — Multi-Point Distance Calculator

    Returns 5 distances:
    1. Start -> End         (no teleportation)
    2. Start -> Door 1
    3. Start -> Door 2
    4. Door 1 -> End
    5. Door 2 -> End

    Returns -1 if no path exists

    Sample Input  : 5 5 | Start(0,0) | End(4,2) | Door1(0,2) | Door2(2,2)
    Sample Output : 6 2 4 4 2

### Task 03 — Full Solution

    Input  : Map + Magic numbers + Door cell positions
    Task   : Identify teleportation doors using Fibonacci
             Find minimum distance with or without teleportation
    Output : Minimum distance or no path message

    Sample Input  : Map + M1=1 + M2=144 + 5 door cells
    Sample Output : The minimum distance from A to E is 4

---

## 🧪 Test Cases

### Milestone 01

| Test | Size | Start | End | Output |
|------|------|-------|-----|--------|
| 0 | 5x4 | (0,0) | (4,2) | Distance = 6 |
| 1 | 5x5 | (0,0) | (4,4) | Distance = 8 |
| 2 | 6x6 | (5,5) | (3,3) | Distance = 20 |

### Milestone 02 Task 02

| Test | Door 1 | Door 2 | Output |
|------|--------|--------|--------|
| 0 | (0,2) | (2,2) | 6 2 4 4 2 |
| 1 | (0,2) | (4,0) | 6 2 -1 4 -1 |

---

## ⚙️ Algorithm Details

### BFS (Breadth-First Search)

    1. Start from source cell
    2. Explore all valid neighbors (up/down/left/right)
    3. Check altitude movement rules before moving
    4. Track visited cells to avoid revisiting
    5. Return distance when destination reached
    6. Return -1 if queue empties without finding destination

### Fibonacci Calculation

    Fib(0) = 0
    Fib(1) = 1
    Fib(n) = Fib(n-1) + Fib(n-2)

---

## 💻 How to Compile and Run

### Compile

    gcc co222-project-m1.c -o milestone1

### Run

    ./milestone1

### Enter Input

    5 5
    0 0
    4 2
    ABCCDGLCKEZZBLFXYCMGDVEGH

---

## 🛠️ Technologies Used

| Tool | Purpose |
|------|---------|
| C Language | Core programming |
| BFS Algorithm | Shortest path finding |
| Global Arrays | Map storage |
| Fibonacci Logic | Door identification |
| GCC Compiler | Compilation |

---

## 📊 Key Concepts Demonstrated

- ✅ 2D Array manipulation in C
- ✅ BFS shortest path algorithm
- ✅ Queue data structure implementation
- ✅ Global array usage
- ✅ Modular function design
- ✅ Fibonacci sequence calculation
- ✅ ASCII-based altitude comparison
- ✅ Graph traversal with constraints

---

## 🎓 Academic Information

| Detail | Info |
|--------|------|
| Course | CO222 - Programming Methodology |
| Year | 2nd Year - 2023 |
| Institution | University of Peradeniya |
| Faculty | Faculty of Engineering |
| Department | Computer Engineering |
| Milestone 01 | Basic BFS Pathfinding |
| Milestone 02 | Fibonacci Teleportation Doors |

---

## 📁 File Naming Convention

    Milestone 01 : co222-project-m1.c
    Milestone 02 : eXXYYYY-co222-project-m2-t1.c
                   eXXYYYY-co222-project-m2-t2.c
                   eXXYYYY-co222-project-m2-t3.c

---

## 👤 Author

**Salinda Madushan**
Mechatronics Engineer | Robotics & AI Specialist

[![LinkedIn](https://img.shields.io/badge/LinkedIn-Connect-blue)](https://linkedin.com/in/h-d-s-m-jayawardhana)
[![GitHub](https://img.shields.io/badge/GitHub-Follow-black)](https://github.com/Salinda1999)

---

## 📄 License

This project was developed as academic coursework at the
University of Peradeniya. All code is original work by the author.

---

*"Not all those who wander are lost." — J.R.R. Tolkien* 🧙
