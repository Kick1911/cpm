
ROOT = ..
include ../project.mk
include ../config.mk

TESTS_C = ${shell find . -name 'test_*.c'}
TESTS_OUT := ${TESTS_C:%.c=%.out}

all: ${TESTS_OUT} shared_library

${TESTS_OUT}: %.out: %.c
	${call print,BIN $<}
	${Q}${CC} $< -o $@ ${CFLAGS} ${LDFLAGS} -l${APP_NAME}

shared_library:
	${Q}${MAKE} -C .. shared_library

test: all
	${Q}LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${shell pwd}/.. valgrind --leak-check=full ${target}

clean:
	${call print,CLEAN ${APP_NAME} tests}
	${Q}${RM} ${TESTS_OUT}

.PHONY: clean all shared_library test

