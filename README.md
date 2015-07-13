<div id="readme" class="blob instapaper_body">
    <article class="markdown-body entry-content" itemprop="mainContentOfPage"><h3><a id="user-content-mer-in-gnu-radio" class="anchor" href="#mer-in-gnu-radio" aria-hidden="true"><span class="octicon octicon-link"></span></a>QAM Modulation error measurements in GNU Radio</h3>

<p><strong>An open source implementation of QAM Modulation error measurements in GNU Radio.</strong></p>

<p>In particular, we implement a set of probes for measurement the Modulation Error Rate (MER) and other measurements that impacts on MER like: system target error (STE), carrier suppression error (CS), amplitude imbalance error (AI), quadrature error (QE) and phase jitter error (PJ). 
This set of measurements is based on the definitions of the following document: Digital Video Broadcasting (DVB);
Measurement guidelines for DVB systems, ETSI, May 1997, pages 27-33.  </p>

<p>While the previous document is specific for DTV, the set of measurements proposed in this document are general for any digital modulation system. Considering the estimation procedures implemented in this software, the set of probes can be used on any QAM system. </p>

<p><strong>Notes and examples</strong></p>

<p>We have implemented  one GNU Radio block for each measurement: MER, STE,CS, AI, QE and PJ,  and one block whose output are  all main measurements.
The input to each block are the complex samples before the constellation demapping at the receiver and the output is an update of the corresponding measurement for each new sample. </p>

<ul>
<li><strong>Examples.</strong>  </li>
In the directory gr-mer/examples/ there are to examples mer.grc and mer_all.grc. In both examples we use the hardware impairments  block of GNU Radio in order to introduce different errors and test the measurement probes.
In the first example we use one probe block for each measurement and in the second one we use the block with all main measurements.
</ul>

<p><strong>Build instructions</strong></p>

<pre><code>git clone https://github.com/git-artes/gr-mer.git  
cd gr-mer  
mkdir build  
cd build  
cmake ../  
make &amp;&amp; sudo make install  
</code></pre>

<p>If installed for the first time:<br>
    sudo ldconfig  </p>

<p>IIE Instituto de Ingeniería Eléctrica<br>
Facultad de Ingeniería<br>
Universidad de la República<br>
Montevideo, Uruguay<br>
<a href="http://iie.fing.edu.uy/investigacion/grupos/artes/">http://iie.fing.edu.uy/investigacion/grupos/artes/</a>  </p>

<p>Please refer to the LICENSE file for contact information and further credits.   </p>
</article>
  </div>


