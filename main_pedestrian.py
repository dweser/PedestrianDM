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
def loadBinaryDouble(file_name):
	# load module within function to avoid installation issues
	import numpy as np

	file  = open(file_name, "rb") 
	file.seek(0, os.SEEK_SET)
	array = np.fromfile(file, dtype=np.float64)
	file.close()
	return array

def loadBinaryBool(file_name):
	import numpy as np

	file  = open(file_name, "rb") 
	file.seek(0, os.SEEK_SET)
	array = np.fromfile(file, dtype=np.bool_)
	file.close()
	return array

# convert data from binary to vtk format
def convertData(parameters, jump_print, data_keep):
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
		x         = loadBinaryDouble(path_data + "particleX_" + extension)[0:N]
		y         = loadBinaryDouble(path_data + "particleY_" + extension)[0:N]   
		# multiply by 1 to implicitly cast bool array as int
		s         = loadBinaryBool(  path_data + "particleS_" + extension)[0:N]*1
	
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
	L 		   = float(root.find("L").text)
	seed_no	   = root.find("SEED_NUMBER").text
	parameters = {'N': N, 'dt': dt, 'nTime': nTime, 'length': length, 'width': width, 'L': L, 'seed': seed_no}
	return parameters

# plot data
def animateData(parameters, jump_print, data_conv):
	import numpy as np
	import matplotlib.pyplot     as plt
	from   matplotlib.animation  import FuncAnimation

	# define our update function for FuncAnimation
	def update_scatter_plot(frame_number):		
		extension = seed_name + "_" + str(frame_number*jump_print).zfill(9) + ext
		# load data
		x         = loadBinaryDouble(path_data + "particleX_" + extension)[0:N]
		y         = loadBinaryDouble(path_data + "particleY_" + extension)[0:N]   
		s         = loadBinaryBool(  path_data + "particleS_" + extension)[0:N]*1

		# update positions
		plt_sct.set_offsets(np.transpose(np.vstack([x, y])))
		# update title
		title.set_text('Time t=' + '{:04.2f}'.format(frame_number*jump_print*dt))
		# update states (color of particles)
		plt_sct.set_array(s)

    # parameters
	cwd       = os.getcwd()
	path_data = cwd + "/data/"
	seed_name = "Seed" + parameters['seed']
	N         = parameters['N']
	dt 		  = parameters['dt']
	ext 	  = ".dat"
	
	## initialization of plot ##
	extension = seed_name + "_" + str(0).zfill(9) + ext
	# load initial data
	x         = loadBinaryDouble(path_data + "particleX_" + extension)[0:N]
	y         = loadBinaryDouble(path_data + "particleY_" + extension)[0:N]   
	s         = loadBinaryBool(  path_data + "particleS_" + extension)[0:N]*1

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
	animation = FuncAnimation(fig, update_scatter_plot, frames=parameters['nTime']/jump_print, interval=24)
	plt.show()

# calculate densities
def calculateDensities(xgrid, ygrid, xys, p_A, p_B, n_dx, n_dy, L):
	for xi in xrange(0,n_dx):
		for yi in xrange(0,n_dy):
			p_A[xi,yi] = len( xys[ (xys[:,0]>xgrid[xi-1,yi]) & (xys[:,0]<=xgrid[xi,yi]) & (xys[:,1]>ygrid[xi,yi-1]) & (xys[:,1]<=ygrid[xi,yi]) & (xys[:,2]==0) ][:,0] )
			p_B[xi,yi] = len( xys[ (xys[:,0]>xgrid[xi-1,yi]) & (xys[:,0]<=xgrid[xi,yi]) & (xys[:,1]>ygrid[xi,yi-1]) & (xys[:,1]<=ygrid[xi,yi]) & (xys[:,2]==1) ][:,0] )
				
			# debug: print densities in each square and value being added to p_t
			# print(p_A[xi,yi], p_B[xi,yi], float(abs(p_A[xi,yi]-p_B[xi,yi]))*dx*dy)

	return p_A, p_B

# plot densities over time
def densitiesInTime(parameters, jump_print, n_dx, n_dy):
	import matplotlib.pyplot as plt
	import numpy as np

	# parameters
	dx 	   = float(parameters['length'])/float((n_dx-1))
	dy     = float(parameters['width'])/float((n_dy-1))
	n_time = int(parameters['nTime']/jump_print)
	N 	   = parameters['N']
	L      = parameters['L']
	cwd       = os.getcwd()
	path_data = cwd + "/data/"
	seed_name = "Seed" + parameters['seed']
	ext 	  = ".dat"

	# arrays to hold each density at a single time step, the integral of their difference over time, and the difference between them over time
	p_A = np.empty([n_dx, n_dy], dtype=int)
	p_B = np.empty([n_dx, n_dy], dtype=int)
	p_t = np.zeros(n_time)
	diff_t = np.zeros(n_time)

	# meshgrid of xy values
	xgrid, ygrid  = np.meshgrid(np.linspace(0,parameters['length'],n_dx), np.linspace(0,parameters['width'],n_dy), indexing='ij')

	# array for x, y, and state data
	xys = np.empty([N,3], dtype=float)

	# load and analyze data of first time step
	extension = seed_name + "_" + str(0).zfill(9) + ext
	xys[:,0]  = loadBinaryDouble(path_data + "particleX_" + extension)[0:N]
	xys[:,1]  = loadBinaryDouble(path_data + "particleY_" + extension)[0:N]   
	xys[:,2]  = loadBinaryBool(  path_data + "particleS_" + extension)[0:N]*1

	p_A, p_B  = calculateDensities(xgrid, ygrid, xys, p_A, p_B, n_dx, n_dy, L)
			
	diff_t[0] += sum(sum(abs(p_A-p_B)))
	p_t[0] 	  += float(sum(sum(abs(p_A-p_B))))*dx*dy/(np.pi*L**2)

	print('Calculated number of defective initially:  ' + str(sum(sum(p_A))))

	# loop through rest of time
	for t in xrange(1,n_time):
		
		# load data
		extension = seed_name + "_" + str(t*jump_print).zfill(9) + ext
		xys[:,0]  = loadBinaryDouble(path_data + "particleX_" + extension)[0:N]
		xys[:,1]  = loadBinaryDouble(path_data + "particleY_" + extension)[0:N]   
		xys[:,2]  = loadBinaryBool(  path_data + "particleS_" + extension)[0:N]*1

		p_A, p_B  = calculateDensities(xgrid, ygrid, xys, p_A, p_B, n_dx, n_dy, L)
				
		diff_t[t] = sum(sum(abs(p_A-p_B)))
		p_t[t] 	  = float(sum(sum(abs(p_A-p_B))))*dx*dy/(np.pi*L**2)

		# debug: print total densities
		# print(sum(sum(p_A))+sum(sum(p_B)))

	print('Calculated number of defective in final period:  ' + str(sum(sum(p_A))))

	# plot integral of difference of densities over time
	plt.plot(np.linspace(0,n_time*jump_print,n_time), p_t, 'r', label=r'$\int|\rho_A-\rho_B|dx$')
	plt.plot(np.linspace(0,n_time*jump_print,n_time), diff_t, 'b', label=r'$|n_A-n_B|$')
	plt.xlabel(r'$t$', fontsize=25)
	plt.title('N=' + str(N) + ';  dx,dy=' + str(round(dx,2)), fontsize=25)
	plt.legend(bbox_to_anchor=(1, 1), loc=2, borderaxespad=0., fontsize=25)
	plt.show()


def animateDensities(parameters, jump_print, n_dx, n_dy):
	import numpy as np
	import matplotlib.pyplot     as plt
	from   matplotlib.animation  import FuncAnimation

	# define our update function for FuncAnimation
	def update_densities(frame_number, xgrid, ygrid, p_A, p_B, xys, n_dx, n_dy, L, path_data, seed_name, ext, jump_print):		
		extension = seed_name + "_" + str(frame_number*jump_print).zfill(9) + ext
		# load data
		xys[:,0]  = loadBinaryDouble(path_data + "particleX_" + extension)[0:N]
		xys[:,1]  = loadBinaryDouble(path_data + "particleY_" + extension)[0:N]   
		xys[:,2]  = loadBinaryBool(  path_data + "particleS_" + extension)[0:N]*1

		# calculate densities
		p_A, p_B  = calculateDensities(xgrid, ygrid, xys, p_A, p_B, n_dx, n_dy, L)

		# update plot
		quad1.set_array(p_A.ravel())
		quad2.set_array(p_B.ravel())
		# update title
		fig.suptitle('Time t=' + '{:04.2f}'.format(frame_number*jump_print*dt), fontsize=30)

	# parameters
	dx 	   = float(parameters['length'])/float((n_dx-1))
	dy     = float(parameters['width'])/float((n_dy-1))
	dt     = round(float(parameters['dt']),2)
	n_time = int(parameters['nTime']/jump_print)
	N 	   = parameters['N']
	L      = parameters['L']
	cwd       = os.getcwd()
	path_data = cwd + "/data/"
	seed_name = "Seed" + parameters['seed']
	ext 	  = ".dat"

	# arrays to hold each density at a single time step
	p_A = np.empty([n_dx, n_dy], dtype=int)
	p_B = np.empty([n_dx, n_dy], dtype=int)

	# array for x, y, and state data
	xys = np.empty([N,3], dtype=float)

	# meshgrid of xy values
	xgrid, ygrid  = np.meshgrid(np.linspace(0,parameters['length'],n_dx), np.linspace(0,parameters['width'],n_dy), indexing='ij')

	## initialization of plot ##
	extension = seed_name + "_" + str(0).zfill(9) + ext
	# load initial data
	x         = loadBinaryDouble(path_data + "particleX_" + extension)[0:N]
	y         = loadBinaryDouble(path_data + "particleY_" + extension)[0:N]   
	s         = loadBinaryBool(  path_data + "particleS_" + extension)[0:N]*1

	# initial figure
	fig, ax = plt.subplots(2, sharex=True, figsize=(15,45))
	quad1   = ax[0].pcolormesh(p_A, vmin=0, vmax=60)
	quad2   = ax[1].pcolormesh(p_B, vmin=0, vmax=60)
	ax[0].set_title(r'$\rho_A$', fontsize=35)
	ax[1].set_title(r'$\rho_B$', fontsize=35)
	fig.colorbar(quad1, ax=ax[0])
	fig.colorbar(quad2, ax=ax[1])
	fig.suptitle('Time t=' + '{:04.2f}'.format(0), fontsize=30)

	# create animation and display it
	animation = FuncAnimation(fig, update_densities, frames=parameters['nTime']/jump_print, interval=24, fargs=[xgrid, ygrid, p_A, p_B, xys, n_dx, n_dy, L,  path_data, seed_name, ext, jump_print], blit=False)
	plt.show()


# main execution
if __name__ == "__main__":
	import os 
	import os.path
	import time
	import xml.etree.ElementTree as ET
	import subprocess
	import sys

	# parameters
	n_dx = 16
	n_dy = 16

	# check if any arguments were passed to script
	# note: script name ('main_pedestrian.py') is 0th argument
	if (len(sys.argv) == 1):
		# default values
		run_simu   = 1
		data_conv  = 0
		data_plot  = 1
		analyze    = 1
		jump_print = 1
		data_keep  = 1
	# first input is whether to run simulation
	elif (len(sys.argv) == 2):
		run_simu   = int(sys.argv[1])
		data_conv  = 0
		data_plot  = 1
		analyze    = 1
		jump_print = 1
		data_keep  = 1
	# second input is whether to convert data
	elif (len(sys.argv) == 2):
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = 1
		analyze    = 1
		jump_print = 1
		data_keep  = 1
	# third input is whether to plot data
	elif (len(sys.argv) == 3):
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = int(sys.argv[3])
		analyze    = 1
		jump_print = 1
		data_keep  = 1
	# fourth input is number of frames to skip during data conversion and plotting
	elif (len(sys.argv) == 4):
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = int(sys.argv[3])
		analyze    = int(sys.argv[4])
		jump_print = 1
		data_keep  = 1
	# fifth input is whether to keep data after plotting
	elif (len(sys.argv) == 5):
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = int(sys.argv[3])
		analyze    = int(sys.argv[4])
		jump_print = int(sys.argv[5])
		data_keep  = 1
	else:
		run_simu   = int(sys.argv[1])
		data_conv  = int(sys.argv[2])
		data_plot  = int(sys.argv[3])
		analyze    = int(sys.argv[4])
		jump_print = int(sys.argv[5])
		data_keep  = int(sys.argv[6])


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

	# analyze densities of two populations
	if (analyze == 1):
		if (data_conv == 0 and data_plot == 0):
			parameters = loadParameters()
		print "Analyzing densities..."
		animateDensities(parameters, jump_print, n_dx, n_dy)
		densitiesInTime(parameters, jump_print, n_dx, n_dy)
		print "Analysis complete."

	# clear directory of binary data
	if (data_keep == 0):
		print "Deleting binary data..."
		os.chdir('data')
		os.system("perl -e 'for(<*>){((stat)[9]<(unlink))}'")
		os.chdir('..')
		print "Binary data deletion complete."

