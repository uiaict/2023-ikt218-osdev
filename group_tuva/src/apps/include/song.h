#ifndef SONG_H
#define SONG_H
#include <cstdint>
#include "frequencies.h"

// Define a struct to represent a single musical note
typedef struct {
    uint32_t frequency; // The frequency of the note in Hz (e.g., A4 = 440 Hz)
    uint32_t duration;  // The duration of the note in milliseconds
} Note;

// Define a struct to represent a song
typedef struct {
    Note* notes;        // Pointer to an array of Note structs representing the song
    uint32_t length;    // The number of notes in the song
} Song;

// Define a struct to represent a song player
typedef struct {
    void (*play_song)(Song* song); // Function pointer to a function that plays a song
} SongPlayer;

// Function prototype for creating a new SongPlayer instance
// Returns a pointer to a newly created SongPlayer object
SongPlayer* create_song_player();


static Note music_1[] = {
    {E5, 250}, {R, 125}, {E5, 125}, {R, 125}, {E5, 125}, {R, 125},
    {C5, 125}, {E5, 125}, {G5, 125}, {R, 125}, {G4, 125}, {R, 250},

    {C5, 125}, {R, 250}, {G4, 125}, {R, 125}, {E4, 125}, {R, 125},
    {A4, 125}, {B4, 125}, {R, 125}, {A_SHARP4, 125}, {A4, 125}, {R, 125},
    {G4, 125}, {E5, 125}, {G5, 125}, {A5, 125}, {F5, 125}, {G5, 125},
    {R, 125}, {E5, 125}, {C5, 125}, {D5, 125}, {B4, 125}, {R, 125},

    {C5, 125}, {R, 250}, {G4, 125}, {R, 125}, {E4, 125}, {R, 125},
    {A4, 125}, {B4, 125}, {R, 125}, {A_SHARP4, 125}, {A4, 125}, {R, 125},
    {G4, 125}, {E5, 125}, {G5, 125}, {A5, 125}, {F5, 125}, {G5, 125},
    {R, 125}, {E5, 125}, {C5, 125}, {D5, 125}, {B4, 125}, {R, 125},
};

static Note music_2[] = {
    {A4, 200}, {E5, 200}, {A5, 200}, {R, 100}, {A5, 200}, {A5, 200}, {Gs5, 200}, {A5, 200},
    {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200},
    {A4, 200}, {E5, 200}, {A5, 200}, {R, 100}, {A5, 200}, {A5, 200}, {Gs5, 200}, {A5, 200},
    {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200},
    {A4, 200}, {E5, 200}, {A5, 200}, {R, 100}, {A5, 200}, {A5, 200}, {Gs5, 200}, {A5, 200},
    {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}, {R, 100}, {E5, 200}
};

static Note music_3[] = {
    {E4, 200}, {E4, 200}, {F4, 200}, {G4, 200}, {G4, 200}, {F4, 200}, {E4, 200}, {D4, 200},
    {C4, 200}, {C4, 200}, {D4, 200}, {E4, 200}, {E4, 400}, {R, 200},
    {D4, 200}, {D4, 200}, {E4, 200}, {F4, 200}, {F4, 200}, {E4, 200}, {D4, 200}, {C4, 200},
    {A4, 200}, {A4, 200}, {A4, 200}, {G4, 400}
};

static Note music_4[] = {
    {C4, 500}, {D4, 500}, {E4, 500}, {C4, 500},
    {C4, 500}, {D4, 500}, {E4, 500}, {C4, 500},
    {E4, 500}, {F4, 500}, {G4, 1000},
    {E4, 500}, {F4, 500}, {G4, 1000},
    {G4, 250}, {A4, 250}, {G4, 250}, {F4, 250}, {E4, 500}, {C4, 500},
    {G4, 250}, {A4, 250}, {G4, 250}, {F4, 250}, {E4, 500}, {C4, 500},
    {C4, 500}, {G3, 500}, {C4, 1000},
    {C4, 500}, {G3, 500}, {C4, 1000}
};

static Note music_5[] = {
    {E4, 375}, {C4, 375}, {D4, 375}, {A3, 375}, {B3, 375}, {D4, 375}, {C4, 375}, {A3, 375},
    {E4, 375}, {C4, 375}, {D4, 375}, {A3, 375}, {B3, 375}, {D4, 375}, {C4, 375}, {A3, 375},
};

static Note music_6[] = {
    {F4, 250}, {F4, 250}, {F4, 250}, {C5, 250}, {A_SHARP4, 250}, {G_SHARP4, 250}, {F4, 500},
    {F4, 250}, {F4, 250}, {F4, 250}, {C5, 250}, {A_SHARP4, 250}, {G_SHARP4, 250}, {F4, 500},
    {A_SHARP4, 250}, {A_SHARP4, 250}, {A_SHARP4, 250}, {F5, 250}, {D5, 250}, {C5, 250}, {A_SHARP4, 500},
    {A_SHARP4, 250}, {A_SHARP4, 250}, {A_SHARP4, 250}, {F5, 250}, {D5, 250}, {C5, 250}, {A_SHARP4, 500},
};

#endif
