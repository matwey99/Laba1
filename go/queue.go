package main

import "fmt"

type Queue struct {
	head *FNode
	tail *FNode
}

func NewQueue() *Queue {
	return &Queue{nil, nil}
}

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

func (q *Queue) Peek() (string, bool) {
	if q.head == nil {
		return "", false
	}
	return q.head.data, true
}

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
