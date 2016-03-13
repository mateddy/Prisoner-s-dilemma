#include <cstdio>
#include <vector>
#include <cstdlib> // rand()
#include <ctime> // time()

#include "strategy.hh"

//#define DEBUG
const unsigned int MIN_TURN = 100;
const unsigned int MAX_TURN = 300;
const unsigned int SINGLE = 15;

void play(strategy* s, strategy* t, unsigned int turn = SINGLE) {
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
  unsigned int turn, mode;
  std::vector<strategy*> ss =
    {new ALLC, new ALLD, new RAND, new TFT, new STFT, new TFTT, new TTFT, new GRIM, new PAVLOV};
  srand(static_cast<unsigned int>(time(NULL)));

  turn = (unsigned int)rand() % (MAX_TURN - MIN_TURN) + MIN_TURN;

  do {
    printf("1: Round robin, %d-%d matches between each strategy\n", MIN_TURN, MAX_TURN);
    printf("2: Single match, %d rounds\n", SINGLE);
    printf("0: Quit\n");
    scanf("%d", &mode);

    switch (mode) {
    case 1:
      // Each strategy play against each other twice, itself once
      for (auto s: ss) for (auto t: ss) play(s, t, turn);
      for (auto s: ss) printf( "%s %.4f\n", typeid(*s).name(), s->score/2.0/ss.size() );
      break;
    case 2:
      printf("Enter contestants: ");
      unsigned int i, j; scanf("%d %d", &i, &j); play(ss.at(i), ss.at(j));
    }

  } while (mode);

  while (!ss.empty()) { delete ss.back(); ss.pop_back(); }
  
}
