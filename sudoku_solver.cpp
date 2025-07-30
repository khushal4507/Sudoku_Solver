// Sudoku Solver - Refactored Version
// Author: Khushal Karadiya (Modified and cleaned)
// Objective: Solve Sudoku puzzles using backtracking algorithm

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <Windows.h>

using namespace std;

class SudokuGrid {
private:
    int board[9][9]; // 9x9 Sudoku board

    void displayMenu();
    void inputFromConsole();
    void inputFromFile();

public:
    SudokuGrid() {
        displayMenu();
    }

    void setCell(int row, int col, int value) {
        board[row][col] = value;
    }

    int getCell(int row, int col) const {
        return board[row][col];
    }

    void displayBoard() const;
};

void SudokuGrid::displayMenu() {
    cout << "\n======================\n";
    cout << "    Sudoku Solver\n";
    cout << "======================\n\n";

    cout << "Welcome! Choose your input method:\n";
    cout << "1. Enter puzzle manually\n";
    cout << "2. Load puzzle from file\n";
    cout << "--> ";

    int choice;
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice. Try again --> ";
        cin >> choice;
    }

    if (choice == 1) inputFromConsole();
    else inputFromFile();
}

void SudokuGrid::inputFromConsole() {
    cout << "\nEnter values row by row (0 for empty cells):\n";

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int value;
            cout << "Enter value for cell [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> value;
            while (value < 0 || value > 9) {
                cout << "Invalid. Enter value between 0 and 9: ";
                cin >> value;
            }
            board[i][j] = value;
        }
        cout << "------------\n";
    }
}

void SudokuGrid::inputFromFile() {
    char filename[30];
    cout << "\nEnter filename (max 20 chars): ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cout << "Error: Cannot open file!\n";
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int value;
            file >> value;
            if (value < 0 || value > 9) {
                cout << "Invalid value at position " << (i * 9 + j + 1) << ".\n";
                exit(EXIT_FAILURE);
            }
            board[i][j] = value;
        }
    }

    file.close();
    cout << "\nFile loaded successfully.\n";
}

void SudokuGrid::displayBoard() const {
    cout << "++=====================================++";
    for (int i = 0; i < 9; ++i) {
        cout << "\n||";
        for (int j = 0; j < 9; ++j) {
            if (j > 0 && j % 3 == 0) cout << "||";
            cout << " ";
            if (board[i][j] != 0) cout << board[i][j] << " ";
            else cout << "  ";
        }
        cout << "||";
        if ((i + 1) % 3 == 0)
            cout << "\n++=====================================++";
        else
            cout << "\n++-----------++-----------++-----------++";
    }
    cout << "\n";
}

class SudokuSolver {
private:
    SudokuGrid grid;
    int recursionCount;

    bool isPlacementValid(int row, int col, int val);
    bool isSubgridValid(int row, int col, int val);
    bool isGridComplete();
    bool solveRecursive();
    void solve();

public:
    SudokuSolver() : recursionCount(0) {
        grid.displayBoard();
        cout << "\nSolving puzzle...\n";
        solve();
        grid.displayBoard();
        cout << "\nTotal recursive calls: " << recursionCount << "\n";
    }
};

bool SudokuSolver::isPlacementValid(int row, int col, int val) {
    for (int i = 0; i < 9; ++i) {
        if (grid.getCell(row, i) == val || grid.getCell(i, col) == val)
            return false;
    }
    return isSubgridValid(row, col, val);
}

bool SudokuSolver::isSubgridValid(int row, int col, int val) {
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int current = grid.getCell(startRow + i, startCol + j);
            if ((startRow + i != row || startCol + j != col) && current == val)
                return false;
        }
    }
    return true;
}

bool SudokuSolver::isGridComplete() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int value = grid.getCell(i, j);
            if (value == 0 || !isPlacementValid(i, j, value))
                return false;
        }
    }
    return true;
}

bool SudokuSolver::solveRecursive() {
    recursionCount++;

    if (isGridComplete()) return true;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid.getCell(row, col) == 0) {
                for (int val = 1; val <= 9; ++val) {
                    if (isPlacementValid(row, col, val)) {
                        grid.setCell(row, col, val);
                        if (solveRecursive()) return true;
                        grid.setCell(row, col, 0);
                    }
                }
                return false; // Trigger backtracking
            }
        }
    }

    return false;
}

void SudokuSolver::solve() {
    if (solveRecursive()) {
        cout << "\nPuzzle Solved Successfully!\n";
    } else {
        cout << "\nNo solution exists for the given puzzle.\n";
    }
}

int main() {
    SudokuSolver solver;
    return 0;
}
