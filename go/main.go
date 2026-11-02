package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Container struct {
	name  string
	kind  byte
	arr   *Array
	flist *FList
	dlist *DList
	stack *Stack
	queue *Queue
	raw   string
	next  *Container
}

type Database struct {
	head *Container
}

func (db *Database) find(name string) *Container {
	for cur := db.head; cur != nil; cur = cur.next {
		if cur.name == name {
			return cur
		}
	}
	return nil
}

func (db *Database) getOrCreate(name string, kind byte) *Container {
	c := db.find(name)
	if c != nil {
		if c.kind != kind {
			return nil
		}
		return c
	}

	c = &Container{name: name, kind: kind}
	switch kind {
	case 'M':
		c.arr = NewArray()
	case 'F':
		c.flist = NewFList()
	case 'L':
		c.dlist = NewDList()
	case 'S':
		c.stack = NewStack()
	case 'Q':
		c.queue = NewQueue()
	}

	if db.head == nil {
		db.head = c
	} else {
		last := db.head
		for last.next != nil {
			last = last.next
		}
		last.next = c
	}
	return c
}

func (db *Database) getExisting(name string, kind byte) *Container {
	c := db.find(name)
	if c == nil || c.kind != kind {
		return nil
	}
	return c
}

func loadFile(db *Database, filename string) {
	file, err := os.Open(filename)
	if err != nil {
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		words := strings.Fields(line)
		if len(words) < 2 {
			continue
		}
		kind := words[0][0]
		if !strings.ContainsRune("MFLSQT", rune(kind)) {
			continue
		}
		c := db.getOrCreate(words[1], kind)
		if c == nil {
			continue
		}
		if kind == 'T' {
			c.raw = line
			continue
		}

		for _, item := range words[2:] {
			switch kind {
			case 'M':
				c.arr.PushBack(item)
			case 'F':
				c.flist.PushBack(item)
			case 'L':
				c.dlist.PushBack(item)
			case 'S':
				c.stack.Push(item)
			case 'Q':
				c.queue.Push(item)
			}
		}
	}
}

func saveStackRec(node *FNode, sb *strings.Builder) {
	if node == nil {
		return
	}
	saveStackRec(node.next, sb)
	sb.WriteString(" " + node.data)
}

func saveFile(db *Database, filename string) {
	var sb strings.Builder
	for c := db.head; c != nil; c = c.next {
		if c.kind == 'T' {
			sb.WriteString(c.raw + "\n")
			continue
		}

		sb.WriteString(string(c.kind) + " " + c.name)
		switch c.kind {
		case 'M':
			for i := 0; i < c.arr.size; i++ {
				sb.WriteString(" " + c.arr.data[i])
			}
		case 'F':
			for cur := c.flist.head; cur != nil; cur = cur.next {
				sb.WriteString(" " + cur.data)
			}
		case 'L':
			for cur := c.dlist.head; cur != nil; cur = cur.next {
				sb.WriteString(" " + cur.data)
			}
		case 'S':
			saveStackRec(c.stack.head, &sb)
		case 'Q':
			for cur := c.queue.head; cur != nil; cur = cur.next {
				sb.WriteString(" " + cur.data)
			}
		}
		sb.WriteString("\n")
	}

	err := os.WriteFile(filename, []byte(sb.String()), 0644)
	if err != nil {
		fmt.Println("-> ERROR: cannot write file")
	}
}

func printError(msg string) {
	fmt.Println("-> ERROR: " + msg)
}

func printBool(ok bool) {
	if ok {
		fmt.Println("-> TRUE")
	} else {
		fmt.Println("-> FALSE")
	}
}

func printResult(value string, ok bool, errMsg string) bool {
	if ok {
		fmt.Println("-> " + value)
	} else {
		printError(errMsg)
	}
	return ok
}

func toInt(s string) (int, bool) {
	n, err := strconv.Atoi(s)
	return n, err == nil
}

func runArray(db *Database, w []string) bool {
	cmd, n := w[0], len(w)
	if n < 2 {
		printError("no name")
		return false
	}
	if cmd == "MPUSH" && n == 3 {
		c := db.getOrCreate(w[1], 'M')
		if c == nil {
			printError("name used by another type")
			return false
		}
		c.arr.PushBack(w[2])
		fmt.Println("-> " + w[2])
		return true
	}
	if cmd == "MINSERT" && n == 4 {
		idx, ok := toInt(w[2])
		if !ok {
			printError("number expected")
			return false
		}
		c := db.getOrCreate(w[1], 'M')
		if c == nil {
			printError("name used by another type")
			return false
		}
		return printResult(w[3], c.arr.InsertAt(idx, w[3]), "bad index")
	}

	c := db.getExisting(w[1], 'M')
	if c == nil {
		printError("array not found")
		return false
	}
	if cmd == "MLEN" && n == 2 {
		fmt.Println("->", c.arr.Length())
		return false
	}
	if n < 3 {
		printError("unknown command or wrong arguments")
		return false
	}
	idx, ok := toInt(w[2])
	if !ok {
		printError("number expected")
		return false
	}

	switch {
	case cmd == "MGET" && n == 3:
		value, ok := c.arr.GetAt(idx)
		printResult(value, ok, "bad index")
		return false
	case cmd == "MSET" && n == 4:
		return printResult(w[3], c.arr.SetAt(idx, w[3]), "bad index")
	case cmd == "MDEL" && n == 3:
		return printResult("deleted", c.arr.RemoveAt(idx), "bad index")
	}
	printError("unknown command or wrong arguments")
	return false
}

type List interface {
	PushFront(value string)
	PushBack(value string)
	PushAfter(target, value string) bool
	PushBefore(target, value string) bool
	PopFront() (string, bool)
	PopBack() (string, bool)
	RemoveAfter(target string) (string, bool)
	RemoveBefore(target string) (string, bool)
	RemoveValue(value string) bool
	GetAt(index int) (string, bool)
	Print()
	PrintReverse()
}

func runList(db *Database, w []string, prefix string) bool {
	cmd, n := w[0], len(w)
	if n < 2 {
		printError("no name")
		return false
	}
	kind := prefix[0]
	op := cmd[1:]

	getList := func(create bool) List {
		var c *Container
		if create {
			c = db.getOrCreate(w[1], kind)
		} else {
			c = db.getExisting(w[1], kind)
		}
		if c == nil {
			return nil
		}
		if kind == 'F' {
			return c.flist
		}
		return c.dlist
	}

	if (op == "PUSH" || op == "PUSHTAIL" || op == "PUSHHEAD") && n == 3 {
		list := getList(true)
		if list == nil {
			printError("name used by another type")
			return false
		}
		if op == "PUSHHEAD" {
			list.PushFront(w[2])
		} else {
			list.PushBack(w[2])
		}
		fmt.Println("-> " + w[2])
		return true
	}

	list := getList(false)
	if list == nil {
		printError("list not found")
		return false
	}

	switch {
	case op == "PUSHAFTER" && n == 4:
		return printResult(w[3], list.PushAfter(w[2], w[3]), "target not found")
	case op == "PUSHBEFORE" && n == 4:
		return printResult(w[3], list.PushBefore(w[2], w[3]), "target not found")
	case op == "DELHEAD" && n == 2:
		value, ok := list.PopFront()
		return printResult(value, ok, "list is empty")
	case op == "DELTAIL" && n == 2:
		value, ok := list.PopBack()
		return printResult(value, ok, "list is empty")
	case op == "DELAFTER" && n == 3:
		value, ok := list.RemoveAfter(w[2])
		return printResult(value, ok, "nothing to delete")
	case op == "DELBEFORE" && n == 3:
		value, ok := list.RemoveBefore(w[2])
		return printResult(value, ok, "nothing to delete")
	case op == "DEL" && n == 3:
		ok := list.RemoveValue(w[2])
		printBool(ok)
		return ok
	case op == "GET" && n == 3:
		idx, ok := toInt(w[2])
		if !ok {
			printError("number expected")
			return false
		}
		value, ok := list.GetAt(idx)
		printResult(value, ok, "bad index")
		return false
	case op == "FIND" && n == 3:

		if kind == 'F' {
			printBool(list.(*FList).FindNode(w[2]) != nil)
		} else {
			printBool(list.(*DList).FindNode(w[2]) != nil)
		}
		return false
	case op == "PRINTREV" && n == 2:
		fmt.Print("-> ")
		list.PrintReverse()
		return false
	}
	printError("unknown command or wrong arguments")
	return false
}

func runStack(db *Database, w []string) bool {
	cmd, n := w[0], len(w)
	if cmd == "SPUSH" && n == 3 {
		c := db.getOrCreate(w[1], 'S')
		if c == nil {
			printError("name used by another type")
			return false
		}
		c.stack.Push(w[2])
		fmt.Println("-> " + w[2])
		return true
	}
	if cmd == "SPOP" && n == 2 {
		c := db.getExisting(w[1], 'S')
		if c == nil {
			printError("stack not found")
			return false
		}
		value, ok := c.stack.Pop()
		return printResult(value, ok, "stack is empty")
	}
	if cmd == "SGET" && n == 2 {
		c := db.getExisting(w[1], 'S')
		if c == nil {
			printError("stack not found")
			return false
		}
		value, ok := c.stack.Peek()
		return printResult(value, ok, "stack is empty")
	}
	printError("unknown command or wrong arguments")
	return false
}

func runQueue(db *Database, w []string) bool {
	cmd, n := w[0], len(w)
	if cmd == "QPUSH" && n == 3 {
		c := db.getOrCreate(w[1], 'Q')
		if c == nil {
			printError("name used by another type")
			return false
		}
		c.queue.Push(w[2])
		fmt.Println("-> " + w[2])
		return true
	}
	if cmd == "QPOP" && n == 2 {
		c := db.getExisting(w[1], 'Q')
		if c == nil {
			printError("queue not found")
			return false
		}
		value, ok := c.queue.Pop()
		return printResult(value, ok, "queue is empty")
	}
	if cmd == "QGET" && n == 2 {
		c := db.getExisting(w[1], 'Q')
		if c == nil {
			printError("queue not found")
			return false
		}
		value, ok := c.queue.Peek()
		return printResult(value, ok, "queue is empty")
	}
	printError("unknown command or wrong arguments")
	return false
}

func runTree(db *Database, w []string) bool {
	printError("trees are implemented in the C++ version")
	return false
}

func runPrint(db *Database, w []string) {
	if len(w) != 2 {
		printError("usage: PRINT name")
		return
	}
	c := db.find(w[1])
	if c == nil {
		printError("not found")
		return
	}
	switch c.kind {
	case 'M':
		fmt.Print("-> ")
		c.arr.Print()
	case 'F':
		fmt.Print("-> ")
		c.flist.Print()
	case 'L':
		fmt.Print("-> ")
		c.dlist.Print()
	case 'S':
		fmt.Print("-> ")
		c.stack.Print()
	case 'Q':
		fmt.Print("-> ")
		c.queue.Print()
	case 'T':
		fmt.Println(c.raw)
	}
}

func execute(db *Database, query string) bool {
	w := strings.Fields(query)
	if len(w) == 0 {
		printError("empty query")
		return false
	}
	cmd := w[0]
	if cmd == "PRINT" {
		runPrint(db, w)
		return false
	}

	switch cmd[0] {
	case 'M':
		return runArray(db, w)
	case 'F':
		return runList(db, w, "F")
	case 'L':
		return runList(db, w, "L")
	case 'S':
		return runStack(db, w)
	case 'Q':
		return runQueue(db, w)
	case 'T':
		return runTree(db, w)
	}
	printError("unknown command")
	return false
}

func main() {

	filename := flag.String("file", "", "data file")
	query := flag.String("query", "", "query")
	flag.Parse()

	if *filename == "" || *query == "" {
		fmt.Println("Usage: ./dbms --file <file> --query '<COMMAND args>'")
		os.Exit(1)
	}

	db := &Database{}
	loadFile(db, *filename)

	if execute(db, *query) {
		saveFile(db, *filename)
	}
}
