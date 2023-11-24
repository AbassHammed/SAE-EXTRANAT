compiler=gcc
CFLAGS=-Wall
builddir=./build


all: main

$(builddir)/%.o: lib/%.c
	$(compiler) $(CFLAGS) -c $^ -o $@

main: main.c $(builddir)/csv.o $(builddir)/table.o
	$(compiler) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(builddir)/*.o

run: main
	$(builddir)/main	
