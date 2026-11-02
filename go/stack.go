package main

import "fmt"

// ---------- Стек на основе односвязного списка (префикс команд S) ----------

// Вершина стека - голова списка: push и pop работают с головой, O(1).
type Stack struct {
	head *FNode
}

func NewStack() *Stack {
	return &Stack{nil}
}

// Новый элемент вставляется в голову списка и становится вершиной стека.
func (s *Stack) Push(value string) {
	s.head = &FNode{value, s.head}
}

func (s *Stack) Pop() (string, bool) {
	if s.head == nil {
		return "", false
	}
	old := s.head
	s.head = old.next
	return old.data, true
}

// Чтение вершины без её удаления.
func (s *Stack) Peek() (string, bool) {
	if s.head == nil {
		return "", false
	}
	return s.head.data, true
}

// Вывод от вершины к дну.
func (s *Stack) Print() {
	if s.head == nil {
		fmt.Println("(empty)")
		return
	}
	fmt.Print("top: ")
	for cur := s.head; cur != nil; cur = cur.next {
		fmt.Print(cur.data, " ")
	}
	fmt.Println()
}
