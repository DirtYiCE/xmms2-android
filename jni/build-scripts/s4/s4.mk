include $(CLEAR_VARS)

S4_SOURCE := $(S4_TOP)/src/lib

LOCAL_SRC_FILES := \
    $(S4_SOURCE)/cond.c \
    $(S4_SOURCE)/const.c \
    $(S4_SOURCE)/fetchspec.c \
    $(S4_SOURCE)/index.c \
    $(S4_SOURCE)/lock.c \
    $(S4_SOURCE)/log.c \
    $(S4_SOURCE)/oplist.c \
    $(S4_SOURCE)/pattern.c \
    $(S4_SOURCE)/relation.c \
    $(S4_SOURCE)/result.c \
    $(S4_SOURCE)/resultset.c \
    $(S4_SOURCE)/sourcepref.c \
    $(S4_SOURCE)/transaction.c \
    $(S4_SOURCE)/uuid.c \
	$(S4_SOURCE)/s4.c \
    $(S4_SOURCE)/val.c

LOCAL_C_INCLUDES := $(GLIB_INCLUDES) $(S4_SOURCE) $(S4_INCLUDE)

LOCAL_MODULE := s4

include $(BUILD_STATIC_LIBRARY)
