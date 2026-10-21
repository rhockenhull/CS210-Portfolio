# Filename: Investment_header.psc
# Date: October 2, 2026
# Author: Ryan Hockenhull
# Description: Defines the Investment class, attributes, constants, and method interfaces.

# Investment.h: class structure only
CLASS Investment
    PRIVATE ATTRIBUTES
        m_initialInvestment as decimal
        m_monthlyDeposit as decimal
        m_annualInterest as decimal
        m_numberOfYears as whole number
    END
    PRIVATE ATTRIBUTES
        # Constant values
        MONTHS_PER_YEAR as whole number with value 12
        PERCENT_DIVISOR as decimal with value 100
    END
    PUBLIC METHODS
        CONSTRUCTOR Investment
            PASS IN t_initialInvestment, t_monthlyDeposit, t_annualInterest, t_numberOfYears
        METHOD displayReportWithoutMonthlyDeposits
        METHOD displayReportWithMonthlyDeposits
    END CONSTRUCTORS
    PRIVATE METHODS
        METHOD displayReport
            PASS IN t_deposit, t_title
        METHOD printDetails
            PASS IN t_year, t_balance, t_interest
    END
END CLASS

