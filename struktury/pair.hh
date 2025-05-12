#ifndef PAIR_H
#define PAIR_H
#include <cstring>
#include <ostream>

class Pair {
  int key;
  int val;
public:
  Pair(int k, int v) : key(k), val(v) { }
  Pair(const Pair& p) : key(p.key), val(p.val) { }
  Pair() : key(0), val(0) { }

  
  int get_key() { return key; }
  int get_val() { return val; }
  void set_key(int k) { key = k; }
  void set_val(int v) { val = v; }

  //operatory dzialające na wartościach klucza
  bool operator==(const Pair& p) const {
    return (key == p.key);
  }
  bool operator!=(const Pair& p) const {
    return (key != p.key);
  }
  bool operator==(const int i) const {
    return (key == i);
  }
  bool operator!=(const int i) const {
    return (key != i);
  }
  bool operator<(const Pair& p) const {
    return (key < p.key);
  }
  bool operator>(const Pair& p) const {
    return (key > p.key);
  }
  bool operator<=(const Pair& p) const {
    return !(*this > p);
  }
  bool operator>=(const Pair& p) const {
    return !(*this < p);
  }
  Pair& operator=(const Pair& p) {
    if (this != &p) {
      key = p.key;
      val = p.val;
    }
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const Pair& p);
};

inline std::ostream& operator<<(std::ostream& os, const Pair& p) {
  os << "(" << p.key << "|" << p.val << ")";
  return os;
}

#endif
