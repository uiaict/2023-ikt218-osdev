#include "song.h"
#include <kernel/pit.h>
#include <kernel/common.h>

void enable_speaker(){
    // Read the current state of the PC speaker control register
    uint8_t speaker_state = inb(PC_SPEAKER_PORT);
    /*
    Bit 0: Speaker gate
            0: Speaker disabled
            1: Speaker enabled
    Bit 1: Speaker data
            0: Data is not passed to the speaker
            1: Data is passed to the speaker
    */
    // Check if bits 0 and 1 are not set (0 means that the speaker is disabled)
    if (speaker_state != (speaker_state | 3)) {
        // If bits 0 and 1 are not set, enable the speaker by setting bits 0 and 1 to 1
        outb(PC_SPEAKER_PORT, speaker_state | 3);
    }
}

void disable_speaker() {
    // Turn off the PC speaker
    uint8_t speaker_state = inb(PC_SPEAKER_PORT);
    outb(PC_SPEAKER_PORT, speaker_state & 0xFC);
}


void play_song_impl(Song *song) {
    enable_speaker();
    for (uint32_t i = 0; i < song->length; i++) {
        Note* note = &song->notes[i];
        //printf("Note: %d, Freq=%d, Sleep=%d\n", i, note->frequency, note->duration);
        play_sound(note->frequency);
        sleep_interrupt(note->duration);
        disable_speaker();
    }
}

void play_song(Song *song) {
    play_song_impl(song);
}

void play_sound(uint32_t frequency) {
    if (frequency == 0) {
        return;
    }

    auto divisor = (uint16_t)(PIT_BASE_FREQUENCY / frequency);

    // Set up the PIT
    outb(PIT_CMD_PORT, 0b10110110); 
    outb(PIT_CHANNEL2_PORT, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL2_PORT, (uint8_t)(divisor >> 8));
}


SongPlayer* create_song_player() {
    auto* player = new SongPlayer();
    player->play_song = play_song_impl;
    return player;
}