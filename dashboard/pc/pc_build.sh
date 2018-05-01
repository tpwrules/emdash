# please excuse the totally not a makefile

cd "$(dirname "$0")"

python3 ../build_src_gen.py

# build the python module with CFFI
python3 pc_app_build.py
