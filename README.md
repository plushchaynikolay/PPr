# Курс параллельного программирования ЮУрГУ, 2020

## Установка Mpich

`sudo apt install mpich`

## для компиляции

`mpicc -o main main.c`

## для запуска

`mpirun -np <number_of_processes> ./main`

или

`mpiexec -n <number_of_processes> ./main`

(`-np` и `-n` синонимы, также как `mprun` и `mpexec`)

Для большего, иди и смотри [mpich-userguide](https://www.mpich.org/static/downloads/3.3.1/mpich-3.3.1-userguide.pdf) и [What is MPI](http://www.mcs.anl.gov/~balaji/permalinks/2014-06-06-argonne-mpi-basic.pptx).

## Материалы

[Вводный курс в MPI](http://www.ssd.sscc.ru/old/old/kraeva/MPI.html) Марины Краевой.

[Введение в параллельное программирование в стандарте MPI](http://nmr.phys.spbu.ru/~komolkin/high-perf-4k/web-kurs/) - Web-курс, разработанный А. В. Комолкиным в 2000 году.

Документация по MPI ([_eng_](https://www.mpi-forum.org/docs/mpi-3.0/mpi30-report.pdf))
