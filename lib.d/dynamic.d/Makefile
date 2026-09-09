CC=gcc

OBJECT=input.o output.o main.o
TARGET=hi
$(TARGET):$(OBJECT)
#hi:input.o output.o main.o
	$(CC) -o $@ $(OBJECT)
#gcc -o hi input.o output.o main.o
%.o:%.c
#input.o:input.c
#output.o:output.c
#main.o:main.c
	$(CC) -c -o $@ $<
#gcc -c -o input.o input.c
#gcc -c -o output.o output.c
#gcc -c -o main.o main.c
clean:
	rm -rf *.o $(TARGET)
