# Лабораторная работа № 1 — абстрактные структуры данных

Индивидуальный вариант: **3 — Complete Binary Tree**.

## Состав репозитория

- `cpp/` — реализация на C++, включая Complete Binary Tree.
- `go/` — реализация линейных структур на Go. Дерево по условию выполняется только на C++.

В обеих версиях реализованы динамический массив, односвязный и двусвязный списки, стек и очередь. C++-версия также содержит Complete Binary Tree с поиском, обходами и проверками `TISCOMPLETE` / `TISFULL`.

## Сборка и запуск C++

```sh
cd cpp
make
./dbms --file data.txt --query 'TINSERT tree 10'
./dbms --file data.txt --query 'PRINT tree'
```

Также доступна сборка через CMake:

```sh
cmake -S . -B build
cmake --build build
```

## Сборка и запуск Go

```sh
cd go
go build -o dbms .
./dbms --file data.txt --query 'SPUSH mystack item'
```

## Контрольные сценарии

В каждой папке есть `test.sh`. Скрипт удаляет и заново создаёт `test.data` в текущей папке, поэтому запускайте его только там, где этот файл можно перезаписать.
