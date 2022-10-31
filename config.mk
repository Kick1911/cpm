ROOT ?= .
SRC_PATH = ${ROOT}/src
COMP_PATH = ${SRC_PATH}/components
DEP_PATH = ${SRC_PATH}/dependents
UTILS_PATH = ${SRC_PATH}/utils
TESTS_PATH = ${ROOT}/tests
INCLUDE_PATH = ${ROOT}/include
SHARE_PATH = ${ROOT}/share
LIB_PATH = ${ROOT}/lib

##### C Language #####
COMP_C = ${shell find ${COMP_PATH} -name '*.c'}
UTILS_C = ${shell find ${UTILS_PATH} -name '*.c'}
SRC_C = ${shell find ${SRC_PATH} -name '*.c'}
TESTS_C = ${shell find ${TESTS_PATH} -name '*.c'}
COMP_O = ${COMP_C:%.c=%.o}
UTILS_O = ${UTILS_C:%.c=%.o}
SRC_O = ${SRC_C:%.c=%.o}
APP_FILE_DEPENDENCIES = ${SRC_O} ${UTILS_O} ${COMP_O}

LDFLAGS += -L${ROOT} -L${LIB_PATH}

CFLAGS += ${DEBUG} -ansi -pedantic -Wall -Wno-deprecated-declarations -I${SRC_PATH} -I${INCLUDE_PATH}

##### Haskell #####
COMP_HS = ${shell find ${COMP_PATH} -name '*.hs'}
UTILS_HS = ${shell find ${UTILS_PATH} -name '*.hs'}
SRC_HS = ${shell find ${SRC_PATH} -name '*.hs'}

ifneq ($(V),1)
Q := @
# Do not print "Entering directory ...".
MAKEFLAGS += --no-print-directory
endif



# 1: Dependencies
# 2: Binary file name
define compile_c
	${Q}${CC} ${1} -o ${2} ${CFLAGS} ${LDFLAGS}
endef

define compile_hs
	${Q}ghc ${1} -o ${2} ${CFLAGS}
endef



GREEN = \033[0;32m
BROWN = \033[0;33m
YELLOW = \033[1;33m
MAGENTA = \033[0;35m
BRIGHT_MAGENTA = \033[1;35m
CYAN = \033[0;36m
BRIGHT_CYAN = \033[1;36m
NC = \033[0m

define print
	@echo -e '  ${1}${NC}'
endef

define get_archive
curl -L -f 'https://github.com/${1}/releases/download/${2}/${3}' \
	-o ${4}
endef

define get_header
curl -L -f 'https://raw.githubusercontent.com/${1}/${2}/src/${3}.h' \
	-o ${4}/${3}.h
endef

