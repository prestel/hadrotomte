./installLHAPDF6.sh

cd pythia8243
./configure --with-lhapdf6=$(pwd)/../LHAPDF6
make && make install
cd ..

cd apfelxx;
cd build;
cmake -DCMAKE_INSTALL_PREFIX=$(pwd) ..;
make ; make install ;
cd ../../

cd dire;
./configure --with-pythia8=$(pwd)/../pythia8243;
make install
