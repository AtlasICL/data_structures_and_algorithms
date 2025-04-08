/**
 * Recursive solution for towers of Hanoi.
 */

#include <iostream>
#include <string>
#include <stdexcept>

class HanoiSolver {
public:
    void solve(int num_disks, std::string source, std::string aux, std::string target) {
        if (num_disks <= 0) {
            std::invalid_argument("Invalid number of disks for Hanoi");
        }
        moveDisks(num_disks, source, aux, target);
    }

private:
    void moveDisks(int num_disks, std::string source, std::string aux, std::string target) {
        if (num_disks == 1) { // base case
            printMove(1, source, target);
            return;
        }
        moveDisks(num_disks - 1, source, target, aux);
        printMove(num_disks, source, target);
        moveDisks(num_disks - 1, aux, source, target);
    }

    // prints a move to the console
    void printMove(int diskNumber, std::string sourceRod, std::string destinationRod) const {
        std::cout << "Move disk " << diskNumber << " from " << sourceRod << " to " << destinationRod << std::endl;
    }

};

int main() {
    int NUM_DISKS = 5;
    HanoiSolver solver;
    solver.solve(NUM_DISKS, "A", "B", "C");
}