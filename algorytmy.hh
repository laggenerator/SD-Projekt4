#ifndef ALGORYTMY_HH
#define ALGORYTMY_HH

#include <limits.h>
#include <stdint.h>
#include <iostream>
#include "struktury/adjacency_list.hh"
#include "struktury/prique.hh"
#include "struktury/adjacency_matrix.hh"

// Zamieniłem funkcje na boole, żeby wiedzieć czy sciezka sie udala, głównie dla bellmana przydatne żeby testy wiedziały że jest ujemny cykl

// Dla listy sąsiedztwa
bool Dijkstra(const IGraph* graf, size_t skad, int* poprzednik, int* odleglosc) {
  const size_t size = graf->vertex_count();
  if(skad >= size) {
    std::cerr << "Nie wyznaczę drogi do nieistniejącego węzła!" << std::endl;
    return false;
  }

  Prique kolejka;
  for(size_t i = 0; i < size; i++) {
    poprzednik[i] = -1;
    odleglosc[i] = INT_MAX;
    if(i == skad)
      odleglosc[i] = 0;
    kolejka.insert(Pair(odleglosc[i], i));
  }

  while(kolejka.size() != 0) {
    //relaksacja sasiadow najblizszego
    Pair u = kolejka.extract_min(); //najblizszy
    List<Pair> sasiedzi;
    graf->neighbors(u.get_val(), sasiedzi);

    for(size_t i = 0; i < sasiedzi.get_size(); ++i) { //dla kazdego sasiada
      if (odleglosc[u.get_val()] == INT_MAX) continue;  //nie ma sensu relaksować, ponadto byłby overflow w nowa_odleglosc
      Pair v = sasiedzi.at_position(i)->value();
      int nowa_odleglosc = odleglosc[u.get_val()] + v.get_key();
  
      //nowa droga jest lepsza niz aktualnie zapisana -- zapisujemy
      if(nowa_odleglosc < odleglosc[v.get_val()]) { 
        odleglosc[v.get_val()] = nowa_odleglosc;
        poprzednik[v.get_val()] = u.get_val();
        kolejka.modify_key(v.get_val(), nowa_odleglosc); //zmiana na kolejke priorytetowa
      }
    }
  }
  return true;
}

bool StaryBellmanFord(const IGraph* graf, size_t skad, int* poprzednik, int* odleglosc) {
  const size_t size = graf->vertex_count();
  if (skad >= size) {
    std::cerr << "Nie wyznaczę drogi do nieistniejącego węzła!" << std::endl;
    return false;
  }

  // Inicjalizacja
  for (size_t i = 0; i < size; ++i) {
    poprzednik[i] = -1;
    odleglosc[i] = INT_MAX;
  }
  odleglosc[skad] = 0;

  // Relaksacja wszystkich krawędzi (V-1 razy)
  for (size_t i = 1; i < size; ++i) {
    for (size_t u = 0; u < size; ++u) {
      List<Pair> sasiedzi;
      graf->neighbors(u, sasiedzi);
      for (size_t j = 0; j < sasiedzi.get_size(); ++j) {
      Pair v = sasiedzi.at_position(j)->value();
      int waga = v.get_key();
      size_t v_indeks = v.get_val();

      if (odleglosc[u] != INT_MAX && odleglosc[u] + waga < odleglosc[v_indeks]) {
        odleglosc[v_indeks] = odleglosc[u] + waga;
        poprzednik[v_indeks] = u;
      }
          }
        }
      }

  // Sprawdzenie ujemnego cyklu
  for (size_t u = 0; u < size; ++u) {
    List<Pair> sasiedzi;
    graf->neighbors(u, sasiedzi);
    for (size_t j = 0; j < sasiedzi.get_size(); ++j) {
      Pair v = sasiedzi.at_position(j)->value();
      int waga = v.get_key();
      size_t v_indeks = v.get_val();

      if (odleglosc[u] != INT_MAX && odleglosc[u] + waga < odleglosc[v_indeks]) {
        std::cerr << "Graf zawiera ujemny cykl!" << std::endl;
        return false;
      }
    }
  }
  return true;
}

bool BellmanFord(const IGraph* graf, size_t skad, int* poprzednik, int* odleglosc) {
  const size_t size = graf->vertex_count();
  if (skad >= size) {
    std::cerr << "Nie wyznaczę drogi do nieistniejącego węzła!" << std::endl;
    return false;
  }

  // Inicjalizacja
  for (size_t i = 0; i < size; ++i) {
    poprzednik[i] = -1;
    odleglosc[i] = INT_MAX;
  }
  odleglosc[skad] = 0;
  DynamicArray<Edge> edges = graf->edges();

  // Relaksacja wszystkich krawędzi (V-1 razy)
  for (size_t i = 0; i < size -1; i++) {
    for (size_t j = 0; j < edges.get_size(); j++) {
        const Edge& e = edges[j];
        if (odleglosc[e.source] != INT_MAX && odleglosc[e.source] + e.weight < odleglosc[e.destination]) {
            odleglosc[e.destination] = odleglosc[e.source] + e.weight;
            poprzednik[e.destination] = e.source;
        }
    }
  }

  // Ostatnia relaksacja dla sprawdzenia ujemnego cyklu
  for (size_t j = 0; j < edges.get_size(); j++) {
    const Edge& e = edges[j];
    if (odleglosc[e.source] != INT_MAX && 
        odleglosc[e.source] + e.weight < odleglosc[e.destination]) {
        std::cerr << "Graf zawiera ujemny cykl!" << std::endl;
        return false;
    }
  }
  return true;

}

#endif
