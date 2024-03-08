// Name: Zach Fauser
// Date: March 8th, 2024
// Purpose: This file is used to declare the functions used in the outputs.cpp file so that the main file can use them.

#include <iostream>

// Used tabulate in order to output a table. source: https://github.com/p-ranav/tabulate
#include "tabulate.hpp"

#ifndef OUTPUTS_H
#define OUTPUTS_H

using namespace std;

extern tabulate::Table paymentsTable;
string FtoS(float inputFloat);
string displayMonthOrYear(int month);
void displayPayments(int month, float principle, float payment, float interest, float newPrinciple);
void calculateLoan(float principle, float monthlyInterest, float payment);

#endif
