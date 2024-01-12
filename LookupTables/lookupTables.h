#ifndef lookupTables_h
#define lookupTables_h

#include <stdint.h>

#define PPQN 192
#define MAX_OCTAVES 10
#define NOTES_IN_SCALE 7
#define TOTAL_NOTES_IN_SCALE 70
#define MAX_BPM 300
#define MAX_BPM_FRACTIONAL 10
#define CLOCK_ISR_FREQ 8000

extern const uint32_t lut_bpm_inc[];
extern const uint32_t lut_bpm_fractional_inc[];
extern const uint8_t lut_scale_major[];
extern const uint8_t lut_scale_major_map[];
extern const uint8_t lut_scale_minor[];
extern const uint8_t lut_scale_minor_map[];
extern const uint8_t lut_scale_mixolydian[];
extern const uint8_t lut_scale_mixolydian_map[];
extern const uint8_t lut_scale_dorian[];
extern const uint8_t lut_scale_dorian_map[];
extern const uint8_t lut_scale_phrygian[];
extern const uint8_t lut_scale_phrygian_map[];
extern const uint8_t lut_scale_lydian[];
extern const uint8_t lut_scale_lydian_map[];
extern const uint8_t lut_scale_aeolyian[];
extern const uint8_t lut_scale_aeolyian_map[];
extern const uint8_t lut_scale_locrian[];
extern const uint8_t lut_scale_locrian_map[];

#endif