__Указания к заданию 18. Коммуникации «точка-точка»: схема «эстафетная палочка»__\
В схеме коммуникации процессов _«эстафетная палочка»_ для обеспечения последовательной от процесса к процессу передачи сообщения (_«эстафетной палочки»_), процесс должен сначала дождаться получения сообщения, а затем пересылать его следующему процессу. Но все процессы не могут начать с вызова операции получения сообщения, т.к. в случае использования блокирующих операций `MPI_Send` и `MPI_Recv` возникнет ситуация тупика (_deadlock_), при которой все процессы будут простаивать и программа никогда не завершиться. Соответственно выделяют процесс, который инициализирует передачу сообщения, т.е. первым действием выполняет операцию отправки сообщения – это процесс с номером `0`. Реализовать это можно следующим образом:\
С помощью оператора `if` выделите в программе две секции кода: для
процесса с номером `0` и для остальных процессов:
```c
if (rank == 0) {
// Код, выполняемый процессом 0
}
else {
// Код, выполняемый остальными процессами
}
```
В секции для процесса `0` присвойте переменной buf значение `0`. С помощью `MPI_Send` отправьте переменную `buf` процессу `1`. Затем, вызвав функцию `MPI_Recv`, ожидайте сообщение от процесса с номером `size-1`. В секции для остальных процессов, вызвав функцию `MPI_Recv`, ожидайте сообщение от процесса с номером `rank-1`. После получения сообщения увеличьте значение переменной `buf` на единицу и отправьте его следующему процессу: для процесса с номером `size-1` это будет `0`, для остальных – `rank+1`.

## 1) Почему для этого алгоритма обменов использованы именно блокирующие функции? Можно ли использовать неблокирующие? 
Для алгоритма были использованы блокирующие функции, так как важен порядок этих функций (получение сообщения должно быть завершено до отправки), а между этими функциями других действий нет.\
Да, можно использовать неблокирующие функции, но перед отправкой сообщения нужно дождаться получения (MPI_Wait()).

## 2) Возможно ли при выполнении программы возникновение тупика? Почему?
Нет, так как цеполка передачи сообщений не замкнута, не выполнено условие возникновение тупика. Это происходит, потому что у нулевого процесса порядок действий обратный, он сначала отправляет сообщение, затем получает.
___
"эстафетная палочка" (очередной процесс дожидается сообщения от предыдущего и потом посылает следующему) и "сдвиг по кольцу" (одновременные посылка и прием сообщений) 