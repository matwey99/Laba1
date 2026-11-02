package main

import "fmt"

// ---------- Очередь на основе односвязного списка (префикс команд Q) ----------

// Добавление в хвост, извлечение из головы: FIFO (first in - first out).
type Queue struct {
	head *FNode // начало очереди, откуда забираем элемент
	tail *FNode // конец очереди, куда добавляем элемент
}

func NewQueue() *Queue {
	return &Queue{nil, nil}
}

// Добавление в конец очереди через ссылку tail - O(1).
func (q *Queue) Push(value string) {
	n := &FNode{value, nil}
	if q.tail == nil {
		q.head = n
		q.tail = n
	} else {
		q.tail.next = n
		q.tail = n
	}
}

// Извлечение из начала очереди - O(1).
func (q *Queue) Pop() (string, bool) {
	if q.head == nil {
		return "", false
	}
	old := q.head
	q.head = old.next
	if q.head == nil {
		q.tail = nil
	}
	return old.data, true
}

// Чтение первого элемента без его извлечения.
func (q *Queue) Peek() (string, bool) {
	if q.head == nil {
		return "", false
	}
	return q.head.data, true
}

// Вывод от начала очереди к концу.
func (q *Queue) Print() {
	if q.head == nil {
		fmt.Println("(empty)")
		return
	}
	fmt.Print("front: ")
	for cur := q.head; cur != nil; cur = cur.next {
		fmt.Print(cur.data, " ")
	}
	fmt.Println()
}
