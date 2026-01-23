/*
Fold expressions in C++
*/

#include <iostream>

// returns the sum of the args
template <typename... types>
auto fold1(types... args){
  return (args + ...);
}

// can get sum of squares
template <typename... types>
auto fold2(types... args){
  return ((args * args) + ...);
}

template <typename t>
void mylog(t item){
  std::cout << item << ", ";
}

// calls log for each item, then subtracts
template <typename... types>
void fold3(types... args){
  std::cout << "Logged values: ";
  // return static_cast<void>(mylog(args), ...); // if we believe comma overloaded
  return (mylog(args), ...); // folding over comma does not return anything,
}


// work we lambdas
template<typename... types>
void fold4(types... args){
  (
    [](auto& arg){
      std::cout << arg << ' ';
    }(args), ...
  );
  std::cout << "\n";
}

// apply lambda capture
template <typename... types>
void revisedFold4(types... args){
  (
    [&]{
      std::cout << args << ' ';
    }(), ...
  );
  std::cout << "\n";
}

// note the direciton of folds
// this is a left fold and subtraction starts from the front
template <typename... types>
int leftfold(types... args){
  return (... - args);
}

// subtraction starts from the right
template <typename... types>
int rightfold(types... args){
  return (args - ...);
}

// binary folds (the two operators used need to be the same)
template <typename... Types>
int BinaryLeftFold(Types... Args){
  return (0 - ... - Args);
}

template <typename... Types>
int BinaryRightFold(Types... Args){
  return (Args - ... - 0);
}

template <typename... Types>
void binFold2(Types... Args){
  (std::cout << ... << Args); // = ((std::cout << "Hello ") << "World") << "!!!";
}

int main(){
  std::cout << "sum of 1, 2, 3, 4, 5: " << fold1(1, 2, 3, 4, 5) << "\n";
  std::cout << "sum squares of 1, 2, 3, 4, 5: " << fold2(1, 2, 3, 4, 5) << "\n";
  fold3(1, 2, 3, 4, 5);
  std::cout << "\n";
  fold4("Hello", "World");
  revisedFold4("Hello", "World");
  std::cout << "(5-10)-20: " << leftfold(5, 10, 20) << "\n";
  std::cout << "5-(10-20): " << rightfold(5, 10, 20) << "\n";
  std::cout << "((0 - 5) - 10) - 20 = " << BinaryLeftFold(5, 10, 20) << "\n";
  std::cout << "5 - (10 - (20 - 0)) = " << BinaryRightFold(5, 10, 20) << "\n";
  binFold2("Hello", "World", "!!!");
  std::cout << "\n";
}

