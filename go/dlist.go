package main

import (
	"fmt"
	"strings"
)

// ---------- Двусвязный список (префикс команд L) ----------

type DNode struct {
	data string
	prev *DNode
	next *DNode
}

type DList struct {
	head *DNode
	tail *DNode
}

func NewDList() *DList {
	return &DList{nil, nil}
}

func (list *DList) FindNode(value string) *DNode {
	cur := list.head
	for cur != nil {
		if cur.data == value {
			return cur
		}
		cur = cur.next
	}
	return nil
}

// ---------- Добавление ----------

// Меняем ссылки и у новой головы, и у прежней головы, O(1).
func (list *DList) PushFront(value string) {
	n := &DNode{value, nil, list.head}
	if list.head != nil {
		list.head.prev = n
	} else {
		list.tail = n
	}
	list.head = n
}

func (list *DList) PushBack(value string) {
	n := &DNode{value, list.tail, nil}
	if list.tail != nil {
		list.tail.next = n
	} else {
		list.head = n
	}
	list.tail = n
}

// Ссылка prev позволяет обойтись без поиска предыдущего узла.
func (list *DList) PushAfter(target, value string) bool {
	p := list.FindNode(target)
	if p == nil {
		return false
	}
	n := &DNode{value, p, p.next}
	if p.next != nil {
		p.next.prev = n
	} else {
		list.tail = n
	}
	p.next = n
	return true
}

func (list *DList) PushBefore(target, value string) bool {
	p := list.FindNode(target)
	if p == nil {
		return false
	}
	n := &DNode{value, p.prev, p}
	if p.prev != nil {
		p.prev.next = n
	} else {
		list.head = n
	}
	p.prev = n
	return true
}

// ---------- Удаление ----------

// unlink - общий помощник: отключает узел от соседей и освобождает память.
// Память узла освобождает сборщик мусора, как только на него нет ссылок.
func (list *DList) unlink(node *DNode) {
	if node.prev != nil {
		node.prev.next = node.next
	} else {
		list.head = node.next
	}
	if node.next != nil {
		node.next.prev = node.prev
	} else {
		list.tail = node.prev
	}
}

// В отличие от односвязного списка, хвост удаляется за O(1).
func (list *DList) PopFront() (string, bool) {
	if list.head == nil {
		return "", false
	}
	value := list.head.data
	list.unlink(list.head)
	return value, true
}

func (list *DList) PopBack() (string, bool) {
	if list.tail == nil {
		return "", false
	}
	value := list.tail.data
	list.unlink(list.tail)
	return value, true
}

func (list *DList) RemoveAfter(target string) (string, bool) {
	p := list.FindNode(target)
	if p == nil || p.next == nil {
		return "", false
	}
	value := p.next.data
	list.unlink(p.next)
	return value, true
}

func (list *DList) RemoveBefore(target string) (string, bool) {
	p := list.FindNode(target)
	if p == nil || p.prev == nil {
		return "", false
	}
	value := p.prev.data
	list.unlink(p.prev)
	return value, true
}

func (list *DList) RemoveValue(value string) bool {
	p := list.FindNode(value)
	if p == nil {
		return false
	}
	list.unlink(p)
	return true
}

// ---------- Чтение ----------

func (list *DList) GetAt(index int) (string, bool) {
	if index < 0 {
		return "", false
	}
	cur := list.head
	for i := 0; i < index && cur != nil; i++ {
		cur = cur.next
	}
	if cur == nil {
		return "", false
	}
	return cur.data, true
}

func (list *DList) String() string {
	if list.head == nil {
		return "(empty)"
	}
	var sb strings.Builder
	for cur := list.head; cur != nil; cur = cur.next {
		if cur != list.head {
			sb.WriteString(" <-> ")
		}
		sb.WriteString(cur.data)
	}
	return sb.String()
}

func (list *DList) Print() {
	fmt.Println(list.String())
}

// Обход от хвоста - просто переход по prev.
func (list *DList) PrintReverse() {
	if list.tail == nil {
		fmt.Println("(empty)")
		return
	}
	var sb strings.Builder
	for cur := list.tail; cur != nil; cur = cur.prev {
		if cur != list.tail {
			sb.WriteString(" <-> ")
		}
		sb.WriteString(cur.data)
	}
	fmt.Println(sb.String())
}
