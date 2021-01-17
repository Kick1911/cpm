include config.mk
include project.mk

all: dep ${APP_NAME}

${APP_NAME}: ${SRC_PATH}/${APP_NAME}.o ${COMP_O} ${UTILS_O}
	${call print,BIN $@}
	${Q}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

%.o: %.c
	${call print,CC $< -> $@}
	${Q}${CC} -c $< -o $@ ${CFLAGS}

static_library: lib${APP_NAME}.a.${VERSION}

lib${APP_NAME}.a.${VERSION}: ${COMP_O} ${UTILS_O}
	${call print,AR $@}
	${Q}cd ${LIB_PATH}; ar -x *.a.[0-9].[0-9].[0-9]
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
	${eval LIB_NAME = ${@F}}
	${eval NO_VERSION = ${shell echo ${LIB_NAME} | awk -v RS=' ' 'match($$#0, "(.+).[0-9].[0-9].[0-9]", a) {print a[1]}'}}
	${eval PROJECT_NAME = ${basename ${NO_VERSION:lib%=%}}}
	${call download,${PROJECT_NAME},${LIB_NAME},${LIB_PATH}}
	${call download,${PROJECT_NAME},${PROJECT_NAME}.h,${INCLUDE_PATH}}
	${Q}ln -sf ${LIB_NAME} ${LIB_PATH}/${NO_VERSION}

register_app:
	${call mkdir,${APP_NAME}}

upload_static: lib${APP_NAME}.a.${VERSION}
	${call upload,${APP_NAME},$<}
	${call upload,${APP_NAME},${SRC_PATH}/${APP_NAME}.h}

install_binary: ${INSTALL_PATH}/bin/
	${call print,INSTALL $<}
	${Q}cp ${APP_NAME} ${INSTALL_PATH}/bin/

install_static: lib${APP_NAME}.a.${VERSION} ${SRC_PATH}/${APP_NAME}.h ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,INSTALL $<}
	${Q}cp ${SRC_PATH}/${APP_NAME}.h ${INSTALL_PATH}/include/
	${Q}cp lib${APP_NAME}.a.${VERSION} ${INSTALL_PATH}/lib/

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

.PHONY: clean all set_pic install_share_folder install_shared install_binary install_static
