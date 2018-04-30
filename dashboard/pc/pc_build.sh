# please excuse the totally not a makefile

cd "$(dirname "$0")"

AP='../src'

../src/pre_build.sh

# build the python module with CFFI
python3 pc_app_build.py
