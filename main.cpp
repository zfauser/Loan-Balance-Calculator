#include <iomanip>
#include <iostream>
#include <limits>

#include "colors.h"
#include "tabulate.hpp" // Used tabulate in order to output a table. source: https://github.com/p-ranav/tabulate

using namespace std;

float loanAmount = 0;
float annualInterestRate = 0;
float monthlyInterestRate = 0;
float monthlyPayment = 0;
bool playAgain = true;
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
  for (int i = 0; i < inputFloat.length(); i++) {
    if (!isdigit(inputFloat[i]) && inputFloat[i] != '.') {
      return true;
    }
  }
  return false;
}

bool checkDecimalPlaces(string inputFloat, bool checkTwoDecimalPlaces) {
  if (checkTwoDecimalPlaces) {
    int len = inputFloat.find_last_of('.');
    // if there is no decimal, return false
    if (len == -1) {
      return false;
    }
    inputFloat.erase(0, len + 1);
    int new_len = inputFloat.length();
    if (new_len > 2) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

float getValidFloat(string prompt, string errorMessage,
                    bool checkTwoDecimalPlaces) {
  string inputFloat = "0";
  // Ask the user to input a number
  cout << GREEN << prompt;
  cin >> inputFloat;

  // While the input is invalid, ask the user to input a number again
  while (cin.fail() || badFloatCharacters(inputFloat) || stof(inputFloat) < 0 ||
         checkDecimalPlaces(inputFloat, checkTwoDecimalPlaces)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << BOLD << RED << errorMessage;
    cin >> inputFloat;
  }
  // Convert the inputNumber to an integer
  float outputFloat = stof(inputFloat);
  return outputFloat;
}

float getAnnualInterestRate() {
  float tempInterestRate = 0;
  tempInterestRate = getValidFloat(
      "I reckon you should enter your annual interest rate (%): ",
      "Invalid input. Please enter a positive numeric value (%): ", false);
  // convert to decimal
  return tempInterestRate / 100;
}

float getMonthlyInterestRate(float annualRate) { return (annualRate / 12); }

float getMonthlyPayment() {
  float payment = 0;
  payment = getValidFloat("I reckon you should enter your monthly payment: $",
                          "Invalid input. Please enter a positive numeric "
                          "value with two decimal places: $",
                          true);
  return payment;
}

bool canLoanBePaidOff(float principle, float monthlyInterest, float payment) {
  if (payment <= principle * monthlyInterest) {
    return false;
  } else {
    return true;
  }
}

string FtoS(float inputFloat) {
  // convert to string 2 decimal places
  ostringstream oss;
  oss << fixed << setprecision(2)
      << inputFloat; // Use std::ostringstream to format the float
  return oss.str();  // Return the formatted string
}

string displayMonthOrYear(int month) {
  // if month is divisible by 12, return year
  if (month % 12 == 0) {
    if (month / 12 == 1) {
      return to_string(month / 12) + " year";
    } else {
      return to_string(month / 12) + " years";
    }
  } else {
    if (month == 1) {
      return to_string(month) + " month";
    } else {
      return to_string(month) + " months";
    }
  }
}

void displayPayments(int month, float principle, float payment, float interest,
                     float newPrinciple) {
  if (month == 1) {
    cout << RESET;
    paymentsTable.add_row({"Month", "Previous Principle", "Payment", "Interest",
                           "New Principle"});
    paymentsTable.format()
        .font_align(tabulate::FontAlign::center)
        .border_right("|")
        .border_left("")
        .border_top("-")
        .border_bottom("-")
        .corner("-");

    for (int i = 0; i < 5; i++) {
      paymentsTable[0][i].format().font_style({tabulate::FontStyle::bold});
    }
  }
  paymentsTable.add_row({displayMonthOrYear(month), "$" + FtoS(principle),
                         "$" + FtoS(payment), "$" + FtoS(interest),
                         "$" + FtoS(newPrinciple)});
}

void calculateLoan(float principle, float monthlyInterest, float payment) {
  int month = 0;
  float newPrinciple = 0;
  while (principle > 0) {
    month++;
    float interest =
        (principle * monthlyInterest) - (payment * monthlyInterest);
    newPrinciple = principle - payment + interest;
    if (newPrinciple < 0) {
      payment = principle;
      interest = 0;
      newPrinciple = 0;
    }
    displayPayments(month, principle, payment, interest, newPrinciple);
    principle = newPrinciple;
  }
  paymentsTable.format();
  cout << paymentsTable << endl;
}

bool askPlayAgain() {
  char playAgain = '0';
  cout << GREEN << "Would you like to calculate another loan? (y/n): ";
  cin >> playAgain;
  playAgain = tolower(playAgain);
  while (playAgain != 'y' && playAgain != 'n') {
    cout << "Invalid input. Please enter 'y' or 'n': ";
    cin >> playAgain;
  }
  if (playAgain == 'y') {
    paymentsTable = tabulate::Table();
    cout << endl << endl;
    return true;
  } else {
    return false;
  }
}

int main() {
  cout << YELLOW
       << "Howdy there, partner! I do declare that this loan calculator is the "
          "best in the west! Yeehaw!"
       << RESET << endl;
  while (playAgain) {
    loanAmount = getValidFloat("I reckon you should enter your loan amount: $",
                               "Invalid input. Please enter a positive numeric "
                               "value with two decimal places: $",
                               true);
    annualInterestRate = getAnnualInterestRate();
    monthlyInterestRate = getMonthlyInterestRate(annualInterestRate);
    monthlyPayment = getMonthlyPayment();
    if (canLoanBePaidOff(loanAmount, monthlyInterestRate, monthlyPayment)) {
      calculateLoan(loanAmount, monthlyInterestRate, monthlyPayment);
    } else {
      cout << "I reckon you can't pay off this loan with that payment." << endl;
    }
    playAgain = askPlayAgain();
  }
}