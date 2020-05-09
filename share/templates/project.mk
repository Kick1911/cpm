CPM = cpm
APP_NAME = ${shell ${CPM} json name}
VERSION = ${shell ${CPM} json version}
LDFLAGS += ${shell ${CPM} json dependencies}
INSTALL_PATH = ${shell ${CPM} json install_path}
${eval CFLAGS += ${shell ${CPM} json cflags}}