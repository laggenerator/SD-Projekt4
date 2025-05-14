#ifndef IGRAPH_HH
#define IGRAPH_HH

#include <cstddef>
#include "pair.hh"
#include "list.hh"

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

    //zwraca liczbę wierzchołków
    virtual size_t vertex_count() const = 0;

    //zwraca liczbę krawędzi
    virtual size_t edge_count() const = 0;

    //wyświetla
    virtual void _show() const = 0;
};

#endif // IGRAPH_HH
