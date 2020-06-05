CPM = cpm
APP_NAME = ${shell cd ${ROOT} && ${CPM} json name}
VERSION = ${shell cd ${ROOT} && ${CPM} json version}
DEPENDENCIES = ${shell cd ${ROOT} && ${CPM} json dependencies}
INSTALL_PATH = ${shell cd ${ROOT} && ${CPM} json install_path}
${eval CFLAGS += ${shell cd ${ROOT} && ${CPM} json cflags}}

STATIC_DEP = ${shell echo ${DEPENDENCIES} | awk -v RS=' ' 'match($$0, "lib(.+).a.[0-9].[0-9].[0-9]", a) {print a[1]}'}
SHARED_DEP = ${shell echo ${DEPENDENCIES} | awk -v RS=' ' 'match($$0, "lib(.+).so.[0-9].[0-9].[0-9]", a) {print a[1]}'}
LDFLAGS += ${STATIC_DEP:%=-l%} ${SHARED_DEP:%=-l%}