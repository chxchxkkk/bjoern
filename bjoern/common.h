#ifndef __common_h__
#define __common_h__

#include <Python.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define GIL_LOCK(n) PyGILState_STATE _gilstate_##n = PyGILState_Ensure()
#define GIL_UNLOCK(n) PyGILState_Release(_gilstate_##n)

#define LENGTH(array) (sizeof(array)/sizeof(array[0]))
#define ADDR_FROM_MEMBER(ptr, strct, mem) (strct*)((size_t)ptr - (size_t)(&(((strct*)NULL)->mem)));

#define TYPECHECK2(what, check_type, print_type, errmsg_name, failure_retval) \
    if(!what || !check_type##_Check(what)) { \
        PyErr_Format(\
            PyExc_TypeError, \
            errmsg_name " must be of type %s, not %s", \
            print_type##_Type.tp_name, \
            Py_TYPE(what ? what : Py_None)->tp_name \
        ); \
        return failure_retval; \
    }
#define TYPECHECK(what, type, ...) TYPECHECK2(what, type, type, __VA_ARGS__);

typedef PyObject* PyKeywordFunc(PyObject* self, PyObject* args, PyObject *kwargs);

typedef enum {
    HTTP_BAD_REQUEST = 400,
    HTTP_SERVER_ERROR = 500
} http_status;

#ifdef DEBUG
    #define DBG(request, ...) \
        do{ \
            printf("[DEBUG Req %ld] ", request->id); \
            printf(__VA_ARGS__); \
            printf("\n"); \
        } while(0)
#else
    #define DBG(...) do{}while(0)
#endif

#endif
