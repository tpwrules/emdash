# please excuse the totally not a makefile

cd "$(dirname "$0")"

AP='../src'

# build the application as a shared library
clang -DPLATFORM_PC -dynamiclib -o libapp.so $AP/app.c $AP/platform_pc.c

# build the python module with CFFI
LIBRARY_PATH="." python3 app_build.py