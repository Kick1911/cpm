ROOT ?= .
SRC_PATH = ${ROOT}/src
COMP_PATH = ${SRC_PATH}/components
DEP_PATH = ${SRC_PATH}/dependents
UTILS_PATH = ${SRC_PATH}/utils
TESTS_PATH = ${ROOT}/tests
INCLUDE_PATH = ${ROOT}/include
SHARE_PATH = ${ROOT}/share
LIB_PATH = ${ROOT}/lib

COMP_C = ${shell find ${COMP_PATH} -name '*.c'}
UTILS_C = ${shell find ${UTILS_PATH} -name '*.c'}
TESTS_C = ${shell find ${TESTS_PATH} -name '*.c'}
COMP_O = ${COMP_C:%.c=%.o}
UTILS_O = ${UTILS_C:%.c=%.o}

LDFLAGS += -L${ROOT} -L${LIB_PATH}

CFLAGS += ${DEBUG} -ansi -pedantic -Wall -Wno-deprecated-declarations -I${SRC_PATH} -I${INCLUDE_PATH}

ifneq ($(V),1)
Q := @
# Do not print "Entering directory ...".
MAKEFLAGS += --no-print-directory
endif

define print
	@echo '  ${1}'
endef

define download
curl 'https://app.smartfile.com/api/2/path/data/${1}/${2}' \
	-H 'Authorization: Basic bFFoUVk0ek10SzRQbk11WjBYUjdFenQyOW9pSWZEOm9WclcxcWJDNlA4OWQyZjBuRTVrUElYaHczTGRvcQ==' \
	-o ${3}/${2}
endef

define upload
curl -X POST  'https://app.smartfile.com/api/2/path/data/${1}' \
	-H 'Authorization: Basic bFFoUVk0ek10SzRQbk11WjBYUjdFenQyOW9pSWZEOm9WclcxcWJDNlA4OWQyZjBuRTVrUElYaHczTGRvcQ==' \
	-H 'Content-Type: multipart/form-data; charset=utf-8'   -F 'file=@${2}'
endef

define mkdir
curl -X PUT  'https://app.smartfile.com/api/2/path/oper/mkdir/${1}' \
	-H 'Authorization: Basic bFFoUVk0ek10SzRQbk11WjBYUjdFenQyOW9pSWZEOm9WclcxcWJDNlA4OWQyZjBuRTVrUElYaHczTGRvcQ=='
endef
