all: dbms

dbms: array.go slist.go dlist.go stack.go queue.go main.go go.mod
	go build -o dbms .

test: dbms
	./test.sh

clean:
	rm -f dbms test.data

.PHONY: all test clean