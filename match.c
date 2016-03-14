#include <stdio.h>
#include <stdlib.h> // rand()
#include <time.h> // time()

//#define DEBUG
#define C 0
#define D 1

#define MIN_TURN 100
#define MAX_TURN 300
#define M 16
#define N 12

unsigned char move(unsigned int s, const unsigned char * const u, const unsigned char * const v, unsigned int k) {
  unsigned int i, j;
  switch (s) {
  case 0: return D;
  case 1: return C;
  case 2: return rand() & 1;
  case 3: return k && v[k-1];
  case 4: return !k || v[k-1];
  case 5: return k > 1 && v[k-1] && v[k-2];
  case 6: return (k > 1 && (v[k-1] || v[k-2])) || (k && v[k-1]);
  case 7: return k && (u[k-1] || v[k-1]);
  case 8: return k ? u[k-1] ^ v[k-1] : rand() & 1;
  case 9: {
    for (i = j = 0; j < k; ++j) if (v[j]) ++i;
    return k && ((i<<1) > k);
  }
  case 10: {
    for (i = j = 0; j < k; ++j) if (v[j]) ++i;
    return !k || ((i<<1) >= k);
  }
  case 11: return k > 1 ? u[0] != v[0] || u[1] != v[1] : !k;
  default: return D;
  }
}

void play(unsigned int s, unsigned int t, double *score, unsigned int turn) {
  unsigned int m, n, k;
  unsigned char a, b;
  unsigned char u[turn], v[turn];
  for (k = 0; k < turn; ++k) { u[k] = v[k] = 0; }

  for (m = n = k = 0; k < turn; ++k) {
    a = move(s, u, v, k); b = move(t, v, u, k);
    if (turn <= M) printf("%d %d\n", a, b);
    u[k] = a; v[k] = b;
    if (a)
      if (b) { m += 1; n += 1; } else m += 5;
    else
      if (b) n += 5; else { m += 3; n += 3; }
  }
  score[s] += ((double) m)/turn; score[t] += ((double) n)/turn;
}

int main() {
  unsigned int turn, mode, s, t;
  const char name[N][N] = {"ALLD", "ALLC", "RAND", "TFT", "STFT", "TFTT",
			   "TTFT", "GRIM", "PAVLOV", "SM", "HM", "Shake"};
  double score[N];
  srand((unsigned int)time(NULL));
  //turn = (unsigned int)rand() % (MAX_TURN - MIN_TURN) + MIN_TURN;

  do {
    printf("1: Round robin, %u-%u matches between each strategy, %u times\n", MIN_TURN, MAX_TURN, M);
    printf("2: Single match, %u rounds\n", M);
    printf("0: Quit\n");
    scanf("%u", &mode);

    switch (mode) {
    case 1:
      // Each strategy play against each other twice, itself once
      for (s = 0; s < N; ++s) score[s] = 0.0;
      for (mode = 0; mode < M; ++mode) for (s = 0; s < N; ++s) for (t = 0; t < N; ++t) {
	    turn = (unsigned int)rand() % (MAX_TURN - MIN_TURN) + MIN_TURN;
	    play(s, t, score, turn);
	  }
      for (s = 0; s < N; ++s) printf( "%s %.4lf\n", name[s], score[s]/((double) (N<<5)));
      break;
    case 2:
      printf("Enter contestants: "); scanf("%u %u", &s, &t);
      printf( "%s %s\n", name[s], name[t]); play(s, t, score, M);
      break;
    }

  } while (mode);
  
}

/* References:
http://www.prisoners-dilemma.com/strategies.html
*/
