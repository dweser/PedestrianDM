#!/usr/bin/env python
#!/usr/bin/python2.7


# run simulation
def runSimulation():
	# check if cpp code is compiled
	if (not os.path.isfile("bin/pedestrianDM")):
		print "Compiling..."
		process_make  = subprocess.Popen("make", stdout=subprocess.PIPE)
		output, error = process_make.communicate()
		# check for compilation errors
		if (error is not None):
			sys.exit("Compilation failed. Error: " + error)
		else:
			print "Compilation complete."

	# execute pedestrianDM cpp code
	os.chdir('bin')
	process_pedestriancpp = subprocess.Popen("./pedestrianDM", stdout=subprocess.PIPE)
	output, error         = process_pedestriancpp.communicate()
	os.chdir('..')
	return error

# functions to load binary
def loadBinary(file_name):
	# load module within function to avoid python module issues
	import numpy as np

	file  = open(file_name, "rb") 
	file.seek(0, os.SEEK_SET)
	array = np.fromfile(file, dtype=np.float64)
	file.close()
	return array

def loadBinaryInt(file_name):
	# load module within function to avoid python module issues
	import numpy as np
	
	file  = open(file_name, "rb") 
	file.seek(0, os.SEEK_SET)
	array = np.fromfile(file, dtype=np.bool_)
	file.close()
	return array

# convert data from binary to vtk format
def convertData(parameters, jump_print, data_keep):
	# load modules within function to avoid python module issues
	import numpy as np
	from pyevtk.hl import pointsToVTK
	
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
		os.chdir('../..')

	# create z-coordinates
	z = np.zeros(N)

	for k in xrange(0, parameters['nTime']-1, jump_print):
		extension = seed_name + "_" + str(k).zfill(9) + ext
		# load data
		x         = loadBinary(   path_data + "particleX_" + extension)[0:N]
		y         = loadBinary(   path_data + "particleY_" + extension)[0:N]   
		# multiply by 1 to implicitly cast bool array as int
		s         = loadBinaryInt(path_data + "particleS_" + extension)[0:N]*1
	
		# write data as VTK
		pointsToVTK(path_vtk + "particles_" + str(k).zfill(9), x, y, z, data = {"Coop_def" : s})

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

# plot data
def animateData(parameters, jump_print, data_conv):
	# load module within function to avoid python module issues
	import matplotlib.pyplot     as plt
	from   matplotlib.animation  import FuncAnimation

	# define our update function for FuncAnimation
	def update_scatter_plot(frame_number):
		# load module within function to avoid python module issues
		import numpy as np
		
		extension = seed_name + "_" + str(frame_number*jump_print).zfill(9) + ext
		# load data
		x         = loadBinary(   path_data + "particleX_" + extension)[0:N]
		y         = loadBinary(   path_data + "particleY_" + extension)[0:N]   
		# multiply by 1 to implicitly cast bool array as int
		s         = loadBinaryInt(path_data + "particleS_" + extension)[0:N]*1

		plt_sct.set_offsets(np.transpose(np.vstack([x, y])))
		title.set_text('Time t=' + '{:04.2f}'.format(frame_number*jump_print*dt))
		plt_sct.set_array(s)

    # parameters
	cwd       = os.getcwd()
	path_data = cwd + "/data/"
	path_vtk  = cwd + "/visualization/dataVTK/"
	seed_name = "Seed" + parameters['seed']
	N         = parameters['N']
	dt 		  = parameters['dt']
	ext 	  = ".dat"
	
	## initialization of plot ##
	extension = seed_name + "_" + str(0).zfill(9) + ext
	# load initial data
	x         = loadBinary(   path_data + "particleX_" + extension)[0:N]
	y         = loadBinary(   path_data + "particleY_" + extension)[0:N]   
	# multiply by 1 to implicitly cast bool array as int
	s         = loadBinaryInt(path_data + "particleS_" + extension)[0:N]*1

	# initial figure
	fig 	= plt.figure()
	ax 		= plt.gca()
	plt_sct = plt.scatter(x, y, s=100, alpha=0.6, c=s, vmin=0, vmax=1)
	title 	= plt.title('Time t=' + '{:04.2f}'.format(0), horizontalalignment='center', fontsize=20)
	plt.axis([-parameters['length'], 2*parameters['length'], -parameters['width'], 2*parameters['width']])
	plt.axes().set_aspect('equal', 'box')
	plt.xlabel(r'$x$', fontsize=25)
	plt.ylabel(r'$y$', fontsize=25)

	# create animation and display it
	animation = FuncAnimation(fig, update_scatter_plot, frames=parameters['nTime']/jump_print, interval=1)
	plt.show()



# main execution
if __name__ == "__main__":
	import os 
	import os.path
	import time
	import xml.etree.ElementTree as ET
	import subprocess
	import sys

	# check if any arguments were passed to script
	# note: script name ('main_pedestrian.py') is 0th argument
	if (len(sys.argv) == 1):
		# default values
		run_simu   = 1
		data_conv  = 0
		data_plot  = 1
		jump_print = 1
		data_keep  = 1
	# first input is whether to run simulation
	elif (len(sys.argv) == 2):
		run_simu   = int(sys.argv[1])
		data_conv  = 0
		data_plot  = 1
		jump_print = 1
		data_keep  = 1
	# second input is whether to convert data
	elif (len(sys.argv) == 2):
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = 1
		jump_print = 1
		data_keep  = 1
	# third input is whether to plot data
	elif (len(sys.argv) == 3):
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = int(sys.argv[3])
		jump_print = 1
		data_keep  = 1
	# fourth input is number of frames to skip during data conversion and plotting
	elif (len(sys.argv) == 4):
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = int(sys.argv[3])
		jump_print = int(sys.argv[4])
		data_keep  = 1
	# fifth input is whether to keep data after plotting
	else:
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = int(sys.argv[3])
		jump_print = int(sys.argv[4])
		data_keep  = int(sys.argv[5])

	# run simulation
	if (run_simu == 1):
		print "Running simulation..."
		tic = time.clock()
		error = runSimulation()
		toc = time.clock() - tic
		# check for errors
		if (error is not None):
			sys.exit("Simulation returned error message: " + error)
		else:
			print "Simulation complete.", '\t\t', "Elapsed time: ", round(toc,2), " seconds."

	# convert data from binary
	if (data_conv == 1):
		print "Converting data..."
		tic = time.clock()
		parameters = loadParameters()
		convertData(parameters, jump_print, data_keep)
		toc = time.clock() - tic
		print "Data conversion complete.", '\t', "Elapsed time: ", round(toc,2), " seconds."

	# plot data
	if (data_plot == 1):
		if (data_conv == 0):
			parameters = loadParameters()
		print "Plotting data..."
		animateData(parameters, jump_print, data_conv)
		print "Plotting complete."

	# clear directory of binary data
	if (data_keep == 0):
		print "Deleting binary data..."
		os.chdir(path_data)
		os.system("perl -e 'for(<*>){((stat)[9]<(unlink))}'")
		os.chdir('..')
		print "Binary data deletion complete."

