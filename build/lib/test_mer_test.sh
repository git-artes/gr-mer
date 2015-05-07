#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/belza/Dropbox/software/gr-mer/lib
export PATH=/home/belza/Dropbox/software/gr-mer/build/lib:$PATH
export LD_LIBRARY_PATH=/home/belza/Dropbox/software/gr-mer/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-mer 
