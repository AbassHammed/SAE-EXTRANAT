compiler=gcc
CFLAGS=-Wall
LDFLAGS=
DEBUGFLAGS=-g
OPTIMIZEFLAGS=-O2
builddir=./build
libdir=./lib
sources=$(wildcard $(libdir)/*.c)
objects=$(patsubst $(libdir)/%.c,$(builddir)/%.o,$(sources))

# Check for debug or optimize options
ifeq ($(filter -d,$(MAKECMDGOALS)), -d)
    CFLAGS += $(DEBUGFLAGS)
endif
ifeq ($(filter -o,$(MAKECMDGOALS)), -o)
    CFLAGS += $(OPTIMIZEFLAGS)
endif

all: main

$(builddir)/%.o: $(libdir)/%.c | $(builddir)
	$(compiler) $(CFLAGS) -c $< -o $@

$(builddir):
	mkdir -p $(builddir)

main: main.c $(objects)
	$(compiler) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(builddir)/*.o main

run: main
	./main

# Add dummy targets for command line arguments
-d:
-o:
