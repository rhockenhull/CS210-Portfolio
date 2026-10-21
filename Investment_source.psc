# Filename: Investment_source.psc
# Date: October 2, 2026
# Author: Ryan Hockenhull
# Description: Plans monthly investment calculations and yearly reports.

# Investment.cpp: method logic
CLASS Investment
    CONSTRUCTOR Investment
        PASS IN t_initialInvestment, t_monthlyDeposit, t_annualInterest, t_numberOfYears
        SET m_initialInvestment to t_initialInvestment
        SET m_monthlyDeposit to t_monthlyDeposit
        SET m_annualInterest to t_annualInterest
        SET m_numberOfYears to t_numberOfYears
    END CONSTRUCTOR

    METHOD displayReportWithoutMonthlyDeposits
        # Starting a separate report keeps the two scenarios independent
        CALL displayReport
            PASS IN zero, "Balance and Interest Without Additional Monthly Deposits"
    END METHOD

    METHOD displayReportWithMonthlyDeposits
        CALL displayReport
            PASS IN m_monthlyDeposit, "Balance and Interest With Additional Monthly Deposits"
    END METHOD

    METHOD displayReport
        PASS IN t_deposit, t_title
        DECLARE balance as decimal initially m_initialInvestment
        DECLARE monthlyRate as decimal
        SET monthlyRate to m_annualInterest divided by PERCENT_DIVISOR divided by MONTHS_PER_YEAR
        DISPLAY t_title
        DISPLAY a separator of 72 equal signs
        DISPLAY Year, Year End Balance, Year End Earned Interest separated by two tabs
        FOR year from one through m_numberOfYears
            DECLARE yearlyInterest as decimal initially zero
            FOR month from one through MONTHS_PER_YEAR
                # The project sample includes the new deposit before interest
                SET balance to balance plus t_deposit
                DECLARE monthlyInterest as decimal
                SET monthlyInterest to balance multiplied by monthlyRate
                SET balance to balance plus monthlyInterest
                SET yearlyInterest to yearlyInterest plus monthlyInterest
                IF balance is not finite or yearlyInterest is not finite THEN
                    THROW an error that the investment grew too large
                ENDIF
            ENDFOR
            CALL printDetails
                PASS IN year, balance, yearlyInterest
            # End the loop after the final year before incrementing its counter
        ENDFOR
    END METHOD

    METHOD printDetails
        PASS IN t_year, t_balance, t_interest
        # Round only the display so monthly calculations keep their precision
        SET output format to fixed with two decimal places
        DISPLAY t_year, dollar sign and t_balance, dollar sign and t_interest separated by two tabs
    END METHOD
END CLASS

