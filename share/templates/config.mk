ROOT ?= .
SRC_PATH = ${ROOT}/src
COMP_PATH = ${SRC_PATH}/components
DEP_PATH = ${SRC_PATH}/dependents
UTILS_PATH = ${SRC_PATH}/utils
TESTS_PATH = ${ROOT}/tests
INCLUDE_PATH = ${ROOT}/include
SHARE_PATH = ${ROOT}/share
LIB_PATH ?= ${shell pwd}/lib

COMP_C = ${shell find ${COMP_PATH} -name '*.c'}
UTILS_C = ${shell find ${UTILS_PATH} -name '*.c'}
TESTS_C = ${shell find ${TESTS_PATH} -name '*.c'}
COMP_O = ${COMP_C:%.c=%.o}
UTILS_O = ${UTILS_C:%.c=%.o}

LDFLAGS += -L${ROOT}

CFLAGS += ${DEBUG} -ansi -pedantic -Wall -Wno-deprecated-declarations -I${SRC_PATH} -I${INCLUDE_PATH}

ifneq ($(V),1)
Q := @
# Do not print "Entering directory ...".
MAKEFLAGS += --no-print-directory
endif

define print
	@echo '  ${1}'
endef

