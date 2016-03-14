#include <stdio.h>
#include <stdlib.h> // rand()
#include <time.h> // time()
#include <math.h> // log()

//#define DEBUG
#define C 0
#define D 1

#define MIN_TURN 100
#define MAX_TURN 300
#define TURN 200
#define M 16
#define N 15

int move(const int s, const int * const u, const int * const v, const int k) {
  int i, j;
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
  case 9:
    for (i = j = 0; j < k; ++j) i += v[j];
    return k && ((i<<1) > k);
  case 10:
    for (i = j = 0; j < k; ++j) i += v[j];
    return !k || ((i<<1) >= k);
  case 11: return k > 1 ? u[0] != v[0] || u[1] != v[1] : !k;
  case 12: return !(k && v[k-1]);
  case 13: return k && rand() % 10 > 0 && v[k-1];
  case 14: return k && !u[k-1];
  default: return D;
  }
}

void turn(int s, int t, int* u, int* v, int k, int *m, int *n) {
  int a = move(s, u, v, k), b = move(t, v, u, k);
  u[k] = a; v[k] = b;
  if (a)
    if (b) { *m += 1; *n += 1; } else *m += 5;
  else
    if (b) *n += 5; else { *m += 3; *n += 3; }
}

void play(int s, int t, double *score, int n_turn) {
  int m, n, k, u[n_turn], v[n_turn];
  for (k = 0; k < n_turn; ++k) u[k] = v[k] = 0;

  for (m = n = k = 0; k < n_turn; ++k) {
    turn(s, t, u, v, k, &m, &n);
    if (n_turn == M) printf("%d %d\n", u[k], v[k]);
  }
  score[s] += ((double) m)/n_turn; score[t] += ((double) n)/n_turn;
}

void qsor(int* p, double* score, int lo, int hi) {
  if (lo < hi) {
    double v = score[p[hi]];
    int i = lo, j, k;
    for (j = lo; j < hi; ++j) if (score[p[j]] <= v) {
	if (i != j) { k = p[i]; p[i] = p[j]; p[j] = k; }
	++i;
      }
    if (i != hi) { k = p[i]; p[i] = p[hi]; p[hi] = k; }
    qsor(p, score, lo, i-1);
    qsor(p, score, i+1, hi);
  }
}

int main() {
  int n_turn, mode, r, s, t;
  double score[N];
  const char name[N][8] = {"ALLD", "ALLC", "RAND", "TFT", "STFT", "TFTT", "TTFT", "GRIM",
			   "PAVLOV", "SM", "HM", "Shake", "RTFT", "G.1TFT", "ALT"};
  srand((unsigned int)time(NULL));

  do {
    //printf("1: Round robin, %u-%u turns between each strategy, %u times\n", MIN_TURN, MAX_TURN, M);
    printf("1: Round robin, ~%u turns between each strategy, %u times\n", TURN, M);
    printf("2: Single match, %u turns\n", M);
    printf("0: Quit              Enter mode: "); scanf("%d", &mode);

    switch (mode) {
    case 1:
      // Each strategy play against each other twice, itself once
      for (s = 0; s < N; ++s) score[s] = 0.0;
      for (r = 0; r < M; ++r) for (s = 0; s < N; ++s) for (t = 0; t < N; ++t) {
	    //n_turn = (int)rand() % (MAX_TURN - MIN_TURN) + MIN_TURN;
	    n_turn = (int) (-TURN * log((double)rand() / (double)(RAND_MAX))) + M+1;
	    play(s, t, score, n_turn);
	  }
      int p[N]; for (s = 0; s < N; ++s) p[s] = s;
      //qsor(p, score, 0, N-1);
      for (s = 1; s < N; ++s) {
	r = p[s]; t = s;
	while (--t >= 0 && score[p[t]] < score[r]) p[t+1] = p[t];
	p[t+1] = r;
      }
      for (s = 0; s < N; ++s) printf( "%s %.4lf\n", name[p[s]], score[p[s]]/((double) (N<<5)));
      break;
    case 2:
      printf("Enter contestants: "); scanf("%d %d", &s, &t);
      printf( "%s %s\n", name[s], name[t]); play(s, t, score, M);
      break;
    }
  } while (mode);
}

/* References:
http://www.prisoners-dilemma.com/strategies.html
*/
