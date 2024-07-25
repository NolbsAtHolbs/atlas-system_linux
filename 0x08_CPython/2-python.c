#define PY_SSIZE_T_CLEAN

#include <Python.h>

void print_python_bytes(PyObject *p);

void print_python_list(PyObject *p)
{
    Py_ssize_t size, i, allocated;
    PyListObject *list;

    if (!PyList_Check(p))
    {
        fprintf(stderr, "[ERROR] Invalid List Object\n");
        return;
    }

    list = (PyListObject *)p;
    size = ((PyVarObject *)p)->ob_size;
    allocated = list->allocated;

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %zd\n", size);
    printf("[*] Allocated = %zd\n", allocated);

    for (i = 0; i < size; i++)
    {
        PyObject *item = list->ob_item[i];
        const char *type = item->ob_type->tp_name;
        printf("Element %zd: %s\n", i, type);
        if (strcmp(type, "bytes") == 0)
        {
            print_python_bytes(item);
        }
    }
}

void print_python_bytes(PyObject *p)
{
    Py_ssize_t size, i;
    char *string;

    printf("[.] bytes object info\n");

    if (!PyBytes_Check(p))
    {
        printf("  [ERROR] Invalid Bytes Object\n");
        return;
    }

    size = ((PyVarObject *)p)->ob_size;
    string = ((PyBytesObject *)p)->ob_sval;

    printf("  size: %zd\n", size);
    printf("  trying string: %s\n", string);
    printf("  first %zd bytes:", size < 10 ? size + 1 : 10);

    for (i = 0; i < size + 1 && i < 10; i++)
    {
        printf(" %02x", (unsigned char)string[i]);
    }

    printf("\n");
}
