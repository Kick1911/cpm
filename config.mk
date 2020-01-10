ROOT ?= .
SRC_PATH = ${ROOT}/src
COMP_PATH = ${SRC_PATH}/components
DEP_PATH = ${SRC_PATH}/dependents
UTILS_PATH = ${SRC_PATH}/utils
TESTS_PATH = ${ROOT}/tests
COMP_C = ${shell find ${COMP_PATH} -name '*.c'}
UTILS_C = ${shell find ${UTILS_PATH} -name '*.c'}
TESTS_C = ${shell find ${TESTS_PATH} -name '*.c'}
COMP_O = ${COMP_C:%.c=%.o}
UTILS_O = ${UTILS_C:%.c=%.o}
INCLUDE_PATH = ${ROOT}/include

LDFLAGS += -L${ROOT}
CFLAGS += ${DEBUG} -ansi -pedantic -Wall -Wno-deprecated-declarations -I${SRC_PATH} -I${INCLUDE_PATH}

