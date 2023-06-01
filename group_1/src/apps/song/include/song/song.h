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
{D4, 250}, {A4, 250}, {A4, 250},
{R, 125}, {E4, 125}, {B4, 500},
{F4, 250}, {C5, 250}, {C5, 250},
{R, 125}, {E4, 125}, {B4, 500},
{D4, 250}, {A4, 250}, {A4, 250},
{R, 125}, {E4, 125}, {B4, 500},
{F4, 250}, {C5, 250}, {C5, 250},
{R, 125}, {E4, 125}, {B4, 500},
{D4, 125}, {F4, 125}, {D5, 500},

{D4, 125}, {F4, 125}, {D5, 500},
{E5, 250}, {F5, 125}, {E5, 125}, {F5, 125},
{E5, 125}, {C5, 125}, {A4, 500},
{A4, 250}, {D4, 250}, {F4, 125}, {G4, 125},
{A4, 500},
{A4, 250}, {D4, 250}, {F4, 125}, {G4, 125},
{E4, 500},
{D4, 125}, {F4, 125}, {D5, 500},
{D4, 125}, {F4, 125}, {D5, 500},

{E5, 250}, {F5, 125}, {E5, 125}, {E5, 125},
{E5, 125}, {C5, 125}, {A4, 500},
{A4, 250}, {D4, 250}, {F4, 125}, {G4, 125},
{A4, 500}, {A4, 250},
{D4, 1000}, 
};

static Note music_2[] = {
  {A4, 500}, {A4, 500}, {A4, 125}, {A4, 125}, {A4, 125}, {A4, 125}, {F4, 250}, {R, 250},
  {A4, 500}, {A4, 500}, {A4, 125}, {A4, 125}, {A4, 125}, {A4, 125}, {F4, 250}, {R, 250},
  {A4, 500}, {A4, 500}, {A4, 500}, {F4, 250}, {C5, 125},

  {A4, 500}, {F4, 250}, {C5, 125}, {A4, 1000},
  {E5, 500}, {E5, 500}, {E5, 500}, {F5, 250}, {C5, 125},
  {A4, 500}, {F4, 250}, {C5, 125}, {A4, 1000},

  {A5, 500}, {A4, 250}, {A4, 125}, {A5, 500}, {Gs5, 250}, {G5, 125},
  {Ds5, 125}, {D5, 125}, {Ds5, 250}, {R, 250}, {A4, 250}, {Ds5, 500}, {D5, 250}, {Cs5, 125},

  {C5, 125}, {B4, 125}, {C5, 125}, {R, 250}, {F4, 250}, {Gs4, 500}, {F4, 250}, {A4, 125},
  {C5, 500}, {A4, 250}, {C5, 125}, {E5, 1000},

  {A5, 500}, {A4, 250}, {A4, 125}, {A5, 500}, {Gs5, 250}, {G5, 125},
  {Ds5, 125}, {D5, 125}, {Ds5, 250}, {R, 250}, {A4, 250}, {Ds5, 500}, {D5, 250}, {Cs5, 125},

  {C5, 125}, {B4, 125}, {C5, 125}, {R, 250}, {F4, 250}, {Gs4, 500}, {F4, 250}, {A4, 125},
  {A4, 500}, {F4, 250}, {C5, 125}, {A4, 1000},
};



#endif
