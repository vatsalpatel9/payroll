#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void tellUser();
double getGrossPay(double hoursWorked, double rateOfPay);
double getTaxes(double grossPay);
double getNetPay(double grossPay, double tax);

int main(){
  // size of arrays to hold employees
  const int SZ = 10;

  string fName[SZ], lName[SZ];

  double hours[SZ], rate[SZ], grossPay[SZ], tax[SZ], netPay[SZ];

  int arrSize = sizeof(fName) / sizeof(fName[0]);
  cout << arrSize << endl;
  bool screenonly = false;

  ifstream inputFile;
  ofstream outputFile;

  //read input from file employees.txt
  tellUser();
  inputFile.open("hourlyInput.txt");
  if (inputFile.is_open())
  {
    int i = 0;
    while (!inputFile.eof()){
      inputFile >> fName[i] >> lName[i] >> rate[i] >> hours[i];
      i++;
    }
  } else {
    cout << "Error! opening file hourlyInput.txt\n\n";
    cout << "end of program";
  }
     
    
  outputFile.open("output.txt");
  if (outputFile.is_open()){
    outputFile << left << "Name" << setw(15) << " "
         << "Hours" << setw(8) << " "
         << "Rate" << setw(8) << " "
         << "Gross" << setw(8) << " "
         << "Taxes" << setw(8) << " "
         << "Net\n\n";
    for (int i = 0; i < arrSize; i++){
      grossPay[i] = getGrossPay(hours[i], rate[i]);
      tax[i] = getTaxes(grossPay[i]);
      netPay[i] = getNetPay(grossPay[i], tax[i]);
    }

    for (int i = 0; i < arrSize; i++){
      outputFile << setw(19) << string(fName[i] + ' ' + lName[i])
                 << setw(13) << fixed << setprecision(2) << rate[i]
                 << setw(12) << hours[i]
                 << setw(13) << grossPay[i]
                 << setw(12) << tax[i]
                 << netPay[i] << endl;
    }
  }else{
    screenonly = true;
    cout << " output file did not open\n";
    cout << " output file will only be sent to the screen\n";
  }

  cout << left << "Name" << setw(15) << " "
             << "Hours" << setw(8) << " "
             << "Rate" << setw(8) << " "
             << "Gross" << setw(8) << " "
             << "Taxes" << setw(8) << " "
             << "Net\n\n";
  for (int i = 0; i < arrSize; i++){
    cout << setw(19) << string(fName[i] + ' ' + lName[i])
         << setw(13) << fixed << setprecision(2) << rate[i]
         << setw(12) << hours[i]
         << setw(13) << grossPay[i]
         << setw(12) << tax[i]
         << netPay[i] << endl;
  }

    inputFile.close();
    cout << "\nInput file closed\n\n";
    if (!screenonly)
      outputFile.close(); 
    return 0;
}
/*
 *function
 *
 */
void tellUser()
{
  cout << "\nThis program reads a file called hourlyInput.txt,\n"<< "and it calculates the paycheck.\n"
  << "output is written to the screen. \n" 
  << "----------------------------------------------------------------------------------------------\n";
}

double getGrossPay(double hoursWorked, double rateOfPay){
  return hoursWorked * rateOfPay;
}

double getTaxes(double grossPay){
  const double fedralTax = .09;
  const double stateTax = .05;
  const double ficaTax = .062;
  return (grossPay * fedralTax) + (grossPay * stateTax) + (grossPay * ficaTax);
}

double getNetPay(double grossPay, double tax){
  return grossPay - tax;
}