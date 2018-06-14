# qap
Ant colony optimization for Quadratic Assignment

## Compiling

The code can be compiled using a make command inside the src folder. The c++ standard used is c++17, which require g++7 to compile.

## Running

The code can be run using `./qap` inside the source folder. The code can take the following parameters

- --instance: filename of the instance (must be located in the instances folder).
- --numAnts: number of ants.
- --alpha: alpha parameter.
- --beta: beta paramter.
- --seed: seed to be used by random generators.
- --maxTours: maximum number of solutions constructed by the heuristic.
- --maxIterations: maximum number of iterations.
- --rho: evaporation weight parameter.
- --sigma: mutation weight operator.
- --mu: mutation probability.
- --ls: turn on local search (only for MMAS).
- --bwas: select BWAS instead of MMAS.
