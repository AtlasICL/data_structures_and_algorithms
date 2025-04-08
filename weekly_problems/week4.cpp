/**
 * Recursive solution for towers of Hanoi.
 */

#include <iostream>
#include <string>

class HanoiSolver {
public:
    void solve(int num_disks, std::string source, std::string aux, std::string target) {
        moveDisks(num_disks, source, aux, target);
    }

private:
    void moveDisks(int num_disks, std::string source, std::string aux, std::string target) {
        if (num_disks == 1) {
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
    int numberOfDisks;
    std::cout << "Enter the number of disks: ";
    std::cin >> numberOfDisks;

    if (std::cin.fail() || numberOfDisks <= 0) {
        std::cerr << "Invalid input. Please enter a positive integer.\n";
        return 1;
    }

    HanoiSolver solver;
    solver.solve(numberOfDisks, "A", "B", "C"); // A = source, B = helper, C = destination

    return 0;
}