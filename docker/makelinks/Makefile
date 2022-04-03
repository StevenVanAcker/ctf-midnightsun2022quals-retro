CCOPT := -Werror

all: makelinks

clean:
	rm -f makelinks

makelinks: makelinks.c
	gcc $(CCOPT) -o $@ $<
	strip $@
