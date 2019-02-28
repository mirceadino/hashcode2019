#include <bits/stdc++.h>
#include "base.h"
#include "domain.h"
#include "solvers/mysolver.h"
#include "solvers/horizontal_greedy.h"
#include "solvers/slide_solver.h"

using namespace std;

int main() {
  InputReader input;
  OutputWriter output;
  input.Read();
  unique_ptr<Solver> solver = make_unique<SlideSolver>(input, output);
  solver->Solve();
  output.Write();

  return 0;
}
