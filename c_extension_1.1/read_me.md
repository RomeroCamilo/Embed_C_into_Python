# how to run:

in terminal type in 'python3'

import cgetSum

cgetSum.cSum([4.1,2.2]) works

# TODO: ACCOUNT FOR THE DIFFERENT TYPES OF INPUT ARGUMENTS such as tuple and clean up code. (VERSION 1.1 UPDATE)

sources: (c-api)
https://docs.python.org/3/c-api/tuple.html

    PyObject* py_args; /* The arguments passed from Python */
    PyObject* py_list; /* The list or tuple argument */
    double sum = 0;
    Py_ssize_t size = 0;

    if (!PyArg_ParseTuple(args, "O|O", &py_list, &py_args)) {
        PyErr_SetString(PyExc_TypeError, "Invalid arguments. Expected a list or tuple, or multiple arguments.");
        return NULL;
    }

    if(py_list != NULL){ /* if argument is either a list or tuple */

        if (PyList_Check(py_list) || PyTuple_Check(py_list)) {
            size = PySequence_Size(py_list);
        } else {
            PyErr_SetString(PyExc_TypeError, "Invalid argument type. Expected a list or tuple.");
            return NULL;
        }

        for (Py_ssize_t i = 0; i < size; i++) {
            PyObject* item;
            if (PyList_Check(py_list)) {
                item = PyList_GetItem(py_list, i);
            } else {
                item = PyTuple_GetItem(py_list, i);
            }
            sum += PyFloat_AsDouble(item);
        }
    }

    return Py_BuildValue("d", sum);



    PyObject* py_args = PyTuple_New(PyTuple_Size(args)); /* Create a new tuple to hold the arguments */
        Py_ssize_t size = PyTuple_Size(args);

        for (Py_ssize_t i = 0; i < size; i++) {
            PyObject* arg = PyTuple_GetItem(args, i);
            PyTuple_SetItem(py_args, i, arg); /* Assign each argument to the new tuple */
            sum += PyFloat_AsDouble(arg);
        }

        Py_DECREF(py_args); /* Decrement reference count to release the new tuple */