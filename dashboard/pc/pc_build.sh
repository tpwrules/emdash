# please excuse the totally not a makefile

cd "$(dirname "$0")"

AP='../src'

pushd ../can
python3 canvars.py
popd

pushd ../pics
python3 piclist.py
popd

# build the application as a shared library
clang -DPLATFORM_PC -dynamiclib -o libapp.so $AP/app.c $AP/platform_pc.c $AP/../can/canvar_defs.c $AP/canvar.c $AP/warn.c

# build the python module with CFFI
LIBRARY_PATH="." python3 pc_app_build.py