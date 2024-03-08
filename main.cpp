/*
  Name: Zach Fauser
  Date: March 5th, 2024
  Description: This program calculates the amount of time it will take to pay off a loam based on the loan amount, annual interest rate, and monthly payment.
*/

#include <iostream>

// Used for the colors in the program
#include "colors.h"

// Used for the functions that get the user's input
#include "inputs.h"

// Used for the functions that output the results
#include "outputs.h"

using namespace std;

// Global variables
float loanAmount = 0;
float annualInterestRate = 0;
float monthlyInterestRate = 0;
float monthlyPayment = 0;
bool playAgain = true;

int main() {
  // Output a welcome message
  cout << YELLOW
       << "Howdy there, partner! I do declare that this loan calculator is the "
          "best in the west! Yeehaw!"
       << RESET << endl;
  // While the user wants to use the program...
  while (playAgain) {
    // Get the loan amount, annual interest rate and, monthly payment from the user
    loanAmount = getValidFloat("I reckon you should enter your loan amount: $",
                               "Invalid input. Please enter a positive numeric "
                               "value with two decimal places: $",
                               true, false);
    annualInterestRate = getAnnualInterestRate();
    monthlyInterestRate = getMonthlyInterestRate(annualInterestRate);
    monthlyPayment = getValidFloat("I reckon you should enter your monthly payment: $",
                          "Invalid input. Please enter a positive numeric "
                          "value with two decimal places: $",
                          true, false);
    // Check if the loan can be paid off with the monthly payment
    if (canLoanBePaidOff(loanAmount, monthlyInterestRate, monthlyPayment)) {
      // Calculate the loan
      calculateLoan(loanAmount, monthlyInterestRate, monthlyPayment);
    } else {
      // Output a message if the loan cannot be paid off with the monthly payment
      cout << RED << BOLD << "I reckon you can't pay off this loan with that payment." << RESET << endl;
    }
    // Ask the user if they want to play again
    playAgain = askPlayAgain(paymentsTable);
  }
}