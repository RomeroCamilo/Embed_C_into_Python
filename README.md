# Embed_C_into_Python
This repo contains a C extension module 'cGetSum' which can be utilized in Python, which allows Python to have access to functions with C/C++ speed and high performance.

#HOW TO COMPILE on Ubuntu Linux:

sudo apt-get install python3-dev

in the terminal, type: python3 setup.py build

a folder named build should be created, that will contain another folder starting with lib.linux with a .so file inside.

create a test.py file.

import the name of that .so only for example, 'import cgetSum'

you will now be able to run the file python file 'python3 test.py'

code is complete so you can look at how it works.

