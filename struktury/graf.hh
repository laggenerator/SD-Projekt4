#ifndef IGRAPH_HH
#define IGRAPH_HH

#include <cstddef>
#include "pair.hh"
#include "list.hh"

struct Edge {
    public:
        int source;
        int destination;
        int weight;
    
      Edge() : source(0), destination(0), weight(0) {}
      Edge(int s, int d, int w) : source(s), destination(d), weight(w) {}
      //operatory np do wyszukiwania w liscie
      bool operator==(const Edge& e) const {
        return (source == e.source && destination == e.destination);
      }
      bool operator!=(const Edge& e) const {
        return !(*this == e);
      }
      friend std::ostream& operator<<(std::ostream& os, const Edge& e);
    };
    
    inline std::ostream& operator<<(std::ostream& os, const Edge& p) {
      os << "(" << p.source << "|" << p.destination << "|" << p.weight << ")";
      return os;
}

class IGraph {
public:
    virtual ~IGraph() {}

    //dodaje skierowaną krawędź od 'skad' do 'dokad' o wadze 'waga'
    virtual void add_edge(size_t skad, size_t dokad, int waga) = 0;

    //usuwa skierowaną krawędź od 'skad' do 'dokad'
    virtual void remove_edge(size_t skad, size_t dokad) = 0;

    //zwraca liczbę krawędzi wchodzących do wierzchołka 'i'
    virtual size_t indeg(size_t i) const = 0;

    //zwraac liczbę krawędzi wychodzących z wierzchołka 'i'
    virtual size_t outdeg(size_t i) const = 0;

    //zwraca true jeśli istnieje krawędź od 'skad' do 'dokad'
    virtual bool has_edge(size_t skad, size_t dokad) const = 0;

    //wypełnia podaną listę sąsiadami wierzchołka 'i'
    virtual void neighbors(size_t i, List<Pair>& wynik) const = 0;
    // wypełnia podaną listę krawędziami w grafie
    virtual DynamicArray<Edge> edges() const = 0;

    //zwraca liczbę wierzchołków
    virtual size_t vertex_count() const = 0;

    //zwraca liczbę krawędzi
    virtual size_t edge_count() const = 0;

    //wyświetla
    virtual void _show() const = 0;
};

#endif // IGRAPH_HH
