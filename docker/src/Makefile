
SOURCES := $(wildcard *.c)
TARGETS := $(patsubst %.c,%.cgi,$(SOURCES))

CCOPT := -Werror

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

%.cgi: %.c
	gcc $(CCOPT) -o $@ $<
	strip $@
