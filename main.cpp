#include <iostream>
#include <limits.h>
#include <vector>
#include "struktury/adjacency_list.hh"
#include "struktury/prique.hh"
#include "struktury/adjacency_matrix.hh"
#include "algorytmy.hh"

//wyswietla
void sciezka(int skad, int dokad, int* odleglosci, int* poprzednicy) {
  if(odleglosci[dokad] == INT_MAX) {
    std::cout << "Nie ma sciezki z " << skad << " do " << dokad << "!" << std::endl;
    return;
  }
  
  int i = dokad;
  std::cout << dokad;
  while(i != skad) {
    i = poprzednicy[i];
    std::cout << " -> " << i;
  }
  std::cout << std::endl;
}
/* Lista sąsiedztwa */
int list_main() {
  // std::vector<std::tuple<int, int, int>> edges = {
  //   {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 1, 1} // przykład z grafu 1
  // };
  std::vector<std::tuple<int, int, int>> edges = {
    {0, 1, 2}, {1, 2, -1}, {2, 3, 3}, {0, 3, 5} // przykład dla bellmana
  };
  /* Wynik dla bellmana licząc z wierzchołka 0:
    Do wierzchołka 0 => odległość = 0, poprzednik = -1  
    Do wierzchołka 1 => odległość = 2, poprzednik = 0  
    Do wierzchołka 2 => odległość = 1, poprzednik = 1  
    Do wierzchołka 3 => odległość = 4, poprzednik = 2  
  */
  AdjacencyList mujgraf(4); // dopasuj do liczby wierzchołków
  
  for (const auto& [u, v, w] : edges) {
    mujgraf.add_edge(u, v, w);
    // jeśli nieskierowany: mujgraf.add_edge(v, u, w);
  }

  mujgraf._show();  
  
  int* poprzednicy = new int[mujgraf.vertex_count()];
  int* odleglosci = new int[mujgraf.vertex_count()];
  // Dijkstra(mujgraf, 3, poprzednicy, odleglosci);
  BellmanFord(mujgraf, 0, poprzednicy, odleglosci);

  std::cout << "Odległości: ";
  for(int i = 0; i < mujgraf.vertex_count(); ++i) {
    std::cout << odleglosci[i] << " ";
  }
  std::cout << "\nPoprzednicy: ";
  for(int i = 0; i < mujgraf.vertex_count(); ++i) {
    std::cout << poprzednicy[i] << " ";
  }
  
  std::cout << "papa" << std::endl;
  delete[] poprzednicy;
  delete[] odleglosci;
  return 0;
}


/* Macierz sąsiedztwa */
int matrix_main() {
  // std::vector<std::tuple<int, int, int>> edges = {
  //   {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 1, 1} // przykład z grafu 1
  // };

  std::vector<std::tuple<int, int, int>> edges = {
    {0, 1, 2}, {1, 2, -1}, {2, 3, 3}, {0, 3, 5} // przykład dla bellmana
  };
  /* Wynik dla bellmana licząc z wierzchołka 0:
    Do wierzchołka 0 => odległość = 0, poprzednik = -1  
    Do wierzchołka 1 => odległość = 2, poprzednik = 0  
    Do wierzchołka 2 => odległość = 1, poprzednik = 1  
    Do wierzchołka 3 => odległość = 4, poprzednik = 2  
  */
  AdjacencyMatrix mujgraf(4); // dopasuj do liczby wierzchołków
  
  for (const auto& [u, v, w] : edges) {
    mujgraf.add_edge(u, v, w);
    // jeśli nieskierowany: mujgraf.add_edge(v, u, w);
  }

  mujgraf._show();
  
  int* poprzednicy = new int[mujgraf.vertex_count()];
  int* odleglosci = new int[mujgraf.vertex_count()];
  // Didzikstra(mujgraf, 3, poprzednicy, odleglosci);
  DzwonnikRenault(mujgraf, 0, poprzednicy, odleglosci);
  
  std::cout << "Odległości: ";
  for(int i = 0; i < mujgraf.vertex_count(); ++i) {
    std::cout << odleglosci[i] << " ";
  }
  std::cout << "\nPoprzednicy: ";
  for(int i = 0; i < mujgraf.vertex_count(); ++i) {
    std::cout << poprzednicy[i] << " ";
  }
  
  std::cout << "papa" << std::endl;
  delete[] poprzednicy;
  delete[] odleglosci;
  return 0;
}

int main(){
  std::cout << "Macierzowa" << std::endl;
  
  matrix_main();

  std::cout << "\n\nListowa" << std::endl;
  list_main();

  return 0;
}