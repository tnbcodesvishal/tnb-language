exce = tnb.out

sources = $(wildcard src/*.c) $(wildcard src/operators/*.c) $(wildcard src/builtins/*.c) $(wildcard src/comparisons/*.c) $(wildcard src/logical/*.c) 
objects = $(sources:.c=.o)

flags = -g

$(exce): $(objects)
	gcc $(objects) $(flags) -o $(exce)

src/%.o: src/%.c include/%.h
	gcc -c $< $(flags) -o $@

install:
	make
	cp ./tnb.out /usr/local/bin/tnb

clean:
	rm -f $(exce)
	rm -f src/*.o
