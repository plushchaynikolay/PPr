# SUSU, SP, KE-220, 2019

## To install Mpich
`sudo apt install mpich`

## to compile code (into directory)
`mpicc -o main main.c`

## to run code (into directory)
`mpirun -np <number_of_processes> ./main`

or

`mpiexec -np <number_of_processes> ./main`

(`-np` and `-n` are synonyms, such as `mprun` and `mpexec` are)

For more, go and see [mpich-userguide](https://www.mpich.org/static/downloads/3.3.1/mpich-3.3.1-userguide.pdf) and [What is MPI](http://www.mcs.anl.gov/~balaji/permalinks/2014-06-06-argonne-mpi-basic.pptx).
