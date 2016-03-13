#ifndef _strategy_
#define _strategy_

#include <vector>

#define vb std::vector<bool>
const bool C = false;
const bool D = true;

class strategy {
public:
  double score = 0.0;
  virtual bool move(const vb, const vb) = 0;
  virtual ~strategy() {}
};

class ALLD final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~ALLD() {}
};

class ALLC final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~ALLC() {}
};

class RAND final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~RAND() {}
};

class TFT final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~TFT() {}
};

class STFT final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~STFT() {}
};

class TFTT final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~TFTT() {}
};

class TTFT final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~TTFT() {}
};

class GRIM final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~GRIM() {}
};

class PAVLOV final : public strategy {
public:
  bool move(const vb, const vb) override;
  ~PAVLOV() {}
};

#endif
