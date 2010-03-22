TEMPLATE = lib
TARGET = coroutine

HEADERS += coroutine.h
SOURCES += coroutine.cpp

INCLUDEPATH += .
DEPENDPATH += .

contains(QMAKE_CXX,g++) {
    win32 {
        # will fail for 64 bit win!
        SOURCES += \
            backend/switchstack_gcc_32_win.cpp \
            backend/initializestack_32.cpp
    }

    mac {
        CONFIG(x86_64) {
            SOURCES += \
                backend/switchstack_gcc_64_linux_mac.s \
                backend/initializestack_64_linux_mac.cpp
        } else {
            SOURCES += \
                backend/switchstack_gcc_32_linux_mac.s \
                backend/initializestack_32.cpp
        }
    }
    !win32:!mac {
        contains(QMAKE_CFLAGS,-m64) {
            SOURCES += \
                backend/switchstack_gcc_64_linux_mac.s \
                backend/initializestack_64_linux_mac.cpp
        } else {
            SOURCES += \
                backend/switchstack_gcc_32_linux_mac.s \
                backend/initializestack_32.cpp
        }
    }
}
win32:contains(QMAKE_CXX,cl) {
    # will fail for 64 bit win!
    SOURCES += \
        backend/switchstack_msvc_32.cpp \
        backend/initializestack_32.cpp
}
