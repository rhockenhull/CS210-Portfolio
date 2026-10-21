# Filename: main.psc
# Date: October 2, 2026
# Author: Ryan Hockenhull
# Description: Plans input validation, object creation, report calls, and program shutdown.

# Overview: validate four inputs, create Investment, display both reports,
# and repeat when the user enters y. Errors display a message and end the program.

# main.cpp: driver and input helpers
# These helpers belong to the driver file rather than the investment class
METHOD readNumber
    PASS IN t_prompt, t_allowZero, t_wholeNumber, t_value by reference
    DECLARE line as text
    DECLARE extra as character
    DECLARE validInput as boolean initially false
    WHILE validInput is equal to false
        DISPLAY t_prompt
        INPUT a complete line into line
        IF the input stream has closed THEN
            THROW an error that input ended
        ENDIF
        CREATE parser from line
        IF parser reads a decimal into t_value and cannot read an extra character THEN
            IF t_value is finite and t_value is greater than or equal to zero THEN
                IF t_allowZero is true or t_value is greater than zero THEN
                    IF t_wholeNumber is false or t_value is a whole number within the integer range THEN
                        SET validInput to true
                    ENDIF
                ENDIF
            ENDIF
        ENDIF
        IF validInput is equal to false THEN
            DISPLAY "Invalid input. Enter a positive whole number of years when t_wholeNumber is true, a number of zero or greater when t_allowZero is true, or a number greater than zero otherwise."
        ENDIF
    ENDWHILE
END METHOD

METHOD readAgain
    PASS IN t_choice by reference
    DECLARE line as text
    DECLARE validInput as boolean initially false
    WHILE validInput is equal to false
        DISPLAY "Try different values? (y/n): "
        INPUT a complete line into line
        IF the input stream has closed THEN
            THROW an error that input ended
        ENDIF
        IF line is equal to "y" or "Y" or "n" or "N" THEN
            SET t_choice to the first character of line
            SET validInput to true
        ENDIF
        IF validInput is equal to false THEN
            DISPLAY "Please enter y or n."
        ENDIF
    ENDWHILE
END METHOD

BEGIN
    DECLARE initialInvestment as decimal
    DECLARE monthlyDeposit as decimal
    DECLARE annualInterest as decimal
    DECLARE yearsInput as decimal
    DECLARE numberOfYears as whole number
    DECLARE choice as character initially "y"
    DECLARE pauseLine as text
    EXCEPTION
        WHILE choice is equal to "y" or "Y"
            DISPLAY "Airgead Banking - Data Input"
            CALL readNumber
                PASS IN "Initial Investment Amount: ", false, false, initialInvestment by reference
            CALL readNumber
                PASS IN "Monthly Deposit: ", true, false, monthlyDeposit by reference
            CALL readNumber
                PASS IN "Annual Interest (%): ", false, false, annualInterest by reference
            CALL readNumber
                PASS IN "Number of Years: ", false, true, yearsInput by reference
            SET numberOfYears to yearsInput converted to a whole number
            DISPLAY "Press Enter to continue..."
            INPUT a complete line into pauseLine
            IF the input stream has closed THEN
                THROW an error that input ended
            ENDIF
            CREATE investment as Investment
                PASS IN initialInvestment, monthlyDeposit, annualInterest, numberOfYears
            CALL investment.displayReportWithoutMonthlyDeposits
            CALL investment.displayReportWithMonthlyDeposits
            CALL readAgain
                PASS IN choice by reference
        ENDWHILE
    WHEN an error is thrown THEN
        DISPLAY the error message
        SET program exit status to one
        END
    END
    SET program exit status to zero
END
