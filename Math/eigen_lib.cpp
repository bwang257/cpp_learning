/*
Exploration of the Eigen Library (template library to linear algebra)

Compile with (macOS with homebrew):
g++ -std=c++17 -O2 -I/opt/homebrew/include/eigen3 eigen_lib.cpp -o run
*/

#include <Eigen/Dense>
#include <iostream>
#include <iomanip> // formatting for I/O streams
#include <string>

using namespace Eigen;

// print vector as a probability distribution nicely
void printDist(const VectorXd& v, const std::string& label = "π") {
    std::cout << label << " = [ ";
    for (int i = 0; i < v.size(); ++i)
        std::cout << std::fixed << std::setprecision(6) << v(i) << (i+1 < v.size() ? ",  " : "");
    std::cout << " ]\n\n";
}

// Application of topics learned in Stochastic Processes
// Transition matrix example
void transition_matrix_ex(){

  // We'll use a 3-state weather chain:
  //   States: 0=Sunny, 1=Cloudy, 2=Rainy
  //
  //      From\To    Sunny  Cloudy  Rainy
  //      Sunny       0.7    0.2    0.1
  //      Cloudy      0.3    0.4    0.3
  //      Rainy       0.2    0.3    0.5

  MatrixXd P(3,3);
  P << 0.7, 0.2, 0.1,
       0.3, 0.4, 0.3,
       0.2, 0.3, 0.5;

  std::cout << "\nRow-stochastic transition matrix P:\n" << P << "\n\n";
  std::cout << "Row sums:\n" << P.rowwise().sum().transpose() << "\n\n";
  std::cout << "Col sums:\n" << P.colwise().sum() << "\n\n"; // check if doubly stochastic

  // access specific rows + cols
  std::cout << "P(Sunny -> ?) = " << P.row(0) << "\n"; 
  std::cout << "P(? -> Rainy) = " << P.col(2).transpose() << "\n\n";

  // multiply an initial distribution by P repeatedly
  RowVectorXd pi = RowVectorXd::Zero(3);
  pi(0) = 1.0; // start sunny

  std::cout << std::fixed << std::setprecision(4);
  std::cout << "n= 0: " << pi << "\n";
  for (int n : {1, 2, 5, 10, 20, 50}){
    MatrixXd Pn = MatrixXd::Identity(3,3);
    for (int i{}; i < n; ++i) Pn = Pn * P;
    std::cout << "n=" << std::setw(2) << n << ": " << (pi * Pn) << "\n";
  }

  // application of power method to find limiting distribution
  // --> this matrix clearly irreducible and aperiodic --> primitive
  std::cout << "\n===Power Method===\n";

  RowVectorXd dist = RowVectorXd::Ones(3) / 3.0; // start with uniform dist
  std::cout << "Starting from uniform: " << dist << "\n\n";
  double tol = 1e-10;
  int max_iter = 100;

  for (int iter{}; iter < max_iter; ++iter){
    RowVectorXd new_dist = dist * P;
    double change = (new_dist - dist).norm(); // L2 norm of change
    dist = new_dist; 

    if (iter < 5 || iter % 20 == 0){
      std::cout << "iter " << std::setw(3) << iter 
                << ": " << dist << " (Δ=" << std::scientific << change << ")\n" << std::fixed;
    }
    if (change < tol){
      std::cout << "\nConverged at iteration " << iter << "\n";
      break;
    }
  }

  std::cout << "\nStationary distribution (power method):\n";
  printDist(dist.transpose());

  // verify πP = π
  std::cout << "Verification:\nsum: " << std::setprecision(4) << dist.sum() << "\n";
  RowVectorXd residual = dist * P - dist;
  std::cout << "sum = " << std::setprecision(4) << dist.sum() << "\n";
  std::cout << "||πP - π|| = " << residual.norm() << "\n\n";
}


int main(){
  transition_matrix_ex();
}