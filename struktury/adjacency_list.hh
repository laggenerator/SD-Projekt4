#ifndef ADJ_LIST
#define ADJ_LIST
#include "dynamic_array.hh"
#include "list.hh"

//numerujmy wierzchołki od 0, size_t
class AdjacencyList {
private:
  //tablica na listy przechowujące wierzchołki, na indeksie i jest lista sąsiadów i-tego wierzchołka
  //wazne ze skierowany, jesli jest 1 -> 2, to dane[1] bedzie 2, ale dane[2] nie ma 1
  DynamicArray<List<size_t>> dane;
public:
  //podaje sie ile wierzcholkow i juz sie tego nie rusza
  AdjacencyList(size_t n_wierzcholki) {
    dane.resize(n_wierzcholki);
    for(size_t j = 0; j < n_wierzcholki; ++j) {
      List<size_t> l0; dane.push_back(l0);
    }
  }

  //dodawanie, jednokierunkowe!
  void add_edge(size_t skad, size_t dokad);
  //usuwanie, skierowane tez
  void remove_edge(size_t skad, size_t dokad);
  //liczba krawedzi wchodzacych do i
  size_t indeg(size_t i) const;
  //liczba krawedzi wychodzacych z i
  size_t outdeg(size_t i) const;
  //czy w ogole jest
  bool has_edge(size_t skad, size_t dokad) const;
  //zwraca liste sasiadow, przyda sie w tak zwanej didżistrze
  const List<size_t>& neighbors(size_t i) const;

  //de facto ilosc krawedzi
  size_t vertex_count() { return dane.size(); }
  //( ͡°͜ʖ ͡°)
  size_t edge_count() { return dane.size(); }

  void _show() { dane._show(); }
};

void AdjacencyList::add_edge(size_t skad, size_t dokad) {
  if((skad > dokad ? skad : dokad) >= dane.size()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba stworzenia krawędzi do nieistniejącego wierzchołka!");

  dane[skad].push_back(dokad); //nie sprawdza czy nie doda pare razy, zreszta to tylko troche spowolni dzialanie a nie zepsuje
}

void AdjacencyList::remove_edge(size_t skad, size_t dokad) {
  if((skad > dokad ? skad : dokad) >= dane.size()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba usunięcia krawędzi do nieistniejącego wierzchołka!");

  size_t indeks = dane[skad].find_index(dokad); //da size jesli nie ma tej wartosci tam
  if(indeks == dane.size())
    throw std::invalid_argument("Próba usunięcia niestniejącej krawędzi do wierzchołka!");
  dane[skad].remove_at(indeks);
}

//to troche jest tricky bo trzeba policzyc w kazdym indeksie ilosc wystapien i (no 1 albo 0 lol)
size_t AdjacencyList::indeg(size_t i) const {
  if(i >= dane.size())
    return 0; //aaaa zostawcie mnie jak nie ma wierzcholka to nie ma sasiadow https://pl.wikipedia.org/wiki/Antynomia_Russella

  int rezultat = 0;
  for(size_t j = 0; j < dane.size(); ++j) {
    if(dane[i].find(i) != nullptr && j != i)
      rezultat++;
  }
  return rezultat;
}

//łatwe, bo tylko ile jest na indeksie i
size_t AdjacencyList::outdeg(size_t i) const {
  if(i < dane.size())
    return dane[i].get_size();
  return 0; //aaaa i to nie problem bo nie zaklamuje prawdy a jedynie wytwarza nowego rodzaju prawde
}

bool AdjacencyList::has_edge(size_t skad, size_t dokad) const {
  if((skad > dokad ? skad : dokad) >= dane.size()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    return false;
  return (dane[skad].find(dokad) != nullptr);
}

const List<size_t>& AdjacencyList::neighbors(size_t i) const {
  if(i >= dane.size()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba pobrania sąsiadów nieistniejącego wierzchołka");
  return dane[i];
}

#endif //ADJ_LIST
