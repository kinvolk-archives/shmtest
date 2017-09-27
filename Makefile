shmtest: shmtest.o
	gcc -Wall -static -o shmtest shmtest.c

docker: shmtest
	docker build -t kinvolk/shmtest .

clean:
	rm -f shmtest shmtest.o


