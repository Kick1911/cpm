
ROOT = ..
include ../project.mk
include ../config.mk

TESTS_C = ${shell find . -name '*.c'}
TESTS_OUT := ${TESTS_C:%.c=%.out}

all: ${TESTS_OUT}

${TESTS_OUT}: %.out: %.c shared_library
	${call print,BIN $<}
	${Q}${CC} $< -o $@ ${CFLAGS} ${LDFLAGS} -l${APP_NAME}

shared_library:
	${Q}${MAKE} -C .. shared_library

clean:
	${call print,CLEAN ${APP_NAME} tests}
	${Q}${RM} ${TESTS_OUT}

.PHONY: clean all shared_library
