#!/bin/bash

set_environment () {

  echo " Set environment variables"

  # Here, define your installation paths, versions etc.
  gccversion="$(gcc -dumpversion)"
  INSTALLD="$(pwd)/LHAPDF6"
  VERSION="6.3.0"
  LOCAL=$INSTALLD
  export LHAPATH=$LOCAL/share/LHAPDF
  export LD_LIBRARY_PATH=$BOOST/lib:$LD_LIBRARY_PATH

}

run () {

  workd=$(pwd)

  echo " Download LHAPDF $VERSION"
  mkdir $INSTALLD
  cd $INSTALLD
  wget http://www.hepforge.org/archive/lhapdf/LHAPDF-${VERSION}.tar.gz

  echo " Unpack LHAPDF"
  tar xvzf LHAPDF-${VERSION}.tar.gz

  echo " Enter LHAPDF directory"
  cd LHAPDF-${VERSION}/

  echo " Configure LHAPDF"
  ./configure CXXFLAGS="-static-libstdc++" --prefix=$LOCAL --bindir=$LOCAL/bin \
  --datadir=$LOCAL/share --libdir=$LOCAL/lib --disable-python \
  --enable-static

  echo " Compile LHAPDF"
  make

  echo " Install LHAPDF"
  make install

  echo "copy index and conf file"
  cd $INSTALLD
  index="$(find . -name 'pdfsets.index')"
  cp $index $INSTALLD/share/LHAPDF/
  conf="$(find . -name 'lhapdf.conf')"
  cp $conf $INSTALLD/share/LHAPDF/

  echo " Get LHAPDF sets"
  cd $INSTALLD/share/LHAPDF

  # Get MMHT2014
  wget http://lhapdfsets.web.cern.ch/lhapdfsets/current/MMHT2014nlo68cl.tar.gz

  ls -1 *.tar.gz | while read line; do tar xvfz $line; done

  echo " Finished LHAPDF installation"
  cd $workd

}

set_environment "$@"
run "$@"

