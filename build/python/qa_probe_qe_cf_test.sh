#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/belza/Dropbox/software/gr-mer/python
export PATH=/home/belza/Dropbox/software/gr-mer/build/python:$PATH
export LD_LIBRARY_PATH=/home/belza/Dropbox/software/gr-mer/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/belza/Dropbox/software/gr-mer/build/swig:$PYTHONPATH
/usr/bin/python2 /home/belza/Dropbox/software/gr-mer/python/qa_probe_qe_cf.py 
