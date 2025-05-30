#include "testy.hh"
#include <iostream>
#include <ctime>

int main(){
  time_t timestamp;
  time(&timestamp);
  std::cout << "Porównanie reprezentacji rozpoczete!" << std::endl;
  std::cout << "Test wierzcholkowy rozpoczety! " << ctime(&timestamp) << std::endl;
  testWierzcholkowy();
  time(&timestamp);
  std::cout << "Test wierzcholkowy zakonczony! " << ctime(&timestamp) << std::endl;

  std::cout << "Test krawedziowy rozpoczety! "  << ctime(&timestamp) << std::endl;
  testKrawedziowy();
  time(&timestamp);
  std::cout << "Test krawedziowy zakonczony! "  << ctime(&timestamp) << std::endl;

  std::cout << "Test z ujemnymi krawedziami rozpoczety! " << ctime(&timestamp) << std::endl;
  testUjemnychKrawedzi();
  time(&timestamp);
  std::cout << "Test z ujemnymi krawedziami zakonczony! " << ctime(&timestamp) << std::endl;
  std::cout << "Porównanie reprezentacji zakoczone!" << std::endl;


  std::cout << "Porównanie algorytmow rozpoczete!" << std::endl;

  std::cout << "Test wierzcholkowy rozpoczety! " << ctime(&timestamp) << std::endl;
  testAlgorytmuWierzcholki();
  time(&timestamp);
  std::cout << "Test wierzcholkowy zakonczony! " << ctime(&timestamp) << std::endl;

  std::cout << "Test krawedziowy rozpoczety! " << ctime(&timestamp) << std::endl;
  testAlgorytmuKrawedzie();
  time(&timestamp);
  std::cout << "Test krawedziowy zakonczony! " << ctime(&timestamp) << std::endl;

  std::cout << "Porównanie algorytmow zakoczone!" << std::endl;
}
