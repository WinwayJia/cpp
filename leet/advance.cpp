#include <iostream>
#include <iterator>
#include <vector>

int main() 
{
  std::vector<int> v{ 3, 1, 4  };

  auto vi = v.begin();
  std::advance(vi, 2);
  std::cout << *vi << '\n';

  auto pv = std::prev(vi, 2);
  std::cout << *pv << '\n';


  std::cout << 1 << " " << *std::next(v.begin()) << std::endl;
  std::cout << 4 << " " << *std::prev(v.end()) << std::endl;
}
