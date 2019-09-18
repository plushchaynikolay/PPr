# SUSU, SP, KE-220, 2019

## To install Mpich
`sudo apt install mpich`

## to compile code (into directory)
`mpicc -o main main.c`

## to run code (into directory)
`mpirun -np <number_of_processes> ./main`

or

`mpiexec -np <number_of_processes> ./main`
