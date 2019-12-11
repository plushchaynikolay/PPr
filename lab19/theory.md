__Указания к заданию 19. Коммуникации «точка-точка»: схема «мастер-рабочие»__

1. С помощью оператора if выделите в программе две секции кода - для master-процесса и для остальных процессов:

```c
if (rank == 0) {
// Код, выполняемый master-процессом
}
else {
// Код, выполняемый slave-процессами
}
```

2. В секции для slave-процессов присвойте переменной buf значение номера процесса. Отправьте buf master-процессу.
3. В секции для master-процесса с помощью оператора for создайте цикл со счетчиком src, изменяющимся от 1 до size-1. В теле цикла с помощью функцию MPI_Recv получите сообщение от процесса с номером src. Выведите полученное сообщение на экран с помощью printf.

## 1) Почему для этого алгоритма обменов использованы блокирующие функции? Можно ли использовать неблокирующие? 

Для приема сообщения использована блокирующая функция, так как за нем последует вывод результата на экран, а буффер приема будет переиспользован в следующем приеме.

## 2) Как избежать синхронизации в порядке приема сообщений без смены функции? Как в этом случае определить отправителя сообщения?

Использовать MPI_ANY_SOURCE:

`MPI_Recv(&recieved, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);`