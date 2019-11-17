ROOT = ..
include ../config.mk
UTIL_TEST := $(UTIL:%=test_%.out)
UTIL_OBJS := $(UTIL_CODE:%.c=%.o)
APPS_TEST := $(APPS:%=test_%.out)
APPS_OBJS := $(APPS_CODE:%.c=%.o)

all: $(UTIL_TEST)

$(UTIL_TEST): %.out : $(UTIL_OBJS) %.c
	$(CC) $^ -o $@ $(CFLAGS)

$(APPS_TEST): test_%.out : $(UTIL_OBJS) $(APPS_PATH)/%.o test_%.c
	$(CC) $^ -o $@ $(CFLAGS)

$(UTIL_OBJS) $(SRC_OBJS): %.o : %.c
	$(MAKE) $(@:../%.o=%.o) -C ..

.PHONY: all
