#ifndef PRIQUE_HH
#define PRIQUE_HH
#include <memory>
#include "pair.hh"
#include "heap.hh"
#include "dynamic_array.hh"
#include "list.hh"

class Prique {
private:
  Heap dane;

public:
  void insert(int p, int val) { dane.insert(Pair(p, val)); };
  void insert(Pair p) { dane.insert(p); };

  Pair extract_min() { return dane.extract_min(); };
  Pair find_min() { return dane.find_min(); };

  void modify_key(int val, int z) { dane.modify_key(val, z); };
  void _show() { dane._show(); }
  size_t size() { return dane.size(); }
};

#endif
