ROOT = ..
include ../project.mk
include ../Makefile.in
include ../config.mk

TESTS_OUT := ${TESTS_C:%.c=%.out}

all: ${TESTS_OUT}

${TESTS_OUT}: %.out: %.c
	${MAKE} -C .. shared_library
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS} -l${APP_NAME}

clean:
	${RM} ${TESTS_OUT}

.PHONY: clean all

