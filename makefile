example.out: example.o
	gcc queue.c -fPIC -shared -o libqueue.so
	gcc example.o -o example.out -L ./ -lqueue

example.o: example.c
	gcc -c example.c -o example.o

lib:
	gcc queue.c -fPIC -shared -o libqueue.so

clean:
	rm *.o *.out