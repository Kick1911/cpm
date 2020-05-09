
ROOT = ..
include ../project.mk
include ../config.mk

TESTS_C = ${shell find . -name '*.c'}
TESTS_OUT := ${TESTS_C:%.c=%.out}

all: ${TESTS_OUT}
	${Q}${MAKE} -C .. shared_library

${TESTS_OUT}: %.out: %.c
	${call print,BIN $<}
	${Q}${CC} $< -o $@ ${CFLAGS} ${LDFLAGS} -l${APP_NAME}

clean:
	${call print,CLEAN ${APP_NAME} tests}
	${Q}${RM} ${TESTS_OUT}

.PHONY: clean all
