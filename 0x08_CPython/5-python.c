#include <Python.h>
#include <stdio.h>

void print_python_int(PyObject *p)
{
    unsigned long int result = 0;
    Py_ssize_t size, i;
    long int factor = 1;
    PyLongObject *py_long;

    if (!PyLong_Check(p))
    {
        printf("Invalid Int Object\n");
        return;
    }

    py_long = (PyLongObject *)p;
    size = Py_SIZE(p);

    if (size < 0)
    {
        size = -size;
        factor = -1;
    }

    for (i = 0; i < size; i++)
    {
        if (i > 0)
        {
            if ((unsigned long int)py_long->ob_digit[i] > (ULONG_MAX >> (i * PyLong_SHIFT)))
            {
                printf("C unsigned long int overflow\n");
                return;
            }
        }
        result += (unsigned long int)(py_long->ob_digit[i]) << (i * PyLong_SHIFT);
    }

    if (factor == -1)
    {
        printf("-%lu\n", result);
    }
    else
    {
        printf("%lu\n", result);
    }
}
