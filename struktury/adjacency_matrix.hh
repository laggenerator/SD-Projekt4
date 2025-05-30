#ifndef ADJ_MATRIX
#define ADJ_MATRIX
#include "dynamic_array.hh"
#include "list.hh"
#include "pair.hh"
#include "graf.hh"

class AdjacencyMatrix : public IGraph{
  private:
    DynamicArray<DynamicArray<Pair>> dane;
  public:
  AdjacencyMatrix(size_t n_wierzcholki) {
    dane.resize(n_wierzcholki);
    Pair noEdge(0, 0); // czy istnieje, waga
    for(size_t j = 0; j < n_wierzcholki; ++j) {
      DynamicArray<Pair> rzad;
      for(size_t j=0;j<n_wierzcholki;j++){
        rzad.push_back(noEdge);
      }
      dane.push_back(rzad);
    }
  }

    //dodawanie, jednokierunkowe!
    void add_edge(size_t skad, size_t dokad, int waga) override;
    //usuwanie, skierowane tez
    void remove_edge(size_t skad, size_t dokad) override;
    //liczba krawedzi wchodzacych do i
    size_t indeg(size_t i) const override;
    //liczba krawedzi wychodzacych z i
    size_t outdeg(size_t i) const override;
    //czy w ogole jest
    bool has_edge(size_t skad, size_t dokad) const override;
    //zwraca liste sasiadow, przyda sie w tak zwanej didżistrze
    void neighbors(size_t i, List<Pair>& wynik) const override;
    // zwraca liste krawedzi w grafie
    DynamicArray<Edge> edges() const override;
  
    //de facto ilosc krawedzi
    size_t vertex_count() const override { return dane.get_size(); }
    //( ͡°͜ʖ ͡°)
    size_t edge_count() const override {
      size_t count = 0;
      for(size_t i=0;i<vertex_count();i++)
        for(size_t j=0;j<vertex_count();j++){
          if(dane[i][j].get_key() == 1) count++;
        }
      return count;
    }
  
    void _show() const override {
      for(size_t i = 0; i < vertex_count(); ++i) {
          std::cout << "[";
          for(size_t j = 0; j < vertex_count(); ++j) {
              std::cout << dane[i][j];
              if(j != vertex_count() - 1) std::cout << "; ";
          }
          std::cout << "]" << std::endl;
      }
  }
};

void AdjacencyMatrix::add_edge(size_t skad, size_t dokad, int waga){
  if((skad > dokad ? skad : dokad) >= vertex_count()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba stworzenia krawędzi z/do nieistniejącego wierzchołka!");

  dane[skad][dokad] = Pair(1, waga);
}

void AdjacencyMatrix::remove_edge(size_t skad, size_t dokad){
  if((skad > dokad ? skad : dokad) >= vertex_count()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba usunięcia krawędzi z/do nieistniejącego wierzchołka!");

  
  size_t indeks = dane[skad].find(Pair(dokad, 0)); //da size jesli nie ma tej wartosci tam
  if(indeks == vertex_count())
    throw std::invalid_argument("Próba usunięcia niestniejącej krawędzi do wierzchołka!");
  dane[skad][dokad] = Pair(0, 0);
}

size_t AdjacencyMatrix::indeg(size_t i) const {
  if(i >= vertex_count()){
    throw std::out_of_range("Taki wierzcholek nie istnieje!");
    // return 0;
  }

  size_t count = 0;
  for(size_t j=0;j<vertex_count();j++){
    if(dane[j][i].get_key() == 1){
      count++;
    }
  }
  return count;
}

size_t AdjacencyMatrix::outdeg(size_t i) const {
  if(i >= vertex_count()){
    throw std::out_of_range("Taki wierzcholek nie istnieje!");
    // return 0;
  }
  size_t count = 0;
  for(size_t j=0;j<vertex_count();j++){
    if(dane[i][j].get_key() == 1){
      count++;
    }
  }
  return count;
}

bool AdjacencyMatrix::has_edge(size_t skad, size_t dokad) const {
  if((skad > dokad ? skad : dokad) >= vertex_count()) //jesli probuje stworzyc krawedz nieistniejącą bo do nieistniejącego wierzchołka
    throw std::invalid_argument("Próba sprawdzenia nieistniejącego wierzchołka!");
  return dane[skad][dokad].get_key() == 1;
}

void AdjacencyMatrix::neighbors(size_t i, List<Pair>& wynik) const {
  if(i >= vertex_count()){
    throw std::out_of_range("Taki wierzcholek nie istnieje!");
    // return 0;
  }
  
  for(size_t j=0;j<vertex_count();j++){
    const Pair& krawedz = dane[i][j];
    if(krawedz.get_key() == 1){
      // Zwraca parę <waga, numer wierzchołka>
      wynik.push_back(Pair(krawedz.get_val(), j));
    }
  }
}

DynamicArray<Edge> AdjacencyMatrix::edges() const {
  DynamicArray<Edge> wynik;
  for(size_t skad=0;skad<vertex_count(); skad++){
    for(size_t dokad=0;dokad<vertex_count();dokad++){
      const Pair& krawedz = dane[skad][dokad];
      if(krawedz.get_key() == 1){
        wynik.push_back(Edge(skad, dokad, krawedz.get_val()));
      }
    }
  }
  return wynik;
}

#endif
