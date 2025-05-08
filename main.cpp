#include <iostream>
#include "struktury/adjacency_list.hh"

int main() {
  AdjacencyList mujgraf(5);
  for(int i = 1; i < 5; ++i){
    mujgraf.add_edge(0, i); //z 0 do kazdego poza 0
    if(i%2 == 1)
      mujgraf.add_edge(2, i);
  }
  std::cout << "Ilość wychodzacych z 0: " << mujgraf.outdeg(0) << std::endl;
  std::cout << "Ilość wchodzacych do 0: " << mujgraf.indeg(0) << std::endl;
  mujgraf._show();
  std::cout << "Sąsiedzi 2: " << mujgraf.neighbors(2) << std::endl;
  return 0;
}
