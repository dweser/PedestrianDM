
PedestrianDM
=========================

**Table of Contents**
- [Installation](#installation)
- [Program execution](#program-execution)
- [Output](#output)
- [Parameters](#parameters)
- [The program](#the-program)

## Installation

From the main folder `PedestrianDM`, execute the `makefile`:
```bash
	> make
```
The compiler will create the executable file `PedestrianDM` in the directory `bin`. By default, the makefile uses the *g++* compiler with MacOS version detection to avoid Clang.

## Program execution

To execute the program, run the binary file:
```bash
	> cd bin/
	> ./PedestrianDM
```
The program reads the XML file `parameters/parameters.xml` and executes the program following those instructions. See the section [Parameters](#parameters) below.

NOTE: Since the parameters are written in XML, white space is NOT ignore, e.g. `<IC>lattice</IC>` is not the same value as `<IC>  lattice  <\IC>`. While indentations and text-aligning looks cleaner, it should not be used in XML files.

During execution, the program  `PedestrianDM` will compute the positions
(`X`) and the strategies (`S`) of the particles at each time step. In the
terminal, the program will display a progress bar and, upon completion, 
execution time.

## Output

The program `PedestrianDM` will save the trajectory and the strategy of each particle at each
time. The `makefile` will create the directory 'data', where the program will store the files:
* `particleX_******`     : x coordinate of the particles
* `particleY_******`     : y coordinate of the particles
* `particleS_******`     : s strategy of the particles,

with `******` a counter of time step.


## Parameters

* `parameters.xml`
 * `N`          : number of particles
 * `DT`         : time step
 * `TIME`       : total time of simulation
 * `SPATIAL`    : boolean indicating whether players change position
 * `LENGTH`     : size of the domain in x
 * `WIDTH`      : size of the domain in y
 * `IC`         : inital condition, either `lattice`, `block`, or `uniform` (see below)
 * `SPREAD`     : how dispersed players should be initially
 * `R_COOP`     : radius of cooperating particle
 * `R_DEF`      : radius of defecting particle
 * `DECISION_MODEL` : 5 different rules (see below)
 * `a_00...`     : payoff matrix
 * `MARKOV_RATE` : intensity of jump process
 * `THRESHOLD`   : use for threshold model
 * `COOP_CONST` : constant added to cooperative payoffs in voter models
 * `GUILT_CONST` : constant subtracted from defective payoffs in voter models
 * `ISING_BETA` : value of parameter `beta` in Ising model
 * `ISING_H` : value of parameter `h` in Ising model
 * `SEED_NUMBER` : seed number for C++ function `rand()`

For the initial conditions (`IC`), `lattice` creates a lattice where the defective players are scattered randomly, `block` creates a lattice where the first n players are defective, and `uniform` scatters the players randomly across the domain with random cooperative/defective states.

For the decision model (`DECISION_MODEL`), the valid options are as follows: `linear vm` - classic linear voter model, `norm vm` - linear voter model with normalized rates, `threshold vm` - threshold voter model, `br` - best response dynamics, and 'ising' - Ising model.

## The program

The program's "main" is the file *main_pedestrianDM.cpp*.
It uses different modules (defined in separated files):

| File                              | Description   |
| ----------------------------------|:-------------:|
| `init_functions`                  | contains functions needed for initialization of program
| `two_spec_iter`                   | updates `X`
| `game_linear_vm`                  | updates `S` using linear voter model
| `fn_neighbors`                    | finds neighbors of all players
| `fn_distance`                     | calculates distance between points using Euclidean metric
| `fn_phi`                          | calculates values of the function `phi`
| `parameters_xml`                  | creates and fills parameters structure from XML file
| `fn_file_print`                   | writes `X` and `S` to binary files
| `str_fixed_length`                | creates string of iteration number for file name



The architecture of the program is the following:
```bash
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  %%    main_pedestrianDM                                                       %%
  %%      -> declaration of variables                                           %%
  %%      -> construction of parameters                                         %%
  %%      -> initialization of variables                                        %%
  %%                                                                            %%
  %%      -> loop in time                                                       %%
  %%        A) update strategy S                                                %%
  %%        B) update position X                                                %%
  %%        D) write trajectories                                               %%
  %%                                                                            %%
  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
```

## Legal notice information

 This program is distributed under the GNU GPL license version 2. For any information or bugs,
please contact me at: `dweser[at]asu.edu`.
