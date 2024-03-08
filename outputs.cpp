/*
  Name: Zach Fauser
  Date: March 8th, 2024
  Purpose: This file contains the functions that output the results of the
  program
*/

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

// Include the outputs.h file so that the functions can be used in the main.cpp
// file
#include "outputs.h"

// Include the colors.h file so that the colors can be used in this program
#include "colors.h"

// Used tabulate in order to output a table. source:
// https://github.com/p-ranav/tabulate
#include "tabulate.hpp"

// Create a variable that will be used to output the payments table
tabulate::Table paymentsTable;

string FtoS(float inputFloat)
/*
  Args:
    inputFloat (float): The float that the user has inputted
  Returns:
    convertedFloat.str() (string): The float that has been converted to a string
  Sources:
      https://stackoverflow.com/questions/14851232/formatting-double-to-string-with-ostringstream
      https://stackoverflow.com/questions/3748749/rounding-off-floats-with-ostringstream
*/
{
  ostringstream convertedFloat;
  // Convert the float to a string with two decimal places
  convertedFloat << fixed << setprecision(2) << inputFloat;
  return convertedFloat.str();
}

string displayMonthOrYear(int month)
/*
  Args:
    month (int): The month that the user has inputted
  Returns:
    result (string): The month and year that the user has inputted
*/
{
  int years = month / 12;
  int months = month % 12;

  string result = "";

  // If the years are greater than 0, add the years to the result
  if (years > 0) {
    // This determine if the year should be plural or not, it does this by using
    // a ternary operator
    result += to_string(years) + (years > 1 ? " yrs. " : " yr. ");
  }

  // If the months are greater than 0, add the months to the result
  if (months > 0) {
    // This determines if the month should be plural or not, and uses a ternary
    // operator like the years if statement
    result += to_string(months) + (months > 1 ? " mths." : " mth.");
  }

  return result;
}

void displayPayments(int month, float principle, float payment, float interest,
                     float newPrinciple)
/*
  Args:
    month (int): The month that the user has inputted
    principle (float): The loan amount
    payment (float): The monthly payment
    interest (float): The interest
    newPrinciple (float): The new loan amount
  Purpose:
    Adds all of the values to the paymentsTable which is used to show the user
  the payments they must make
*/
{
  // If the month is 1, define the tables properties
  if (month == 1) {
    cout << RESET;
    paymentsTable.add_row({"Month/Year", "Previous Principle", "Payment",
                           "Interest", "New Principle"});
    // Center the text and add borders to the table
    paymentsTable.format()
        .font_align(tabulate::FontAlign::center)
        .border_right("|")
        .border_left("")
        .border_top("-")
        .border_bottom("-")
        .corner("-");
    // Make the first row bold
    for (int i = 0; i < 5; i++) {
      paymentsTable[0][i].format().font_style({tabulate::FontStyle::bold});
    }
  }
  // Add the row with appropriate values to the table
  paymentsTable.add_row({displayMonthOrYear(month), "$" + FtoS(principle),
                         "$" + FtoS(payment), "$" + FtoS(interest),
                         "$" + FtoS(newPrinciple)});
}

void calculateLoan(float principle, float monthlyInterest, float payment)
/*
  Args:
    principle (float): The loan amount
    monthlyInterest (float): The monthly interest rate
    payment (float): The monthly payment
  Outputs:
    paymentsTable: The table that shows the user the payments they must make
    The amount of years/months it will take to pay off the loan
*/
{
  int month = 0;
  float newPrinciple = 0;
  float totalInterest = 0;
  float originalPrinciple = principle;
  // while the principle is greater than 0, calculate the interest and new
  // principle
  while (principle > 0) {
    month++;
    // Calculate the interest and new principle
    float interest =
        (principle * monthlyInterest) - (payment * monthlyInterest);
    newPrinciple = principle - payment + interest;
    // If the new principle is less than 0, set the payment to the principle and
    // the interest to 0
    if (newPrinciple < 0) {
      payment = principle;
      interest = 0;
      newPrinciple = 0;
    }
    // Add the interest to the total interest
    totalInterest += interest;
    // Add the desired values to the paymentsTable
    displayPayments(month, principle, payment, interest, newPrinciple);
    // Set the principle to the new principle
    principle = newPrinciple;
  }
  // Calculate the users total payment
  float totalPayment = totalInterest + originalPrinciple;
  // Output the paymentsTable
  cout << paymentsTable << endl;
  // Output the amount of interest and principle that the user has paid
  cout << "It cost you "
       << "$" + FtoS(totalInterest)
       << " in interest and $" + FtoS(originalPrinciple) << " in principle"
       << endl;
  cout << "In total, you paid $" + FtoS(totalPayment) << endl;
  // Output the amount of months/years it will take to pay off the loan
  cout << "I do declare your loan to be paid off after " +
              displayMonthOrYear(month)
       << endl;
}