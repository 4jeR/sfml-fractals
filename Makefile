CC=g++
CXXFLAGS= -g -Wall -pedantic -lsfml-graphics -lsfml-window -lsfml-system
OBJS = main.o 
OUT = exe

$(OUT): $(OBJS)
	$(CC)  -o $@  $^ $(CXXFLAGS)
	
.c.o:
	$(CC) -c -o $@ $< $(CXXFLAGS) 
	
.PHONY: clean run

clean:
	rm -f *o
	rm -f $(OUT)
	clear
	
run:
	./$(OUT)









	