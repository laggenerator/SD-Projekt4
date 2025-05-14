#include <iostream>
#include <limits.h>
#include <vector>
#include <chrono>
#include "struktury/adjacency_list.hh"
#include "struktury/prique.hh"
#include "struktury/adjacency_matrix.hh"
#include "algorytmy.hh"
#include "generator.hh"

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

int wierzcholki = 1000;
int krawedzie = wierzcholki*(wierzcholki-1);
// int krawedzie = 10000;
std::vector<std::tuple<int, int, int>> edging;
// std::vector<std::tuple<int, int, int>> edging = {
//   {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 1, 1} // przykład z grafu 1
// };

// std::vector<std::tuple<int, int, int>> edging = {
//   {0, 1, 2}, {1, 2, -1}, {2, 3, 3}, {0, 3, 5} // przykład dla bellmana
// };

/* Lista sąsiedztwa */
int list_main() {
  /* Wynik dla bellmana licząc z wierzchołka 0:
    Do wierzchołka 0 => odległość = 0, poprzednik = -1  
    Do wierzchołka 1 => odległość = 2, poprzednik = 0  
    Do wierzchołka 2 => odległość = 1, poprzednik = 1  
    Do wierzchołka 3 => odległość = 4, poprzednik = 2  
  */
  AdjacencyList mujgraf(wierzcholki); // dopasuj do liczby wierzchołków
  
  for (const auto& [u, v, w] : edging) {
    mujgraf.add_edge(u, v, w);
    // jeśli nieskierowany: mujgraf.add_edge(v, u, w);
  }

  // mujgraf._show();  
  
  int* poprzednicy = new int[mujgraf.vertex_count()];
  int* odleglosci = new int[mujgraf.vertex_count()];
  Dijkstra(mujgraf, 3, poprzednicy, odleglosci);
  // BellmanFord(mujgraf, 3, poprzednicy, odleglosci);

  // std::cout << "Odległości: ";
  // for(int i = 0; i < mujgraf.vertex_count(); ++i) {
  //   std::cout << odleglosci[i] << " ";
  // }
  // std::cout << "\nPoprzednicy: ";
  // for(int i = 0; i < mujgraf.vertex_count(); ++i) {
  //   std::cout << poprzednicy[i] << " ";
  // }
  std::cout << std::endl;

  sciezka(3, wierzcholki/2, odleglosci, poprzednicy);
  
  std::cout << "papa" << std::endl;
  delete[] poprzednicy;
  delete[] odleglosci;
  return 0;
}


/* Macierz sąsiedztwa */
int matrix_main() {
  /* Wynik dla bellmana licząc z wierzchołka 0:
    Do wierzchołka 0 => odległość = 0, poprzednik = -1  
    Do wierzchołka 1 => odległość = 2, poprzednik = 0  
    Do wierzchołka 2 => odległość = 1, poprzednik = 1  
    Do wierzchołka 3 => odległość = 4, poprzednik = 2  
  */
  AdjacencyMatrix mujgraf(wierzcholki); // dopasuj do liczby wierzchołków
  
  for (const auto& [u, v, w] : edging) {
    mujgraf.add_edge(u, v, w);
    // jeśli nieskierowany: mujgraf.add_edge(v, u, w);
  }

  // mujgraf._show();
  
  int* poprzednicy = new int[mujgraf.vertex_count()];
  int* odleglosci = new int[mujgraf.vertex_count()];
  Didzikstra(mujgraf, 3, poprzednicy, odleglosci);
  // DzwonnikRenault(mujgraf, 3, poprzednicy, odleglosci);
  
  // std::cout << "Odległości: ";
  // for(int i = 0; i < mujgraf.vertex_count(); ++i) {
  //   std::cout << odleglosci[i] << " ";
  // }
  // std::cout << "\nPoprzednicy: ";
  // for(int i = 0; i < mujgraf.vertex_count(); ++i) {
  //   std::cout << poprzednicy[i] << " ";
  // }
  

  std::cout << std::endl;
  sciezka(3, wierzcholki/2, odleglosci, poprzednicy);

  std::cout << "papa" << std::endl;
  delete[] poprzednicy;
  delete[] odleglosci;
  return 0;
}

int main(){
  wierzcholki = 50;
  krawedzie = wierzcholki*(wierzcholki-1); //graf pelny
  edging = generujGraf(wierzcholki, krawedzie, 10, 100);
  // W matrix_main i list_main mozesz sobie wybrac czy patrzysz bellmana czy didżikstre
  std::cout << "Porównanie didżikstry albo bellmana dla macierzy i listy sąsiedztwa przy V=" << wierzcholki << " wierzchołków i E=" << krawedzie << " krawędzi" << std::endl;
  if(krawedzie == wierzcholki*(wierzcholki-1)){
    std::cout << "Graf skierowany pełny btw\n" << std::endl;
  }
  std::cout << "Macierzowa" << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  matrix_main();
  auto end = std::chrono::high_resolution_clock::now();
  auto czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::string jednostka;
  jednostka = "ms";
  for(int czasownik=0;czasownik<2;czasownik++){
    if(czas < 100){
      if(czasownik == 0){
        czas = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        jednostka = "us";
      }
      else {
        czas = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        jednostka = "ns";  
      }
    }
  }
  std::cout << "\nCzas: " << czas << " " << jednostka << std::endl;

  std::cout << "\n\nListowa" << std::endl;
  
  start = std::chrono::high_resolution_clock::now();
  list_main();
  end = std::chrono::high_resolution_clock::now();
  czas = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  jednostka = "ms";
  for(int czasownik=0;czasownik<2;czasownik++){
    if(czas < 100){
      if(czasownik == 0){
        czas = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        jednostka = "us";
      }
      else {
        czas = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        jednostka = "ns";  
      }
    }
  }
  std::cout << "\nCzas: " << czas << " " << jednostka << std::endl;

  return 0;
}