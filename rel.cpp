/*using namespace std;
#include <iostream>
#include <sstream>
#include <string>

int main() {

    int b,n,c;
    double r; 
    int i = 0;

    cin>>b >> n;
    cout<<"Budget: "<<b<<endl;
    cout<<"Number Steps: "<<n<<endl;
    
    int *cost = new int[n];
    double *rel = new double[n];

    for (std::string line; std::getline(std::cin, line);) {
        std::cout <<line<<endl;
        
        // there is an empty line coming here, not sure why. need to find elegant way to avoid it 
        if(line.length() == 0) {
            continue;
        }
        
        istringstream iss(line);
        iss >> c >> r;
        //cout << "cost: "<<c <<endl; 
        //cout << "rel: "<<r <<endl; 
        cost[i] = c;
        rel[i] = r;
        i = i+1; 
    }

      return 0;
}*/

 /*
Author - Navya Swetha Daggubati
CS 621 / Assignment 5
C++ program to find a maximum reliability given a fixed budget using iterative version.
*/

#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main() {
  int b, n, c_temp;
  double r_temp;
  int k = 0;
  int i, s;

  // read budget and number of machines
  cin >> b >> n;
  cout << "Budget: " << b << endl;
  cout << "Number Machines: " << n << endl;
  
  int cost[n];
  double r[n];
  
  // allocate memory on heap to avoid stack overflow / seg fault
  int **copies = new int * [n];
  for (i = 0; i<n; i++) {
    copies[i] = new int[b];
  }

  double **REL = new double * [n + 1]; 
  for (i = 0; i<n+1; i++) { 
    REL[i] = new double[b+1];
  } 

  // read cost and reliability input
  for (std::string line; std::getline(std::cin, line);) {
    //std::cout <<line<<endl;
    if (line.length() == 0) {
      continue;
    }

    istringstream iss(line);
    iss >> c_temp >> r_temp;
    cost[k] = c_temp;
    r[k] = r_temp;
    k = k + 1;
  }
  
  
  // sanity checks
  if (b == 0) {
    cout << "Please provide a valid budget >0. Exiting." << endl;
    exit(1);
  }

  if (n == 0) {
    cout << "Please provide a valid number of machines >0. Exiting." << endl;
    exit(1);
  }
  
  int base_cost =0;
  for (i=0;i <n; i++){
      base_cost = base_cost + cost[i];
  }
  if (base_cost > b) {
      cout << "budget should cover atleast one copy of all machines. please provide a valid budget. Exiting." << endl;
      exit(1);
  }
  

  // REL[i,b] is reliability of the system at step i, given budget b
  // initialize REL[i, b] = 1 when i =0
  for (s = 0; s <= b; s++) {
    REL[0][s] = 1.0;
  }

  // initialize REL[i,b] = 0 when b = 0
  for (i = 1; i <= n; i++) // init the 0 spent colum
  {
    REL[i][0] = 0;
  }

  for (i = 1; i <= n; i++) {
    for (s = 1; s <= b; s++) {
      int max_machines = s / cost[i - 1]; // max number of machines
      double max_rel = 0;
      copies[i - 1][s - 1] = 0;
      
      // find max reliability from 1 and max_machines
      for (int mi = 1; mi <= max_machines; mi++) {
        double sp = 1.0 - powf((1.0 - r[i - 1]), mi); // rel of the mi step
        int balance_budget = s - mi * cost[i - 1];
        double agg_rel = REL[i - 1][balance_budget] * sp; // rel so far
        if (max_rel < agg_rel) {
          max_rel = agg_rel;
          copies[i - 1][s - 1] = mi; // number of copies at this level
        }
      }
      REL[i][s] = max_rel;
    }
   }

  // Print the number of extra machines best employed for each step 
  int answer[n];
  int remain = b - 1;
  
  cout << "\nIterated Version: " << endl;
  cout << "Maximum reliability: " << REL[n][b] << endl;
  
  for (i = n - 1; i >= 0; i--) // get the result in reverse order  
  {
    answer[i] = copies[i][remain];
    int c = copies[i][remain] * cost[i]; 
    remain = remain - c; 
    cout << answer[i] << " copies of machine " << i + 1 << " of cost " << cost[i] << endl;
  }

}






 

    


