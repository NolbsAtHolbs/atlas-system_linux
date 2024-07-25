#include <Python.h>
#include <stdio.h>

void print_python_string(PyObject *p)
{
    printf("[.] string object info\n");

    if (!PyUnicode_Check(p))
    {
        printf("  [ERROR] Invalid String Object\n");
        return;
    }

    Py_ssize_t length = PyUnicode_GET_LENGTH(p);
    const char *type;

    if (PyUnicode_IS_COMPACT_ASCII(p))
        type = "compact ascii";
    else
        type = "compact unicode object";

    printf("  type: %s\n", type);
    printf("  length: %zd\n", length);
    printf("  value: %ls\n", PyUnicode_AS_UNICODE(p));
}
