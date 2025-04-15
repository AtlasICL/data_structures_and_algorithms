/**
 * Recursive solution for towers of Hanoi.
 */

#include <iostream>
#include <string>
#include <stdexcept>

enum Rod {
    A,
    B,
    C
}; 

// helper function to convert Rod enum to string
std::string rodToStr(Rod rod) {
    switch (rod) {
        case Rod::A: return "A";
        case Rod::B: return "B";
        case Rod::C: return "C";
        default: return "";
    }
}

class HanoiSolver {
public:
    void solve(int num_disks, Rod source, Rod aux, Rod target) {
        if (num_disks <= 0) {
            std::invalid_argument("Invalid number of disks for Hanoi");
        }
        moveDisks(num_disks, source, aux, target);
    }

private:
    void moveDisks(int num_disks, Rod source, Rod aux, Rod target) {
        if (num_disks == 1) { // base case
            printMove(1, source, target);
            return;
        }
        moveDisks(num_disks - 1, source, target, aux);
        printMove(num_disks, source, target);
        moveDisks(num_disks - 1, aux, source, target);
    }

    // prints a move to the console
    void printMove(int diskNumber, Rod sourceRod, Rod destinationRod) const {
        std::cout << "Move disk " << diskNumber << " from " << rodToStr(sourceRod) << " to " << rodToStr(destinationRod) << std::endl;
    }
};

int main() {
    int NUM_DISKS = 2;
    HanoiSolver solver;
    solver.solve(NUM_DISKS, Rod::A, Rod::B, Rod::C);
}