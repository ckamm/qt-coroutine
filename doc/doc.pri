defineReplace(targetPath) {
    return($$replace(1, /, $$QMAKE_DIR_SEP))
}

QDOC_BIN = $$targetPath($$[QT_INSTALL_BINS]/qdoc3)
HELPGENERATOR = $$targetPath($$[QT_INSTALL_BINS]/qhelpgenerator)

equals(QMAKE_DIR_SEP, /) {   # unix, mingw+msys
    QDOC = SRCDIR=$$PWD/../src OUTDIR=$$OUT_PWD/doc/html $$QDOC_BIN
} else:win32-g++* {   # just mingw
    # The lack of spaces in front of the && is necessary!
    QDOC = set SRCDIR=$$PWD&& set OUTDIR=$$OUT_PWD/doc/html&& $$QDOC_BIN
} else {   # nmake
    QDOC = set SRCDIR=$$PWD $$escape_expand(\n\t) \
           set OUTDIR=$$OUT_PWD/doc/html $$escape_expand(\n\t) \
           $$QDOC_BIN
}

QHP_FILE = $$OUT_PWD/doc/html/coroutine.qhp
QCH_FILE = $$OUT_PWD/share/doc/coroutine/coroutine.qch

html_docs.commands = $$QDOC $$PWD/coroutine.qdocconf
html_docs.depends += $$PWD/coroutine.qdocconf
html_docs.files = $$QHP_FILE

qch_docs.commands = $$HELPGENERATOR -o \"$$QCH_FILE\" $$QHP_FILE
qch_docs.depends += html_docs
qch_docs.files = $$QCH_FILE

unix:!macx {
    qch_docs.path = $$PREFIX/share/doc/coroutine
    qch_docs.CONFIG += no_check_exist
    INSTALLS += qch_docs
}

docs.depends = qch_docs
QMAKE_EXTRA_TARGETS += html_docs qch_docs docs

OTHER_FILES = $$PWD/coroutine.qdocconf
