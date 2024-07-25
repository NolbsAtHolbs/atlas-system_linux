#include <Python.h>
#include <stdio.h>
#include <string.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);
void print_python_float(PyObject *p);

void print_python_list(PyObject *p)
{
    Py_ssize_t size, allocated, i;
    PyObject *elem;
    PyListObject *list = NULL;
    const char *type = NULL;

    if (!PyList_Check(p))
	{
        fprintf(stderr, "[ERROR] Invalid List Object\n");
        return;
    }

    size = ((PyVarObject *)p)->ob_size;
    allocated = ((PyListObject *)p)->allocated;
    list = (PyListObject *)p;

    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %zd\n", size);
    printf("[*] Allocated = %zd\n", allocated);

    for (i = 0; i < size; i++)
    {
        elem = list->ob_item[i];
        type = elem->ob_type->tp_name;
        printf("Element %zd: %s\n", i, type);
        if (strcmp(type, "bytes") == 0)
            print_python_bytes(elem);
        else if (strcmp(type, "float") == 0)
            print_python_float(elem);
    }
}

void print_python_bytes(PyObject *p)
{
    Py_ssize_t size, i;
    const char *str;

    printf("[.] bytes object info\n");

    if (!PyBytes_Check(p)) {
        printf("  [ERROR] Invalid Bytes Object\n");
        return;
    }

    size = ((PyVarObject *)p)->ob_size;
    str = ((PyBytesObject *)p)->ob_sval;

    printf("  size: %zd\n", size);
    printf("  trying string: %s\n", str);
    size = size < 10 ? size : 10;
    printf("  first %zd bytes: ", size);
    for (i = 0; i < size; i++)
    {
        printf("%02x", (unsigned char)str[i]);
        if (i + 1 < size)
            printf(" ");
    }
    printf("\n");
}

void print_python_float(PyObject *p)
{
    double value;

    printf("[.] float object info\n");

    if (!PyFloat_Check(p))
	{
        printf("  [ERROR] Invalid Float Object\n");
        return;
    }

    value = ((PyFloatObject *)p)->ob_fval;
    printf("  value: %.1f\n", value);
}
