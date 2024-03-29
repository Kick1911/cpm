ROOT ?= .
SRC_PATH = ${ROOT}/src
COMP_PATH = ${SRC_PATH}/components
DEP_PATH = ${ROOT}/dependents
UTILS_PATH = ${SRC_PATH}/utils
TESTS_PATH = ${ROOT}/tests
INCLUDE_PATH = ${ROOT}/include
SHARE_PATH = ${ROOT}/share
LIB_PATH = ${ROOT}/lib
DIST_PATH = ${ROOT}/dist

COMP_C := ${shell find ${COMP_PATH} -name '*.c'}
UTILS_C := ${shell find ${UTILS_PATH} -name '*.c'}
TESTS_C := ${shell find ${TESTS_PATH} -name 'test_*.c'}
TESTS_OUT := ${TESTS_C:%.c=%.out}
COMP_O := ${COMP_C:%.c=%.o}
UTILS_O := ${UTILS_C:%.c=%.o}

LDFLAGS += -L${ROOT} -L${LIB_PATH}

CFLAGS += ${DEBUG} -std=c89 -pedantic -Wall -Wno-deprecated-declarations
CFLAGS +=  -D_FORTIFY_SOURCE=2 -pipe -Werror=format-security
CFLAGS += -Werror -Wno-variadic-macros
CFLAGS += -I${SRC_PATH} -I${INCLUDE_PATH}
PROD_CFLAGS = -O3

ifneq ($(V),1)
Q := @
# Do not print "Entering directory ...".
MAKEFLAGS += --no-print-directory
endif

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
curl -L -f 'https://raw.githubusercontent.com/${1}/${2}/src/${3}' \
	-o ${4}
endef

define gitlab_get_file
	${Q}curl -L -f 'https://gitlab.com/api/v4/projects/${1}/packages/generic/dist/v${2}/dist.tar.gz' -O --output-dir ${3}
endef
