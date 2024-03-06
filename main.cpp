#include <iostream>

using namespace std;

float loanAmount = 0;
float annualInterestRate = 0;
float monthlyInterestRate = 0;
int month = 0;

float getLoanAmount() {}

int getLoanTerm() {}

float getAnnualInterestRate() {}

float getMonthlyInterestRate(float annualRate) {}

float getMonthlyPayment() {}

bool canLoanBePaidOff(int amount, float monthlyRate) {}

void calculateLoan() {}

void displayPayments() {}

int main() {
  cout << "Howdy there, partner! I do declare that this loan calculator is the best in the west! Yeehaw!";
  cout << "I reckon you should enter your loan amount: ";
  getLoanAmount();
  cout << "I reckon you should enter your annual interest rate: ";
  getAnnualInterestRate();
  getMonthlyInterestRate(annualInterestRate);
  cout << "I reckon you should enter your monthly payment: ";
  getMonthlyPayment();
  if (canLoanBePaidOff(loanAmount, monthlyInterestRate)) {
    calculateLoan();
    displayPayments();
  } else {
    cout << "I reckon you can't pay off this loan with that payment.";
  }
}