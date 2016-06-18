#ifndef LUTFREQ_H
#define LUTFREQ_H

#define LUT_NUM_NOTES	99
#define LUT_MIDI_NOTE_SHIFT	10
#define LUT_LEN	(LUT_NUM_NOTES)
#define LUT_NOTE_LIMIT (LUT_LEN + LUT_MIDI_NOTE_SHIFT)

extern unsigned int code LUTFreq[LUT_LEN];

#endif