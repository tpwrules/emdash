# import the shared library made by CFFI
from _app import lib, ffi

# call entry point
lib.app_entry()