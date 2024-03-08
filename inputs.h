// Name: Zach Fauser
// Date: March 8th, 2024
// Purpose: This file is used to declare the functions used in the inputs.cpp
// file so that the main file can use them.

#include "tabulate.hpp"
#include <iostream>

#ifndef INPUTS_H
#define INPUTS_H

using namespace std;

bool badFloatCharacters(string inputFloat);
bool checkDecimalPlaces(string inputFloat, bool checkTwoDecimalPlaces);
bool checkOneHundred(string inputFloat, bool check100);
float getValidFloat(string prompt, string errorMessage,
                    bool checkTwoDecimalPlaces, bool check100);
float getAnnualInterestRate();
float getMonthlyInterestRate(float annualRate);
bool canLoanBePaidOff(float principle, float monthlyInterest, float payment);
bool askPlayAgain(tabulate::Table &paymentsTable);

#endif
