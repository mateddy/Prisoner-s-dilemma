#include <cstdlib> // rand
#include "strategy.hh"

bool ALLD::move(const vb, const vb) {
  return D;
}

bool ALLC::move(const vb, const vb) {
  return C;
}

bool RAND::move(const vb, const vb) {
  return rand() & 1;
}

bool TFT::move(const vb, const vb v) {
  return !v.empty() && v.back();
}

bool STFT::move(const vb, const vb v) {
  return v.empty() || v.back();
}

bool TFTT::move(const vb, const vb v) {
  return v.size() > 1 && v.back() && v[v.size()-2];
}

bool TTFT::move(const vb, const vb v) {
  return (v.size() > 1 && (v.back() || v[v.size()-2])) ||
    (!v.empty() && v.back());
}

bool GRIM::move(const vb u, const vb v) {
  return !v.empty() && (u.back() || v.back());
}

bool PAVLOV::move(const vb u, const vb v) {
  return v.empty() ? rand() & 1 : u.back() ^ v.back();
}
