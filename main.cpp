#include <iostream>
#include <limits.h>
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
    kolejka._show();
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
  AdjacencyList mujgraf(6);
  mujgraf.add_edge(0, 1, 7);
  mujgraf.add_edge(0, 2, 9);
  mujgraf.add_edge(0, 5, 14);
  mujgraf.add_edge(1, 2, 10);
  mujgraf.add_edge(1, 3, 15);
  mujgraf.add_edge(2, 3, 11);
  mujgraf.add_edge(2, 5, 2);
  mujgraf.add_edge(3, 4, 6);
  mujgraf.add_edge(4, 5, 9);

  int* poprzednicy = new int[mujgraf.vertex_count()];
  int* odleglosci = new int[mujgraf.vertex_count()];
  Dijkstra(mujgraf, 0, poprzednicy, odleglosci);

  sciezka(0, 0, odleglosci, poprzednicy);
  sciezka(0, 1, odleglosci, poprzednicy);
  sciezka(0, 2, odleglosci, poprzednicy);
  sciezka(0, 3, odleglosci, poprzednicy);
  sciezka(0, 4, odleglosci, poprzednicy);
  sciezka(0, 5, odleglosci, poprzednicy);

  std::cout << "papa" << std::endl;
  delete[] poprzednicy;
  delete[] odleglosci;
  return 0;
}
