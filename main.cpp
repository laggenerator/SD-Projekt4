#include <iostream>
#include <limits.h>
#include <vector>
#include "algorytmy.hh"
#include "struktury/adjacency_list.hh"
#include "struktury/edge_list.hh"
#include "struktury/prique.hh"
#include "struktury/graf.hh"

//wyswietla
void sciezka(int skad, int dokad, int* odleglosci, int* poprzednicy) {
  if(odleglosci[dokad] == INT_MAX) {
    std::cout << "Nie ma sciezki z " << skad << " do " << dokad << "!" << std::endl;
    return;
  }
  std::cout << "Sciezka z: " << skad << " do: " << dokad  << std::endl;
  int i = dokad;
  int razemwaga = odleglosci[i];
  std::cout << dokad << " (" << odleglosci[i] << ")";
  while(i != skad) {
    i = poprzednicy[i];
    std::cout << " <- " << i << " (" << odleglosci[i] << ")";
    razemwaga += odleglosci[i];
  }
  std::cout << "\nSuma wag w sciezce: " << razemwaga << std::endl;
}

int main() {
  IGraph* graf = new AdjacencyList(6);
  graf->add_edge(0, 1, 7);
  graf->add_edge(0, 2, 9);
  graf->add_edge(0, 5, 14);
  graf->add_edge(1, 2, 10);
  graf->add_edge(1, 3, 15);
  graf->add_edge(2, 3, 11);
  graf->add_edge(2, 5, 2);
  graf->add_edge(3, 4, 6);
  graf->add_edge(4, 5, 9);

  int wielkosc[6];
  int poprzednicy[6];
  Dijkstra(graf, 0, wielkosc, poprzednicy);
  std::cout << "Ścieżki otrzymane z Dijkstry: " << std::endl;
  std::cout << "dlugosci sciezek:\n";
  for(int i = 0; i < 5; ++i) {
    std::cout << wielkosc[i] << " "; 
  }
  std::cout << wielkosc[5] << std::endl;
  std::cout << "poprzednicy:\n";
  for(int i = 0; i < 5; ++i) {
    std::cout << poprzednicy[i] << " "; 
  }
  std::cout << poprzednicy[5] << std::endl;
  
  BellmanFord(graf, 0, wielkosc, poprzednicy);
  std::cout << "Ścieżki otrzymane z Bellmana Forda: " << std::endl;
    std::cout << "dlugosci sciezek:\n";
  for(int i = 0; i < 5; ++i) {
    std::cout << wielkosc[i] << " "; 
  }
  std::cout << wielkosc[5] << std::endl;
  std::cout << "poprzednicy:\n";
  for(int i = 0; i < 5; ++i) {
    std::cout << poprzednicy[i] << " "; 
  }
  std::cout << poprzednicy[5] << std::endl;
  
  return 0;
}
