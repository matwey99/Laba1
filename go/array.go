package main

import (
	"fmt"
	"strings"
)

type Array struct {
	data     []string
	size     int
	capacity int
}

func NewArray() *Array {

	return &Array{data: make([]string, 4), size: 0, capacity: 4}
}

func (arr *Array) grow() {
	arr.capacity *= 2
	newData := make([]string, arr.capacity)
	for i := 0; i < arr.size; i++ {
		newData[i] = arr.data[i]
	}
	arr.data = newData
}

func (arr *Array) PushBack(value string) {
	if arr.size == arr.capacity {
		arr.grow()
	}
	arr.data[arr.size] = value
	arr.size++
}

func (arr *Array) InsertAt(index int, value string) bool {
	if index < 0 || index > arr.size {
		return false
	}
	if arr.size == arr.capacity {
		arr.grow()
	}
	for i := arr.size; i > index; i-- {
		arr.data[i] = arr.data[i-1]
	}
	arr.data[index] = value
	arr.size++
	return true
}

func (arr *Array) GetAt(index int) (string, bool) {
	if index < 0 || index >= arr.size {
		return "", false
	}
	return arr.data[index], true
}

func (arr *Array) SetAt(index int, value string) bool {
	if index < 0 || index >= arr.size {
		return false
	}
	arr.data[index] = value
	return true
}

func (arr *Array) RemoveAt(index int) bool {
	if index < 0 || index >= arr.size {
		return false
	}
	for i := index; i < arr.size-1; i++ {
		arr.data[i] = arr.data[i+1]
	}
	arr.size--
	arr.data[arr.size] = ""
	return true
}

func (arr *Array) Length() int {
	return arr.size
}

func (arr *Array) String() string {

	parts := make([]string, 0, arr.size)
	for i := 0; i < arr.size; i++ {

		parts = append(parts, arr.data[i])
	}

	return "[" + strings.Join(parts, ", ") + "]"
}

func (arr *Array) Print() {
	fmt.Println(arr.String())
}
