APP_NAME = cpm
VERSION = 0.14.3
PACKAGE_CONTENTS := ${APP_NAME}

PROD_CFLAGS = -O3 -static
INSTALL_PATH = /opt
CFLAGS += -DINSTALL_PATH=${INSTALL_PATH}

# Projects
UNITEST_PROJECT_ID = 11728468

STATIC_DEP =
SHARED_DEP = c

DEPENDENCIES += gitlab/${UNITEST_PROJECT_ID}/0.2.0

LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}
INSTALL_STEPS = install_binary

project: all
preprocess: ${SRC_PATH}/project_map.h

${SRC_PATH}/project_map.h: ${ROOT}/cpack.py ${shell find ${SHARE_PATH}/templates}
	${call print,${YELLOW}PREPROCESS $@}
	${Q}${ROOT}/cpack.py > ${SRC_PATH}/project_map.h

.PHONY: project
