CPM = ./cpm
APP_NAME = ${shell ${CPM} json name}
VERSION = ${shell ${CPM} json version}
LDFLAGS += ${shell ${CPM} json dependencies}
CONFIG_INSTALL_PATH = ${shell ${CPM} json install_path}