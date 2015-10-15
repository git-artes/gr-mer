title: gr-mer
brief: An open source implementation of QAM Modulation error measurements in GNU Radio. 
tags: # Tags are arbitrary, but look at CGRAN what other authors are using
  - MER
  - QAM
  - Measurements

author: 
  - Pablo Belzarena <belza@fing.edu.uy>
  - Federico "Larroca" La Rocca 
  - Gabriel Gomez Sena 
  - Pablo Flores Guridi 
  - Victor Gonzalez Barbone 

copyright_owner: 
  - Pablo Belzarena 
  - Federico "Larroca" La Rocca  
  - Gabriel Gomez Sena 
  - Pablo Flores Guridi 
  - Victor Gonzalez Barbone 

license:  
repo: 
website: http://iie.fing.edu.uy/investigacion/grupos/artes/gr-isdbt/ 
icon: http://iie.fing.edu.uy/investigacion/grupos/artes/gr-isdbt/icono_gr-mer.png  
--- 
An open source implementation of QAM Modulation error measurements in GNU Radio

In particular, we implement a set of probes for the measurement of the Modulation Error Rate (MER) and other measurements that impact on MER, such as system target error (STE), carrier suppression error (CS), amplitude imbalance error (AI), quadrature error (QE) and phase jitter error (PJ).

This set of measurements is based on the definitions of the following document:
-Digital Video Broadcasting (DVB); Measurement guidelines for DVB systems, ETSI, May 1997, pages 27-33.

While the previous document is specific for DTV, the set of measurements proposed in this document is general for any digital modulation system. Considering the estimation procedures implemented in this software, the set of probes can be used on any QAM system.


