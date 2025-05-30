#ifndef GENERATOR_HH
#define GENERATOR_HH

#include <vector>
#include <tuple>
#include <set>
#include <random>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
// CHyba trzeba zrobic cykl hamiltona chyba żeby mieć ten spójny grafik

// Jeżeli będą ujemne wagi to i tak wykorzystywany jest jedynie Bellman-Ford który wykryje ujemne cykle
std::vector<std::tuple<int, int, int>> generujGraf(int wierzcholki, int krawedzie, int minWaga, int maxWaga, bool ujemneWagi = false) {
    if (wierzcholki < 1 || krawedzie < wierzcholki || krawedzie > wierzcholki * (wierzcholki - 1)) {
        throw std::invalid_argument("Nieprawidłowe parametry - nie można utworzyć spójnego grafu");
    }

    
    std::vector<std::tuple<int, int, int>> edges;
    std::set<std::pair<int, int>> istniejace;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wierz(0, wierzcholki - 1);
    if(ujemneWagi) minWaga = -1 * minWaga;
    std::uniform_int_distribution<> waga(minWaga, maxWaga);
    std::uniform_int_distribution<> waga2(1, maxWaga);
    
    // Minimalna ilosc wierzcholkow to K=V bo musi byc spojny 
    for(int i=0;i<wierzcholki;i++){
      int u = i;
      int v = (i+1)%wierzcholki;
      int w = waga2(gen);
      edges.emplace_back(u, v, w);
      istniejace.insert({u, v});
    }
    int ileujemnych = 0;
    // Tu już jest dodawanie losowych pozostałości
    while((int)edges.size() < krawedzie){
      int u = wierz(gen);
      int v = wierz(gen);
      if(u == v) continue; // Nie chcemy pętli
      std::pair<int, int> krawedz = {u, v};
      if(istniejace.count(krawedz)) continue; // Nie chcemy powtarzalnych

      int w = waga(gen);
      if(ujemneWagi){
        if(w < 0){
          if(ileujemnych < (int)(krawedzie*0.01 + 0.5)){
            ileujemnych++;
          } else {
            w = -w;
          }
        }
      }
        
      edges.emplace_back(u, v, w);
      istniejace.insert({u, v});
    }

    return edges;
}

void zapisz(const char* nazwa_pliku, double** dane, size_t n, bool testKrawedzi, size_t co_ile_zapis = 1) {
    std::ofstream plik(nazwa_pliku, std::ios::out | std::ios::trunc);
    if (!plik.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << nazwa_pliku << std::endl;
        return;
    }
    if(!testKrawedzi){
      plik << "n;Macierz_sasiedztwa;Lista_sasiedztwa;Lista_krawedzi" << std::endl;
      for (size_t i = 2; i < n; i += co_ile_zapis) {
          plik << i;
          for (size_t j = 0; j < 3; ++j) {
              plik << ";" << dane[j][i];
          }
          plik << std::endl;
      }
      plik << n;
      for (size_t j = 0; j < 3; ++j) {
          plik << ";" << dane[j][n];
      }
      plik << std::endl;
    } else {
      plik << "n;Macierz_sasiedztwa;Lista_sasiedztwa;Lista_krawedzi" << std::endl;
      for (size_t i = 0; i <= n; i += co_ile_zapis) {
          plik << (i*50 + 100)/99.0;
          for (size_t j = 0; j < 3; ++j) {
              plik << ";" << dane[j][i];
          }
          plik << std::endl;
      }
    }

    plik.close();
}


void zapiszAlgorytmy(const char* nazwa_pliku, double** dane, size_t n, bool testKrawedzi, size_t co_ile_zapis = 1) {
    std::ofstream plik(nazwa_pliku, std::ios::out | std::ios::trunc);
    if (!plik.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << nazwa_pliku << std::endl;
        return;
    }
    if(!testKrawedzi){
      plik << "n;Dijkstra;BellmanFord" << std::endl;
      for (size_t i = 2; i < n; i += co_ile_zapis) {
          plik << i;
          for (size_t j = 0; j < 2; ++j) {
              plik << ";" << dane[j][i];
          }
          plik << std::endl;
      }
      plik << n;
      for (size_t j = 0; j < 2; ++j) {
          plik << ";" << dane[j][n];
      }
      plik << std::endl;
    } else {
      plik << "n;Dijkstra;BellmanFord" << std::endl;
      for (size_t i = 0; i <= n; i += co_ile_zapis) {
          plik << (i*50 + 100)/99.0;
          for (size_t j = 0; j < 2; ++j) {
              plik << ";" << dane[j][i];
          }
          plik << std::endl;
      }
    }

    plik.close();
}



#endif