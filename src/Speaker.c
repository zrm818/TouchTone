
#include "inc/Speaker.h"

uint16_t current_tone = 0;
uint16_t previous_tone = 1;

// GPT-GENERATED PERIODS
uint16_t note_periods_us[18] = {
    3822, // C4:   261.63 Hz
    3608, // C#4:  277.18 Hz
    3405, // D4:   293.66 Hz
    3214, // D#4:  311.13 Hz
    3034, // E4:   329.63 Hz
    2863, // F4:   349.23 Hz
    2703, // F#4:  369.99 Hz
    2551, // G4:   392.00 Hz
    2408, // G#4:  415.30 Hz
    2273, // A4:   440.00 Hz
    2145, // A#4:  466.16 Hz
    2025, // B4:   493.88 Hz
    1911, // C5:   523.25 Hz
    1804, // C#5:  554.37 Hz
    1703, // D5:   587.33 Hz
    1607, // D#5:  622.25 Hz
    1517, // E5:   659.25 Hz
    1432  // F5:   698.46 Hz
};

void Update_Speakers()
{
    // Sets tone of speakers once per recieved distance measurement
    if (US2_distance_cm == -1 && speaker_is_on) { Turn_Off_Speaker(); }

    else if (US2_distance_cm > SPEAKER_LOWER_BOUND_CM &&
             US2_distance_cm < SPEAKER_UPPER_BOUND_CM)
    {
        current_tone = Map_Distance_To_Tone(US2_distance_cm);

        if (current_tone != previous_tone || !speaker_is_on)
        {
            Play_Tone(current_tone);
            previous_tone = current_tone;
        }
    }
}

uint16_t Map_Distance_To_Tone(float distance)
{
    int bin = (int)distance;
    bin = bin / 10;
    return note_periods_us[bin * 2];
}

void Play_Tone(uint16_t note_period_us)
{
    Update_Timer_A1_Period(note_period_us);
    speaker_is_on = 1;
}

void Turn_Off_Speaker()
{
    TIMER_A1->CTL &= ~0x0030;
    speaker_is_on = 0;
}
