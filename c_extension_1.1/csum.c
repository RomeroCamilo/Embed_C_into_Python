#include <python3.10/Python.h>
#include <stdlib.h>

/* 
 * self points to the Module Object. args are the arguments 
 * that get passed into the python script later. 
 */

/*
 * cSum is the name of the function you will call when accessing the module in a python file.
 */


static PyObject* cSum(PyObject* self, PyObject* args) {

    double sum = 0;
    
    Py_ssize_t amt_args = PyTuple_Size(args);

    if((PyTuple_Check(args) || PyList_Check(args)) && amt_args == 1){

        PyObject* py_list; /* The list or tuple argument */

        Py_ssize_t size = 0;
        
        sum = 0;

        if (!PyArg_ParseTuple(args, "O", &py_list)) {
            PyErr_SetString(PyExc_TypeError, "Invalid arguments. Expected a list or tuple, or multiple arguments.");
            return NULL;
        }

        if(py_list != NULL){ /* if argument is either a list or tuple */

            PyObject* single_arg = PyTuple_GetItem(args, 0);
            if (PyNumber_Check(single_arg)) { /* Check if the single argument is just 1 number. */
                sum = PyFloat_AsDouble(single_arg); 
            }
            else{ /* If its not a single argument, then it is a list or float */
                if (PyList_Check(py_list) || PyTuple_Check(py_list)) {
                    size = PySequence_Size(py_list);
                } else {
                    PyErr_SetString(PyExc_TypeError, "Invalid argument type. Expected a list or tuple or number.");
                    return NULL;
                }

                for (Py_ssize_t i = 0; i < size; i++) { /* Geting the sum of list or tuple */
                    PyObject* item = PySequence_GetItem(py_list, i);
                    
                    sum += PyFloat_AsDouble(item);
                }
            }
        }
    }
    else{ /* If contains multiple arguments */

        PyObject* py_args = PyTuple_New(PyTuple_Size(args)); /* Create a new tuple to hold the arguments */
        Py_ssize_t size = PyTuple_Size(args);

        for (Py_ssize_t i = 0; i < size; i++) {
            PyObject* arg = PyTuple_GetItem(args, i);
            PyTuple_SetItem(py_args, i, arg); /* Assign each argument to the new tuple */
            sum += PyFloat_AsDouble(arg);
        }

        Py_DECREF(py_args); /* Decrement reference count to release the new tuple */
        
    }
    
    return Py_BuildValue("d", sum);
}

/* 
 * Meta information that tells the Python interpreter 
 * about the methods defined in the module.
 */
static PyMethodDef mainMethods[] = {

        {"cSum",cSum,METH_VARARGS,"Calculate the sum of a list in C"}, 
        {NULL,NULL,0,NULL}

};

/* Module definition */
static struct PyModuleDef cgetSum = {

        PyModuleDef_HEAD_INIT ,
        "cgetSum" , /* give module name here */
        "Python interface for calculating the sum of a list in C." , /* module docstring */
        -1 , /* Amount of memory needed to store the programs state */
        mainMethods

};

/* Gets executed when the Python program gets called by a script to import the module */
PyMODINIT_FUNC PyInit_cgetSum(void){
        return PyModule_Create(&cgetSum);
}