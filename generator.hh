#ifndef GENERATOR_HH
#define GENERATOR_HH

#include <iostream>
#include <vector>
#include <tuple>
#include <random>
#include <set>

using namespace std;

vector<tuple<int, int, int>> generujGraf(int wierzcholki, int krawedzie, int minWaga, int maxWaga) {
  vector<tuple<int, int, int>> edges;
  set<pair<int, int>> istniejące;

  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> wierz(0, wierzcholki - 1);
  uniform_int_distribution<> waga(minWaga, maxWaga);

  while ((int)edges.size() < krawedzie) {
      int u = wierz(gen);
      int v = wierz(gen);
      if (u == v) continue;

      pair<int, int> krawedz = make_pair(u, v);
      if (istniejące.count(krawedz)) continue;

      istniejące.insert(krawedz);
      int w = waga(gen);
      edges.emplace_back(u, v, w);
  }

  return edges;
}

#endif