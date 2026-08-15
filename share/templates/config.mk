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

CFLAGS += ${DEBUG} -std=c89 -pedantic
CFLAGS += -Wall -Wextra -Wconversion -Wshadow -Wstrict-prototypes -Wformat-security -Wformat=2 -Werror -Wno-deprecated-declarations -Wno-variadic-macros
CFLAGS += -D_FORTIFY_SOURCE=2 -pipe
CFLAGS += -I${SRC_PATH} -I${INCLUDE_PATH}

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
	${Q}curl -sSL -f 'https://github.com/${1}/releases/download/${2}/${3}' \
		-o ${4}
endef

define get_header
	${Q}curl -sSL -f 'https://raw.githubusercontent.com/${1}/${2}/src/${3}' \
		-o ${4}
endef

define gitlab_get_file
	${Q}curl -sSL -f 'https://gitlab.com/api/v4/projects/${1}/packages/generic/dist/v${2}/dist.tar.gz' -O --output-dir ${3}
endef

define parse_lib_target
	${eval LIB_WORDS = ${subst /, ,$@}}
	${eval LIB_ORG = ${word 2,${LIB_WORDS}}}
	${eval LIB_PROJECT = ${word 3,${LIB_WORDS}}}
	${eval LIB_VERSION = ${word 4,${LIB_WORDS}}}
	${eval LIB_FILE = ${word 5,${LIB_WORDS}}}
endef

define mangle_objects
	${Q}for obj in `find ${TEMP_OBJECTS_PATH} -name '*.o' ! -path '${TEMP_OBJECTS_PATH}/project/*'` ; do \
		for symbol in `nm --defined-only -j -g $$obj` ; do \
			salt=`tr -dc 'A-Za-z0-9' </dev/urandom | head -c 4` ; \
			for x in ${TEMP_OBJECTS_PATH}/project/*.o $$obj ; do \
				objcopy --redefine-sym $$symbol="${APP_NAME}_$$salt$$symbol" $$x ; \
			done \
		done \
	done
endef
