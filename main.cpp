#include <iostream>
#include <limits.h>
#include <vector>
#include "struktury/adjacency_list.hh"
#include "struktury/prique.hh"


void Dijkstra(const AdjacencyList& graf, size_t skad, int* poprzednik, int* odleglosc) {
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

int main() {
  std::vector<std::tuple<int, int, int>> edges = {
    {0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {3, 1, 1} // przykład z grafu 1
  };
  AdjacencyList mujgraf(4); // dopasuj do liczby wierzchołków

  for (const auto& [u, v, w] : edges) {
    mujgraf.add_edge(u, v, w);
    // jeśli nieskierowany: mujgraf.add_edge(v, u, w);
  }

  int* poprzednicy = new int[mujgraf.vertex_count()];
  int* odleglosci = new int[mujgraf.vertex_count()];
  Dijkstra(mujgraf, 3, poprzednicy, odleglosci);

  for(int i = 0; i < mujgraf.vertex_count(); ++i) {
    std::cout << odleglosci[i] << " ";
  }
  std::cout << "\n";
  for(int i = 0; i < mujgraf.vertex_count(); ++i) {
    std::cout << poprzednicy[i] << " ";
  }
  
  std::cout << "papa" << std::endl;
  delete[] poprzednicy;
  delete[] odleglosci;
  return 0;
}
