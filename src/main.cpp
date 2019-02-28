#include <bits/stdc++.h>
#include "base.h"
#include "domain.h"
#include "solvers/mysolver.h"

using namespace std;

#define dbg(x) (cout<<#x<<" = "<<(x)<<'\n')

typedef long long int lld;
/* const int INF = (1LL << 30) - 1; */
/* const lld LINF = (1LL << 62) - 1; */

int main(int argc, char** argv) {
  cin.sync_with_stdio(false);

  int FLAGS_age;
  if (argc <= /* #flags = */ 1) {
    fprintf(stderr, "usage: %s <age>\n", argv[0]);
    return -1;
  } else {
    sscanf(argv[1], "%d", &FLAGS_age);
  }

  Dog dog;
  dog.age = FLAGS_age;
  printf("The dog is %d.\n", dog.age);

  InputReader input;
  OutputWriter output;
  unique_ptr<Solver> solver = make_unique<MySolver>(input, output);
  solver->Solve();
  output.Write();

  return 0;
}
