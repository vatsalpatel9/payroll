#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void tellUser();

double regular(int &);

int main(){
  // size of arrays to hold employees
  const int SZ = 10;

  string fName[SZ], lName[SZ];

  double hours[SZ], rate[SZ];

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
               << "Regular" << setw(8) << " "
               << "Overtime" << setw(8) << " "
               << "Gross\n\n";
    for (int i = 0; i < arrSize; i++){
      outputFile << setw(19) << string(fName[i] + ' ' + lName[i])
                 << setw(13) << fixed << setprecision(2) << rate[i]
                 << hours[i] << endl;
    }
  }else{
    screenonly = true;
    cout << " output file did not open\n";
    cout << " output file will only be sent to the screen\n";
  }

  cout << left << "Name" << setw(15) << " "
             << "Hours" << setw(8) << " "
             << "Rate" << setw(8) << " "
             << "Regular" << setw(8) << " "
             << "Overtime" << setw(8) << " "
             << "Gross\n\n";
  for (int i = 0; i < arrSize; i++){
    cout << setw(19) << string(fName[i] + ' ' + lName[i])
         << setw(13) << fixed << setprecision(2) << rate[i]
         << hours[i] << endl;
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
  << "output is written to the screen. \n\n";
}

double regular(int &)
{
  int empCount;
  double grossPay;
  double hours, rate;
  if(hours <= 40)
      grossPay = hours * rate;
  
}
