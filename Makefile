it:	all

PROGS	:=	rol
CFLAGS	+=	-Wall -pedantic -s

all:	$(PROGS)
clean:
	rm -f $(PROGS)
