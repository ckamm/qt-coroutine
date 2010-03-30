# Expects target to be set and changes it

win32 | macx {
    RELEASEMODE=unspecified
    
    !build_pass {
        win32 {
            contains(CONFIG_WIN,debug) {
                RELEASEMODE=debug
            } else:contains(CONFIG_WIN,release) {
                RELEASEMODE=release
            }
        }

        # In Windows we want to build libraries in debug and release mode if the user
        # didn't select a version, and if Qt is built in debug_and_release.
        # This avoids problems for third parties as qmake builds debug mode by default
        # Silently disable unsupported configurations

        # MacOSX always builds debug and release libs when using mac framework

        CONFIG -= debug release debug_and_release build_all

        contains(RELEASEMODE,unspecified) {
            contains(QT_CONFIG,debug):contains(QT_CONFIG,release) | (macx:contains(QT_CONFIG,qt_framework):contains(TEMPLATE,.*lib)) {
                CONFIG += debug_and_release build_all
            } else {
                contains(QT_CONFIG,debug): CONFIG+=debug
                contains(QT_CONFIG,release): CONFIG+=release
            }
        } else {
            CONFIG += $$RELEASEMODE
        }
    }

    #suffix changes
    contains(TEMPLATE,.*lib) {
        TARGET=$$qtLibraryTarget($${TARGET})
    } 
}

DESTDIR=build

# build libraries as frameworks on OSX, omitting plugins.
mac:contains(QT_CONFIG,qt_framework) {
    CONFIG += lib_bundle absolute_library_soname
    FRAMEWORK_HEADERS.version = Versions
    FRAMEWORK_HEADERS.files = $${PUBLIC_HEADERS}
    FRAMEWORK_HEADERS.path = Headers
    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
}

