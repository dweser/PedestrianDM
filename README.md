
PedestrianDM
=========================

**Table of Contents**
- [Program requirements](#program-requirements)
- [Program execution](#program-execution)
- [Output](#output)
- [Parameters](#parameters)
- [The program](#the-program)


## Program requirements

The user must ensure the following Python packages are installed: 
* NumPy, if the user wishes to plot or convert the data produced by the simulation; 
* PyEVTK, if the user wishes to convert the data produced by the simulation to VTK format;
* Matplotlib, if the user wishes to plot the data produced by the simulation.

## Program execution

To execute the program, run the Python script in the main folder `PedestrianDM`:
```bash
	> python main_pedestrian.py arg1 arg2 arg3 arg4 arg5 arg6
```

The arguments of the Python script are as follows:
* `arg1` :  whether to run the simulation
  * Valid values: 0, 1
  * Default value: 1
* `arg2` :  whether to convert the binary data in the folder `data` to VTK format and store in the folder `visualization/dataVTK`
  * Valid values: 0, 1
  * Default value: 0
* `arg3` :  whether to plot the data in the folder `data` natively in Python
  * Valid values: 0, 1
  * Default value: 1
* `arg4` : whether to analyze and plot the densities over time
  * Valid values: 0, 1
  * Default value: 1
* `arg5` :  how many periods of data to systematically skip in conversion or plotting
  * Valid values: any positive integer
  * Default value: 1
* `arg6` :  whether to keep the binary data in the folder `data` after execution of the script
  * Valid values: 0, 1
  * Default value: 1

First, if `arg1=1`, then the program checks if the C++ source code has been compiled. 
If not, it compiles the code for the user. Then, it executes the C++ executable `pedestrianDM` located in `bin`.
First, the program reads the XML file `parameters/parameters.xml` and executes the program following those 
instructions. See the section [Parameters](#parameters) below. Then, the program computes the positions
(`X`) and the strategies (`S`) of the particles at each time step. Other than final execution time,
nothing will be output to the terminal.

Second, if `arg2=1`, then the program converts the binary data as indicated above, ommiting every `arg4` data files.

Third, if `arg3=1`, then the program plots the data natively in Python, ommiting every `arg5` data files. 
The data is plot as an animation, so the user must close the resulting window to stop the animation.

Fourth, if `arg4=1`, then the program plots the densities and differences between densities natively in Python, ommiting every `arg5` data files. 
The data is plot as an animation, so the user must close the resulting window to stop the animation.

Finally, if `arg6=1`, then the program deletes the binary data in the folder `data`.


## Output

The program `PedestrianDM` will write the trajectories and the strategies of each particle at each
time step as binary files. The `makefile` will create the directory `data`, where the program will store the aforementioned binary files:
* `particleX_******`     : x coordinate of the particles
* `particleY_******`     : y coordinate of the particles
* `particleS_******`     : s strategy of the particles,

where the value `******` is a counter of the time step.

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
 * `R_COOP`     : radius of cooperating particle for pushing
 * `R_DEF`      : radius of defecting particle for pushing
 * `L`          : radius of all particles for reaction
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

NOTE: Since the parameters are written in XML, white space is NOT ignored, e.g. `<IC>lattice</IC>` is not the same value as `<IC>  lattice  <\IC>`. While indentations and text-aligning looks cleaner, it should not be used in XML files.

## The program

The program's "main" is the file *main_pedestrianDM.cpp*.
It uses different modules (defined in separated files):

| File                              | Description   |
| ----------------------------------|:-------------:|
| `init_functions`                  | contains functions needed for initialization of program
| `two_spec_iter`                   | updates `X`
| `decision_strategies`             | updates `S` using various models
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
