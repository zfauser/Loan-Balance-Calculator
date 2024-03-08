#include <iomanip>
#include <iostream>
#include <limits>

#include "colors.h"
#include "tabulate.hpp" // Used tabulate in order to output a table. source: https://github.com/p-ranav/tabulate

using namespace std;

// Global variables
float loanAmount = 0;
float annualInterestRate = 0;
float monthlyInterestRate = 0;
float monthlyPayment = 0;
bool playAgain = true;
tabulate::Table paymentsTable;

bool badFloatCharacters(string inputFloat)
/*
  Args:
    inputFloat (string): The float that the user has inputted as a string
  Returns:
    bool: Returns true if the inputFloat contains an invalid character, and
  false if it does not
*/
{
  // For the length of the inputNumber, make sure each character is a number or a decimal
  for (int i = 0; i < inputFloat.length(); i++) {
    // if an invalid character is found, return true
    if (!isdigit(inputFloat[i]) && inputFloat[i] != '.') {
      return true;
    }
  }
  // if no invalid characters are found, return false
  return false;
}

bool checkDecimalPlaces(string inputFloat, bool checkTwoDecimalPlaces) 
/*
  Args:
    inputFloat (string): The float that the user has inputted as a string
    checkTwoDecimalPlaces (bool): A boolean that determins if the function should check for two decimal places
  Returns:
    bool: Returns true if the inputFloat contains more than two decimal places, and false if it does not
*/
{
  if (checkTwoDecimalPlaces) {
    int len = inputFloat.find_last_of('.');
    // if there is no decimal, return false
    if (len == -1) {
      return false;
    }
    // erase the string up to the decimal
    inputFloat.erase(0, len + 1);
    // if the length of the string after the decimal is greater than 2, return true
    int new_len = inputFloat.length();
    if (new_len > 2) {
      return true;
    } 
    // if the length of the string after the decimal is less than 2, return false
    else {
      return false;
    }
  } 
  // if the function should not check for two decimal places, return false
  else {
    return false;
  }
}

bool checkOneHundred(string inputFloat, bool check100) 
/*
  Args: 
    inputFloat (string): The float that the user has inputted as a string
    check100 (bool): A boolean that determins if the function should check if the input is greater than 100
  Returns:
    bool: Returns true if the inputFloat is greater than 100, and false if it is not
*/
{
  // if the function should check if the input is greater than 100
  if (check100) {
    // if the input is greater than 100, return true
    if (stof(inputFloat) > 100) {
      return true;
    } 
    // if the input is less than 100, return false
    else {
      return false;
    }
  } 
  // if the function should not check if the input is greater than 100, return false
  else {
    return false;
  }
}

float getValidFloat(string prompt, string errorMessage,
                    bool checkTwoDecimalPlaces, bool check100)
/*
  Args: 
    prompt (string): The prompt that the user will see when asked to input a number
    errorMessage (string): The error message that the user will see if they input an invalid number
    checkTwoDecimalPlaces (bool): A boolean that determins if the function should check for two decimal places
    check100 (bool): A boolean that determins if the function should check if the input is greater than 100
  Returns:
    outputFloat (float): The error trapped version of the float
*/
{
  string inputFloat = "0";
  // Ask the user to input a number
  cout << GREEN << prompt;    // Purposely did not reset color so that the users input is green
  cin >> inputFloat;

  // While the input is invalid, ask the user to input a number again
  while (cin.fail() || badFloatCharacters(inputFloat) || stof(inputFloat) < 0 ||
         checkDecimalPlaces(inputFloat, checkTwoDecimalPlaces) || checkOneHundred(inputFloat, check100)) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Display an error message
    cout << BOLD << RED << errorMessage;
    cin >> inputFloat;
    cout << RESET;
  }
  // Convert the inputNumber to an integer
  float outputFloat = stof(inputFloat);
  return outputFloat;
}

float getAnnualInterestRate() 
/*
  Returns:
    tempInterestRate (float): The annual interest rate that the user has inputted
*/
{
  float tempInterestRate = 0;
  // Ask the user to input their annual interest rate
  tempInterestRate = getValidFloat(
      "I reckon you should enter your annual interest rate (%): ",
      "Invalid input. Please enter a positive numeric value that is less than or equal to 100 (%): ", false, true);
  // convert to decimal
  return tempInterestRate / 100;
}

float getMonthlyInterestRate(float annualRate) 
/*
  Arg:
    annualRate (float): The annual interest rate that the user has inputted
*/
{
  // convert to monthly interest rate
  return (annualRate / 12);
}

bool canLoanBePaidOff(float principle, float monthlyInterest, float payment) 
/*
  Args:
    principle (float): The loan amount
    monthlyInterest (float): The monthly interest rate
    payment (float): The monthly payment
*/
{
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
  int years = month / 12;
  int months = month % 12;

  string result = "";

  if (years > 0) {
    // This determine if the year should be plural or not, it does this by using a ternary operator
    result += to_string(years) + (years > 1 ? " yrs. " : " yr. ");
  }

  if (months > 0) {
    // This determines if the month should be plural or not, and uses a ternary operator like the years if statement
    result += to_string(months) + (months > 1 ? " mths." : " mth.");
  }

  return result;
}

void displayPayments(int month, float principle, float payment, float interest,
                     float newPrinciple) {
  if (month == 1) {
    cout << RESET;
    paymentsTable.add_row({"Month/Year", "Previous Principle", "Payment", "Interest",
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
  cout << "I do declare your loan to be paid off after " + displayMonthOrYear(month) << endl;
}

bool askPlayAgain()
/*
  Returns:
    inputPlayAgain (bool): Returns true if the user wants to play again, and
  false if they do not
*/
{
  bool inputPlayAgain;
  string userAnswer;
  // Ask the user if they want to play again
  cout << GREEN << "Would you like to play again? (Y or N): " << RESET;
  cin >> userAnswer;
  // While the input is invalid, ask the user to input a different answer
  while (userAnswer != "Y" && userAnswer != "N" && userAnswer != "y" &&
         userAnswer != "n") {
    cout << BOLD << RED << "Invalid input. Please enter Y or N: " << RESET;
    cin >> userAnswer;
  }
  // If the user wants to play again, set inputPlayAgain to true, otherwise set
  // it to false
  if (userAnswer == "Y" || userAnswer == "y") {
    paymentsTable = tabulate::Table();
    cout << endl << endl;
    inputPlayAgain = true;
  } else {
    inputPlayAgain = false;
  }
  return inputPlayAgain;
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
                               true, false);
    annualInterestRate = getAnnualInterestRate();
    monthlyInterestRate = getMonthlyInterestRate(annualInterestRate);
    monthlyPayment = getValidFloat("I reckon you should enter your monthly payment: $",
                          "Invalid input. Please enter a positive numeric "
                          "value with two decimal places: $",
                          true, false);
    if (canLoanBePaidOff(loanAmount, monthlyInterestRate, monthlyPayment)) {
      calculateLoan(loanAmount, monthlyInterestRate, monthlyPayment);
    } else {
      cout << RED << BOLD << "I reckon you can't pay off this loan with that payment." << RESET << endl;
    }
    playAgain = askPlayAgain();
  }
}