import ruamel.yaml as yaml
import numpy as np
import matplotlib.pyplot as plt
import MatplotlibSettings
from scipy.interpolate import make_interp_spline, BSpline

# Loada data
data = np.loadtxt("PDFExpansion.dat")

muv = [10, 80, 91.188, 100, 1000]
ndt = 1000

for i in range(len(muv)):
    x = data[i*ndt:(i+1)*ndt,3]
    explo   = data[i*ndt:(i+1)*ndt,4]
    expnlo  = data[i*ndt:(i+1)*ndt,5]
    expnnlo = data[i*ndt:(i+1)*ndt,6]
    res     = data[i*ndt:(i+1)*ndt,7]

    f, (ax1, ax2) = plt.subplots(2, 1, sharex = "all", gridspec_kw = dict(width_ratios = [1], height_ratios = [3, 1]))
    plt.subplots_adjust(wspace = 0, hspace = 0)

    ax1.set_title(r"\textbf{$\mu_R=\mu_F=91.188$ GeV, $\mu = " + str(muv[i]) + "$ GeV}")
    ax1.set(ylabel = r"\textbf{$xf_{d}(x, \mu = " + str(muv[i]) + "$ GeV$)$}")
    ax1.set_xlim([0.00001, 1])
    ax1.set_xscale("log")
    ax1.plot(x, explo,   label = r"\textbf{LO expansion}",      color = "red")
    ax1.plot(x, expnlo,  label = r"\textbf{NLO expansion}",     color = "blue")
    ax1.plot(x, expnnlo, label = r"\textbf{NNLO expansion}",    color = "green")
    ax1.plot(x, res,     label = r"\textbf{Resummed (LHAPDF)}", color = "black", ls = "--")

    ax1.legend(fontsize = 18)

    ax2.set_xlabel(r"\textbf{$x$}")
    ax2.set_ylabel(r"\textbf{Ratio to Res.}", fontsize = 16)
    ax2.set_ylim([0.7, 1.3])
    ax2.plot(x, res/res,     label = r"\textbf{Resummed (LHAPDF)}", color = "black", lw = 1.5, ls = "--")
    ax2.plot(x, explo/res,   label = r"\textbf{LO expansion}",      color = "red")
    ax2.plot(x, expnlo/res,  label = r"\textbf{NLO expansion}",     color = "blue")
    ax2.plot(x, expnnlo/res, label = r"\textbf{NNLO expansion}",    color = "green")

    plt.savefig("PDFExpansion_mu_" + str(muv[i]) + ".pdf")
    plt.close()

