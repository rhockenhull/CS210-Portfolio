/*
 * Author: Ryan Hockenhull
 * Course: CS-210 Programming Languages
 * Project: Project Two - Airgead Banking
 * Date: October 2, 2026
 * File: main.cpp
 * Description: Collects and validates user input, then displays both investment reports.
 */
#include "Investment.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>

// Read whole lines so text such as 5abc cannot be accepted as the number 5.
void readNumber(const std::string& t_prompt, bool t_allowZero,
                bool t_wholeNumber, double& t_value) {
    std::string line;
    char extra;
    while (true) {
        std::cout << t_prompt;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Input ended. Closing the program.");
        }
        std::istringstream parser(line);
        if ((parser >> t_value) && !(parser >> extra)) {
            // Reject negatives, nonfinite numbers, and zero when a positive value is needed.
            if (std::isfinite(t_value) && t_value >= 0.0 &&
                (t_allowZero || t_value > 0.0)) {
                // Years must fit in an integer and cannot contain a fraction.
                if (!t_wholeNumber ||
                    (std::floor(t_value) == t_value &&
                     t_value <= std::numeric_limits<int>::max())) {
                    break;
                }
            }
        }
        std::cout << "Invalid input. Enter "
                  << (t_wholeNumber ? "a positive whole number of years."
                      : t_allowZero ? "a number of zero or greater."
                                    : "a number greater than zero.") << '\n';
    }
}

void readAgain(char& t_choice) {
    std::string line;
    while (true) {
        std::cout << "\nTry different values? (y/n): ";
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Input ended. Closing the program.");
        }
        // Only accept a clear yes or no so accidental text does not start another run.
        if (line == "y" || line == "Y" || line == "n" || line == "N") {
            t_choice = line.front();
            break;
        }
        std::cout << "Please enter y or n.\n";
    }
}

int main() {
    double initialInvestment = 0.0;
    double monthlyDeposit = 0.0;
    double annualInterest = 0.0;
    double yearsInput = 0.0;
    int numberOfYears = 0;
    char choice = 'y';
    std::string pauseLine;
    try {
        // Repeat the input screen so the user can compare different investments.
        while (choice == 'y' || choice == 'Y') {
            std::cout << "\nAirgead Banking - Data Input\n";
            readNumber("Initial Investment Amount: ", false, false, initialInvestment);
            readNumber("Monthly Deposit: ", true, false, monthlyDeposit);
            readNumber("Annual Interest (%): ", false, false, annualInterest);
            readNumber("Number of Years: ", false, true, yearsInput);
            numberOfYears = static_cast<int>(yearsInput);
            // Enter provides a portable pause without operating-system commands.
            std::cout << "Press Enter to continue...";
            if (!std::getline(std::cin, pauseLine)) {
                throw std::runtime_error("Input ended. Closing the program.");
            }
            Investment investment(initialInvestment, monthlyDeposit,
                                  annualInterest, numberOfYears);
            investment.displayReportWithoutMonthlyDeposits();
            investment.displayReportWithMonthlyDeposits();
            readAgain(choice);
        }
    } catch (const std::exception& error) {
        // Give a readable message instead of ending with an unhandled exception.
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
