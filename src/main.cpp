#include <bits/stdc++.h>
#include "base.h"
#include "domain.h"
#include "solvers/mysolver.h"
#include "solvers/horizontal_greedy.h"
#include "solvers/slide_solver.h"

using namespace std;

#define dbg(x) (cout<<#x<<" = "<<(x)<<'\n')

typedef long long int lld;
/* const int INF = (1LL << 30) - 1; */
/* const lld LINF = (1LL << 62) - 1; */

int main(int argc, char** argv) {
  cin.sync_with_stdio(false);

  /* int FLAGS_age; */
  if (argc <= /* #flags = */ 0) {
    fprintf(stderr, "usage: %s\n", argv[0]);
    return -1;
  } else {
    /* sscanf(argv[1], "%d", &FLAGS_age); */
  }

  InputReader input;
  OutputWriter output;
  input.Read();
  unique_ptr<Solver> solver = make_unique<SlideSolver>(input, output);
  /* unique_ptr<Solver> solver = make_unique<HorizontalGreedySolver>(input, output); */
  solver->Solve();
  output.Write();

  return 0;
}
