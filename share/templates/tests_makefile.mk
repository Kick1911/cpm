
ROOT = ..
include ../project.mk
include ../config.mk

TESTS_C = ${shell find . -name '*.c'}
TESTS_OUT := ${TESTS_C:%.c=%.out}

all: ${TESTS_OUT}
	${MAKE} -C .. shared_library

${TESTS_OUT}: %.out: %.c
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS} -l${APP_NAME}

clean:
	${RM} ${TESTS_OUT}

.PHONY: clean all
