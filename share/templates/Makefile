# Made with C Project Manager
# Author: Caswall Engelsman (mail@cengelsman.com)

include config.mk
include project.mk

ARCHIVE_FILES := ${APP_NAME:%=lib%.a}
LIBRARY_FILES := ${APP_NAME:%=lib%.so}
LIBRARY_FILES_VERSIONS := ${LIBRARY_FILES:%.so=%.so.${VERSION}}
DEP_PACKAGE_PATHS := ${DEPENDENCIES:%=${DEP_PATH}/%}
GITLAB_DEP := ${filter ${DEP_PATH}/gitlab/%,${DEP_PACKAGE_PATHS}}
LDFLAGS += ${DEPENDENCIES:%=-L${DEP_PATH}/%}
CFLAGS += ${DEPENDENCIES:%=-I${DEP_PATH}/%} -DVERSION='"${VERSION}"'
TEMP_OBJECTS_PATH := /tmp/${APP_NAME}_objs

TAR_NAME ?= ${word 1,${APP_NAME}}-${VERSION}.tar.gz
PACKAGE_CONTENTS ?= ${APP_NAME} ${ARCHIVE_FILES}

all: CFLAGS += -g3 -DLOG_LEVEL=1 -fsanitize=address -fsanitize=undefined
all: dep ${APP_NAME}

${APP_NAME}: %: ${SRC_PATH}/%.o ${COMP_O} ${UTILS_O}
	${call print,${GREEN}BIN $@}
	${Q}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS}

%.d: ;
%.o: %.c %.d
	${call print,${CYAN}CC $@}
	${Q}${CC} -MMD -MP -c $< -o $@ ${CFLAGS}

-include ${APP_NAME:%=${SRC_PATH}/%.d} ${COMP_O:%.o=%.d} ${UTILS_O:%.o=%.d}

static_library: dep ${ARCHIVE_FILES}

${TEMP_OBJECTS_PATH}:
	${Q}rm -rf $@
	${Q}mkdir -p $@

${ARCHIVE_FILES}: CFLAGS += -fPIE
${ARCHIVE_FILES}: LDFLAGS += -static

${ARCHIVE_FILES}: ${TEMP_OBJECTS_PATH} ${DEP_PACKAGE_PATHS} ${COMP_O} ${UTILS_O}
	${call print,${BROWN}AR $@}
	${eval DEP_ARCHIVES = ${shell find ${DEP_PACKAGE_PATHS} ${SYSTEM_DEP_ARCHIVES} -name '*.a'}}
	${Q}for arch in ${DEP_ARCHIVES} ; do \
		mkdir -p ${TEMP_OBJECTS_PATH}/`basename $$arch .a` ; \
		ar x $$arch --output ${TEMP_OBJECTS_PATH}/`basename $$arch .a` ; \
	done
	${Q}mkdir -p ${TEMP_OBJECTS_PATH}/project
	${Q}cp ${filter %.o,$^} ${TEMP_OBJECTS_PATH}/project/
	${call mangle_objects}
	${Q}ld -r -o ${APP_NAME}.o `find ${TEMP_OBJECTS_PATH} -name '*.o'`
	${Q}ar -cq $@ ${APP_NAME}.o
	${Q}nm $@ | grep -q "__fprintf_chk" && echo "Error: glibc __fprintf_chk found!" && return 1 || true
	${Q}rm ${APP_NAME}.o

shared_library: dep ${LIBRARY_FILES}

${LIBRARY_FILES}: %.so: %.so.${VERSION}
	${call print,${BRIGHT_CYAN}SYMLINK $@}
	${Q}ln -sf $< $@

${LIBRARY_FILES_VERSIONS}: CFLAGS += -fPIC

${LIBRARY_FILES_VERSIONS}: ${COMP_O} ${UTILS_O}
	${call print,${BRIGHT_MAGENTA}LIB $@}
	${Q}${CC} -shared -Wl,-soname,$@ -o $@ $^ ${LDFLAGS}

dep: ${GITLAB_DEP} preprocess

test_compile: CFLAGS += -g3 -DLOG_LEVEL=2
test_compile: dep ${TESTS_OUT}

test: test_compile
	${Q}set -e ; for exe in ${TESTS_OUT} ; do \
		valgrind --error-exitcode=1 --leak-check=full $$exe ; \
	done

${TESTS_OUT}: %.out: %.c ${COMP_O} ${UTILS_O}
	${call print,${GREEN}BIN $@}
	${Q}${CC} $^ -o $@ ${CFLAGS} ${LDFLAGS} ${TEST_LDFLAGS}

release:
	${call print,${GREEN}RELEASE v${VERSION}}
	${Q}git tag -a v${VERSION} -m 'Version ${VERSION}'
	${Q}git push origin v${VERSION}

${GITLAB_DEP}:
	${eval DEP_PREFIX = ${DEP_PATH}/gitlab}
	${eval DEP_CLEAN = ${DEP_PREFIX:./%=%}}
	${eval DEP_INFO = ${@:${DEP_CLEAN}/%=%}}
	${eval DEP_WORDS = ${subst /, ,${DEP_INFO}}}
	${eval DEP_PROJECT = ${word 1,${DEP_WORDS}}}
	${eval DEP_VERSION = ${word 2,${DEP_WORDS}}}
	${Q}mkdir -p $@
	${call gitlab_get_file,${DEP_PROJECT},${DEP_VERSION},$@}
	${Q}cd $@ && tar xvf dist.tar.gz

${LIB_PATH}/%.a:
	${call parse_lib_target}
	${Q}mkdir -p ${dir $@}
	${call get_archive,${LIB_ORG}/${LIB_PROJECT},${LIB_VERSION},${LIB_FILE},$@}
	${Q}ln -sf $(CURDIR)/$@ $(CURDIR)/${LIB_PATH}/${LIB_FILE}

${LIB_PATH}/%.h:
	${call parse_lib_target}
	${Q}mkdir -p ${dir $@}
	${Q}mkdir -p ${INCLUDE_PATH}
	${call get_header,${LIB_ORG}/${LIB_PROJECT},${LIB_VERSION},${LIB_FILE},$@}
	${Q}ln -sf $(CURDIR)/$@ $(CURDIR)/${INCLUDE_PATH}/${LIB_FILE}

prod: CFLAGS += ${PROD_CFLAGS}
prod: LDFLAGS += ${PROD_LDFLAGS}
prod: dep ${APP_NAME}

package: CFLAGS += ${PROD_CFLAGS}
package: LDFLAGS += ${PROD_LDFLAGS}
package: dep ${TAR_NAME}

${TAR_NAME}: ${PACKAGE_CONTENTS}
	${call print,${GREEN}TAR $@}
	${Q}mkdir -p ${DIST_PATH}
	${Q}cp -R $^ ${DIST_PATH}
	${Q}tar -czf $@ -C ${DIST_PATH} .

install: ${INSTALL_STEPS}

install_binary: ${INSTALL_PATH}/bin/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME} ${INSTALL_PATH}/bin/

install_static: ${ARCHIVE_FILES} ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/
	${Q}cp ${ARCHIVE_FILES} ${INSTALL_PATH}/lib/

install_shared: ${APP_NAME:%=lib%.so.${VERSION}} ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/ ${INSTALL_PATH}/lib/
	${call print,${GREEN}INSTALL $<}
	${Q}cp ${APP_NAME:%=${SRC_PATH}/%.h} ${INSTALL_PATH}/include/
	${Q}cp ${APP_NAME:%=lib%.so.${VERSION}} ${INSTALL_PATH}/lib/

install_share_folder: ${APP_NAME:%=${INSTALL_PATH}/share/%}
	${call print,${GREEN}INSTALL $<}
	${Q}cp -R ${SHARE_PATH}/* ${APP_NAME:%=${INSTALL_PATH}/share/%}

${INSTALL_PATH}/%:
	${call print,${GREEN}MKDIR $@}
	${Q}mkdir -p $@

clean:
	${call print,${BRIGHT_CYAN}CLEAN ${APP_NAME}}
	${Q}${RM} ${APP_NAME} ${TAR_NAME} ${APP_NAME:%=${SRC_PATH}/%.o} ${APP_NAME:%=${SRC_PATH}/%.d} ${APP_NAME:%=lib%.*} ${COMP_O} ${UTILS_O} ${COMP_O:%.o=%.d} ${UTILS_O:%.o=%.d}
	${Q}${RM} -R ${DIST_PATH}
	${call print,${BRIGHT_CYAN}CLEAN tests}
	${Q}${RM} ${TESTS_OUT}

.PHONY: preprocess package test test_compile clean prod all install install_share_folder install_shared install_binary install_static static_library shared_library release dep
