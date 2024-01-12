import numpy
import sys
dir = '/Users/joostbooy/Desktop/Code/Atom/Python/armScripts'
sys.path.insert(0,dir)
import lutCompiler


#table variables
tables = []
ppqn = 192
max_bpm = 300
max_bpm_fractional = 10
clock_isr_freq = 8000


'''____________________
	BPM INC
________________________'''

name = 'bpm_inc'

bpm = numpy.arange(1.0, max_bpm + 1)
hertz = bpm / 60 * ppqn
values = hertz / clock_isr_freq * (1 << 32);

tables.append('uint32_t ' + name)
tables.append(values.astype(int))


'''__________________________
	BPM FRACTIONAL INC
_____________________________'''

name = 'bpm_fractional_inc'

stepsize = 1.0 / max_bpm_fractional
bpmFraction = numpy.arange(0.00, 1.00, stepsize)
hertz = bpmFraction / 60 * ppqn
values = hertz / clock_isr_freq * (1 << 32);

tables.append('uint32_t ' + name)
tables.append(values.astype(int))

'''____________________
    MIDI NOTE SCALES
    (10 octaves per scale)
________________________'''


def make_map(notes):
    result = []
    for i in range(128 // len(notes) + 1):
        shifted_notes = numpy.clip(notes + i * 12, 0, 127)
        result += shifted_notes.tolist()
        if len(result) >= 128:
            break
    return result[:128]


max_octaves = 10
notes_in_scale = 7
octaves = numpy.repeat(numpy.arange(0, 12 * max_octaves, 12), notes_in_scale)

#MAJOR
name = 'scale_major'

notes = numpy.array([0,2,4,5,7,9,11] * max_octaves) + octaves
tables.append('uint8_t ' + name)
tables.append(notes)

notes_map = numpy.array([0,0,2,2,4,5,5,7,7,9,9,11])
tables.append('uint8_t ' + name + '_map')
tables.append(make_map(notes_map))

#MINOR
name = 'scale_minor'

notes = numpy.array([0,2,3,5,7,8,10] * max_octaves) + octaves
tables.append('uint8_t ' + name)
tables.append(notes)

notes_map = numpy.array([0,0,2,3,3,5,5,7,8,8,10,10])
tables.append('uint8_t ' + name + '_map')
tables.append(make_map(notes_map))

#MIXOLYDIAN
name = 'scale_mixolydian'

notes = numpy.array([0,2,4,5,7,9,10] * max_octaves) + octaves
tables.append('uint8_t ' + name)
tables.append(notes.astype(int))

notes_map = numpy.array([0,0,2,2,4,5,5,7,7,9,10,10])
tables.append('uint8_t ' + name + '_map')
tables.append(make_map(notes_map))

#DORIAN
name = 'scale_dorian'

notes = numpy.array([0,2,3,5,7,9,10] * max_octaves) + octaves
tables.append('uint8_t ' + name)
tables.append(notes.astype(int))

notes_map = numpy.array([0,0,2,3,3,5,5,7,7,9,10,10])
tables.append('uint8_t ' + name + '_map')
tables.append(make_map(notes_map))

#PHRYGIAN
name = 'scale_phrygian'

notes = numpy.array([0,1,3,5,7,8,10] * max_octaves) + octaves
tables.append('uint8_t ' + name)
tables.append(notes.astype(int))

notes_map = numpy.array([0,1,1,3,3,5,5,7,8,8,10,10])
tables.append('uint8_t ' + name + '_map')
tables.append(make_map(notes_map))

#LYDIAN
name ='scale_lydian'

notes = numpy.array([0,2,4,6,7,9,11] * max_octaves) + octaves
tables.append('uint8_t ' + name)
tables.append(notes.astype(int))

notes_map = numpy.array([0,0,2,2,4,4,6,7,7,9,9,11,11])
tables.append('uint8_t ' + name + '_map')
tables.append(make_map(notes_map))

#AEOLYIAN
name ='scale_aeolyian'

notes = numpy.array([0,2,3,5,7,8,10] * 10) + octaves
tables.append('uint8_t ' + name)
tables.append(notes.astype(int))

notes_map = numpy.array([0,0,2,3,3,5,5,7,8,8,10,10])
tables.append('uint8_t ' + name + '_map')
tables.append(make_map(notes_map))

#LOCRIAN
name ='scale_locrian'

notes = numpy.array([0,1,3,5,6,8,10] * 10) + octaves
tables.append('uint8_t ' + name)
tables.append(notes.astype(int))

notes_map = numpy.array([0,1,1,3,3,5,6,6,8,8,10,10])
tables.append('uint8_t ' + name + '_map')
tables.append(make_map(notes_map))

'''____________________
	DEFINES
________________________'''

defines = [
'PPQN '					+ str(ppqn),
'MAX_OCTAVES '			+ str(max_octaves),
'NOTES_IN_SCALE '		+ str(notes_in_scale),
'TOTAL_NOTES_IN_SCALE '	+ str(notes_in_scale * max_octaves),
'MAX_BPM '				+ str(max_bpm),
'MAX_BPM_FRACTIONAL '	+ str(max_bpm_fractional),
'CLOCK_ISR_FREQ '		+ str(clock_isr_freq)
]


'''____________________
	COMPILING
________________________'''

# set directory to write tables (argument given in makeFile)
lutCompiler.setDir(str(sys.argv[1]))
# compile and store
lutCompiler.compile(tables, defines)
