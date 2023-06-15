# PURPOSE OF FILE: COMPILES AND LINKS TO THE RIGHT LIBRARIES IN THE 'Python.h' file. #

from distutils.core import setup, Extension

sum_module = Extension('cgetSum', sources = ['csum.c']) 

setup (name = 'SumExtension',
       version = '1.0',
       description= 'This package returns the sum of an array in C.',
       ext_modules = [sum_module],
       #sources = ['function.c'],
)