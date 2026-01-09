/*
Introduction to std::mdspan
 */

 // multidimensional arrays: harder to get size, more performance overhead
 // prefer working in a single array

 // multidimensional [] opreator added in C++23
 // views that iteract with multidim array

 #include <iostream>
 #include <array>
 #include <vector>
 #include <mdspan>


 int main(){
  std::array Array{
    1, 2, 3,
    4, 5, 6
  };

  // first arg is ptr to where array begins, then a variable num of args for shape of multidim view
  std::mdspan Span{Array.data(), 2, 3}; // 2x3 span
  std::cout << "2D span size: " << sizeof(Span) << std::endl;
  std::cout << "Top Left: " << Span[0,0] << "\n";
  std::cout << "Top Bottom Right: " << Span[1,2] << "\n";

  std::cout << "Size: " << Span.size() << "\n";
  std::cout << "Rank: " << Span.rank() << "\n";
  std::cout << "\nGetting the size of dimensions:\n";
  std::cout << "Rows: " << Span.extent(0) << "\n";
  std::cout << "Cols: " << Span.extent(1) << "\n";

  std::cout << "Left Column: ";
  for (size_t i{0}; i < Span.extent(0); ++i)
    std::cout << Span[i, 0] << ", ";

  std::cout << "\nTop Row: ";
  for (size_t i{0}; i < Span.extent(1); ++i)
    std::cout << Span[0, i] << ", ";

  std::cout << "\nEverything: ";
    for (size_t i{0}; i < Span.extent(0); ++i)
      for (size_t j{0}; j < Span.extent(1); ++j)
        std::cout << Span[i, j] << ", ";
  
  std::cout << std::endl;

  // Getting more into the template parameters of std::mspan
  // takes in 4 parameters, the first 2: element type and extents type
  // static extent
  using Extents = std::extents<size_t, 2, 3>;  // size_t is index type
  std::mdspan<int, Extents> Span1{Array.data()};

  // if dim not known at compile time --> dynamic extents
  // ex. num cols not known
  using Extents2 = std::extents<size_t, 2, std::dynamic_extent>;
  std::mdspan<int, Extents2> Span2{Array.data(), 3}; // num cols passed into constructor at runtime
  
  // std::dextents used if all dim are dynamic, takes in num dim
  using Extents3 = std::dextents<size_t, 3>;
  std::mdspan<int, Extents3> Span3{Array.data(), 2, 2, 2};
  std::cout << "Dimensions of Span3: " << Span3.rank() << "\n";


}

  // g++ -std=c++23 ./multi_dim_spans.cpp -o run





