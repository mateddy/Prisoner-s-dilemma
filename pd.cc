#include <cstdio>
#include <vector>
#include <cstdlib> // rand()
#include <ctime> // time()

#include "strategy.hh"

//#define DEBUG
const unsigned int MIN_TURN = 100;
const unsigned int MAX_TURN = 300;

void play(strategy* s, strategy* t, unsigned int turn = 15) {
  unsigned int m, n, k;
  bool a, b;
  vb u, v;
  u.clear(); v.clear();
  for (m = n = k = 0; k < turn; ++k) {
    a = s->move(u, v); b = t->move(v, u);
    if (turn <= 20) printf("%d %d\n", a, b);
    u.push_back(a); v.push_back(b);
    if (a)
      if (b) { m += 1; n += 1; } else m += 5;
    else
      if (b) n += 5; else { m += 3; n += 3; }
  }
  s->score += ((double) m)/turn; t->score += ((double) n)/turn;
}

int main() {
  unsigned int turn;
  std::vector<strategy*> ss =
    {new ALLC, new ALLD, new RAND, new TFT, new STFT, new TFTT, new TTFT, new GRIM, new PAVLOV};
  srand(static_cast<unsigned int>(time(NULL)));

  // Each strategy play against each other twice, itself once
  turn = (unsigned int)rand() % (MAX_TURN - MIN_TURN) + MIN_TURN;
#ifdef DEBUG
  unsigned int i, j; scanf("%d %d", &i, &j); play(ss.at(i), ss.at(j));
#else
   
  for (auto s: ss) for (auto t: ss) play(s, t, turn);
  // Output and cleanup
  for (auto s: ss) printf( "%.4f\n", s->score/2.0/ss.size() );
#endif
  
  while (!ss.empty()) { delete ss.back(); ss.pop_back(); }
  
}
