# please excuse the totally not a makefile

cd "$(dirname "$0")"

AP='../src'

pushd ../misc
python3 write_build_version.py
popd

pushd ../can
python3 canvars.py
popd

pushd ../pics
python3 piclist.py
popd

# build the application as a shared library
clang -DPLATFORM_PC -Wall -dynamiclib -o libapp.so $AP/app.c $AP/../can/canvar_defs.c $AP/canvar.c $AP/warn.c $AP/drive.c $AP/version.c $AP/modes.c platform_pc.c

# build the python module with CFFI
LIBRARY_PATH="." python3 pc_app_build.py
