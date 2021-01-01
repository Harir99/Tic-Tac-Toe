FLAGS: -std=c99 -pedantic -Wall

CC: gcc

all: show_node alphatoe count_nodes

clean:
	rm -f *.o show_node  alphatoe count_nodes

show_node: show_node.o ttt1.o ttt2.o
	$(CC) $(CFLAGS)  show_node.o ttt1.o ttt2.o -o show_node

show_node.o: show_node.c ttt.h ttt.h
	$(CC) $(CFLAGS) -c show_node.c -o show_node.o

alphatoe: alphatoe.o ttt1.o ttt2.o
	$(CC) $(CFLAGS)  alphatoe.o ttt1.o ttt2.o -o alphatoe

alphatoe.o: alphatoe.c ttt.h ttt.h
	$(CC) $(CFLAGS) -c alphatoe.c -o alphatoe.o

count_nodes: count_nodes.o ttt1.o ttt2.o
	$(CC) $(CFLAGS)  count_nodes.o ttt1.o ttt2.o -o count_nodes

count_nodes.o: count_nodes.c ttt.h ttt.h
	$(CC) $(CFLAGS) -c count_nodes.c -o count_nodes.o

ttt1.o: ttt1.c ttt.h 
	$(CC) $(CFLAGS) -c ttt1.c -o ttt1.o

ttt2.o: ttt2.c ttt.h 
	$(CC) $(CFLAGS) -c ttt2.c -o ttt2.o