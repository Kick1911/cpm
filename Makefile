include config.mk
include project.mk

all: dep ${APP_NAME}

${APP_NAME}: ${SRC_PATH}/${APP_NAME}.o ${COMP_O} ${UTILS_O}
	${call print,BIN $@}
	${Q}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

%.o: %.c
	${call print,CC $< -> $@}
	${Q}${CC} -c $< -o $@ ${CFLAGS}

static_library: lib${APP_NAME}.a

lib${APP_NAME}.a: ${COMP_O} ${UTILS_O}
	${call print,AR $@}
	${Q}cd ${LIB_PATH}; ar -x *.a || true
	${Q}ar -cq $@ $^ ${shell find ${LIB_PATH} -name '*.o'}

set_pic:
	${eval CFLAGS += -fPIC}

shared_library: set_pic lib${APP_NAME}.so

lib${APP_NAME}.so: ${COMP_O} ${UTILS_O}
	${call print,LIB $@.${VERSION}}
	${Q}${CC} -shared -Wl,-soname,$@ -o $@.${VERSION} $^ ${LDFLAGS}
	${call print,'SYMLINK $@'}
	${Q}ln -sf $@.${VERSION} $@

dep: ${DEPENDENCIES:%=${LIB_PATH}/%}

${LIB_PATH}/%:
	${eval WORD_LIST = ${subst /, ,$@}}
	${eval ORG = ${word 2, ${WORD_LIST}}}
	${eval PROJECT = ${word 3, ${WORD_LIST}}}
	${eval VERSION = ${word 4, ${WORD_LIST}}}
	${eval LIB_NAME = ${word 5, ${WORD_LIST}}}
	${eval NAME = ${word 1, ${subst ., ,${LIB_NAME:lib%=%}}}}

	${Q}mkdir -p ${dir $@}
	${call get_archive,${ORG}/${PROJECT},${VERSION},${LIB_NAME},$@}
	${call get_header,${ORG}/${PROJECT},${VERSION},${NAME},${INCLUDE_PATH}}
	${Q}ln -sf ${shell pwd}/$@ ${shell pwd}/${LIB_PATH}/${LIB_NAME}

install_binary: ${INSTALL_PATH}/bin/
	${call print,INSTALL $<}
	${Q}cp ${APP_NAME} ${INSTALL_PATH}/bin/

install_static: lib${APP_NAME}.a ${SRC_PATH}/${APP_NAME}.h ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,INSTALL $<}
	${Q}cp ${SRC_PATH}/${APP_NAME}.h ${INSTALL_PATH}/include/
	${Q}cp lib${APP_NAME}.a ${INSTALL_PATH}/lib/

install_shared: lib${APP_NAME}.so.${VERSION} ${SRC_PATH}/${APP_NAME}.h ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,INSTALL $<}
	${Q}cp ${SRC_PATH}/${APP_NAME}.h ${INSTALL_PATH}/include/
	${Q}cp lib${APP_NAME}.so.${VERSION} ${INSTALL_PATH}/lib/

install_share_folder: ${INSTALL_PATH}/share/${APP_NAME}
	${call print,INSTALL $<}
	${Q}cp -R ${SHARE_PATH}/* ${INSTALL_PATH}/share/${APP_NAME}

${INSTALL_PATH}/%:
	${call print,MKDIR $@}
	${Q}mkdir -p $@

clean:
	${call print,CLEAN ${APP_NAME}}
	${Q}${MAKE} -C tests clean
	${Q}${RM} ${APP_NAME} ${SRC_PATH}/${APP_NAME}.o lib${APP_NAME}.* ${COMP_O} ${UTILS_O}

.PHONY: clean all set_pic install_share_folder install_shared install_binary install_static dep
