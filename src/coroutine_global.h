#ifndef COROUTINE_GLOBAL_H
#define COROUTINE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COROUTINE_LIBRARY)
#  define COROUTINE_EXPORT Q_DECL_EXPORT
#else
#  define COROUTINE_EXPORT Q_DECL_IMPORT
#endif

#endif // COROUTINE_GLOBAL_H
