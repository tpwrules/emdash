# please excuse the totally not a makefile

cd "$(dirname "$0")"

APP_PATH='../src'

# build the application as a shared library
clang -DPLATFORM_PC -dynamiclib -o libapp.so $APP_PATH/app.c

# build the python module with CFFI
LIBRARY_PATH="." python3 app_build.py