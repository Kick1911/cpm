#ifndef C_PROJECT_H
#define C_PROJECT_H

#define _SRC "/src"
#define _COMP "/components"
#define _DEP "/dependents"
#define _TESTS "/tests"
#define _UTILS "/utils"

#define CONFIG_MK \
    _BR("ROOT ?= .") \
    _BR("SRC_PATH = ${ROOT}" _SRC) \
    _BR("COMP_PATH = ${SRC_PATH}" _COMP) \
    _BR("DEP_PATH = ${SRC_PATH}" _DEP) \
    _BR("UTILS_PATH = ${SRC_PATH}" _UTILS) \
    _BR("TESTS_PATH = ${ROOT}" _TESTS) \
    _BR("COMP_C = ${shell find ${COMP_PATH} -name '*.c'}") \
    _BR("UTILS_C = ${shell find ${UTILS_PATH} -name '*.c'}") \
    _BR("TESTS_C = ${shell find ${TESTS_PATH} -name '*.c'}") \
    _BR("COMP_O = ${COMP_C:%.c=%.o}") \
    _BR("UTILS_O = ${UTILS_C:%.c=%.o}") \
    _BR("") \
    _BR("LD_LIBRARY_PATH += ${ROOT}") \
    _BR("CFLAGS += ${DEBUG} -ansi -pedantic -Wall -Wno-deprecated-declarations -I${SRC_PATH}") \
    _BR("")

#define PROJECT_MK \
    _BR("APP_NAME = $0") \
    _BR("")

#define APP_MAKEFILE \
    _BR("include project.mk") \
    _BR(_BR("include config.mk")) \
    _BR(_BR("all: ${APP_NAME}")) \
    _BR("${APP_NAME}: ${SRC_PATH}/${APP_NAME}.c ${COMP_O} ${UTILS_O}") \
    _TR("${CC} $^ -o $@ ${CFLAGS}") \
    _BR("%.o: %.c") \
    _TR("${CC} -c $< -o $@ ${CFLAGS}") \
    _BR("") \
    _BR("CFLAGS += -D STATIC") \
    _BR("static_library: lib${APP_NAME}.a") \
    _BR("") \
    _BR("lib${APP_NAME}.a: ${COMP_O} ${UTILS_O}") \
    _TR("ar -cvq $@ $^") \
    _BR("") \
    _BR("CFLAGS += -fPIC") \
    _BR("shared_library: lib${APP_NAME}.so") \
    _BR("") \
    _BR("lib${APP_NAME}.so: ${COMP_O} ${UTILS_O}") \
    _TR("${CC} -shared -o $@.1 $^") \
    _TR("ln -s $@.1 $@") \
    _BR("") \
    _BR("clean:") \
    _TR("${RM} ${APP_NAME} lib${APP_NAME}.*") \
    _BR("") \
    _BR(".INTERMEDIATE: ${COMP_O} ${UTILS_O}") \
    _BR(".PHONY: clean all") \
    _BR("")

#define APP_C \
    _BR("#include <utils/utils.h>") \
    _BR("#include <stdio.h>") \
    _BR("") \
    _BR("int main(int argc, char** argv){") \
    _TR("printf(\"Hello World\\n\");") \
    _TR("printf(\"5 + 6 = %d\\n\", add(5, 6));") \
    _TR("return 0;") \
    _BR(_BR("}"))

#define UTILS_UTILS_H \
    _BR("#ifndef UTILS_H") \
    _BR("#define UTILS_H") \
    _BR("int add(int, int);") \
    _BR(_BR("#endif"))

#define UTILS_UTILS_C \
    _BR("#include <utils/utils.h>") \
    _BR("") \
    _BR("int add(int a, int b){") \
    _TR("return a + b;") \
    _BR(_BR("}"))

#define TESTS_MAKEFILE \
    _BR("ROOT = ..") \
    _BR("include ../project.mk") \
    _BR("include ../config.mk") \
    _BR("") \
    _BR("TESTS_OUT := ${TESTS_C:%.c=%.out}") \
    _BR("all: ${TESTS_OUT}") \
    _BR("") \
    _BR("${TESTS_OUT}: %.out: %.c") \
    _TR("${MAKE} -C .. shared_library") \
    _TR("${CC} $< -o $@ ${CFLAGS} -l${APP_NAME}") \
    _BR("")

#define TEST_UTILS_C \
    _BR("#include <unitest.h>") \
    _BR("#include <stdio.h>") \
    _BR("#include <utils/utils.h>") \
    _BR("") \
    _BR("int main(void){") \
    _TR("TEST(Add function,") \
    _TR("\tT_ASSERT_NUM(add(-1, 1), 0);") \
    _TR("\tT_ASSERT_NUM(add(8, 2), 10);") \
    _TR(");") \
    _TR("return 0;") \
    _BR(_BR("}"))

#endif
