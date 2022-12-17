#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"

bool satCallingMiniSat(unsigned int numVar, std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  Minisat::vec<Minisat::Lit> literals;
  for(int i = 0; i < numVar; i++){
    literals.push(Minisat::mkLit(solver->newVar()));
  }
  for(std::vector<int> &clause: cnf){
    Minisat::vec<Minisat::Lit> new_clause;
    for(int literal: clause) {
      if (literal < 0) {
        new_clause.push(~literals[-literal - 1]);
      } else {
        new_clause.push(literals[literal - 1]);
      }
    }
    solver->addClause(new_clause);
  }
  return solver->solve();
}
