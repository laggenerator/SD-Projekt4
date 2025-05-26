#include "testy.hh"
#include <iostream>

int main(){
  std::cout << "Test wierzcholkowy rozpoczety!" << std::endl;
  testWierzcholkowy();
  std::cout << "Test wierzcholkowy zakonczony!" << std::endl;

  std::cout << "Test krawedziowy rozpoczety!" << std::endl;
  testKrawedziowy();
  std::cout << "Test krawedziowy zakonczony!" << std::endl;

  std::cout << "Test z ujemnymi krawedziami rozpoczety!" << std::endl;
  testUjemnychKrawedzi();
  std::cout << "Test z ujemnymi krawedziami zakonczony!" << std::endl;
}
