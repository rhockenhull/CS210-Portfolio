/*
 * Author: Ryan Hockenhull
 * Course: CS-210 Programming Languages
 * Project: Project Two - Airgead Banking
 * Date: October 2, 2026
 * File: Investment.h
 * Description: Defines the Investment class, its attributes, and its methods.
 */
#ifndef AIRGEAD_BANKING_INVESTMENT_H_
#define AIRGEAD_BANKING_INVESTMENT_H_
#include <string>

class Investment {
public:
    // Public Methods
    Investment(double t_initialInvestment, double t_monthlyDeposit,
               double t_annualInterest, int t_numberOfYears);
    void displayReportWithoutMonthlyDeposits() const;
    void displayReportWithMonthlyDeposits() const;

private:
    // Attributes
    double m_initialInvestment;
    double m_monthlyDeposit;
    double m_annualInterest;
    int m_numberOfYears;

    // Constants
    static constexpr int MONTHS_PER_YEAR = 12;
    static constexpr double PERCENT_DIVISOR = 100.0;

    // Private Methods
    void displayReport(double t_deposit, const std::string& t_title) const;
    void printDetails(int t_year, double t_balance, double t_interest) const;
};
#endif // AIRGEAD_BANKING_INVESTMENT_H_
