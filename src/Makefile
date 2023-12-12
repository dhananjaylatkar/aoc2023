# CC=clang
IDIR=../include

PROG=../aoc2023

ODIR=obj

LDIR=
LIBS=-lm

DEPS=$(wildcard ${IDIR}/*.h)

OBJ=$(patsubst %,$(ODIR)/%,$(patsubst %.c,%.o,$(wildcard *.c)))

CFLAGS=-I${IDIR}
CPPFLAGS=

ifdef DEBUG
	CPPFLAGS+=-g -DDEBUG=1
endif


all: ${PROG}

$(ODIR)/%.o: %.c ${DEPS}
	@mkdir -p ${ODIR}
	@$(CC) -c $< ${CFLAGS} ${CPPFLAGS} -o $@

${PROG}: $(OBJ)
	@$(CC) $^ $(CFLAGS) $(LIBS) -o $@

clean:
	@rm -rf $(ODIR) *~ $(INCDIR)/*~ ${PROG}

.PHONY: clean
