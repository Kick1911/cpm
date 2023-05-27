APP_NAME = cpm
VERSION = 0.11.0
TAR_NAME = dist-${VERSION}.tar.gz
INSTALL_PATH = /opt
CFLAGS += -DINSTALL_PATH=${INSTALL_PATH}

# Projects
JSON_PROJECT_ID = 16394907
UNITEST_PROJECT_ID = 11728468

STATIC_DEP = json
SHARED_DEP =

DEPENDENCIES = gitlab/${JSON_PROJECT_ID}/0.0.2
DEPENDENCIES += gitlab/${UNITEST_PROJECT_ID}/0.10.0

LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}
INSTALL_STEPS = install_share_folder install_binary
