

APP = task1
APP1 = task2a
APP2 = task2b
APP3 = task2c
APP4 = task3a
APP5 = task3b

CC = gcc

all :
	$(CC) -pthread -o $(APP)  task1.c -Wall
	$(CC) -pthread -o $(APP1)  task2a.c -Wall
	$(CC) -pthread -o $(APP2)  task2b.c -Wall
	$(CC) -pthread -o $(APP3)  task2c.c -Wall
	$(CC) -pthread -o $(APP4)  task3a.c -Wall
	$(CC) -pthread -o $(APP5)  task3b.c -Wall

clean:

	rm -f $(APP)
	rm -f $(APP1)
	rm -f $(APP2)
	rm -f $(APP3)
	rm -f $(APP4)
	rm -f $(APP5)
	rm -f *.dat
