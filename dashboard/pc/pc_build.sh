# please excuse the totally not a makefile

cd "$(dirname "$0")"

AP='../src'

../src/pre_build.sh

# build the application as a shared library
clang -DPLATFORM_PC -Wall -dynamiclib -o libapp.so ../src/*.c ../src_gen/*.c platform_pc.c

# build the python module with CFFI
LIBRARY_PATH="." python3 pc_app_build.py
