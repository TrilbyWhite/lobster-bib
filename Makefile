PROG		=  lobster-bib
VER		=  0.1
LDFLAGS	+= -lbtparse
PREFIX	?= /usr

all: lobster.c
	@gcc -o ${PROG} lobster.c ${CFLAGS} ${LDFLAGS}

install:
	@install -Dm755 ${PROG} ${DESTDIR}${PREFIX}/bin/${PROG}

