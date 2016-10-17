#!/usr/bin/env python
#!/usr/bin/python2.7


from   pyevtk.hl import pointsToVTK
import numpy as np
import os
import time
import xml.etree.ElementTree as ET
import subprocess
import sys
import pygtk
import matplotlib
matplotlib.use('GTKAgg')
import matplotlib.pyplot as plt
from   matplotlib.patches import Ellipse



# functions to load binary
def loadBinary(file_name):
	file  = open(file_name, "rb") 
	file.seek(0, os.SEEK_SET)
	array = np.fromfile(file, dtype=np.float64)
	file.close()
	return array

def loadBinaryInt(file_name):
	file  = open(file_name, "rb") 
	file.seek(0, os.SEEK_SET)
	array = np.fromfile(file, dtype=np.bool_)
	file.close()
	return array

# create dictionary of relevant parameter values
def loadParameters():
	tree  	   = ET.parse("parameters/parameters.xml")
	root  	   = tree.getroot()
	N 	  	   = int(root.find("N").text)
	dt 		   = float(root.find("DT").text)
	nTime 	   = int(float(root.find("TIME").text)/float(root.find("DT").text))
	length     = int(root.find("LENGTH").text)
	width      = int(root.find("WIDTH").text)
	seed_no	   = root.find("SEED_NUMBER").text
	parameters = {'N': N, 'dt': dt, 'nTime': nTime, 'length': length, 'width': width, 'seed': seed_no}
	return parameters

# convert data from binary to vtk format
def convertData(parameters, jump_print, data_keep):
	cwd       = os.getcwd()
	path_data = cwd + "/data/"
	path_vtk  = cwd + "/visualization/dataVTK/"
	seed_name = "Seed" + parameters['seed']
	N         = parameters['N']
	ext 	  = ".dat"

	# create directory for VTK data under "visualization" if it does not already exist
	if (not os.path.isdir(path_vtk)):
		os.makedirs(path_vtk)
	# delete contents of directory otherwise
	else:
		os.chdir(path_vtk)
		os.system("perl -e 'for(<*>){((stat)[9]<(unlink))}'")
		os.chdir('..')

	# create z-coordinates
	z = np.zeros(N)

	for k in range(0, parameters['nTime']-1, jump_print):
		extension = seed_name + "_" + str(k).zfill(9) + ext
		# load data
		x         = loadBinary(   path_data + "ParticleX_" + extension)[0:N]
		y         = loadBinary(   path_data + "ParticleY_" + extension)[0:N]   
		# multiply by 1 to implicitly cast bool array as int
		s         = loadBinaryInt(path_data + "ParticleS_" + extension)[0:N]*1
	
		# write data as VTK
		pointsToVTK(path_vtk + "particles_" + str(k).zfill(9), x, y, z, data = {"Coop_def" : s})
		
		##########
		# debug file conversion by writing csv
		# np.savetxt(folderVTK + "particles_" + str(k).zfill(9) + ".csv", np.column_stack( (x, y, z, s) ), delimiter=",", fmt='%.14f')
		##########

	# clear directory of binary data
	if (data_keep == 0):
		os.chdir(path_data)
		os.system("perl -e 'for(<*>){((stat)[9]<(unlink))}'")
		os.chdir('..')

# sub functions for plots
def init_scatter_plot(parameters, x, y, color=1):
    myFig 	= plt.figure()
    ax 		= plt.gca()
    ellipse =  Ellipse(xy=(0, 0), width=8.0, height=3, edgecolor='olive', fc='y', lw=2, zorder=0)
    ax.add_patch(ellipse)
    pltScat = plt.scatter(x, y, s=100, alpha=0.6, c=color, vmin=0, vmax=1)  # c='g'
    title 	= plt.title('Time t=' + '{:04.2f}'.format(0),
                         horizontalalignment='center', fontsize=20)
    plt.axis([-parameters['length'], 2*parameters['length'], -parameters['width'], 2*parameters['width']])
    plt.axes().set_aspect('equal', 'box')
    plt.xlabel(r'$x$', fontsize=25)
    plt.ylabel(r'$y$', fontsize=25)
    plt.draw()
    return (pltScat, title)

def update_scatter_plot(pltScat, title, x, y, time, color=1):
    pltScat.set_offsets(np.transpose(np.vstack([x, y])))
    title.set_text('Time t=' + '{:04.2f}'.format(time) + ', N=' + str(len(x)))
    pltScat.set_array(color)

# plot data
def plotData(parameters, jump_print, data_conv):
	cwd       = os.getcwd()
	path_data = cwd + "/data/"
	path_vtk  = cwd + "/visualization/dataVTK/"
	seed_name = "Seed" + parameters['seed']
	N         = parameters['N']
	dt 		  = parameters['dt']
	ext 	  = ".dat"
	
	# draw first plot
	extension = seed_name + "_" + str(0).zfill(9) + ext
	# load data
	x         = loadBinary(   path_data + "ParticleX_" + extension)[0:N]
	y         = loadBinary(   path_data + "ParticleY_" + extension)[0:N]   
	# multiply by 1 to implicitly cast bool array as int
	s         = loadBinaryInt(path_data + "ParticleS_" + extension)[0:N]*1

	plt.ion()
	plt.show()
	pltScat, title = init_scatter_plot(parameters, x, y, s)

	# plot rest of data
	for t in range(1, parameters['nTime']-1, jump_print):
		extension = seed_name + "_" + str(t).zfill(9) + ext
		# load data
		x         = loadBinary(   path_data + "ParticleX_" + extension)[0:N]
		y         = loadBinary(   path_data + "ParticleY_" + extension)[0:N]   
		# multiply by 1 to implicitly cast bool array as int
		s         = loadBinaryInt(path_data + "ParticleS_" + extension)[0:N]*1

		update_scatter_plot(pltScat, title, x, y, t*dt, s)
		plt.draw()
		time.sleep(.01)



# main execution
if __name__ == "__main__":
	# execute pedestrianDM cpp code
	tic = time.time()
	os.chdir('bin')
	process_pedestriancpp = subprocess.Popen("./pedestrianDM", stdout=subprocess.PIPE)
	output, error = process_pedestriancpp.communicate()
	os.chdir('..')
	toc = time.time() - tic

	# check for errors
	if (error is not None):
		print "Simulation returned error message: ", error
	else:
		print "Simulation complete.", '\t\t', "Elapsed time: ", round(toc,2), " seconds."

	# check if any arguments were passed to script
	if (not sys.argv):
		# default values are ones
		data_conv  = 1
		data_keep  = 1
		jump_print = 1
		data_plot  = 1
	# first input is whether to plot data
	elif (len(sys.argv) == 1):
		data_conv  = int(sys.argv[1])
		data_keep  = 1
		jump_print = 1
		data_plot  = 1
	# second input is whether to keep data after plotting
	elif (len(sys.argv) == 2):
		data_conv  = int(sys.argv[1])
		data_keep  = int(sys.argv[2])
		jump_print = 1
		data_plot  = 1
	# third input is number of frames to skip
	elif (len(sys.argv) == 3):
		data_conv  = int(sys.argv[1])
		data_keep  = int(sys.argv[2])
		jump_print = int(sys.argv[3])
		data_plot  = 1
	else:
		data_conv  = int(sys.argv[1])
		data_keep  = int(sys.argv[2])
		jump_print = int(sys.argv[3])
		data_plot  = int(sys.argv[4])

	# convert data from binary
	if (data_conv == 1):
		tic = time.clock()
		parameters = loadParameters()
		convertData(parameters, jump_print, data_keep)
		toc = time.clock() - tic
		print "Data conversion complete.", '\t', "Elapsed time: ", round(toc,2), " seconds."

	# plot data
	if (data_plot == 1):
		if (data_conv == 0):
			parameters = loadParameters()
		plotData(parameters, jump_print, data_conv)

