/*
 * Author: Ryan Hockenhull
 * Course: CS-210 Programming Languages
 * Project: Project Two - Airgead Banking
 * Date: October 2, 2026
 * File: Investment.cpp
 * Description: Calculates investment growth and displays the yearly reports.
 */
#include "Investment.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

// Store the validated inputs so both reports use the same starting information.
Investment::Investment(double t_initialInvestment, double t_monthlyDeposit,
                       double t_annualInterest, int t_numberOfYears)
    : m_initialInvestment(t_initialInvestment), m_monthlyDeposit(t_monthlyDeposit),
      m_annualInterest(t_annualInterest), m_numberOfYears(t_numberOfYears) {}

void Investment::displayReportWithoutMonthlyDeposits() const {
    // A zero deposit lets us reuse the monthly calculation without adding money.
    displayReport(0.0, "Balance and Interest Without Additional Monthly Deposits");
}

void Investment::displayReportWithMonthlyDeposits() const {
    // This report starts over with the original investment, using monthly deposits.
    displayReport(m_monthlyDeposit, "Balance and Interest With Additional Monthly Deposits");
}

void Investment::displayReport(double t_deposit, const std::string& t_title) const {
    double balance = m_initialInvestment;
    // Convert the entered percent into a monthly decimal rate.
    const double monthlyRate = m_annualInterest / PERCENT_DIVISOR / MONTHS_PER_YEAR;
    std::cout << '\n' << t_title << '\n' << std::string(72, '=') << '\n'
              << "Year\t\tYear End Balance\t\tYear End Earned Interest\n";
    for (int year = 1; year <= m_numberOfYears; ++year) {
        // Reset interest each year because the report needs annual totals.
        double yearlyInterest = 0.0;
        for (int month = 1; month <= MONTHS_PER_YEAR; ++month) {
            // Add the deposit first to match the Project Two sample report.
            balance += t_deposit;
            const double monthlyInterest = balance * monthlyRate;
            balance += monthlyInterest;
            yearlyInterest += monthlyInterest;
            // Stop safely if an unusually large input exceeds the numeric range.
            if (!std::isfinite(balance) || !std::isfinite(yearlyInterest)) {
                throw std::overflow_error("The investment grew too large to calculate.");
            }
        }
        printDetails(year, balance, yearlyInterest);
        // Avoid overflowing the year counter at the maximum integer value.
        if (year == m_numberOfYears) {
            break;
        }
    }
}

void Investment::printDetails(int t_year, double t_balance, double t_interest) const {
    // Only round the displayed amounts, keeping full precision in calculations.
    std::cout << std::fixed << std::setprecision(2)
              << t_year << "\t\t$" << t_balance << "\t\t$" << t_interest << '\n';
}
