APP_NAME = cpm
VERSION = 0.12.0
PACKAGE_CONTENTS := ${APP_NAME} ${SHARE_PATH}

PROD_CFLAGS = -O3 -static
INSTALL_PATH = /opt
CFLAGS += -DINSTALL_PATH=${INSTALL_PATH}

# Projects
JSON_PROJECT_ID = 16394907
UNITEST_PROJECT_ID = 11728468

STATIC_DEP = json
SHARED_DEP = c

DEPENDENCIES += gitlab/${JSON_PROJECT_ID}/0.0.2
DEPENDENCIES += gitlab/${UNITEST_PROJECT_ID}/0.2.0

LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}
INSTALL_STEPS = install_share_folder install_binary

project: all
preprocess: ${SRC_PATH}/project_map.h

${SRC_PATH}/project_map.h: ${ROOT}/cpack.py
	${ROOT}/cpack.py > ${SRC_PATH}/project_map.h

.PHONY: project
