#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <listobject.h>
#include <object.h>

void print_python_list(PyObject *p)
{
    Py_ssize_t size, i, allocated;
    PyListObject *list;

    if (!PyList_Check(p))
    {
        fprintf(stderr, "Invalid List Object\n");
        return;
    }

    list = (PyListObject *)p;
    size = PyList_Size(p);
    allocated = list->allocated;

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %zd\n", size);
    printf("[*] Allocated = %zd\n", allocated);

    for (i = 0; i < size; i++)
    {
        printf("Element %zd: %s\n", i, Py_TYPE(PyList_GetItem(p, i))->tp_name);
    }
}
