#include <iostream>
#include <iomanip> // Include the necessary header file
#include "tabulate.hpp"
#include "colors.h"

// may use https://github.com/DenisSamilton/CppConsoleTable
// TODO: Error trap only two decimal places for money
// TODO: Fix table formatting

using namespace std;

float loanAmount = 0;
float annualInterestRate = 0;
float monthlyInterestRate = 0;
float monthlyPayment = 0;
tabulate::Table paymentsTable;

bool badFloatCharacters(string inputFloat)
/*
  Args:
    inputNumber (string): The number that the user has inputted as a string
  Returns:
    bool: Returns true if the inputNumber contains an invalid character, and
  false if it does not
*/
{
  // For the length of the inputNumber, make sure each character is a number
  for (int i = 0; i < inputFloat.length(); i++)
  {
    if (!isdigit(inputFloat[i]) && inputFloat[i] != '.')
    {
      return true;
    }
  }
  return false;
}

float getValidFloat(string prompt, string errorMessage) {
  string inputFloat = "0";
    // Ask the user to input a number
    cout << GREEN << prompt;
    cin >> inputFloat;

    // While the input is invalid, ask the user to input a number again
    while (cin.fail() || badFloatCharacters(inputFloat) ||
           stof(inputFloat) < 0)
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << BOLD << RED
           << errorMessage;
      cin >> inputFloat;
    }
    // Convert the inputNumber to an integer
    float outputFloat = stof(inputFloat);
    return outputFloat;
}

  float getAnnualInterestRate() {
    float tempInterestRate = 0;
    tempInterestRate = getValidFloat("I reckon you should enter your annual interest rate (%): ", "Invalid input. Please enter a positive numeric value (%): ");
    // convert to decimal
    return tempInterestRate / 100;
  }

  float getMonthlyInterestRate(float annualRate) {
    return (annualRate / 12);
  }

  float getMonthlyPayment() {
    float payment = 0;
    payment = getValidFloat("I reckon you should enter your monthly payment: $", "Invalid input. Please enter a positive numeric value: $");
    return payment;
  }

  bool canLoanBePaidOff(float principle, float monthlyInterest, float payment) {
    if (payment <= principle * monthlyInterest)
    {
      return false;
    } else {
      return true;
    }

  }

  string FtoS(float inputFloat) {
    // convert to string 2 decimal places
    ostringstream oss;
    oss << fixed << setprecision(2) << inputFloat; // Use std::ostringstream to format the float
    return oss.str(); // Return the formatted string
  }

  void displayPayments(int month, float principle, float payment, float interest, float newPrinciple) {
    // cout << "Month: " << month << " | Previous Loan Amount: $" << principle << " | Payment: $" << payment << " | Interest: $" << interest << " | New Loan Amount: $" << newPrinciple << endl;
    if (month == 1)
    {
      // paymentsTable[0].format().font_align(tabulate::FontAlign::center);
      paymentsTable.add_row({"Month", "Previous Loan Amount", "Payment", "Interest", "New Loan Amount"});
    }
    paymentsTable.add_row({FtoS(month), "$" + FtoS(principle), "$" + FtoS(payment), "$" + FtoS(interest), "$" + FtoS(newPrinciple)});
  }
/*
  14, prev bal: 16.74, payment: 16.74, interest: 0.00, new bal: 0.00
*/

  void calculateLoan(float principle, float monthlyInterest, float payment) {
    int month = 0;
    float newPrinciple = 0;
    while (principle > 0)
    {
      month++;
      float interest = (principle * monthlyInterest) - (payment * monthlyInterest);
      newPrinciple = principle - payment + interest;
      if (newPrinciple < 0)
      {
        payment = principle;
        interest = 0;
        newPrinciple = 0;
      }
      displayPayments(month, principle, payment, interest, newPrinciple);
      principle = newPrinciple;
    }
    paymentsTable.format()
        .border_left(" ")
        .border_right(" ")
        .corner(" ")
        .padding_left(1)
        .padding_right(1);
    cout << paymentsTable << endl;
  }

  int main()
  {
    cout << YELLOW << "Howdy there, partner! I do declare that this loan calculator is the best in the west! Yeehaw!" << RESET << endl;
    loanAmount = getValidFloat("I reckon you should enter your loan amount: $", "Invalid input. Please enter a positive numeric value: $");
    annualInterestRate = getAnnualInterestRate();
    monthlyInterestRate = getMonthlyInterestRate(annualInterestRate);
    monthlyPayment = getMonthlyPayment();
    if (canLoanBePaidOff(loanAmount, monthlyInterestRate, monthlyPayment))
    {
      calculateLoan(loanAmount, monthlyInterestRate, monthlyPayment);
    }
    else
    {
      cout << "I reckon you can't pay off this loan with that payment." << endl;
    }
  }