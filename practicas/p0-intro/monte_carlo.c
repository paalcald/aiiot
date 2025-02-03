#include "Python.h"

static PyObject *integra_mc(PyObject *self, PyObject *args)
{
    PyObject *fun;
    double a;
    double b;
    PyObject *result = NULL;
    int num_puntos;
    double r;
    double ymax = 0;
    int count = 0;
    double x;
    if (PyArg_ParseTuple(args, "OddI", &fun, &a, &b, &num_puntos))
    {
        if (!PyCallable_Check(fun))
        {
            return NULL;
        }
        double *y = (double *)calloc(num_puntos, sizeof(double));
        for (int i = 0; i < num_puntos; i++)
        {
            r = (double)rand() / ((double)RAND_MAX / (b - a)) + a;
            y[i] = PyFloat_AsDouble(PyObject_CallFunction(fun, "f", r));
            if (ymax < y[i])
            {
                ymax = y[i];
            }
        }
        for (int i = 0; i < num_puntos; i++)
        {
            x = (double)rand() / ((double)RAND_MAX / ymax);
            if (x < y[i])
            {
                count++;
            }
        }
        free(y);
        result = Py_BuildValue("f", ((double)count) * (b - a) * (ymax) / (double)num_puntos);
        return result;
    }
    return result;
}

static PyMethodDef MonteCarloMethods[] = {
    {"integra_mc", integra_mc, METH_VARARGS, "Calcula la integral"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef montecarlo = {
    PyModuleDef_HEAD_INIT,
    "monte_carlo", /* name of module */
    "todo docs",   /* module documentation, may be NULL */
    -1,            /* size of per-interpreter state of the module,
                      or -1 if the module keeps state in global variables. */
    MonteCarloMethods};

PyMODINIT_FUNC
PyInit_monte_carlo(void)
{
    return PyModule_Create(&montecarlo);
}
