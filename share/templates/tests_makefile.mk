
ROOT = ..
include ../project.mk
include ../config.mk

TESTS_C = ${shell find . -name 'test_*.c'}
TESTS_OUT := ${TESTS_C:%.c=%.out}

all: shared_library ${TESTS_OUT}

${TESTS_OUT}: %.out: %.c
	${call print,${GREEN}BIN $@}
	${Q}${CC} $< -o $@ ${CFLAGS} ${LDFLAGS} -l${APP_NAME}

shared_library:
	${Q}${MAKE} -C .. shared_library

test: all
	@for exe in $(TESTS_OUT) ; do \
		LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${shell pwd}/.. valgrind --error-exitcode=1 --leak-check=full $$exe ; \
	done

clean:
	${call print,${BRIGHT_CYAN}CLEAN ${APP_NAME} tests}
	${Q}${RM} ${TESTS_OUT}

.PHONY: clean all shared_library test

