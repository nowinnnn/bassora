// Plik wygenerowany przez tools/gen_presets.py - nie edytuj ręcznie.
#pragma once

#include "Parameters.h"
#include <vector>

namespace FactoryPresets
{
    struct Value  { const char* id; float value; };
    struct Preset { const char* category; const char* name; const Value* values; int numValues; };

    inline constexpr Value v1[] = { { IDs::sub, 0.5f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 55.0f }, { IDs::attack, 1.0f }, { IDs::decay, 1800.0f }, { IDs::sustain, 0.0f }, { IDs::release, 150.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 12000.0f } };
    inline constexpr Value v2[] = { { IDs::sub, 0.55f }, { IDs::click, 0.12f }, { IDs::pitchAmt, 10.0f }, { IDs::pitchTime, 50.0f }, { IDs::decay, 2200.0f }, { IDs::sustain, 0.0f }, { IDs::release, 180.0f }, { IDs::drive, 0.05f }, { IDs::cutoff, 14000.0f } };
    inline constexpr Value v3[] = { { IDs::sub, 0.6f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 60.0f }, { IDs::decay, 3600.0f }, { IDs::sustain, 0.0f }, { IDs::release, 400.0f }, { IDs::drive, 0.1f }, { IDs::cutoff, 9000.0f } };
    inline constexpr Value v4[] = { { IDs::sub, 0.5f }, { IDs::click, 0.3f }, { IDs::pitchAmt, 18.0f }, { IDs::pitchTime, 35.0f }, { IDs::decay, 450.0f }, { IDs::sustain, 0.0f }, { IDs::release, 80.0f }, { IDs::drive, 0.1f } };
    inline constexpr Value v5[] = { { IDs::sub, 0.45f }, { IDs::click, 0.05f }, { IDs::pitchAmt, 8.0f }, { IDs::pitchTime, 70.0f }, { IDs::attack, 6.0f }, { IDs::decay, 1800.0f }, { IDs::sustain, 0.0f }, { IDs::release, 200.0f }, { IDs::cutoff, 2800.0f }, { IDs::reso, 0.05f }, { IDs::drive, 0.0f } };
    inline constexpr Value v6[] = { { IDs::sub, 0.55f }, { IDs::click, 0.45f }, { IDs::pitchAmt, 26.0f }, { IDs::pitchTime, 28.0f }, { IDs::decay, 1400.0f }, { IDs::sustain, 0.0f }, { IDs::release, 120.0f }, { IDs::drive, 0.2f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -16.0f }, { IDs::compRatio, 4.0f }, { IDs::compAttack, 8.0f }, { IDs::compRelease, 90.0f }, { IDs::compMakeup, 3.0f } };
    inline constexpr Value v7[] = { { IDs::tune, -3.0f }, { IDs::sub, 0.75f }, { IDs::click, 0.08f }, { IDs::pitchAmt, 20.0f }, { IDs::pitchTime, 85.0f }, { IDs::decay, 2600.0f }, { IDs::sustain, 0.0f }, { IDs::release, 300.0f }, { IDs::cutoff, 3500.0f }, { IDs::drive, 0.05f } };
    inline constexpr Value v8[] = { { IDs::tune, 4.0f }, { IDs::sub, 0.5f }, { IDs::pitchAmt, 12.0f }, { IDs::pitchTime, 45.0f }, { IDs::decay, 1500.0f }, { IDs::sustain, 0.0f }, { IDs::release, 130.0f }, { IDs::drive, 0.12f } };
    inline constexpr Value v9[] = { { IDs::wave, 1.0f }, { IDs::sub, 0.6f }, { IDs::click, 0.35f }, { IDs::pitchAmt, 10.0f }, { IDs::pitchTime, 40.0f }, { IDs::decay, 900.0f }, { IDs::sustain, 0.0f }, { IDs::release, 140.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 6000.0f } };
    inline constexpr Value v10[] = { { IDs::sub, 0.5f }, { IDs::pitchAmt, 12.0f }, { IDs::pitchTime, 55.0f }, { IDs::decay, 2000.0f }, { IDs::sustain, 0.0f }, { IDs::release, 160.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 5200.0f }, { IDs::eqHiF, 4000.0f }, { IDs::eqHiG, -3.0f } };
    inline constexpr Value v11[] = { { IDs::wave, 1.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 55.0f }, { IDs::decay, 2000.0f }, { IDs::sustain, 0.0f }, { IDs::release, 150.0f }, { IDs::drive, 0.15f } };
    inline constexpr Value v12[] = { { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 6.0f }, { IDs::pitchTime, 80.0f }, { IDs::attack, 4.0f }, { IDs::decay, 2200.0f }, { IDs::sustain, 0.0f }, { IDs::release, 250.0f }, { IDs::cutoff, 1800.0f }, { IDs::reso, 0.1f }, { IDs::drive, 0.05f } };
    inline constexpr Value v13[] = { { IDs::sub, 0.7f }, { IDs::click, 0.5f }, { IDs::pitchAmt, 32.0f }, { IDs::pitchTime, 22.0f }, { IDs::decay, 520.0f }, { IDs::sustain, 0.0f }, { IDs::release, 70.0f }, { IDs::drive, 0.25f }, { IDs::cutoff, 8000.0f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -14.0f }, { IDs::compRatio, 6.0f }, { IDs::compAttack, 3.0f }, { IDs::compRelease, 60.0f }, { IDs::compMakeup, 4.0f } };
    inline constexpr Value v14[] = { { IDs::sub, 0.5f }, { IDs::click, 0.15f }, { IDs::pitchAmt, 8.0f }, { IDs::pitchTime, 45.0f }, { IDs::glide, 90.0f }, { IDs::legato, 1.0f }, { IDs::decay, 2400.0f }, { IDs::sustain, 0.15f }, { IDs::release, 220.0f }, { IDs::drive, 0.15f } };
    inline constexpr Value v15[] = { { IDs::wave2, 2.0f }, { IDs::level2, 0.15f }, { IDs::detune2, 0.0f }, { IDs::sub, 0.5f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 55.0f }, { IDs::decay, 1700.0f }, { IDs::sustain, 0.0f }, { IDs::release, 140.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v16[] = { { IDs::sub, 0.85f }, { IDs::click, 0.1f }, { IDs::pitchAmt, 24.0f }, { IDs::pitchTime, 90.0f }, { IDs::decay, 2200.0f }, { IDs::sustain, 0.0f }, { IDs::release, 300.0f }, { IDs::drive, 0.05f }, { IDs::cutoff, 4000.0f } };
    inline constexpr Value v17[] = { { IDs::sub, 0.9f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 3.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.9f }, { IDs::release, 120.0f }, { IDs::drive, 0.0f }, { IDs::cutoff, 800.0f }, { IDs::gain, -4.0f } };
    inline constexpr Value v18[] = { { IDs::wave, 1.0f }, { IDs::wave2, 0.0f }, { IDs::level2, 0.3f }, { IDs::semis2, -12.0f }, { IDs::detune2, 0.0f }, { IDs::sub, 0.7f }, { IDs::pitchAmt, 4.0f }, { IDs::pitchTime, 90.0f }, { IDs::decay, 1800.0f }, { IDs::sustain, 0.3f }, { IDs::release, 300.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 700.0f }, { IDs::reso, 0.1f } };
    inline constexpr Value v19[] = { { IDs::sub, 0.8f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 8.0f }, { IDs::decay, 900.0f }, { IDs::sustain, 0.8f }, { IDs::release, 250.0f }, { IDs::drive, 0.1f }, { IDs::cutoff, 400.0f }, { IDs::gain, -2.0f } };
    inline constexpr Value v20[] = { { IDs::sub, 0.8f }, { IDs::pitchAmt, 36.0f }, { IDs::pitchTime, 320.0f }, { IDs::decay, 3000.0f }, { IDs::sustain, 0.0f }, { IDs::release, 400.0f }, { IDs::drive, 0.05f }, { IDs::cutoff, 3000.0f } };
    inline constexpr Value v21[] = { { IDs::sub, 0.8f }, { IDs::click, 0.25f }, { IDs::pitchAmt, 28.0f }, { IDs::pitchTime, 30.0f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.0f }, { IDs::release, 100.0f }, { IDs::drive, 0.08f }, { IDs::cutoff, 2500.0f } };
    inline constexpr Value v22[] = { { IDs::wave, 1.0f }, { IDs::sub, 0.7f }, { IDs::pitchAmt, 5.0f }, { IDs::pitchTime, 70.0f }, { IDs::decay, 1500.0f }, { IDs::sustain, 0.5f }, { IDs::release, 220.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 1500.0f }, { IDs::eqLoF, 70.0f }, { IDs::eqLoG, 2.0f } };
    inline constexpr Value v23[] = { { IDs::sub, 0.9f }, { IDs::pitchAmt, 30.0f }, { IDs::pitchTime, 400.0f }, { IDs::attack, 20.0f }, { IDs::decay, 4000.0f }, { IDs::sustain, 0.0f }, { IDs::release, 1600.0f }, { IDs::drive, 0.1f }, { IDs::cutoff, 1800.0f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -20.0f }, { IDs::compRatio, 3.0f }, { IDs::compMakeup, 2.0f } };
    inline constexpr Value v24[] = { { IDs::wave2, 0.0f }, { IDs::level2, 0.5f }, { IDs::semis2, -12.0f }, { IDs::detune2, 0.0f }, { IDs::sub, 0.4f }, { IDs::pitchAmt, 8.0f }, { IDs::pitchTime, 50.0f }, { IDs::decay, 1800.0f }, { IDs::sustain, 0.2f }, { IDs::release, 200.0f }, { IDs::drive, 0.1f }, { IDs::cutoff, 5000.0f } };
    inline constexpr Value v25[] = { { IDs::sub, 0.75f }, { IDs::click, 0.1f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 40.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.0f }, { IDs::release, 90.0f }, { IDs::drive, 0.05f }, { IDs::cutoff, 3000.0f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -20.0f }, { IDs::compRatio, 5.0f }, { IDs::compAttack, 4.0f }, { IDs::compRelease, 70.0f }, { IDs::compMakeup, 3.0f } };
    inline constexpr Value v26[] = { { IDs::sub, 0.8f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 16.0f }, { IDs::pitchTime, 50.0f }, { IDs::decay, 1600.0f }, { IDs::sustain, 0.0f }, { IDs::release, 140.0f }, { IDs::drive, 0.1f }, { IDs::cutoff, 5000.0f }, { IDs::eqLoF, 60.0f }, { IDs::eqLoG, 2.5f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -20.0f }, { IDs::compRatio, 6.0f }, { IDs::compAttack, 5.0f }, { IDs::compRelease, 80.0f }, { IDs::compMakeup, 4.0f } };
    inline constexpr Value v27[] = { { IDs::sub, 0.5f }, { IDs::click, 0.35f }, { IDs::pitchAmt, 18.0f }, { IDs::pitchTime, 45.0f }, { IDs::decay, 1200.0f }, { IDs::sustain, 0.0f }, { IDs::release, 120.0f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.7f }, { IDs::cutoff, 6000.0f } };
    inline constexpr Value v28[] = { { IDs::driveType, 1.0f }, { IDs::drive, 0.8f }, { IDs::sub, 0.55f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 16.0f }, { IDs::pitchTime, 50.0f }, { IDs::decay, 1400.0f }, { IDs::sustain, 0.0f }, { IDs::release, 130.0f }, { IDs::cutoff, 5000.0f }, { IDs::gain, -6.0f } };
    inline constexpr Value v29[] = { { IDs::driveType, 2.0f }, { IDs::drive, 0.55f }, { IDs::sub, 0.5f }, { IDs::click, 0.25f }, { IDs::pitchAmt, 16.0f }, { IDs::pitchTime, 50.0f }, { IDs::decay, 1600.0f }, { IDs::sustain, 0.0f }, { IDs::release, 130.0f }, { IDs::cutoff, 7000.0f }, { IDs::gain, -5.0f } };
    inline constexpr Value v30[] = { { IDs::driveType, 0.0f }, { IDs::drive, 0.6f }, { IDs::sub, 0.5f }, { IDs::click, 0.3f }, { IDs::pitchAmt, 20.0f }, { IDs::pitchTime, 45.0f }, { IDs::decay, 1300.0f }, { IDs::sustain, 0.0f }, { IDs::release, 120.0f }, { IDs::cutoff, 4500.0f }, { IDs::reso, 0.15f }, { IDs::gain, -5.0f } };
    inline constexpr Value v31[] = { { IDs::driveType, 1.0f }, { IDs::drive, 1.0f }, { IDs::sub, 0.45f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 55.0f }, { IDs::decay, 1100.0f }, { IDs::sustain, 0.0f }, { IDs::release, 100.0f }, { IDs::cutoff, 2500.0f }, { IDs::reso, 0.2f }, { IDs::gain, -8.0f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -12.0f }, { IDs::compRatio, 4.0f }, { IDs::compMakeup, 4.0f } };
    inline constexpr Value v32[] = { { IDs::driveType, 0.0f }, { IDs::drive, 0.45f }, { IDs::sub, 0.55f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 55.0f }, { IDs::decay, 1900.0f }, { IDs::sustain, 0.0f }, { IDs::release, 160.0f }, { IDs::cutoff, 8000.0f }, { IDs::gain, -4.0f } };
    inline constexpr Value v33[] = { { IDs::driveType, 0.0f }, { IDs::drive, 0.5f }, { IDs::sub, 0.5f }, { IDs::pitchAmt, 16.0f }, { IDs::pitchTime, 50.0f }, { IDs::decay, 1700.0f }, { IDs::sustain, 0.0f }, { IDs::release, 140.0f }, { IDs::cutoff, 6000.0f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -22.0f }, { IDs::compRatio, 8.0f }, { IDs::compAttack, 4.0f }, { IDs::compRelease, 100.0f }, { IDs::compMakeup, 8.0f }, { IDs::compMix, 0.8f } };
    inline constexpr Value v34[] = { { IDs::wave, 2.0f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.9f }, { IDs::sub, 0.5f }, { IDs::click, 0.3f }, { IDs::pitchAmt, 22.0f }, { IDs::pitchTime, 45.0f }, { IDs::decay, 900.0f }, { IDs::sustain, 0.0f }, { IDs::release, 100.0f }, { IDs::cutoff, 3500.0f }, { IDs::reso, 0.3f }, { IDs::gain, -8.0f } };
    inline constexpr Value v35[] = { { IDs::wave, 11.0f }, { IDs::wtPos, 0.3f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.4f }, { IDs::sub, 0.5f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 50.0f }, { IDs::decay, 1300.0f }, { IDs::sustain, 0.0f }, { IDs::release, 120.0f }, { IDs::cutoff, 6000.0f }, { IDs::gain, -5.0f } };
    inline constexpr Value v36[] = { { IDs::wave, 6.0f }, { IDs::wtPos, 0.35f }, { IDs::sub, 0.5f }, { IDs::pitchAmt, 14.0f }, { IDs::pitchTime, 55.0f }, { IDs::decay, 1500.0f }, { IDs::sustain, 0.0f }, { IDs::release, 140.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 9000.0f } };
    inline constexpr Value v37[] = { { IDs::driveType, 1.0f }, { IDs::drive, 0.6f }, { IDs::sub, 0.35f }, { IDs::click, 0.3f }, { IDs::pitchAmt, 16.0f }, { IDs::pitchTime, 45.0f }, { IDs::decay, 1000.0f }, { IDs::sustain, 0.0f }, { IDs::release, 100.0f }, { IDs::cutoff, 3000.0f }, { IDs::reso, 0.35f }, { IDs::gain, -6.0f }, { IDs::eqMidF, 1500.0f }, { IDs::eqMidG, 3.0f }, { IDs::eqMidQ, 1.2f } };
    inline constexpr Value v38[] = { { IDs::driveType, 0.0f }, { IDs::drive, 0.5f }, { IDs::click, 0.8f }, { IDs::sub, 0.5f }, { IDs::pitchAmt, 18.0f }, { IDs::pitchTime, 40.0f }, { IDs::decay, 1400.0f }, { IDs::sustain, 0.0f }, { IDs::release, 120.0f }, { IDs::cutoff, 7000.0f }, { IDs::gain, -5.0f } };
    inline constexpr Value v39[] = { { IDs::sub, 0.4f }, { IDs::click, 0.15f }, { IDs::pitchAmt, 6.0f }, { IDs::pitchTime, 40.0f }, { IDs::glide, 120.0f }, { IDs::legato, 1.0f }, { IDs::decay, 2500.0f }, { IDs::sustain, 0.4f }, { IDs::release, 250.0f }, { IDs::drive, 0.3f } };
    inline constexpr Value v40[] = { { IDs::sub, 0.5f }, { IDs::pitchAmt, 4.0f }, { IDs::pitchTime, 40.0f }, { IDs::glide, 80.0f }, { IDs::legato, 1.0f }, { IDs::decay, 900.0f }, { IDs::sustain, 0.1f }, { IDs::release, 140.0f }, { IDs::drive, 0.2f } };
    inline constexpr Value v41[] = { { IDs::sub, 0.5f }, { IDs::pitchAmt, 3.0f }, { IDs::glide, 260.0f }, { IDs::legato, 1.0f }, { IDs::decay, 3000.0f }, { IDs::sustain, 0.5f }, { IDs::release, 300.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 9000.0f } };
    inline constexpr Value v42[] = { { IDs::wave, 1.0f }, { IDs::sub, 0.45f }, { IDs::pitchAmt, 0.0f }, { IDs::glide, 140.0f }, { IDs::legato, 1.0f }, { IDs::attack, 3.0f }, { IDs::decay, 2000.0f }, { IDs::sustain, 0.6f }, { IDs::release, 250.0f }, { IDs::drive, 0.25f }, { IDs::cutoff, 6000.0f } };
    inline constexpr Value v43[] = { { IDs::sub, 0.6f }, { IDs::click, 0.1f }, { IDs::pitchAmt, 10.0f }, { IDs::pitchTime, 60.0f }, { IDs::glide, 100.0f }, { IDs::legato, 1.0f }, { IDs::decay, 2800.0f }, { IDs::sustain, 0.3f }, { IDs::release, 300.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 1800.0f }, { IDs::reso, 0.15f } };
    inline constexpr Value v44[] = { { IDs::sub, 0.35f }, { IDs::click, 0.3f }, { IDs::pitchAmt, 6.0f }, { IDs::glide, 70.0f }, { IDs::legato, 1.0f }, { IDs::decay, 2200.0f }, { IDs::sustain, 0.25f }, { IDs::release, 200.0f }, { IDs::drive, 0.1f }, { IDs::cutoff, 16000.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.12f }, { IDs::detune2, 3.0f } };
    inline constexpr Value v45[] = { { IDs::wave2, 0.0f }, { IDs::level2, 0.4f }, { IDs::detune2, 8.0f }, { IDs::semis2, 0.0f }, { IDs::sub, 0.4f }, { IDs::pitchAmt, 6.0f }, { IDs::glide, 110.0f }, { IDs::legato, 1.0f }, { IDs::decay, 2400.0f }, { IDs::sustain, 0.4f }, { IDs::release, 250.0f }, { IDs::drive, 0.25f } };
    inline constexpr Value v46[] = { { IDs::sub, 0.55f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 5.0f }, { IDs::pitchTime, 30.0f }, { IDs::glide, 60.0f }, { IDs::legato, 1.0f }, { IDs::decay, 1200.0f }, { IDs::sustain, 0.0f }, { IDs::release, 120.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 9000.0f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -18.0f }, { IDs::compRatio, 4.0f }, { IDs::compMakeup, 3.0f } };
    inline constexpr Value v47[] = { { IDs::wave, 2.0f }, { IDs::sub, 0.55f }, { IDs::click, 0.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 18.0f }, { IDs::level2, 0.9f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 6.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.85f }, { IDs::release, 220.0f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.35f }, { IDs::cutoff, 1400.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v48[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.95f }, { IDs::detune2, 14.0f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 8.0f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 1800.0f }, { IDs::reso, 0.25f } };
    inline constexpr Value v49[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 1.0f }, { IDs::detune2, 24.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 10.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 300.0f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.35f }, { IDs::cutoff, 2400.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v50[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.85f }, { IDs::detune2, 12.0f }, { IDs::sub, 0.6f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 6.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 800.0f }, { IDs::reso, 0.35f } };
    inline constexpr Value v51[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.9f }, { IDs::detune2, 16.0f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 6.0f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoRate, 0.3f }, { IDs::lfoDepth, 0.35f }, { IDs::drive, 0.3f }, { IDs::cutoff, 1200.0f }, { IDs::reso, 0.35f } };
    inline constexpr Value v52[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.9f }, { IDs::detune2, 18.0f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::lfoShape, 6.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 3.0f }, { IDs::lfoDepth, 0.5f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 1500.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v53[] = { { IDs::wave, 2.0f }, { IDs::wave2, 3.0f }, { IDs::level2, 0.7f }, { IDs::detune2, 7.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.6f }, { IDs::cutoff, 2600.0f }, { IDs::reso, 0.45f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.4f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -18.0f }, { IDs::compRatio, 4.0f }, { IDs::compMakeup, 3.0f } };
    inline constexpr Value v54[] = { { IDs::wave, 6.0f }, { IDs::wtPos, 0.5f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.6f }, { IDs::detune2, 11.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.9f }, { IDs::release, 180.0f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 5.0f }, { IDs::lfoDepth, 0.5f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.4f }, { IDs::cutoff, 3500.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v55[] = { { IDs::wave, 12.0f }, { IDs::wtPos, 0.55f }, { IDs::wave2, 12.0f }, { IDs::wtPos2, 0.3f }, { IDs::level2, 0.7f }, { IDs::semis2, 7.0f }, { IDs::detune2, 9.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.9f }, { IDs::release, 180.0f }, { IDs::lfoShape, 6.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 4.0f }, { IDs::lfoDepth, 0.45f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.45f }, { IDs::cutoff, 4000.0f }, { IDs::reso, 0.25f } };
    inline constexpr Value v56[] = { { IDs::wave, 8.0f }, { IDs::wtPos, 0.4f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.5f }, { IDs::detune2, 10.0f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.9f }, { IDs::release, 180.0f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 5.0f }, { IDs::lfoDepth, 0.6f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.35f }, { IDs::cutoff, 3000.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v57[] = { { IDs::wave, 11.0f }, { IDs::wtPos, 0.5f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.6f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.9f }, { IDs::release, 180.0f }, { IDs::lfoShape, 4.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 7.0f }, { IDs::lfoDepth, 0.5f }, { IDs::drive, 0.3f }, { IDs::cutoff, 5000.0f }, { IDs::reso, 0.25f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -16.0f }, { IDs::compRatio, 3.0f }, { IDs::compMakeup, 2.0f } };
    inline constexpr Value v58[] = { { IDs::wave, 10.0f }, { IDs::wtPos, 0.5f }, { IDs::wave2, 10.0f }, { IDs::wtPos2, 0.8f }, { IDs::level2, 0.65f }, { IDs::detune2, 13.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.9f }, { IDs::release, 180.0f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.5f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.4f }, { IDs::cutoff, 3500.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v59[] = { { IDs::wave, 12.0f }, { IDs::wtPos, 0.35f }, { IDs::wave2, 2.0f }, { IDs::detune2, 14.0f }, { IDs::level2, 0.6f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 5.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.85f }, { IDs::release, 220.0f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 4.0f }, { IDs::lfoDepth, 0.4f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 2000.0f }, { IDs::reso, 0.2f }, { IDs::eqLoF, 80.0f }, { IDs::eqLoG, 3.0f }, { IDs::eqHiG, -2.0f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -16.0f }, { IDs::compRatio, 3.0f }, { IDs::compMakeup, 2.0f } };
    inline constexpr Value v60[] = { { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoRate, 3.0f }, { IDs::lfoDepth, 0.55f }, { IDs::cutoff, 700.0f }, { IDs::reso, 0.45f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v61[] = { { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.6f }, { IDs::cutoff, 600.0f }, { IDs::reso, 0.45f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -18.0f }, { IDs::compRatio, 4.0f }, { IDs::compMakeup, 3.0f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v62[] = { { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 5.0f }, { IDs::lfoDepth, 0.7f }, { IDs::cutoff, 500.0f }, { IDs::reso, 0.5f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v63[] = { { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 7.0f }, { IDs::lfoDepth, 0.5f }, { IDs::cutoff, 900.0f }, { IDs::reso, 0.4f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v64[] = { { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 11.0f }, { IDs::lfoDepth, 0.6f }, { IDs::cutoff, 650.0f }, { IDs::reso, 0.45f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v65[] = { { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 15.0f }, { IDs::lfoDepth, 0.6f }, { IDs::cutoff, 650.0f }, { IDs::reso, 0.45f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v66[] = { { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 4.0f }, { IDs::lfoDepth, 0.75f }, { IDs::cutoff, 450.0f }, { IDs::reso, 0.55f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.6f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v67[] = { { IDs::lfoShape, 3.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.5f }, { IDs::cutoff, 700.0f }, { IDs::reso, 0.4f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v68[] = { { IDs::lfoShape, 2.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.65f }, { IDs::cutoff, 600.0f }, { IDs::reso, 0.45f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v69[] = { { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 2.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.8f }, { IDs::cutoff, 3000.0f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.3f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.3f }, { IDs::driveType, 2.0f } };
    inline constexpr Value v70[] = { { IDs::lfoShape, 2.0f }, { IDs::lfoTarget, 0.0f }, { IDs::lfoSync, 5.0f }, { IDs::lfoDepth, 0.6f }, { IDs::cutoff, 3000.0f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.3f } };
    inline constexpr Value v71[] = { { IDs::wave, 0.0f }, { IDs::sub, 0.7f }, { IDs::level2, 0.0f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.1f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 3.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.8f }, { IDs::cutoff, 5000.0f } };
    inline constexpr Value v72[] = { { IDs::wave, 2.0f }, { IDs::sub, 0.5f }, { IDs::level2, 0.0f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 1.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.95f }, { IDs::release, 60.0f }, { IDs::drive, 0.3f }, { IDs::lfoShape, 3.0f }, { IDs::lfoTarget, 3.0f }, { IDs::lfoSync, 7.0f }, { IDs::lfoDepth, 1.0f }, { IDs::cutoff, 2500.0f } };
    inline constexpr Value v73[] = { { IDs::lfoShape, 4.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 7.0f }, { IDs::lfoDepth, 0.7f }, { IDs::cutoff, 600.0f }, { IDs::reso, 0.5f }, { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::detune2, 12.0f }, { IDs::level2, 0.5f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f } };
    inline constexpr Value v74[] = { { IDs::wave, 6.0f }, { IDs::wtPos, 0.55f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 5.0f }, { IDs::lfoDepth, 0.6f }, { IDs::attack, 3.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.8f }, { IDs::release, 160.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 3000.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v75[] = { { IDs::wave, 9.0f }, { IDs::wtPos, 0.2f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 3.0f }, { IDs::lfoDepth, 0.9f }, { IDs::attack, 4.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.9f }, { IDs::release, 200.0f }, { IDs::drive, 0.25f }, { IDs::cutoff, 4000.0f } };
    inline constexpr Value v76[] = { { IDs::wave, 9.0f }, { IDs::wtPos, 0.1f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 6.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 2.0f }, { IDs::lfoDepth, 1.0f }, { IDs::attack, 6.0f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 5000.0f } };
    inline constexpr Value v77[] = { { IDs::wave, 9.0f }, { IDs::wtPos, 0.5f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 5.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 5.0f }, { IDs::lfoDepth, 0.8f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.4f }, { IDs::cutoff, 5000.0f } };
    inline constexpr Value v78[] = { { IDs::wave, 9.0f }, { IDs::wtPos, 0.7f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.4f }, { IDs::detune2, 9.0f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.9f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.35f }, { IDs::cutoff, 4500.0f } };
    inline constexpr Value v79[] = { { IDs::wave, 10.0f }, { IDs::wtPos, 0.6f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.7f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.35f }, { IDs::cutoff, 3500.0f } };
    inline constexpr Value v80[] = { { IDs::wave, 6.0f }, { IDs::wtPos, 0.8f }, { IDs::wave2, 8.0f }, { IDs::wtPos2, 0.5f }, { IDs::level2, 0.5f }, { IDs::detune2, 8.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 7.0f }, { IDs::lfoDepth, 0.4f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.5f }, { IDs::cutoff, 2800.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v81[] = { { IDs::wave, 12.0f }, { IDs::wtPos, 0.6f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 6.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 4.0f }, { IDs::lfoDepth, 0.6f }, { IDs::attack, 2.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.9f }, { IDs::release, 150.0f }, { IDs::drive, 0.4f }, { IDs::cutoff, 1500.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v82[] = { { IDs::wave, 9.0f }, { IDs::wtPos, 0.3f }, { IDs::wave2, 9.0f }, { IDs::wtPos2, 0.8f }, { IDs::level2, 0.6f }, { IDs::detune2, 8.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoRate, 0.4f }, { IDs::lfoDepth, 0.6f }, { IDs::attack, 10.0f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.9f }, { IDs::release, 300.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 6000.0f } };
    inline constexpr Value v83[] = { { IDs::wave, 8.0f }, { IDs::wtPos, 0.8f }, { IDs::sub, 0.35f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::lfoShape, 2.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.6f }, { IDs::attack, 1.0f }, { IDs::decay, 400.0f }, { IDs::sustain, 0.9f }, { IDs::release, 120.0f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.5f }, { IDs::cutoff, 3800.0f }, { IDs::reso, 0.5f } };
    inline constexpr Value v84[] = { { IDs::wave, 1.0f }, { IDs::sub, 0.7f }, { IDs::click, 0.5f }, { IDs::pitchAmt, 30.0f }, { IDs::pitchTime, 30.0f }, { IDs::decay, 220.0f }, { IDs::sustain, 0.0f }, { IDs::release, 60.0f }, { IDs::drive, 0.2f } };
    inline constexpr Value v85[] = { { IDs::sub, 0.7f }, { IDs::click, 0.4f }, { IDs::pitchAmt, 12.0f }, { IDs::pitchTime, 25.0f }, { IDs::attack, 0.5f }, { IDs::decay, 280.0f }, { IDs::sustain, 0.0f }, { IDs::release, 60.0f }, { IDs::drive, 0.1f }, { IDs::cutoff, 6000.0f } };
    inline constexpr Value v86[] = { { IDs::wave, 3.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 5.0f }, { IDs::pitchTime, 40.0f }, { IDs::decay, 350.0f }, { IDs::sustain, 0.0f }, { IDs::release, 80.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 2200.0f }, { IDs::reso, 0.25f } };
    inline constexpr Value v87[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.5f }, { IDs::detune2, 9.0f }, { IDs::sub, 0.35f }, { IDs::click, 0.1f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 260.0f }, { IDs::sustain, 0.0f }, { IDs::release, 90.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 1800.0f }, { IDs::reso, 0.35f } };
    inline constexpr Value v88[] = { { IDs::wave, 5.0f }, { IDs::wtPos, 0.4f }, { IDs::sub, 0.5f }, { IDs::click, 0.1f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 420.0f }, { IDs::sustain, 0.0f }, { IDs::release, 100.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 2800.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v89[] = { { IDs::wave, 1.0f }, { IDs::sub, 0.6f }, { IDs::click, 0.9f }, { IDs::pitchAmt, 20.0f }, { IDs::pitchTime, 15.0f }, { IDs::decay, 160.0f }, { IDs::sustain, 0.0f }, { IDs::release, 40.0f }, { IDs::drive, 0.1f } };
    inline constexpr Value v90[] = { { IDs::wave, 3.0f }, { IDs::sub, 0.3f }, { IDs::click, 0.4f }, { IDs::pitchAmt, 12.0f }, { IDs::pitchTime, 20.0f }, { IDs::decay, 120.0f }, { IDs::sustain, 0.0f }, { IDs::release, 40.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 4500.0f } };
    inline constexpr Value v91[] = { { IDs::wave, 12.0f }, { IDs::wtPos, 0.5f }, { IDs::sub, 0.4f }, { IDs::click, 0.3f }, { IDs::pitchAmt, 4.0f }, { IDs::pitchTime, 30.0f }, { IDs::decay, 300.0f }, { IDs::sustain, 0.0f }, { IDs::release, 80.0f }, { IDs::drive, 0.1f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v92[] = { { IDs::wave, 6.0f }, { IDs::wtPos, 0.4f }, { IDs::sub, 0.4f }, { IDs::click, 0.2f }, { IDs::pitchAmt, 3.0f }, { IDs::decay, 380.0f }, { IDs::sustain, 0.0f }, { IDs::release, 90.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 4000.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v93[] = { { IDs::wave, 2.0f }, { IDs::sub, 0.5f }, { IDs::click, 0.1f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 1.0f }, { IDs::decay, 200.0f }, { IDs::sustain, 0.6f }, { IDs::release, 50.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 1500.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v94[] = { { IDs::sub, 0.5f }, { IDs::click, 0.3f }, { IDs::pitchAmt, 10.0f }, { IDs::pitchTime, 35.0f }, { IDs::glide, 40.0f }, { IDs::legato, 1.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.0f }, { IDs::release, 90.0f }, { IDs::drive, 0.15f } };
    inline constexpr Value v95[] = { { IDs::wave, 2.0f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 3.0f }, { IDs::decay, 400.0f }, { IDs::sustain, 0.8f }, { IDs::release, 120.0f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.5f }, { IDs::cutoff, 900.0f }, { IDs::reso, 0.35f } };
    inline constexpr Value v96[] = { { IDs::wave, 3.0f }, { IDs::sub, 0.6f }, { IDs::pitchAmt, 3.0f }, { IDs::pitchTime, 80.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.6f }, { IDs::release, 200.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 500.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v97[] = { { IDs::wave, 5.0f }, { IDs::wtPos, 0.3f }, { IDs::sub, 0.6f }, { IDs::click, 0.05f }, { IDs::pitchAmt, 2.0f }, { IDs::pitchTime, 50.0f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoRate, 0.8f }, { IDs::lfoDepth, 0.7f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.7f }, { IDs::release, 180.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 2500.0f } };
    inline constexpr Value v98[] = { { IDs::wave, 2.0f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 400.0f }, { IDs::sustain, 0.8f }, { IDs::release, 150.0f }, { IDs::drive, 0.25f }, { IDs::cutoff, 2000.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v99[] = { { IDs::wave, 3.0f }, { IDs::sub, 0.4f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 400.0f }, { IDs::sustain, 0.8f }, { IDs::release, 150.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 1400.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v100[] = { { IDs::wave, 2.0f }, { IDs::sub, 0.2f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::glide, 60.0f }, { IDs::legato, 1.0f }, { IDs::attack, 1.0f }, { IDs::decay, 280.0f }, { IDs::sustain, 0.25f }, { IDs::release, 80.0f }, { IDs::drive, 0.4f }, { IDs::cutoff, 450.0f }, { IDs::reso, 0.8f }, { IDs::lfoShape, 2.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.4f } };
    inline constexpr Value v101[] = { { IDs::wave, 1.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.35f }, { IDs::detune2, 4.0f }, { IDs::sub, 0.5f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.7f }, { IDs::release, 200.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 900.0f }, { IDs::reso, 0.35f } };
    inline constexpr Value v102[] = { { IDs::wave, 2.0f }, { IDs::sub, 0.35f }, { IDs::click, 0.35f }, { IDs::pitchAmt, 2.0f }, { IDs::pitchTime, 30.0f }, { IDs::decay, 350.0f }, { IDs::sustain, 0.35f }, { IDs::release, 80.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 1600.0f }, { IDs::reso, 0.4f }, { IDs::eqMidF, 800.0f }, { IDs::eqMidG, 3.0f } };
    inline constexpr Value v103[] = { { IDs::wave, 5.0f }, { IDs::wtPos, 0.5f }, { IDs::sub, 0.45f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 500.0f }, { IDs::sustain, 0.7f }, { IDs::release, 150.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 1800.0f }, { IDs::reso, 0.25f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoRate, 0.6f }, { IDs::lfoDepth, 0.3f } };
    inline constexpr Value v104[] = { { IDs::wave, 3.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.5f }, { IDs::detune2, 7.0f }, { IDs::sub, 0.45f }, { IDs::pitchAmt, 6.0f }, { IDs::pitchTime, 40.0f }, { IDs::decay, 300.0f }, { IDs::sustain, 0.5f }, { IDs::release, 90.0f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.35f }, { IDs::cutoff, 2800.0f }, { IDs::reso, 0.3f } };
    inline constexpr Value v105[] = { { IDs::wave, 8.0f }, { IDs::wtPos, 0.5f }, { IDs::sub, 0.4f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 450.0f }, { IDs::sustain, 0.7f }, { IDs::release, 150.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 3500.0f }, { IDs::reso, 0.2f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoRate, 0.5f }, { IDs::lfoDepth, 0.4f } };
    inline constexpr Value v106[] = { { IDs::wave, 10.0f }, { IDs::wtPos, 0.2f }, { IDs::sub, 0.55f }, { IDs::pitchAmt, 0.0f }, { IDs::decay, 600.0f }, { IDs::sustain, 0.75f }, { IDs::release, 180.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 1200.0f }, { IDs::reso, 0.15f } };
    inline constexpr Value v107[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.8f }, { IDs::detune2, 20.0f }, { IDs::sub, 0.5f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 3.0f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.85f }, { IDs::release, 220.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 2200.0f }, { IDs::compOn, 1.0f }, { IDs::compThresh, -18.0f }, { IDs::compRatio, 3.0f }, { IDs::compMakeup, 2.0f } };
    inline constexpr Value v108[] = { { IDs::wave, 4.0f }, { IDs::wtPos, 0.1f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 3.0f }, { IDs::lfoDepth, 0.9f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 5000.0f } };
    inline constexpr Value v109[] = { { IDs::wave, 4.0f }, { IDs::wtPos, 0.5f }, { IDs::lfoShape, 6.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoRate, 0.12f }, { IDs::lfoDepth, 1.0f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 30.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 400.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 6000.0f } };
    inline constexpr Value v110[] = { { IDs::wave, 7.0f }, { IDs::wtPos, 0.2f }, { IDs::lfoShape, 5.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 2.0f }, { IDs::lfoDepth, 0.9f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v111[] = { { IDs::wave, 5.0f }, { IDs::wtPos, 0.5f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoRate, 0.35f }, { IDs::lfoDepth, 0.8f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v112[] = { { IDs::wave, 6.0f }, { IDs::wtPos, 0.4f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoRate, 0.2f }, { IDs::lfoDepth, 0.8f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v113[] = { { IDs::wave, 8.0f }, { IDs::wtPos, 0.3f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 4.0f }, { IDs::lfoDepth, 0.9f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v114[] = { { IDs::wave, 9.0f }, { IDs::wtPos, 0.5f }, { IDs::lfoShape, 1.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 2.0f }, { IDs::lfoDepth, 1.0f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v115[] = { { IDs::wave, 12.0f }, { IDs::wtPos, 0.4f }, { IDs::lfoShape, 6.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoRate, 0.25f }, { IDs::lfoDepth, 0.9f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v116[] = { { IDs::wave, 10.0f }, { IDs::wtPos, 0.5f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 5.0f }, { IDs::lfoDepth, 0.8f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.15f }, { IDs::cutoff, 7000.0f } };
    inline constexpr Value v117[] = { { IDs::wave, 11.0f }, { IDs::wtPos, 0.5f }, { IDs::lfoShape, 6.0f }, { IDs::lfoTarget, 4.0f }, { IDs::lfoSync, 6.0f }, { IDs::lfoDepth, 0.8f }, { IDs::sub, 0.45f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 4.0f }, { IDs::decay, 800.0f }, { IDs::sustain, 0.9f }, { IDs::release, 250.0f }, { IDs::drive, 0.25f }, { IDs::cutoff, 7000.0f }, { IDs::driveType, 1.0f } };
    inline constexpr Value v118[] = { { IDs::wave, 2.0f }, { IDs::sub, 0.0f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 48.0f }, { IDs::pitchTime, 350.0f }, { IDs::decay, 700.0f }, { IDs::sustain, 0.0f }, { IDs::release, 200.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 9000.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v119[] = { { IDs::sub, 0.5f }, { IDs::pitchAmt, 40.0f }, { IDs::pitchTime, 480.0f }, { IDs::attack, 1.0f }, { IDs::decay, 2500.0f }, { IDs::sustain, 0.0f }, { IDs::release, 800.0f }, { IDs::drive, 0.2f }, { IDs::cutoff, 2500.0f } };
    inline constexpr Value v120[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 0.6f }, { IDs::detune2, 22.0f }, { IDs::sub, 0.2f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 500.0f }, { IDs::decay, 3000.0f }, { IDs::sustain, 1.0f }, { IDs::release, 800.0f }, { IDs::lfoShape, 5.0f }, { IDs::lfoTarget, 1.0f }, { IDs::lfoRate, 0.08f }, { IDs::lfoDepth, 1.0f }, { IDs::drive, 0.3f }, { IDs::cutoff, 600.0f }, { IDs::reso, 0.4f } };
    inline constexpr Value v121[] = { { IDs::wave, 2.0f }, { IDs::click, 1.0f }, { IDs::sub, 0.2f }, { IDs::pitchAmt, 20.0f }, { IDs::pitchTime, 25.0f }, { IDs::decay, 150.0f }, { IDs::sustain, 0.0f }, { IDs::release, 60.0f }, { IDs::driveType, 1.0f }, { IDs::drive, 0.5f }, { IDs::cutoff, 10000.0f } };
    inline constexpr Value v122[] = { { IDs::wave, 3.0f }, { IDs::sub, 0.0f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 0.0f }, { IDs::attack, 1.0f }, { IDs::sustain, 1.0f }, { IDs::decay, 500.0f }, { IDs::release, 100.0f }, { IDs::lfoShape, 3.0f }, { IDs::lfoTarget, 0.0f }, { IDs::lfoSync, 7.0f }, { IDs::lfoDepth, 0.5f }, { IDs::drive, 0.2f }, { IDs::cutoff, 3500.0f }, { IDs::reso, 0.2f } };
    inline constexpr Value v123[] = { { IDs::wave, 2.0f }, { IDs::wave2, 2.0f }, { IDs::level2, 1.0f }, { IDs::detune2, 40.0f }, { IDs::sub, 0.0f }, { IDs::click, 0.0f }, { IDs::pitchAmt, 6.0f }, { IDs::pitchTime, 120.0f }, { IDs::glide, 80.0f }, { IDs::legato, 1.0f }, { IDs::attack, 2.0f }, { IDs::decay, 400.0f }, { IDs::sustain, 0.8f }, { IDs::release, 200.0f }, { IDs::lfoShape, 0.0f }, { IDs::lfoTarget, 0.0f }, { IDs::lfoRate, 5.5f }, { IDs::lfoDepth, 0.08f }, { IDs::driveType, 2.0f }, { IDs::drive, 0.5f }, { IDs::cutoff, 4500.0f }, { IDs::reso, 0.3f } };

    inline const std::vector<Preset>& all()
    {
        static const std::vector<Preset> presets
        {
        { "Init", "Init", nullptr, 0 },
        { "808", "808 Classic", v1, 10 },
        { "808", "808 Clean", v2, 9 },
        { "808", "808 Long Tail", v3, 8 },
        { "808", "808 Short Tap", v4, 8 },
        { "808", "808 Soft", v5, 11 },
        { "808", "808 Punchy", v6, 14 },
        { "808", "808 Deep", v7, 10 },
        { "808", "808 Tuned Up", v8, 8 },
        { "808", "808 Boom Bap", v9, 10 },
        { "808", "808 Warm Tube", v10, 10 },
        { "808", "808 Triangle", v11, 9 },
        { "808", "808 Mellow", v12, 11 },
        { "808", "808 Kick-Bass", v13, 15 },
        { "808", "808 Rubber", v14, 10 },
        { "808", "808 Sine+Saw", v15, 11 },
        { "Sub & Boom", "Sub Boom", v16, 9 },
        { "Sub & Boom", "Pure Sub", v17, 10 },
        { "Sub & Boom", "Sub Rumble", v18, 14 },
        { "Sub & Boom", "Sub Floor", v19, 10 },
        { "Sub & Boom", "Sub Drop", v20, 8 },
        { "Sub & Boom", "Sub Thump", v21, 9 },
        { "Sub & Boom", "Sub Warm", v22, 11 },
        { "Sub & Boom", "Cinema Boom", v23, 13 },
        { "Sub & Boom", "Octave Sub", v24, 12 },
        { "Sub & Boom", "Sub Tight", v25, 15 },
        { "Sub & Boom", "Tight Sub Comp", v26, 17 },
        { "Distorted", "Distorted 808", v27, 10 },
        { "Distorted", "808 Hard Clip", v28, 11 },
        { "Distorted", "808 Fold Dirt", v29, 11 },
        { "Distorted", "808 Crunch", v30, 12 },
        { "Distorted", "808 Fuzz", v31, 16 },
        { "Distorted", "808 Overdrive", v32, 10 },
        { "Distorted", "808 Saturated Comp", v33, 16 },
        { "Distorted", "808 Wrecked", v34, 13 },
        { "Distorted", "808 Bitten", v35, 13 },
        { "Distorted", "808 Wavefolder", v36, 10 },
        { "Distorted", "808 Radio", v37, 15 },
        { "Distorted", "808 Gritty Click", v38, 11 },
        { "Trap & Slides", "Trap Slide", v39, 10 },
        { "Trap & Slides", "Slide Short", v40, 9 },
        { "Trap & Slides", "Slide Long", v41, 9 },
        { "Trap & Slides", "Glide Legato", v42, 11 },
        { "Trap & Slides", "Trap Dark", v43, 12 },
        { "Trap & Slides", "Trap Hi-Fi", v44, 13 },
        { "Trap & Slides", "Trap Detune Slide", v45, 12 },
        { "Trap & Slides", "Drill Slide", v46, 15 },
        { "Reese & Neuro", "Reese Detune", v47, 15 },
        { "Reese & Neuro", "Reese Classic", v48, 14 },
        { "Reese & Neuro", "Reese Wide", v49, 15 },
        { "Reese & Neuro", "Reese Dark", v50, 14 },
        { "Reese & Neuro", "Reese Filtered", v51, 18 },
        { "Reese & Neuro", "Reese Moving", v52, 18 },
        { "Reese & Neuro", "Neuro Bite", v53, 23 },
        { "Reese & Neuro", "Neuro Fold", v54, 19 },
        { "Reese & Neuro", "Neuro FM", v55, 21 },
        { "Reese & Neuro", "Neuro Sync", v56, 19 },
        { "Reese & Neuro", "Neuro Digital", v57, 21 },
        { "Reese & Neuro", "Neuro Phase", v58, 20 },
        { "Reese & Neuro", "FM Reese", v59, 27 },
        { "Wobble & Dubstep", "Dub Wobble", v60, 18 },
        { "Wobble & Dubstep", "Wobble 1/8", v61, 22 },
        { "Wobble & Dubstep", "Wobble 1/4", v62, 18 },
        { "Wobble & Dubstep", "Wobble 1/16", v63, 18 },
        { "Wobble & Dubstep", "Wobble Triplet", v64, 18 },
        { "Wobble & Dubstep", "Wobble Dotted", v65, 18 },
        { "Wobble & Dubstep", "Half-time Wub", v66, 18 },
        { "Wobble & Dubstep", "Wobble Square", v67, 18 },
        { "Wobble & Dubstep", "Wobble Saw Down", v68, 18 },
        { "Wobble & Dubstep", "Wobble Fold", v69, 18 },
        { "Wobble & Dubstep", "Pitch Dive Wobble", v70, 17 },
        { "Wobble & Dubstep", "Tremolo Sub", v71, 15 },
        { "Wobble & Dubstep", "Stutter Gate", v72, 15 },
        { "Wobble & Dubstep", "Random Wub", v73, 18 },
        { "Growl & Vowel", "Fold Growl", v74, 16 },
        { "Growl & Vowel", "Vowel Talk", v75, 15 },
        { "Growl & Vowel", "Vowel Slow", v76, 15 },
        { "Growl & Vowel", "Yoi Growl", v77, 16 },
        { "Growl & Vowel", "Mouth Bass", v78, 18 },
        { "Growl & Vowel", "Phase Growl", v79, 16 },
        { "Growl & Vowel", "Growl Mean", v80, 21 },
        { "Growl & Vowel", "Growl Throat", v81, 16 },
        { "Growl & Vowel", "Growl Choir", v82, 19 },
        { "Growl & Vowel", "Growl Screech", v83, 17 },
        { "Pluck & Short", "Short Punch", v84, 9 },
        { "Pluck & Short", "Pluck Sub", v85, 10 },
        { "Pluck & Short", "Pluck Square", v86, 11 },
        { "Pluck & Short", "Stab Saw", v87, 13 },
        { "Pluck & Short", "Pluck PWM", v88, 11 },
        { "Pluck & Short", "Tick Bass", v89, 9 },
        { "Pluck & Short", "Blip", v90, 10 },
        { "Pluck & Short", "Plink FM", v91, 11 },
        { "Pluck & Short", "Pluck Fold", v92, 11 },
        { "Pluck & Short", "Staccato", v93, 11 },
        { "Pluck & Short", "Rubber Pluck", v94, 10 },
        { "Synth Bass", "Saw Growl", v95, 12 },
        { "Synth Bass", "Square Rumble", v96, 10 },
        { "Synth Bass", "PWM Mono", v97, 15 },
        { "Synth Bass", "Mono Saw", v98, 10 },
        { "Synth Bass", "Mono Square", v99, 10 },
        { "Synth Bass", "Acid Bass", v100, 17 },
        { "Synth Bass", "Moog-ish Triangle", v101, 12 },
        { "Synth Bass", "Funk Bass", v102, 13 },
        { "Synth Bass", "Analog Pulse", v103, 14 },
        { "Synth Bass", "Electro Bass", v104, 14 },
        { "Synth Bass", "Sync Lead Bass", v105, 14 },
        { "Synth Bass", "Hollow Bass", v106, 10 },
        { "Synth Bass", "Wide Saw Bass", v107, 17 },
        { "Wavetable Morph", "Morph Sweep", v108, 15 },
        { "Wavetable Morph", "Slow Evolve", v109, 15 },
        { "Wavetable Morph", "Harmonics Rise", v110, 15 },
        { "Wavetable Morph", "PWM Sweep", v111, 15 },
        { "Wavetable Morph", "Fold Evolve", v112, 15 },
        { "Wavetable Morph", "Sync Sweep", v113, 15 },
        { "Wavetable Morph", "Vowel Cycle", v114, 15 },
        { "Wavetable Morph", "FM Evolve", v115, 15 },
        { "Wavetable Morph", "Phase Morph", v116, 15 },
        { "Wavetable Morph", "Digital Crush Morph", v117, 16 },
        { "FX & Experimental", "Laser Drop", v118, 11 },
        { "FX & Experimental", "Pitch Bomb", v119, 9 },
        { "FX & Experimental", "Riser Saw", v120, 18 },
        { "FX & Experimental", "Noise Hit", v121, 11 },
        { "FX & Experimental", "Alarm", v122, 15 },
        { "FX & Experimental", "Hoover Bass", v123, 22 },
        };
        return presets;
    }
}
