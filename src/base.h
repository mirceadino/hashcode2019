#ifndef SRC_BASE_H
#define SRC_BASE_H

#include <bits/stdc++.h>
#include "domain.h"

using namespace std;

class InputReader {
  public:
    void Read() {
    }

  protected:
};


class OutputWriter {
  public:
    void Write() {
    }

  protected:
};


class Solver {
  public:
    Solver(InputReader& input, OutputWriter& output):
      input_(input), output_(output) {
    }

    virtual ~Solver() {}

    virtual void Solve() {}

  protected:
    InputReader input_;
    OutputWriter output_;
};

#endif  // SRC_BASE_H
