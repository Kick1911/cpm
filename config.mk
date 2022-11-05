ROOT ?= .
SRC_PATH = ${ROOT}/src
COMP_PATH = ${SRC_PATH}/components
DEP_PATH = ${SRC_PATH}/dependents
UTILS_PATH = ${SRC_PATH}/utils
TESTS_PATH = ${ROOT}/tests
INCLUDE_PATH = ${ROOT}/include
SHARE_PATH = ${ROOT}/share
LIB_PATH = ${ROOT}/lib

define get_extension
	${shell find ${1} -name '*.${2}'}
endef

##### C Language #####
COMP_C = ${call get_extension,${COMP_PATH},c}
UTILS_C = ${call get_extension,${UTILS_PATH},c}
SRC_C = ${call get_extension,${SRC_PATH},c}
TESTS_C = ${call get_extension,${TESTS_PATH},c}
COMP_O = ${COMP_C:%.c=%.o}
UTILS_O = ${UTILS_C:%.c=%.o}
SRC_O = ${SRC_C:%.c=%.o}

APP_FILE_DEPENDENCIES_c = ${SRC_O} ${UTILS_O} ${COMP_O}
CLEANUP_FILES_c = ${APP_NAME:%=lib%.*} ${APP_FILE_DEPENDENCIES_c}
LDFLAGS += -L${ROOT} -L${LIB_PATH}
CFLAGS += ${DEBUG} -ansi -pedantic -Wall -Wno-deprecated-declarations -I${SRC_PATH} -I${INCLUDE_PATH}
COMPILE_FLAGS_c = ${CFLAGS} ${LDFLAGS}

##### Haskell #####
COMP_HS = ${call get_extension,${COMP_PATH},hs}
UTILS_HS = ${call get_extension,${UTILS_PATH},hs}
SRC_HS = ${call get_extension,${SRC_PATH},hs}

COMP_HI = ${COMP_HS:%.hs=%.hi}
UTILS_HI = ${UTILS_HS:%.hs=%.hi}
SRC_HI = ${SRC_HS:%.hs=%.hi}

APP_FILE_DEPENDENCIES_hs = ${SRC_HS} ${UTILS_HS} ${COMP_HS}
CLEANUP_FILES_hs = ${SRC_HI} ${UTILS_HI} ${COMP_HI} ${SRC_HS:%.hs=%.o} ${UTILS_HS:%.hs=%.o} ${COMP_HS:%.hs=%.o}
COMPILE_FLAGS_hs =

ifneq ($(V),1)
Q := @
# Do not print "Entering directory ...".
MAKEFLAGS += --no-print-directory
endif

# 1: Dependencies
# 2: Binary file name
define compile_c
	${Q}${CC} ${1} -o ${2} ${COMPILE_FLAGS_c}
endef

define compile_hs
	${Q}ghc ${1} -o ${2} ${COMPILE_FLAGS_hs}
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
