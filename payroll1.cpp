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
  int choice;

  string fName[SZ], lName[SZ];

  double hours[SZ], rate[SZ], grossPay[SZ], tax[SZ], netPay[SZ];

  int arrSize = sizeof(fName) / sizeof(fName[0]);
  bool screenonly = false;
  bool programActive = true;

  ifstream inputFile;
  ofstream outputFile;

  inputFile.open("hourlyInput.txt");
  if (inputFile.is_open()){
    int i = 0;
    while (!inputFile.eof()){
      inputFile >> fName[i] >> lName[i] >> rate[i] >> hours[i];
      i++;
    }
  }else{
    cout << "Error! opening file hourlyInput.txt\n\n";
    cout << "end of program";
  }

  for (int i = 0; i < arrSize; i++){
    grossPay[i] = getGrossPay(hours[i], rate[i]);
    tax[i] = getTaxes(grossPay[i]);
    netPay[i] = getNetPay(grossPay[i], tax[i]);
  }

  inputFile.close();
  cout << "\nInput file closed\n\n";

  while(programActive){
    cout << "\n1. Run payroll report\n"
        << "2. View payroll statistics\n"
        << "3. View overtime employee\n"
        << "4. Exit\n\n";
    cin >> choice;
    switch(choice){
      case 1:
      {
        outputFile.open("output.txt");
        if (outputFile.is_open()){
          outputFile << left << "Name" << setw(15) << " "
                     << "Hours" << setw(8) << " "
                     << "Rate" << setw(8) << " "
                     << "Gross" << setw(8) << " "
                     << "Taxes" << setw(8) << " "
                     << "Net\n\n";
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

        cout << "-------------------------------------------------------------\n";
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
        cout << "-------------------------------------------------------------\n";
        break;
      }
      case 2:
      {
        double totalGross, totalTax, totalNet;
        for(int i = 0; i < arrSize; i++){
          totalGross += grossPay[i];
          totalTax += tax[i];
          totalNet += netPay[i];
        }
        cout << "--------------------------\n";
        cout << "Weekly Payroll Statistic\n";
        cout << "Total Gross Pay: " << fixed << setprecision(2) << totalGross << endl;
        cout << "Total Tax:       " << fixed << setprecision(2) << totalTax << endl;
        cout << "Total Net Pay:   " << fixed << setprecision(2) << totalNet << endl;
        cout << "--------------------------\n"; 
        break;
      }
      case 3:
      {
        cout << "--------------------------\n";
        cout << "Overtime Report\n";
        for(int i = 0; i < arrSize; i++){
          if(hours[i] > 40){
            cout << string(fName[i] + ' ' + lName[i])
                 << setw(13) << fixed << setprecision(0) << hours[i] << " hours\n";
          }
        }
        cout << "--------------------------\n";
        break;
      }
      case 4:
        programActive = false;
        break;

      default:
        cout << "Not a Valid Choice. \n";
        cout << "Choose again.\n";
        cin >> choice;
        break;
    }
  }
  
    if (!screenonly)
      outputFile.close(); 
    return 0;
}
/*
 *function
 *
 */
void tellUser(){
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