#ifndef TESTY_HH
#define TESTY_HH

#include <random>
#include <chrono>
#include <memory>
#include "generator.hh"
#include "struktury/graf.hh"
#include "algorytmy.hh"
#include "struktury/adjacency_list.hh"
#include "struktury/edge_list.hh"
#include "struktury/prique.hh"
#include "struktury/graf.hh"
#include "generator.hh"


// Przy ujemnych wagach MIN_WAGA nie ma znaczenia, zakres to od -MAX do MAX
#define MIN_WAGA 10
#define MAX_WAGA 1000
// Testy wierzchołkowe od 2 do MAX_WIERZCHOŁKÓW, a krawędziowe wykorzystują MAX_WIERZCHOŁKÓW do testu
#define MAX_WIERZCHOLKOW 100
#define MAX_WIERZCHOLKOW_W_UJEMNYM 100
#define MAX_WIERZCHOLKOW_GESTOSC 30
// Przy ujemnych wagach ILOSC_PROB * 10 żeby dać większą szansę na brak ujemnych cykli
#define ILOSC_PROB 5

// Pomocniczy żeby płynnie to testować, a w konstruktorze grafu jest podanie wierzcholkow :((
// Domyślnie szuka z punktu 0 ale https://www.youtube.com/shorts/NhALUIA0h00
void testPomocniczy(std::unique_ptr<IGraph> graf, const int wierzcholkow, const int krawedzie, double &czasDijkstra, double &czasBellman, const int punkt_startowy = 0, const bool ujemneWagi = false){
  czasDijkstra = 0;
  czasBellman = 0;

  int przezIleDzielic[2] = {ILOSC_PROB,ILOSC_PROB}; // Didżikstra, Bellman - zmiejsza się gdy będzie ujemny cykl bo wtedy czas jest zero bo nie może znaleźć ścieżki
  for(int i=0;i<ILOSC_PROB;i++){
    // Tworzenie grafu spójnego, skierowanego, z wagami i bez pętli
    std::vector<std::tuple<int, int, int>> edging = generujGraf(wierzcholkow, krawedzie, MIN_WAGA, MAX_WAGA, ujemneWagi);
  
    for (const auto& [u, v, w] : edging) {
      // if(w < 0) std::cout << "Ujemna waga: " << w << std::endl;
      graf->add_edge(u, v, w);
    }
  
    // Tablice na wyniki
    int odleglosci[wierzcholkow];
    int poprzednicy[wierzcholkow];
    for(int i=0;i<wierzcholkow;i++){
      odleglosci[i] = 0;
      poprzednicy[i] = 0;
    }
  
    // Test Didżikstry
    if(!ujemneWagi){
      auto start = std::chrono::high_resolution_clock::now();
      Dijkstra(graf.get(), punkt_startowy, poprzednicy, odleglosci);
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::nano> czas = end - start;
      czasDijkstra += czas.count();
    } else {
      przezIleDzielic[0] = 1;
      czasDijkstra = 0;
    }
  
    auto start = std::chrono::high_resolution_clock::now();
    if(!(BellmanFord(graf.get(), punkt_startowy, poprzednicy, odleglosci))){
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::nano> czas = end - start;
      czasBellman += czas.count();
    } else {
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double, std::nano> czas = end - start;
      czasBellman += czas.count();
    }
  }

  if(przezIleDzielic[0] == 0) przezIleDzielic[0] = 1;
  if(przezIleDzielic[1] == 0) przezIleDzielic[1] = 1;

  czasDijkstra /= przezIleDzielic[0];
  czasBellman /= przezIleDzielic[1];

  // std::cout << "Didżikstra V=" << wierzcholkow << " - czas: " << czasDijkstra << std::endl;
  // std::cout << "Bellman V=" << wierzcholkow << " - czas: " << czasBellman << std::endl;
}

// Maks 1000 wierzchołków bo przy pełnym grafie to jest 500k krawędzi komputer wybuchnie
void testWierzcholkowy(){

  //Macierz, lista sasiedztwa, lista krawedzi
  double** czasyDijkstra = new double*[3];
  double** czasyBellman = new double*[3];
  for(int i=0;i<3;i++){
    czasyBellman[i] = new double[MAX_WIERZCHOLKOW]; 
    czasyDijkstra[i] = new double[MAX_WIERZCHOLKOW];
  }
  
  // Minimum grafu to 2 wierzcholki bo jak krawedz wstawic
  for(int wierzcholki=2;wierzcholki<=MAX_WIERZCHOLKOW;wierzcholki++){
    int ile_krawedzi = wierzcholki;
    std::cout << "Wierzcholki: " << wierzcholki << std::endl;
    // Macierz sąsiedztwa
    testPomocniczy(std::make_unique<AdjacencyMatrix>(wierzcholki), wierzcholki, ile_krawedzi, czasyDijkstra[0][wierzcholki], czasyBellman[0][wierzcholki]);
    // Lista sąsiedztwa
    testPomocniczy(std::make_unique<AdjacencyList>(wierzcholki), wierzcholki, ile_krawedzi, czasyDijkstra[1][wierzcholki], czasyBellman[1][wierzcholki]);
    // Lista krawędzi
    testPomocniczy(std::make_unique<EdgeList>(wierzcholki), wierzcholki, ile_krawedzi, czasyDijkstra[2][wierzcholki], czasyBellman[2][wierzcholki]);
  }
  
  zapisz("testWierzcholkowyBellman.csv", czasyBellman, MAX_WIERZCHOLKOW, false);
  zapisz("testWierzcholkowyDijkstra.csv", czasyDijkstra, MAX_WIERZCHOLKOW, false);
}

// Załóżmy że jest robiony test dla V=100, bo to daje nam całkiem duży rozjazd i nie trwa godziny
void testKrawedziowy(){
  int V=MAX_WIERZCHOLKOW_GESTOSC;
  int krok = 50;
  int ile_danych = V*(V-2) / krok;
  // Czasy dla % krawedzi -- 0% to K=0, , 100% to K=V*(V-1)/2
  //Macierz, lista sasiedztwa, lista krawedzi
  double** czasyDijkstra = new double*[3];
  double** czasyBellman = new double*[3];
  for(int i=0;i<3;i++){
    czasyBellman[i] = new double[ile_danych]; 
    czasyDijkstra[i] = new double[ile_danych];
  }
  int xd = 0;
  for(int ile_krawedzi=V;ile_krawedzi<=V*(V-1);ile_krawedzi+=krok){
    std::cout << "Test [" << xd/(ile_danych*1.0) << "] -> " << ile_krawedzi << "/" << V*(V-1) << " = " << ile_krawedzi*1.0/(V*(V-1)) << "%" << std::endl;
    // Macierz sąsiedztwa
    testPomocniczy(std::make_unique<AdjacencyMatrix>(V), V, ile_krawedzi, czasyDijkstra[0][xd], czasyBellman[0][xd]);
    // Lista sąsiedztwa
    testPomocniczy(std::make_unique<AdjacencyList>(V), V, ile_krawedzi, czasyDijkstra[1][xd], czasyBellman[1][xd]);
    // Lista krawędzi
    testPomocniczy(std::make_unique<EdgeList>(V), V, ile_krawedzi, czasyDijkstra[2][xd], czasyBellman[2][xd]);
    xd++;
  }
  
  zapisz("testKrawedziowyBellman.csv", czasyBellman, ile_danych, true);
  zapisz("testKrawedziowyDijkstra.csv", czasyDijkstra, ile_danych, true);
}

void testUjemnychKrawedzi(){
  //Macierz, lista sasiedztwa, lista krawedzi
  double** czasyDijkstra = new double*[3]; // Useless ale taka funkcja testowa ze trzeba ;(
  double** czasyBellman = new double*[3];
  for(int i=0;i<3;i++){
    czasyBellman[i] = new double[MAX_WIERZCHOLKOW_W_UJEMNYM]; 
    czasyDijkstra[i] = new double[MAX_WIERZCHOLKOW_W_UJEMNYM];
  }
  
  // Minimum grafu to 2 wierzcholki bo jak krawedz wstawic
  for(int wierzcholki=2;wierzcholki<=MAX_WIERZCHOLKOW_W_UJEMNYM;wierzcholki++){
    
    int ile_krawedzi = wierzcholki*1.5;
    if(wierzcholki == 2) ile_krawedzi = 2;
    std::cout << "Wierzcholki: " << wierzcholki << " krawedzie: " << ile_krawedzi << std::endl;
    // Macierz sąsiedztwa
    try{
      testPomocniczy(std::make_unique<AdjacencyMatrix>(wierzcholki), wierzcholki, ile_krawedzi, czasyDijkstra[0][wierzcholki], czasyBellman[0][wierzcholki], 0, true);
    } catch (const std::runtime_error& e){
      std::cerr << "Err: " << e.what() << std::endl;
    }
    // Lista sąsiedztwa
    try{
      testPomocniczy(std::make_unique<AdjacencyList>(wierzcholki), wierzcholki, ile_krawedzi, czasyDijkstra[1][wierzcholki], czasyBellman[1][wierzcholki], 0, true);
    } catch (const std::runtime_error& e){
      std::cerr << "Err: " << e.what() << std::endl;
    }
    // Lista krawędzi
    try{
      testPomocniczy(std::make_unique<EdgeList>(wierzcholki), wierzcholki, ile_krawedzi, czasyDijkstra[2][wierzcholki], czasyBellman[2][wierzcholki], 0, true);
    } catch (const std::runtime_error& e){
      std::cerr << "Err: " << e.what() << std::endl;
    }
  }
  
  zapisz("wierzcholowyTestUjemnychKrawedziBellman.csv", czasyBellman, MAX_WIERZCHOLKOW_W_UJEMNYM, false);
}

void testAlgorytmuKrawedzie(){
  int V=MAX_WIERZCHOLKOW_GESTOSC;
  int krok = 50;
  int ile_danych = V*(V-2) / krok;
  // Czasy dla % krawedzi -- 0% to K=V-1, 100% to K=V*(V-1)/2
  //Macierz, lista sasiedztwa, lista krawedzi
  double** czasyDijkstra = new double*[3];
  double** czasyBellman = new double*[3];
  for(int i=0;i<3;i++){
    czasyBellman[i] = new double[ile_danych]; 
    czasyDijkstra[i] = new double[ile_danych];
  }
  int xd = 0;
  for(int ile_krawedzi=V;ile_krawedzi<=V*(V-1);ile_krawedzi+=krok){
    std::cout << "Test [" << xd << "] -> " << ile_krawedzi << "/" << V*(V-1) << " = " << ile_krawedzi*100.0/(V*(V-1)) << "%" << std::endl;
    // Macierz sąsiedztwa
    testPomocniczy(std::make_unique<AdjacencyMatrix>(V), V, ile_krawedzi, czasyDijkstra[0][xd], czasyDijkstra[1][xd]);
    // Lista sąsiedztwa
    testPomocniczy(std::make_unique<AdjacencyList>(V), V, ile_krawedzi, czasyBellman[0][xd], czasyBellman[1][xd]);
    xd++;
  }
  
  zapiszAlgorytmy("algorytmKrawedzieMacierz.csv", czasyDijkstra, ile_danych, true);
  zapiszAlgorytmy("algorytmKrawedzieLista.csv", czasyBellman, ile_danych, true);
}

void testAlgorytmuWierzcholki(){
  //Macierz, lista sasiedztwa, lista krawedzi
  double** czasyDijkstra = new double*[3];
  double** czasyBellman = new double*[3];
  for(int i=0;i<3;i++){
    czasyBellman[i] = new double[MAX_WIERZCHOLKOW]; 
    czasyDijkstra[i] = new double[MAX_WIERZCHOLKOW];
  }
  
  // Minimum grafu to 2 wierzcholki bo jak krawedz wstawic
  for(int wierzcholki=2;wierzcholki<=MAX_WIERZCHOLKOW;wierzcholki++){
    int ile_krawedzi = wierzcholki;
    std::cout << "Wierzcholki: " << wierzcholki << std::endl;
    // Macierz sąsiedztwa
    testPomocniczy(std::make_unique<AdjacencyMatrix>(wierzcholki), wierzcholki, ile_krawedzi, czasyBellman[0][wierzcholki], czasyBellman[1][wierzcholki]);
    // Lista sąsiedztwa
    testPomocniczy(std::make_unique<AdjacencyList>(wierzcholki), wierzcholki, ile_krawedzi, czasyDijkstra[0][wierzcholki], czasyDijkstra[1][wierzcholki]);
  }
  
  zapiszAlgorytmy("algorytmWierzcholkiMacierz.csv", czasyBellman, MAX_WIERZCHOLKOW, false);
  zapiszAlgorytmy("algorytmWierzcholkiLista.csv", czasyDijkstra, MAX_WIERZCHOLKOW, false);
}

#endif