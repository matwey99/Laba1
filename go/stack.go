package main

import "fmt"

type Stack struct {
	head *FNode
}

func NewStack() *Stack {
	return &Stack{nil}
}

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

func (s *Stack) Peek() (string, bool) {
	if s.head == nil {
		return "", false
	}
	return s.head.data, true
}

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
