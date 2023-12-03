CC=clang
IDIR=../include

PROG=../aoc2023

ODIR=obj

LDIR=
LIBS=

DEPS=$(wildcard ${IDIR}/*.h)

OBJ=$(patsubst %,$(ODIR)/%,$(patsubst %.c,%.o,$(wildcard *.c)))

CFLAGS=-I${IDIR}
CPPFLAGS=-Wall -Werror -Wunused-but-set-variable -Wunused-variable

all: ${PROG}

$(ODIR)/%.o: %.c ${DEPS}
	@mkdir -p ${ODIR}
	@$(CC) -c $< ${CFLAGS} ${CPPFLAGS} -o $@

${PROG}: $(OBJ)
	@$(CC) $^ $(CFLAGS) $(LIBS) -o $@

clean:
	@rm -rf $(ODIR) *~ $(INCDIR)/*~ ${PROG}

.PHONY: clean
