import numpy
import sys
dir = '/Users/joostbooy/Desktop/Code/Atom/Python/armScripts'
sys.path.insert(0,dir)
import lutCompiler


#table variables
tables = []
exp_table_size = 1024


'''____________________
	EXP TABLE
________________________'''
name = 'exp'

values = numpy.arange(0, exp_table_size)

tables.append('float ' + name)
tables.append(values.astype('float32'))

'''____________________
	INV EXP TABLE
________________________'''
name = 'inv_exp'

tables.append('float ' + name)
tables.append(1.0 - values.astype('float32'))


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
