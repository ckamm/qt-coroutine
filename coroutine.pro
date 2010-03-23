TEMPLATE = subdirs
SUBDIRS = src

include(doc/doc.pri)

system(echo "INCLUDEPATH *= $$PWD/src" > use_coroutine.pri)
system(echo "LIBS *= -L$$OUT_PWD/lib" >> use_coroutine.pri)
system(echo "LIBS *= -l$$qtLibraryTarget(coroutine)" >> use_coroutine.pri)
system(echo "unix:LIBS *= -Wl,-rpath,$$OUT_PWD/lib" >> use_coroutine.pri)
