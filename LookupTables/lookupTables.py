import numpy
import sys
dir = '/Users/joostbooy/Desktop/Code/Atom/Python/armScripts'
sys.path.insert(0,dir)
import lutCompiler


#table variables
tables = []

'''____________________
	RECIPROCAL
________________________'''
name = 'reciprocal'

max_steps = 16
step = numpy.arange(1, max_steps + 1)
values = 1.0 / step
values = numpy.insert(values, 0, 0.0)

tables.append('float ' + name)
tables.append(values.astype('float32'))


'''____________________
	EXP TABLE
________________________'''

exp_table_size = 1024
stepsize = 1.0 / exp_table_size
x = numpy.arange(0, 1.0, stepsize)

name = 'exp'
values = 1.0 - numpy.exp(-6 * x)
values /= values.max()

tables.append('float ' + name)
tables.append(values.astype('float32'))

name = 'inv_exp'
values = 1.0 - values[::-1]

tables.append('float ' + name)
tables.append(values.astype('float32'))


'''____________________
	DEFINES
________________________'''

defines = [
'EXP_TABLE_SIZE '	+ str(exp_table_size),
]


'''____________________
	COMPILING
________________________'''

# set directory to write tables (argument given in makeFile)
lutCompiler.setDir(str(sys.argv[1]))
# compile and store
lutCompiler.compile(tables, defines)
