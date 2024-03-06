#include <iostream>
#include "colors.h"

// may use https://github.com/DenisSamilton/CppConsoleTable
// TODO: Error trap only two decimal places for money

using namespace std;

float loanAmount = 0;
float annualInterestRate = 0;
float monthlyInterestRate = 0;
float monthlyPayment = 0;
int month = 0;

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
    return annualRate / 12;
  }

  float getMonthlyPayment() {
    float payment = 0;
    payment = getValidFloat("I reckon you should enter your monthly payment: $", "Invalid input. Please enter a positive numeric value: $");
    return payment;
  }

  bool canLoanBePaidOff(int amount, float monthlyRate, float payment) {
    if ((amount * monthlyRate) - (payment * monthlyRate) > amount)
    {
      return false;
    }
    return true;
  }

  void calculateLoan() {}

  void displayPayments() {}

  int main()
  {
    cout << "Howdy there, partner! I do declare that this loan calculator is the best in the west! Yeehaw!" << endl;
    loanAmount = getValidFloat("I reckon you should enter your loan amount: $", "Invalid input. Please enter a positive numeric value: $");
    cout << loanAmount << endl;
    annualInterestRate = getAnnualInterestRate();
    cout << annualInterestRate << endl;
    monthlyInterestRate = getMonthlyInterestRate(annualInterestRate);
    cout << monthlyInterestRate << endl;
    monthlyPayment = getMonthlyPayment();
    cout << monthlyPayment << endl;
    if (canLoanBePaidOff(loanAmount, monthlyInterestRate, monthlyPayment))
    {
      calculateLoan();
      displayPayments();
    }
    else
    {
      cout << "I reckon you can't pay off this loan with that payment." << endl;
    }
  }