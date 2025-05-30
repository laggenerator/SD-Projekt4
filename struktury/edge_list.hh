#ifndef EDGE_LIST
#define EDGE_LIST
#include "dynamic_array.hh"
#include "pair.hh"
#include "list.hh"
#include "graf.hh"


//numerujmy wierzchołki od 0, size_t
//wierzchołki przechowywane jako pary, gdzie klucz to waga, wartosc to numer wierzcholka
class EdgeList : public IGraph {
private:
  //tablica na listy przechowujące wierzchołki, na indeksie i jest lista sąsiadów i-tego wierzchołka
  //wazne ze skierowany, jesli jest 1 -> 2, to dane[1] bedzie 2, ale dane[2] nie ma 1
  List<Edge> dane;
  size_t rozmiar;
public:
  //i tak dostaje jakis rozmiar chociaz tu to nie jest konieczne, bo przyjmujemy w sumie
  //ze istnieja WSZYSTKIEEEEE i tylko dajemy jakies polaczenia (tak ideowo)
  EdgeList(size_t n_wierzcholki) : rozmiar(n_wierzcholki) { }

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
  DynamicArray<Edge> edges() const override;

  //de facto ilosc krawedzi
  size_t vertex_count() const override { return rozmiar; }
  //( ͡°͜ʖ ͡°)
  size_t edge_count() const override { return dane.get_size(); }

  void _show() const override { dane._show(); }
};

void EdgeList::add_edge(size_t skad, size_t dokad, int waga) {
  if(skad >= rozmiar || dokad >= rozmiar)
    throw std::invalid_argument("Próba stworzenia krawędzi z/do nieistniejącego wierzchołka!");

  dane.push_back(Edge(skad, dokad, waga));
  
}

void EdgeList::remove_edge(size_t skad, size_t dokad) {
  size_t gdzie = dane.find_index(Edge(skad, dokad, 0));
  if(gdzie == dane.get_size())
    throw std::invalid_argument("Próba usunięcia krawędzi z/do nieistniejącego wierzchołka!");
  dane.remove_at(gdzie);
}

//to tutaj trzeba przejsc przez całe nie ma rady i liczyc gdzie dokad jest i
size_t EdgeList::indeg(size_t i) const {
  //bez zabezpieczenia przez za duzymi indeksami, jak chca to niech licza
  size_t rezultat = 0;
  for(size_t j = 0; j < dane.get_size(); ++j) {
    if(size_t(dane.at_position(j)->value().destination) == i)
      rezultat++;
  }
  return rezultat;
}

//analogcznie jak wyzej, ale source
size_t EdgeList::outdeg(size_t i) const {
  //bez zabezpieczenia przez za duzymi indeksami, jak chca to niech licza
  size_t rezultat = 0;
  for(size_t j = 0; j < dane.get_size(); ++j) {
    if(size_t(dane.at_position(j)->value().source) == i) //tylko zeby sie kompilator nie darł
      rezultat++;
  }
  return rezultat;
}

bool EdgeList::has_edge(size_t skad, size_t dokad) const {
  return (dane.find(Edge(skad, dokad, 0)) != nullptr);
}

void EdgeList::neighbors(size_t i, List<Pair>& wynik) const {
  for(size_t j = 0; j < dane.get_size(); ++j) {
    Edge rozpatrywana = dane.at_position(j)->value();
    if(size_t(rozpatrywana.source) == i)
      wynik.push_back(Pair(rozpatrywana.weight, rozpatrywana.destination));
  }
}
DynamicArray<Edge> EdgeList::edges() const {
  return dane.getElements();
}

#endif //ADJ_LIST
