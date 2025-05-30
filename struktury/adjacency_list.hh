#ifndef ADJ_LIST
#define ADJ_LIST
#include "dynamic_array.hh"
#include "list.hh"
#include "pair.hh"
#include "graf.hh"

//numerujmy wierzchołki od 0, size_t
//wierzchołki przechowywane jako pary, gdzie klucz to waga, wartosc to numer wierzcholka
class AdjacencyList : public IGraph {
private:
  //tablica na listy przechowujące wierzchołki, na indeksie i jest lista sąsiadów i-tego wierzchołka
  //wazne ze skierowany, jesli jest 1 -> 2, to dane[1] bedzie 2, ale dane[2] nie ma 1
  DynamicArray<List<Pair>> dane;
public:
  //podaje sie ile wierzcholkow i juz sie tego nie rusza
  AdjacencyList(size_t n_wierzcholki) {
    dane.resize(n_wierzcholki);
    for(size_t j = 0; j < n_wierzcholki; ++j) {
      dane.push_back(List<Pair>());
    }
  }

  //dodawanie, jednokierunkowe!
  void add_edge(size_t skad, size_t dokad, int waga) override ;
  //usuwanie, skierowane tez
  void remove_edge(size_t skad, size_t dokad) override ;
  //liczba krawedzi wchodzacych do i
  size_t indeg(size_t i) const override ;
  //liczba krawedzi wychodzacych z i
  size_t outdeg(size_t i) const override ;
  //czy w ogole jest
  bool has_edge(size_t skad, size_t dokad) const override ;
  //zwraca liste sasiadow, przyda sie w tak zwanej didżistrze
  void neighbors(size_t i, List<Pair>& wynik) const override ;
  // zwraca liste krawedzi w grafie
  DynamicArray<Edge> edges() const override;

  //de facto ilosc krawedzi
  size_t vertex_count() const override { return dane.get_size(); }
  //( ͡°͜ʖ ͡°)
  size_t edge_count() const override {
    size_t rezultat = 0;
    for(size_t i = 0; i < dane.get_size(); ++i)
      rezultat += dane[i].get_size();
    return rezultat;
  }

  void _show() const override { dane._show(); }
};

void AdjacencyList::add_edge(size_t skad, size_t dokad, int waga) {
  if((skad > dokad ? skad : dokad) >= dane.get_size()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba stworzenia krawędzi do nieistniejącego wierzchołka!");

  dane[skad].push_back(Pair(waga, dokad)); //nie sprawdza czy nie doda pare razy, zreszta to tylko troche spowolni dzialanie a nie zepsuje
}

void AdjacencyList::remove_edge(size_t skad, size_t dokad) {
  if((skad > dokad ? skad : dokad) >= dane.get_size()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba usunięcia krawędzi do nieistniejącego wierzchołka!");

  size_t indeks = dane[skad].find_index(Pair(dokad, 0)); //da size jesli nie ma tej wartosci tam
  if(indeks == dane.get_size())
    throw std::invalid_argument("Próba usunięcia niestniejącej krawędzi do wierzchołka!");
  dane[skad].remove_at(indeks);
}

//to troche jest tricky bo trzeba policzyc w kazdym indeksie ilosc wystapien i (no 1 albo 0 lol)
size_t AdjacencyList::indeg(size_t i) const {
  if(i >= dane.get_size())
    return 0; //aaaa zostawcie mnie jak nie ma wierzcholka to nie ma sasiadow https://pl.wikipedia.org/wiki/Antynomia_Russella

  int rezultat = 0;
  for(size_t j = 0; j < dane.get_size(); ++j) {
    if(dane[j].find(Pair(i, 0)) != nullptr && j != i)
      rezultat++;
  }
  return rezultat;
}

//łatwe, bo tylko ile jest na indeksie i
size_t AdjacencyList::outdeg(size_t i) const {
  if(i < dane.get_size())
    return dane[i].get_size();
  return 0; //aaaa i to nie problem bo nie zaklamuje prawdy a jedynie wytwarza nowego rodzaju prawde
}

bool AdjacencyList::has_edge(size_t skad, size_t dokad) const {
  if((skad > dokad ? skad : dokad) >= dane.get_size()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    return false;
  return (dane[skad].find(Pair(dokad, 0)) != nullptr);
}

void AdjacencyList::neighbors(size_t i, List<Pair>& wynik) const {
  if(i >= dane.get_size()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba pobrania sąsiadów nieistniejącego wierzchołka");
  wynik = dane[i];
}

DynamicArray<Edge> AdjacencyList::edges() const {
  DynamicArray<Edge> wynik;
  for(size_t skad=0;skad<vertex_count(); skad++){
    DynamicArray<Pair> krawedzie = dane[skad].getElements();
    size_t size = krawedzie.get_size();
    for(size_t i=0;i<size;i++){
      wynik.push_back(Edge(skad, krawedzie[i].get_val(), krawedzie[i].get_key()));
    }
  }
  return wynik;
}

#endif //ADJ_LIST
