#ifndef ALGORYTMY_HH
#define ALGORYTMY_HH

#include <limits.h>
#include <stdint.h>
#include <iostream>
#include "struktury/adjacency_list.hh"
#include "struktury/prique.hh"
#include "struktury/adjacency_matrix.hh"

// Dla listy sąsiedztwa
void Dijkstra(const AdjacencyList& graf, size_t skad, int* poprzednik, int* odleglosc) {
  const size_t size = graf.vertex_count();
  if(skad >= size) {
    std::cerr << "Nie wyznaczę drogi do nieistniejącego węzła!" << std::endl;
    return;
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
    const List<Pair>& sasiedzi = graf.neighbors(u.get_val());

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
}
void BellmanFord(const AdjacencyList& graf, size_t skad, int* poprzednik, int* odleglosc) {
  const size_t size = graf.vertex_count();
  if (skad >= size) {
      std::cerr << "Nie wyznaczę drogi do nieistniejącego węzła!" << std::endl;
      return;
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
          const List<Pair>& sasiedzi = graf.neighbors(u);
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
      const List<Pair>& sasiedzi = graf.neighbors(u);
      for (size_t j = 0; j < sasiedzi.get_size(); ++j) {
          Pair v = sasiedzi.at_position(j)->value();
          int waga = v.get_key();
          size_t v_indeks = v.get_val();

          if (odleglosc[u] != INT_MAX && odleglosc[u] + waga < odleglosc[v_indeks]) {
              std::cerr << "Graf zawiera ujemny cykl!" << std::endl;
              return;
          }
      }
  }
}

// Dla macierzy sąsiedztwa


void Didzikstra(const AdjacencyMatrix& graf, size_t skad, int* poprzednik, int* odleglosc){
  const size_t size = graf.vertex_count();
  if(skad >= size) {
    std::cerr << "Nie wyznaczę drogi do nieistniejącego węzła!" << std::endl;
    return;
  }

  Prique kolejka;
  for(size_t i = 0; i < size; ++i) {
    poprzednik[i] = -1;
    odleglosc[i] = INT_MAX;
    if(i == skad)
      odleglosc[i] = 0;
    kolejka.insert(Pair(odleglosc[i], i));
  }

  while(kolejka.size() != 0) {
    //relaksacja sasiadow najblizszego
    Pair u = kolejka.extract_min(); //najblizszy
    const DynamicArray<Pair>& sasiedzi = graf.neighbors(u.get_val());
    for(size_t i = 0; i < sasiedzi.get_size(); ++i) { //dla kazdego sasiada
      if (odleglosc[u.get_val()] == INT_MAX) continue;  //nie ma sensu relaksować, ponadto byłby overflow w nowa_odleglosc
      Pair v = sasiedzi[i];
      int nowa_odleglosc = odleglosc[u.get_val()] + v.get_key();
  
      //nowa droga jest lepsza niz aktualnie zapisana -- zapisujemy
      if(nowa_odleglosc < odleglosc[v.get_val()]) { 
        odleglosc[v.get_val()] = nowa_odleglosc;
        poprzednik[v.get_val()] = u.get_val();
        kolejka.modify_key(v.get_val(), nowa_odleglosc); //zmiana na kolejke priorytetowa
      }
    }
  }
}


void DzwonnikRenault(const AdjacencyMatrix& graf, size_t skad, int* poprzednik, int* odleglosc){
  const size_t size = graf.vertex_count();
  if(skad >= size) {
    std::cerr << "Nie wyznaczę drogi do nieistniejącego węzła!" << std::endl;
    return;
  }
  // Inicjalizacja jak w didzikstrze
  for (size_t i = 0; i < size; ++i) {
    poprzednik[i] = -1;
    odleglosc[i] = INT_MAX;
  }
  odleglosc[skad] = 0;

  // Relaksacja wszystkich krawędzi (V-1) RAZY!!!!!!!!!
  for(size_t i=1;i<size;i++){
    for(size_t u=0;u<size;u++){
      const DynamicArray<Pair>& sasiedzi = graf.neighbors(u);
      for(size_t j=0;j<sasiedzi.get_size();j++){
        Pair wierzcholek = sasiedzi[j];
        size_t v = wierzcholek.get_val();
        int waga = wierzcholek.get_key();

        if(odleglosc[u] != INT_MAX && odleglosc[u] + waga < odleglosc[v]){
          odleglosc[v] = odleglosc[u] + waga;
          poprzednik[v] = u;
        }
      }
    }
  }
  // Sprawdzanie ujemnego cyklu joł
  for(size_t u=0;u<size;u++){
    const DynamicArray<Pair>& sasiedzi = graf.neighbors(u);
    for(size_t j=0;j<sasiedzi.get_size();j++){
      Pair wierzcholek = sasiedzi[j];
      size_t v = wierzcholek.get_val();
      int waga = wierzcholek.get_key();

      if (odleglosc[u] != INT_MAX && odleglosc[u] + waga < odleglosc[v]) {
        std::cerr << "Graf zawiera ujemny cykl!" << std::endl;
        return;
    }
    }
  }
}

#endif