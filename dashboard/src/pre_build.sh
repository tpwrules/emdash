# please excuse the totally not a makefile

PATH=/usr/local/bin:$PATH

cd "$(dirname "$0")"

pushd ../misc
python3 write_build_version.py
popd

pushd ../can
python3 canvars.py
popd

pushd ../pics
python3 piclist.py
popd
