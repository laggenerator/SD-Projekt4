#include <iostream>
#include <limits.h>
#include <vector>
#include "algorytmy.hh"
#include "struktury/adjacency_list.hh"
#include "struktury/edge_list.hh"
#include "struktury/prique.hh"
#include "struktury/graf.hh"
#include "generator.hh"

//wyswietla
void sciezka(int skad, int dokad, int* odleglosci, int* poprzednicy) {
  if(odleglosci[dokad] == INT_MAX) {
    std::cout << "Nie ma sciezki z " << skad << " do " << dokad << "!" << std::endl;
    return;
  }
  std::cout << "Wyswietlana w nawiasach waga do suma wag od punktu " << skad << " do danego punktu\n";
  std::cout << "Sciezka z: " << skad << " do: " << dokad  << std::endl;
  int i = dokad;
  int razemwaga = odleglosci[i];
  std::cout << dokad << " (" << odleglosci[i] << ")";
  while(i != skad) {
    i = poprzednicy[i];
    std::cout << " <- " << i << " (" << odleglosci[i] << ")";
    razemwaga += odleglosci[i];
  }
  std::cout << std::endl;
  // std::cout << "\nSuma wag w sciezce: " << razemwaga << std::endl;
}

int main() {
  // IGraph* graf = new EdgeList(6);
  // graf->add_edge(0, 1, 7);
  // graf->add_edge(0, 2, 9);
  // graf->add_edge(0, 5, 14);
  // graf->add_edge(1, 2, 10);
  // graf->add_edge(1, 3, 15);
  // graf->add_edge(2, 3, 11);
  // graf->add_edge(2, 5, 2);
  // graf->add_edge(3, 4, 6);
  // graf->add_edge(4, 5, 9);

  int wierzcholkow = 3;
  int krawedzi = wierzcholkow * (wierzcholkow - 1) / 2; // Graf pełny
  krawedzi = wierzcholkow - 1; // Drzewo
  IGraph* graf = new AdjacencyMatrix(wierzcholkow);
  std::vector<std::tuple<int, int, int>> edging;
  edging = generujGraf(wierzcholkow, krawedzi, 10, 1000);

  int i = 0;
  for (const auto& [u, v, w] : edging) {
    std::cout << "Dodaje krawędź #" << i++ << std::endl;
    std::cout << "Z: " << u << " do: " << v << " waga: " << w << std::endl;
    graf->add_edge(u, v, w);
  }

  int wielkosc[wierzcholkow] = {0};
  int poprzednicy[wierzcholkow] = {0};
  Dijkstra(graf, 0, poprzednicy, wielkosc);
  std::cout << "Ścieżki otrzymane z Dijkstry: " << std::endl;
  std::cout << "poprzednicy:\n";
  for(int i = 0; i < wierzcholkow - 1; ++i) {
    std::cout << poprzednicy[i] << " "; 
  }
  std::cout << poprzednicy[wierzcholkow - 1] << std::endl;
  std::cout << "dlugosci sciezek:\n";
  for(int i = 0; i < wierzcholkow - 1; ++i) {
    std::cout << wielkosc[i] << " "; 
  }
  std::cout << wielkosc[wierzcholkow - 1] << std::endl;
  
  BellmanFord(graf, 0, poprzednicy, wielkosc);
  std::cout << "Ścieżki otrzymane z Bellmana Forda: " << std::endl;
  std::cout << "poprzednicy:\n";
  for(int i = 0; i < wierzcholkow - 1; ++i) {
    std::cout << poprzednicy[i] << " "; 
  }
  std::cout << poprzednicy[wierzcholkow - 1] << std::endl;
  std::cout << "dlugosci sciezek:\n";
    for(int i = 0; i < wierzcholkow - 1; ++i) {
      std::cout << wielkosc[i] << " "; 
    }
    std::cout << wielkosc[wierzcholkow - 1] << std::endl;

    sciezka(0, 2, wielkosc, poprzednicy);
  
  return 0;
}
