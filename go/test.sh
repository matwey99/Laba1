#!/bin/bash

DBMS=./dbms
DATA=test.data

if [ ! -x "$DBMS" ]; then
    echo "Сначала соберите проект: make" >&2
    exit 1
fi

rm -f "$DATA"

run() {
    echo "\$ $DBMS --file $DATA --query '$1'"
    $DBMS --file "$DATA" --query "$1"
    echo
}

section() {
    echo "============================================================"
    echo "$1"
    echo "============================================================"
    echo
}

section "Массив (M)"
run "MPUSH arr 10"
run "MPUSH arr 20"
run "MPUSH arr 30"
run "MINSERT arr 1 15"
run "MGET arr 1"
run "MSET arr 0 99"
run "MDEL arr 2"
run "MLEN arr"
run "PRINT arr"

section "Односвязный список (F)"
run "FPUSH flist a"
run "FPUSH flist b"
run "FPUSHHEAD flist start"
run "FPUSHAFTER flist b mid"
run "FPUSHBEFORE flist mid before-mid"
run "PRINT flist"
run "FGET flist 2"
run "FFIND flist mid"
run "FDELAFTER flist b"
run "FDELHEAD flist"
run "FDEL flist b"
run "FPRINTREV flist"
run "PRINT flist"

section "Двусвязный список (L)"
run "LPUSH dlist x"
run "LPUSH dlist y"
run "LPUSHHEAD dlist first"
run "LPUSHAFTER dlist y mid"
run "LPUSHBEFORE dlist mid before-mid"
run "PRINT dlist"
run "LGET dlist 2"
run "LFIND dlist mid"
run "LDELAFTER dlist y"
run "LDELBEFORE dlist x"
run "LDELTAIL dlist"
run "LPRINTREV dlist"
run "PRINT dlist"

section "Стек (S)"
run "SPUSH mystack a"
run "SPUSH mystack b"
run "SPUSH mystack c"
run "SGET mystack"
run "SPOP mystack"
run "PRINT mystack"

section "Очередь (Q)"
run "QPUSH myqueue a"
run "QPUSH myqueue b"
run "QPUSH myqueue c"
run "QGET myqueue"
run "QPOP myqueue"
run "PRINT myqueue"

section "Дерево (T) — реализовано только в версии на C++"
run "TINSERT mytree 10"
run "PRINT mytree"

section "Обработка ошибок"
run "SPOP unknown"
run "MGET arr 100"
run "BADCOMMAND arg"

section "Содержимое файла данных после выполнения команд"
cat "$DATA"
