package main

import (
	"fmt"
	"strings"
)

// ---------- Односвязный список (префикс команд F) ----------

type FNode struct {
	data string
	next *FNode
}

type FList struct {
	head *FNode
	tail *FNode // для добавления в конец за O(1)
}

func NewFList() *FList {
	// &FList{nil, nil} - поля без имён заполняются по порядку: head, tail
	return &FList{nil, nil}
}

// Линейный поиск узла по значению: идём от головы до конца списка, O(n).
func (list *FList) FindNode(value string) *FNode {
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

// Новый узел становится головой: переставляем одну ссылку, O(1).
func (list *FList) PushFront(value string) {
	n := &FNode{value, list.head} // data = value, next = старая голова
	list.head = n
	if list.tail == nil {
		list.tail = n
	}
}

// Добавление в конец через ссылку tail - O(1).
func (list *FList) PushBack(value string) {
	n := &FNode{value, nil}
	if list.tail == nil {
		list.head = n
		list.tail = n
	} else {
		list.tail.next = n // цепочка точек: поле next у узла tail
		list.tail = n
	}
}

// target, value string - два параметра одного типа, тип пишется один раз в конце
func (list *FList) PushAfter(target, value string) bool {
	p := list.FindNode(target)
	if p == nil {
		return false
	}
	n := &FNode{value, p.next}
	p.next = n
	if p == list.tail {
		list.tail = n
	}
	return true
}

func (list *FList) PushBefore(target, value string) bool {
	if list.head == nil {
		return false
	}
	if list.head.data == target { // цель - голова списка
		list.PushFront(value)
		return true
	}
	prev := list.head
	for prev.next != nil && prev.next.data != target {
		prev = prev.next
	}
	if prev.next == nil {
		return false
	}
	n := &FNode{value, prev.next}
	prev.next = n
	return true
}

// ---------- Удаление ----------

// (string, bool) - значение и признак успеха
func (list *FList) PopFront() (string, bool) {
	if list.head == nil {
		return "", false
	}
	old := list.head
	list.head = old.next
	if list.head == nil {
		list.tail = nil
	}
	return old.data, true
}

// В односвязном списке удалить хвост за O(1) нельзя:
// у последнего узла нет ссылки на предыдущий, поэтому ищем его, O(n).
func (list *FList) PopBack() (string, bool) {
	if list.head == nil {
		return "", false
	}
	if list.head == list.tail { // единственный узел
		value := list.head.data
		list.head, list.tail = nil, nil
		return value, true
	}
	prev := list.head
	for prev.next != list.tail {
		prev = prev.next
	}
	value := list.tail.data
	list.tail = prev
	list.tail.next = nil
	return value, true
}

func (list *FList) RemoveAfter(target string) (string, bool) {
	p := list.FindNode(target)
	if p == nil || p.next == nil {
		return "", false
	}
	victim := p.next
	value := victim.data
	p.next = victim.next
	if victim == list.tail {
		list.tail = p
	}
	return value, true
}

func (list *FList) RemoveBefore(target string) (string, bool) {
	if list.head == nil || list.head.data == target {
		return "", false // перед головой ничего нет
	}
	if list.head.next == nil {
		return "", false
	}
	if list.head.next.data == target {
		return list.PopFront()
	}
	prev := list.head
	for prev.next.next != nil && prev.next.next.data != target {
		prev = prev.next
	}
	if prev.next.next == nil {
		return "", false
	}
	victim := prev.next
	value := victim.data
	prev.next = victim.next
	return value, true
}

func (list *FList) RemoveValue(value string) bool {
	if list.head == nil {
		return false
	}
	if list.head.data == value {
		list.PopFront()
		return true
	}
	prev := list.head
	for prev.next != nil && prev.next.data != value {
		prev = prev.next
	}
	if prev.next == nil {
		return false
	}
	victim := prev.next
	prev.next = victim.next
	if victim == list.tail {
		list.tail = prev
	}
	return true
}

// ---------- Чтение ----------

// Доступ по индексу: идём от головы index шагов, O(n).
func (list *FList) GetAt(index int) (string, bool) {
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

func (list *FList) String() string {
	if list.head == nil {
		return "(empty)"
	}
	var sb strings.Builder
	for cur := list.head; cur != nil; cur = cur.next {
		if cur != list.head {
			sb.WriteString(" -> ")
		}
		sb.WriteString(cur.data)
	}
	return sb.String()
}

func (list *FList) Print() {
	fmt.Println(list.String())
}

// Обход от хвоста к голове (рекурсия вместо стека).
func (list *FList) PrintReverse() {
	if list.head == nil {
		fmt.Println("(empty)")
		return
	}
	printReverseRec(list.head)
	fmt.Println()
}

func printReverseRec(node *FNode) {
	if node == nil {
		return
	}
	printReverseRec(node.next)
	fmt.Print(node.data, " ")
}
