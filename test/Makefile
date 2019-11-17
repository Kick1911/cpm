ROOT = ..
include ../config.mk
UTIL_TEST := $(UTIL:%=test_%.out)
UTIL_OBJS := $(UTIL_CODE:%.c=%.o)

all: $(UTIL_TEST)

$(UTIL_TEST): %.out : $(UTIL_OBJS) %.c
	$(CC) $^ -o $@ $(CFLAGS)

$(UTIL_OBJS): %.o : %.c
	$(MAKE) $(@:../%.o=%.o) -C ..

.PHONY: all
