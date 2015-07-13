### GR-MER, QAM Modulation error measurements

** An open source implementation of QAM Modulation error measurements in GNU Radio** 

In particular, we implement a set of probes for measurement the Modulation Error Rate (MER) and other measurements that impacts on MER like: system target error (STE), carrier suppression error (CS), amplitude imbalance error (AI), quadrature error (QE) and phase jitter error (PJ). 

This set of measurements is based on the definitions of the following document:

Digital Video Broadcasting (DVB); Measurement guidelines for DVB systems, ETSI, May 1997, pages 27-33.

While the previous document is specific for DTV, the set of measurements proposed in this document are general for any digital modulation system. Considering the estimation procedures implemented in this software, the set of probes can be used on any QAM system. 

**Notes and examples**

We have implemented  one GNU Radio block for each measurement: MER, STE,CS, AI, QE and PJ,  and one block whose output are  all main measurements.
The input to each block are the complex samples before the constellation demapping at the receiver and the output is an update of the corresponding measurement for each new sample. 

- **Examples**
In the directory gr-mer/examples/ there are to examples mer.grc and mer_all.grc. In both examples we use the hardware impairments  block of GNU Radio in order to introduce different errors and test the measurement probes.
In the first example we use one probe block for each measurement and in the second one we use the block with all main measurements.

**Build instructions**

    git clone https://github.com/git-artes/gr-mer.git  
    cd gr-mer  
    mkdir build  
    cd build  
    cmake ../  
    make && sudo make install  


If installed for the first time:
    sudo ldconfig

IIE Instituto de Ingeniería Eléctrica
Facultad de Ingeniería
Universidad de la República
Montevideo, Uruguay
http://iie.fing.edu.uy/investigacion/grupos/artes/

Please refer to the LICENSE file for contact information and further credits.

