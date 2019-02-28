#ifndef SRC_SOLVERS_MYSOLVER_H
#define SRC_SOLVERS_MYSOLVER_H

#include <bits/stdc++.h>
#include "../base.h"
#include "../domain.h"

class MySolver: public Solver {
  public:
    MySolver(InputReader& input, OutputWriter& output):
      Solver(input, output) {}

    void Solve() override {
    }
};

#endif  // SRC_SOLVERS_MYSOLVER_H
