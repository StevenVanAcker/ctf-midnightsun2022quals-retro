CCOPT := -Werror

all: showflag

clean:
	rm -f showflag

showflag: showflag.c
	gcc $(CCOPT) -o $@ $<
	strip $@
