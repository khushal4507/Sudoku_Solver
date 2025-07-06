# Sudoku Solver

## Overview

This project implements a Sudoku solver in C++. The solver reads a Sudoku puzzle either from user input or from a file, validates the input, and employs a backtracking algorithm to solve the puzzle.

## Features

- **Input Methods**: Choose between manual entry or reading from a file.
- **Validation**: Ensures that input values are within valid ranges (0-9).
- **Backtracking Algorithm**: Utilizes a recursive approach to solve the puzzle efficiently.

## Technical Details

### Class Structure

1. **`SudokuGrid`**:
   - Manages the 9x9 grid and handles user input.
   - Contains methods for displaying the grid, setting, and getting cell values.

2. **`SudokuSolver`**:
   - Contains the logic for solving the Sudoku puzzle using backtracking.
   - Tracks recursive calls to provide statistics on the solving process.

### Input Format

- For manual input, the user is prompted to enter values for each cell (0 for empty cells).
- For file input, the file should contain 81 integers separated by spaces, representing the Sudoku grid.

### Usage

1. Compile the program using a C++ compiler:
   ```bash
   g++ -o sudoku_solver sudoku_solver.cpp
   ```

2. Run the program:
   ```bash
   ./sudoku_solver
   ```

3. Follow the prompts to input the Sudoku puzzle.

## Complexity Analysis

The time complexity of the backtracking algorithm used in this solver is generally \(O(9^{n})\), where \(n\) is the number of empty cells in the Sudoku puzzle. In the worst case, this can lead to a significant number of recursive calls, but in practice, most puzzles can be solved much more quickly.
