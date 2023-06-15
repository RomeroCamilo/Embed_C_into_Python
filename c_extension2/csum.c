#include <python3.10/Python.h>

/* Function that will get the sum of a list of numbers in C */
double cFastSum(const double* numbers, int size){

        double sum = 0;
    
        for (int i = 0; i < size; i++) {
            sum += numbers[i];
        }

        return sum;

}

/* 
 * self points to the Module Object. args are the arguments 
 * that get passed into the python script later. 
 */

/*
 * This is the name of the function you will call when accessing the module in a python file.
 */

/* TODO: FULLY DOCUMENT AND UNDERSTAND WHAT THIS FUNCTION DOES LINE BY LINE */
static PyObject* cSum(PyObject* self, PyObject* args){ 

        PyObject* py_list; /* The list the user has input in args */
        

        if (!PyArg_ParseTuple(args, "O", &py_list)) {
            return NULL;
        }

        Py_ssize_t size = PyList_Size(py_list); /* Getting length of the list */
        if (size == -1) {
            PyErr_SetString(PyExc_TypeError, "Argument must be a list");
            return NULL;
        }

        double* numbers = (double*)malloc(size * sizeof(double)); /* Allocating space for numbers*/
        if (!numbers) { 
            PyErr_SetString(PyExc_MemoryError, "Memory allocation failed");
            return NULL;
        }

        for (Py_ssize_t i = 0; i < size; i++) {
            PyObject* item = PyList_GetItem(py_list, i); /* Getting current iteration value */
            
            if (!PyFloat_Check(item)) { /* Will check if list has valid type values. */
                free(numbers);
                PyErr_SetString(PyExc_TypeError, "List must contain only float values");
                return NULL; /* End program due to invalid data type being found */
            }

            numbers[i] = PyFloat_AsDouble(item);
        }

        double result = cFastSum(numbers, size); /* Call our function after test cases passed */
        free(numbers); /* After storing result, free numbers from memory allocation */

        return Py_BuildValue("d", result);
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