package main

import (
	"fmt"
	"strings"
)

// ---------- Массив (префикс команд M) ----------

// []string - срез строк. Срез = указатель на блок памяти + длина + ёмкость,
// индексация как у обычного массива: data[i]
type Array struct {
	data     []string
	size     int
	capacity int
}

func NewArray() *Array {
	// make([]string, 4) - срез из 4 пустых строк (аналог new string[4])
	// &Array{поле: значение, ...} - создать структуру и взять её адрес
	return &Array{data: make([]string, 4), size: 0, capacity: 4}
}

// (arr *Array) перед именем - получатель: функция становится методом Array.
// arr внутри - то же, что Array* arr в C++, вызов через точку: arr.grow()
//
// При заполнении блока памяти ёмкость увеличивается в 2 раза.
func (arr *Array) grow() {
	arr.capacity *= 2
	newData := make([]string, arr.capacity)
	for i := 0; i < arr.size; i++ {
		newData[i] = arr.data[i]
	}
	arr.data = newData
}

// Добавление в конец: элементы не сдвигаются, O(1) амортизированно.
func (arr *Array) PushBack(value string) {
	if arr.size == arr.capacity {
		arr.grow()
	}
	arr.data[arr.size] = value
	arr.size++
}

// Добавление по индексу: элементы правее index сдвигаются вправо, O(n).
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

// (string, bool) - два возвращаемых значения через запятую.
// Вызов: value, ok := arr.GetAt(1)
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

// Удаление по индексу: элементы левее удалённого сдвигаются влево, O(n).
func (arr *Array) RemoveAt(index int) bool {
	if index < 0 || index >= arr.size {
		return false
	}
	for i := index; i < arr.size-1; i++ {
		arr.data[i] = arr.data[i+1]
	}
	arr.size--
	arr.data[arr.size] = "" // освобождаем ссылку на удалённую строку
	return true
}

func (arr *Array) Length() int {
	return arr.size
}

func (arr *Array) String() string {
	// make([]string, 0, arr.size) - срез длины 0, но с памятью под arr.size элементов
	parts := make([]string, 0, arr.size)
	for i := 0; i < arr.size; i++ {
		// append возвращает новый срез, поэтому результат присваиваем обратно в parts
		parts = append(parts, arr.data[i])
	}
	// strings.Join склеивает элементы среза через разделитель ", "
	return "[" + strings.Join(parts, ", ") + "]"
}

func (arr *Array) Print() {
	fmt.Println(arr.String())
}
