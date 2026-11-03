#!/usr/bin/env python3
"""Generuje Source/FactoryPresets.h (presety fabryczne BASSORA).

Uruchom z katalogu projektu:   python tools/gen_presets.py
Wartości nieujęte w presecie = domyślne wartości parametrów (patrz PluginProcessor.cpp).
"""
import pathlib, sys

WAVES = ["Sine", "Triangle", "Saw", "Square", "Morph", "PWM", "Fold", "Harmonics", "Sync", "Vowel", "Phase Dist", "Digital", "FM"]
SHAPES = ["Sine", "Tri", "Saw", "Square", "S&H", "Ramp", "Smooth"]
TARGETS = ["Pitch", "Cutoff", "Drive", "Amp", "Morph"]
SYNCS = ["Free", "4 Bar", "2 Bar", "1 Bar", "1/2", "1/4", "1/8", "1/16", "1/32",
         "1/2T", "1/4T", "1/8T", "1/16T", "1/2D", "1/4D", "1/8D", "1/16D"]

# skrót -> (ID parametru, zakres min, max, lista nazw dla parametrów wyborowych)
KEYS = {
    "wave": ("wave", 0, 12, WAVES), "wt": ("wtPos", 0, 1, None), "tune": ("tune", -12, 12, None),
    "sub": ("sub", 0, 1, None), "click": ("click", 0, 1, None),
    "wave2": ("wave2", 0, 12, WAVES), "wt2": ("wtPos2", 0, 1, None), "semi2": ("semis2", -24, 24, None),
    "det2": ("detune2", -100, 100, None), "lvl2": ("level2", 0, 1, None),
    "pamt": ("pitchAmt", 0, 48, None), "ptime": ("pitchTime", 5, 500, None), "glide": ("glide", 0, 1000, None),
    "legato": ("legato", 0, 1, None),
    "lshape": ("lfoShape", 0, 6, SHAPES), "ltarget": ("lfoTarget", 0, 4, TARGETS), "lsync": ("lfoSync", 0, 16, SYNCS),
    "lrate": ("lfoRate", 0.05, 30, None), "ldepth": ("lfoDepth", 0, 1, None),
    "a": ("attack", 0.5, 500, None), "d": ("decay", 5, 4000, None), "s": ("sustain", 0, 1, None), "r": ("release", 5, 4000, None),
    "dtype": ("driveType", 0, 2, ["Soft", "Hard", "Fold"]), "drive": ("drive", 0, 1, None),
    "cut": ("cutoff", 20, 20000, None), "res": ("reso", 0, 1, None), "gain": ("gain", -24, 6, None),
    "m1": ("macro1", 0, 1, None), "m2": ("macro2", 0, 1, None), "m3": ("macro3", 0, 1, None), "m4": ("macro4", 0, 1, None),
    "eq": ("eqOn", 0, 1, None),
    "eq_lf": ("eqLoF", 20, 500, None), "eq_lg": ("eqLoG", -12, 12, None),
    "eq_mf": ("eqMidF", 100, 8000, None), "eq_mg": ("eqMidG", -12, 12, None), "eq_mq": ("eqMidQ", 0.2, 8, None),
    "eq_hf": ("eqHiF", 1000, 16000, None), "eq_hg": ("eqHiG", -12, 12, None),
    "comp": ("compOn", 0, 1, None), "cth": ("compThresh", -60, 0, None), "cratio": ("compRatio", 1, 20, None),
    "catt": ("compAttack", 0.1, 100, None), "crel": ("compRelease", 10, 1000, None),
    "cmk": ("compMakeup", 0, 24, None), "cmix": ("compMix", 0, 1, None),
}

CATS = ["Init", "808", "Sub & Boom", "Distorted", "Trap & Slides", "Reese & Neuro", "Wobble & Dubstep",
        "Growl & Vowel", "Pluck & Short", "Synth Bass", "Wavetable Morph", "FX & Experimental"]

PRESETS = []   # (kategoria, nazwa, {skrót: wartość})


def P(cat, name, **kw):
    PRESETS.append((cat, name, kw))


# ----------------------------------------------------------------------------- Init
P("Init", "Init")

# ----------------------------------------------------------------------------- 808
P("808", "808 Classic", sub=.5, click=.2, pamt=14, ptime=55, a=1, d=1800, s=0, r=150, drive=.15, cut=12000)
P("808", "808 Clean", sub=.55, click=.12, pamt=10, ptime=50, d=2200, s=0, r=180, drive=.05, cut=14000)
P("808", "808 Long Tail", sub=.6, pamt=14, ptime=60, d=3600, s=0, r=400, drive=.1, cut=9000)
P("808", "808 Short Tap", sub=.5, click=.3, pamt=18, ptime=35, d=450, s=0, r=80, drive=.1)
P("808", "808 Soft", sub=.45, click=.05, pamt=8, ptime=70, a=6, d=1800, s=0, r=200, cut=2800, res=.05, drive=0)
P("808", "808 Punchy", sub=.55, click=.45, pamt=26, ptime=28, d=1400, s=0, r=120, drive=.2,
  comp=1, cth=-16, cratio=4, catt=8, crel=90, cmk=3)
P("808", "808 Deep", tune=-3, sub=.75, click=.08, pamt=20, ptime=85, d=2600, s=0, r=300, cut=3500, drive=.05)
P("808", "808 Tuned Up", tune=4, sub=.5, pamt=12, ptime=45, d=1500, s=0, r=130, drive=.12)
P("808", "808 Boom Bap", wave="Triangle", sub=.6, click=.35, pamt=10, ptime=40, d=900, s=0, r=140, drive=.2, cut=6000)
P("808", "808 Warm Tube", sub=.5, pamt=12, ptime=55, d=2000, s=0, r=160, drive=.3, cut=5200, eq_hf=4000, eq_hg=-3)
P("808", "808 Triangle", wave="Triangle", sub=.4, click=.2, pamt=14, ptime=55, d=2000, s=0, r=150, drive=.15)
P("808", "808 Mellow", sub=.5, click=0, pamt=6, ptime=80, a=4, d=2200, s=0, r=250, cut=1800, res=.1, drive=.05)
P("808", "808 Kick-Bass", sub=.7, click=.5, pamt=32, ptime=22, d=520, s=0, r=70, drive=.25, cut=8000,
  comp=1, cth=-14, cratio=6, catt=3, crel=60, cmk=4)
P("808", "808 Rubber", sub=.5, click=.15, pamt=8, ptime=45, glide=90, legato=1, d=2400, s=.15, r=220, drive=.15)
P("808", "808 Sine+Saw", wave2="Saw", lvl2=.15, det2=0, sub=.5, pamt=14, ptime=55, d=1700, s=0, r=140, drive=.2, cut=7000)

# ----------------------------------------------------------------------------- Sub & Boom
P("Sub & Boom", "Sub Boom", sub=.85, click=.1, pamt=24, ptime=90, d=2200, s=0, r=300, drive=.05, cut=4000)
P("Sub & Boom", "Pure Sub", sub=.9, click=0, pamt=0, a=3, d=600, s=.9, r=120, drive=0, cut=800, gain=-4)
P("Sub & Boom", "Sub Rumble", wave="Triangle", wave2="Sine", lvl2=.3, semi2=-12, det2=0, sub=.7, pamt=4, ptime=90,
  d=1800, s=.3, r=300, drive=.15, cut=700, res=.1)
P("Sub & Boom", "Sub Floor", sub=.8, click=0, pamt=0, a=8, d=900, s=.8, r=250, drive=.1, cut=400, gain=-2)
P("Sub & Boom", "Sub Drop", sub=.8, pamt=36, ptime=320, d=3000, s=0, r=400, drive=.05, cut=3000)
P("Sub & Boom", "Sub Thump", sub=.8, click=.25, pamt=28, ptime=30, d=700, s=0, r=100, drive=.08, cut=2500)
P("Sub & Boom", "Sub Warm", wave="Triangle", sub=.7, pamt=5, ptime=70, d=1500, s=.5, r=220, drive=.2, cut=1500,
  eq_lf=70, eq_lg=2)
P("Sub & Boom", "Cinema Boom", sub=.9, pamt=30, ptime=400, a=20, d=4000, s=0, r=1600, drive=.1, cut=1800,
  comp=1, cth=-20, cratio=3, cmk=2)
P("Sub & Boom", "Octave Sub", wave2="Sine", lvl2=.5, semi2=-12, det2=0, sub=.4, pamt=8, ptime=50, d=1800, s=.2,
  r=200, drive=.1, cut=5000)
P("Sub & Boom", "Sub Tight", sub=.75, click=.1, pamt=14, ptime=40, d=500, s=0, r=90, drive=.05, cut=3000,
  comp=1, cth=-20, cratio=5, catt=4, crel=70, cmk=3)
P("Sub & Boom", "Tight Sub Comp", sub=.8, click=.2, pamt=16, ptime=50, d=1600, s=0, r=140, drive=.1, cut=5000,
  eq_lf=60, eq_lg=2.5, comp=1, cth=-20, cratio=6, catt=5, crel=80, cmk=4)

# ----------------------------------------------------------------------------- Distorted
P("Distorted", "Distorted 808", sub=.5, click=.35, pamt=18, ptime=45, d=1200, s=0, r=120, dtype="Hard", drive=.7, cut=6000)
P("Distorted", "808 Hard Clip", dtype="Hard", drive=.8, sub=.55, click=.2, pamt=16, ptime=50, d=1400, s=0, r=130, cut=5000, gain=-6)
P("Distorted", "808 Fold Dirt", dtype="Fold", drive=.55, sub=.5, click=.25, pamt=16, ptime=50, d=1600, s=0, r=130, cut=7000, gain=-5)
P("Distorted", "808 Crunch", dtype="Soft", drive=.6, sub=.5, click=.3, pamt=20, ptime=45, d=1300, s=0, r=120, cut=4500, res=.15, gain=-5)
P("Distorted", "808 Fuzz", dtype="Hard", drive=1.0, sub=.45, click=.2, pamt=14, ptime=55, d=1100, s=0, r=100, cut=2500, res=.2,
  gain=-8, comp=1, cth=-12, cratio=4, cmk=4)
P("Distorted", "808 Overdrive", dtype="Soft", drive=.45, sub=.55, pamt=14, ptime=55, d=1900, s=0, r=160, cut=8000, gain=-4)
P("Distorted", "808 Saturated Comp", dtype="Soft", drive=.5, sub=.5, pamt=16, ptime=50, d=1700, s=0, r=140, cut=6000,
  comp=1, cth=-22, cratio=8, catt=4, crel=100, cmk=8, cmix=.8)
P("Distorted", "808 Wrecked", wave="Saw", dtype="Fold", drive=.9, sub=.5, click=.3, pamt=22, ptime=45, d=900, s=0, r=100,
  cut=3500, res=.3, gain=-8)
P("Distorted", "808 Bitten", wave="Digital", wt=.3, dtype="Hard", drive=.4, sub=.5, click=.2, pamt=14, ptime=50, d=1300, s=0,
  r=120, cut=6000, gain=-5)
P("Distorted", "808 Wavefolder", wave="Fold", wt=.35, sub=.5, pamt=14, ptime=55, d=1500, s=0, r=140, drive=.2, cut=9000)
P("Distorted", "808 Radio", dtype="Hard", drive=.6, sub=.35, click=.3, pamt=16, ptime=45, d=1000, s=0, r=100, cut=3000, res=.35,
  gain=-6, eq_mf=1500, eq_mg=3, eq_mq=1.2)
P("Distorted", "808 Gritty Click", dtype="Soft", drive=.5, click=.8, sub=.5, pamt=18, ptime=40, d=1400, s=0, r=120, cut=7000, gain=-5)

# ----------------------------------------------------------------------------- Trap & Slides
P("Trap & Slides", "Trap Slide", sub=.4, click=.15, pamt=6, ptime=40, glide=120, legato=1, d=2500, s=.4, r=250, drive=.3)
P("Trap & Slides", "Slide Short", sub=.5, pamt=4, ptime=40, glide=80, legato=1, d=900, s=.1, r=140, drive=.2)
P("Trap & Slides", "Slide Long", sub=.5, pamt=3, glide=260, legato=1, d=3000, s=.5, r=300, drive=.2, cut=9000)
P("Trap & Slides", "Glide Legato", wave="Triangle", sub=.45, pamt=0, glide=140, legato=1, a=3, d=2000, s=.6, r=250, drive=.25, cut=6000)
P("Trap & Slides", "Trap Dark", sub=.6, click=.1, pamt=10, ptime=60, glide=100, legato=1, d=2800, s=.3, r=300, drive=.2, cut=1800, res=.15)
P("Trap & Slides", "Trap Hi-Fi", sub=.35, click=.3, pamt=6, glide=70, legato=1, d=2200, s=.25, r=200, drive=.1, cut=16000,
  wave2="Saw", lvl2=.12, det2=3)
P("Trap & Slides", "Trap Detune Slide", wave2="Sine", lvl2=.4, det2=8, semi2=0, sub=.4, pamt=6, glide=110, legato=1, d=2400, s=.4, r=250, drive=.25)
P("Trap & Slides", "Drill Slide", sub=.55, click=.2, pamt=5, ptime=30, glide=60, legato=1, d=1200, s=0, r=120, drive=.3, cut=9000,
  comp=1, cth=-18, cratio=4, cmk=3)

# ----------------------------------------------------------------------------- Reese & Neuro
P("Reese & Neuro", "Reese Detune", wave="Saw", sub=.55, click=0, wave2="Saw", det2=18, lvl2=.9, pamt=0, a=6, d=600, s=.85, r=220,
  dtype="Fold", drive=.35, cut=1400, res=.3)
P("Reese & Neuro", "Reese Classic", wave="Saw", wave2="Saw", lvl2=.95, det2=14, sub=.45, click=0, pamt=0, a=8, d=700, s=.9, r=250,
  drive=.3, cut=1800, res=.25)
P("Reese & Neuro", "Reese Wide", wave="Saw", wave2="Saw", lvl2=1.0, det2=24, sub=.4, click=0, pamt=0, a=10, d=800, s=.9, r=300,
  dtype="Fold", drive=.35, cut=2400, res=.2)
P("Reese & Neuro", "Reese Dark", wave="Saw", wave2="Saw", lvl2=.85, det2=12, sub=.6, click=0, pamt=0, a=6, d=600, s=.9, r=250,
  drive=.3, cut=800, res=.35)
P("Reese & Neuro", "Reese Filtered", wave="Saw", wave2="Saw", lvl2=.9, det2=16, sub=.5, click=0, pamt=0, a=6, d=700, s=.9, r=250,
  lshape="Sine", ltarget="Cutoff", lrate=.3, ldepth=.35, drive=.3, cut=1200, res=.35)
P("Reese & Neuro", "Reese Moving", wave="Saw", wave2="Saw", lvl2=.9, det2=18, sub=.5, click=0, pamt=0, d=700, s=.9, r=250,
  lshape="Smooth", ltarget="Cutoff", lsync="1 Bar", ldepth=.5, dtype="Fold", drive=.3, cut=1500, res=.3)
P("Reese & Neuro", "Neuro Bite", wave="Saw", wave2="Square", lvl2=.7, det2=7, sub=.4, click=0, pamt=0, a=2, d=500, s=.9, r=150,
  dtype="Hard", drive=.6, cut=2600, res=.45, lshape="Tri", ltarget="Cutoff", lsync="1/8", ldepth=.4,
  comp=1, cth=-18, cratio=4, cmk=3)
P("Reese & Neuro", "Neuro Fold", wave="Fold", wt=.5, wave2="Saw", lvl2=.6, det2=11, sub=.4, click=0, pamt=0, d=600, s=.9, r=180,
  lshape="Tri", ltarget="Morph", lsync="1/4", ldepth=.5, dtype="Fold", drive=.4, cut=3500, res=.3)
P("Reese & Neuro", "Neuro FM", wave="FM", wt=.55, wave2="FM", wt2=.3, lvl2=.7, semi2=7, det2=9, sub=.4, click=0, pamt=0, d=600, s=.9, r=180,
  lshape="Smooth", ltarget="Morph", lsync="1/2", ldepth=.45, dtype="Hard", drive=.45, cut=4000, res=.25)
P("Reese & Neuro", "Neuro Sync", wave="Sync", wt=.4, wave2="Saw", lvl2=.5, det2=10, sub=.45, click=0, pamt=0, d=600, s=.9, r=180,
  lshape="Sine", ltarget="Morph", lsync="1/4", ldepth=.6, dtype="Fold", drive=.35, cut=3000, res=.3)
P("Reese & Neuro", "Neuro Digital", wave="Digital", wt=.5, wave2="Saw", lvl2=.6, sub=.45, click=0, pamt=0, d=600, s=.9, r=180,
  lshape="S&H", ltarget="Morph", lsync="1/16", ldepth=.5, drive=.3, cut=5000, res=.25,
  comp=1, cth=-16, cratio=3, cmk=2)
P("Reese & Neuro", "Neuro Phase", wave="Phase Dist", wt=.5, wave2="Phase Dist", wt2=.8, lvl2=.65, det2=13, sub=.4, click=0, pamt=0,
  d=600, s=.9, r=180, lshape="Tri", ltarget="Morph", lsync="1/8", ldepth=.5, dtype="Hard", drive=.4, cut=3500, res=.3)
P("Reese & Neuro", "FM Reese", wave="FM", wt=.35, wave2="Saw", det2=14, lvl2=.6, sub=.5, click=0, pamt=0, a=5, d=600, s=.85, r=220,
  lshape="Sine", ltarget="Morph", lsync="1/2", ldepth=.4, dtype="Fold", drive=.3, cut=2000, res=.2,
  eq_lf=80, eq_lg=3, eq_hg=-2, comp=1, cth=-16, cratio=3, cmk=2)

# ----------------------------------------------------------------------------- Wobble & Dubstep
_wob = dict(wave="Saw", wave2="Saw", det2=12, lvl2=.5, sub=.5, click=0, pamt=0, a=2, d=500, s=.9, r=150, drive=.4)
P("Wobble & Dubstep", "Dub Wobble", lshape="Sine", ltarget="Cutoff", lrate=3, ldepth=.55, cut=700, res=.45, **_wob)
P("Wobble & Dubstep", "Wobble 1/8", lshape="Sine", ltarget="Cutoff", lsync="1/8", ldepth=.6, cut=600, res=.45,
  comp=1, cth=-18, cratio=4, cmk=3, **_wob)
P("Wobble & Dubstep", "Wobble 1/4", lshape="Sine", ltarget="Cutoff", lsync="1/4", ldepth=.7, cut=500, res=.5, **_wob)
P("Wobble & Dubstep", "Wobble 1/16", lshape="Sine", ltarget="Cutoff", lsync="1/16", ldepth=.5, cut=900, res=.4, **_wob)
P("Wobble & Dubstep", "Wobble Triplet", lshape="Sine", ltarget="Cutoff", lsync="1/8T", ldepth=.6, cut=650, res=.45, **_wob)
P("Wobble & Dubstep", "Wobble Dotted", lshape="Sine", ltarget="Cutoff", lsync="1/8D", ldepth=.6, cut=650, res=.45, **_wob)
P("Wobble & Dubstep", "Half-time Wub", lshape="Tri", ltarget="Cutoff", lsync="1/2", ldepth=.75, cut=450, res=.55,
  **{**_wob, "sub": .6})
P("Wobble & Dubstep", "Wobble Square", lshape="Square", ltarget="Cutoff", lsync="1/8", ldepth=.5, cut=700, res=.4, **_wob)
P("Wobble & Dubstep", "Wobble Saw Down", lshape="Saw", ltarget="Cutoff", lsync="1/8", ldepth=.65, cut=600, res=.45, **_wob)
P("Wobble & Dubstep", "Wobble Fold", lshape="Sine", ltarget="Drive", lsync="1/8", ldepth=.8, cut=3000,
  **{**_wob, "dtype": "Fold", "drive": .3, "lvl2": .3})
P("Wobble & Dubstep", "Pitch Dive Wobble", lshape="Saw", ltarget="Pitch", lsync="1/4", ldepth=.6, cut=3000,
  **{**_wob, "drive": .3})
P("Wobble & Dubstep", "Tremolo Sub", wave="Sine", sub=.7, lvl2=0, click=0, pamt=0, a=2, d=500, s=.9, r=150, drive=.1,
  lshape="Sine", ltarget="Amp", lsync="1/8", ldepth=.8, cut=5000)
P("Wobble & Dubstep", "Stutter Gate", wave="Saw", sub=.5, lvl2=0, click=0, pamt=0, a=1, d=500, s=.95, r=60, drive=.3,
  lshape="Square", ltarget="Amp", lsync="1/16", ldepth=1.0, cut=2500)
P("Wobble & Dubstep", "Random Wub", lshape="S&H", ltarget="Cutoff", lsync="1/16", ldepth=.7, cut=600, res=.5, **_wob)

# ----------------------------------------------------------------------------- Growl & Vowel
P("Growl & Vowel", "Fold Growl", wave="Fold", wt=.55, sub=.45, click=0, pamt=0, lshape="Tri", ltarget="Morph", lsync="1/4", ldepth=.6,
  a=3, d=500, s=.8, r=160, drive=.3, cut=3000, res=.2)
P("Growl & Vowel", "Vowel Talk", wave="Vowel", wt=.2, sub=.5, click=0, pamt=0, lshape="Sine", ltarget="Morph", lsync="1 Bar", ldepth=.9,
  a=4, d=600, s=.9, r=200, drive=.25, cut=4000)
P("Growl & Vowel", "Vowel Slow", wave="Vowel", wt=.1, sub=.5, click=0, pamt=0, lshape="Smooth", ltarget="Morph", lsync="2 Bar", ldepth=1.0,
  a=6, d=700, s=.9, r=250, drive=.2, cut=5000)
P("Growl & Vowel", "Yoi Growl", wave="Vowel", wt=.5, sub=.45, click=0, pamt=0, lshape="Ramp", ltarget="Morph", lsync="1/4", ldepth=.8,
  a=2, d=500, s=.9, r=150, dtype="Hard", drive=.4, cut=5000)
P("Growl & Vowel", "Mouth Bass", wave="Vowel", wt=.7, wave2="Saw", lvl2=.4, det2=9, sub=.45, click=0, pamt=0, lshape="Tri", ltarget="Morph",
  lsync="1/8", ldepth=.9, a=2, d=500, s=.9, r=150, drive=.35, cut=4500)
P("Growl & Vowel", "Phase Growl", wave="Phase Dist", wt=.6, sub=.45, click=0, pamt=0, lshape="Sine", ltarget="Morph", lsync="1/8", ldepth=.7,
  a=2, d=500, s=.9, r=150, dtype="Fold", drive=.35, cut=3500)
P("Growl & Vowel", "Growl Mean", wave="Fold", wt=.8, wave2="Sync", wt2=.5, lvl2=.5, det2=8, sub=.4, click=0, pamt=0, lshape="Tri", ltarget="Morph",
  lsync="1/16", ldepth=.4, a=2, d=500, s=.9, r=150, dtype="Hard", drive=.5, cut=2800, res=.3)
P("Growl & Vowel", "Growl Throat", wave="FM", wt=.6, sub=.45, click=0, pamt=0, lshape="Smooth", ltarget="Cutoff", lsync="1/2", ldepth=.6,
  a=2, d=500, s=.9, r=150, drive=.4, cut=1500, res=.3)
P("Growl & Vowel", "Growl Choir", wave="Vowel", wt=.3, wave2="Vowel", wt2=.8, lvl2=.6, det2=8, sub=.4, click=0, pamt=0, lshape="Sine",
  ltarget="Morph", lrate=.4, ldepth=.6, a=10, d=700, s=.9, r=300, drive=.2, cut=6000)
P("Growl & Vowel", "Growl Screech", wave="Sync", wt=.8, sub=.35, click=0, pamt=0, lshape="Saw", ltarget="Morph", lsync="1/8", ldepth=.6,
  a=1, d=400, s=.9, r=120, dtype="Hard", drive=.5, cut=3800, res=.5)

# ----------------------------------------------------------------------------- Pluck & Short
P("Pluck & Short", "Short Punch", wave="Triangle", sub=.7, click=.5, pamt=30, ptime=30, d=220, s=0, r=60, drive=.2)
P("Pluck & Short", "Pluck Sub", sub=.7, click=.4, pamt=12, ptime=25, a=.5, d=280, s=0, r=60, drive=.1, cut=6000)
P("Pluck & Short", "Pluck Square", wave="Square", sub=.4, click=.2, pamt=5, ptime=40, d=350, s=0, r=80, drive=.2, cut=2200, res=.25)
P("Pluck & Short", "Stab Saw", wave="Saw", wave2="Saw", lvl2=.5, det2=9, sub=.35, click=.1, pamt=0, d=260, s=0, r=90, drive=.3, cut=1800, res=.35)
P("Pluck & Short", "Pluck PWM", wave="PWM", wt=.4, sub=.5, click=.1, pamt=0, d=420, s=0, r=100, drive=.15, cut=2800, res=.2)
P("Pluck & Short", "Tick Bass", wave="Triangle", sub=.6, click=.9, pamt=20, ptime=15, d=160, s=0, r=40, drive=.1)
P("Pluck & Short", "Blip", wave="Square", sub=.3, click=.4, pamt=12, ptime=20, d=120, s=0, r=40, drive=.15, cut=4500)
P("Pluck & Short", "Plink FM", wave="FM", wt=.5, sub=.4, click=.3, pamt=4, ptime=30, d=300, s=0, r=80, drive=.1, cut=7000)
P("Pluck & Short", "Pluck Fold", wave="Fold", wt=.4, sub=.4, click=.2, pamt=3, d=380, s=0, r=90, drive=.2, cut=4000, res=.2)
P("Pluck & Short", "Staccato", wave="Saw", sub=.5, click=.1, pamt=0, a=1, d=200, s=.6, r=50, drive=.3, cut=1500, res=.3)
P("Pluck & Short", "Rubber Pluck", sub=.5, click=.3, pamt=10, ptime=35, glide=40, legato=1, d=500, s=0, r=90, drive=.15)

# ----------------------------------------------------------------------------- Synth Bass
P("Synth Bass", "Saw Growl", wave="Saw", sub=.5, click=0, pamt=0, a=3, d=400, s=.8, r=120, dtype="Fold", drive=.5, cut=900, res=.35)
P("Synth Bass", "Square Rumble", wave="Square", sub=.6, pamt=3, ptime=80, d=600, s=.6, r=200, drive=.3, cut=500, res=.2)
P("Synth Bass", "PWM Mono", wave="PWM", wt=.3, sub=.6, click=.05, pamt=2, ptime=50, lshape="Sine", ltarget="Morph", lrate=.8, ldepth=.7,
  d=700, s=.7, r=180, drive=.2, cut=2500)
P("Synth Bass", "Mono Saw", wave="Saw", sub=.5, click=0, pamt=0, d=400, s=.8, r=150, drive=.25, cut=2000, res=.2)
P("Synth Bass", "Mono Square", wave="Square", sub=.4, click=0, pamt=0, d=400, s=.8, r=150, drive=.2, cut=1400, res=.2)
P("Synth Bass", "Acid Bass", wave="Saw", sub=.2, click=0, pamt=0, glide=60, legato=1, a=1, d=280, s=.25, r=80, drive=.4, cut=450, res=.8,
  lshape="Saw", ltarget="Cutoff", lsync="1/8", ldepth=.4)
P("Synth Bass", "Moog-ish Triangle", wave="Triangle", wave2="Saw", lvl2=.35, det2=4, sub=.5, pamt=0, d=600, s=.7, r=200, drive=.3, cut=900, res=.35)
P("Synth Bass", "Funk Bass", wave="Saw", sub=.35, click=.35, pamt=2, ptime=30, d=350, s=.35, r=80, drive=.3, cut=1600, res=.4,
  eq_mf=800, eq_mg=3)
P("Synth Bass", "Analog Pulse", wave="PWM", wt=.5, sub=.45, pamt=0, d=500, s=.7, r=150, drive=.2, cut=1800, res=.25,
  lshape="Sine", ltarget="Morph", lrate=.6, ldepth=.3)
P("Synth Bass", "Electro Bass", wave="Square", wave2="Saw", lvl2=.5, det2=7, sub=.45, pamt=6, ptime=40, d=300, s=.5, r=90,
  dtype="Hard", drive=.35, cut=2800, res=.3)
P("Synth Bass", "Sync Lead Bass", wave="Sync", wt=.5, sub=.4, pamt=0, d=450, s=.7, r=150, drive=.3, cut=3500, res=.2,
  lshape="Sine", ltarget="Morph", lrate=.5, ldepth=.4)
P("Synth Bass", "Hollow Bass", wave="Phase Dist", wt=.2, sub=.55, pamt=0, d=600, s=.75, r=180, drive=.15, cut=1200, res=.15)
P("Synth Bass", "Wide Saw Bass", wave="Saw", wave2="Saw", lvl2=.8, det2=20, sub=.5, click=0, pamt=0, a=3, d=700, s=.85, r=220, drive=.3, cut=2200,
  comp=1, cth=-18, cratio=3, cmk=2)

# ----------------------------------------------------------------------------- Wavetable Morph
_wt = dict(sub=.45, click=0, pamt=0, a=4, d=800, s=.9, r=250, drive=.15, cut=7000)
P("Wavetable Morph", "Morph Sweep", wave="Morph", wt=.1, lshape="Tri", ltarget="Morph", lsync="1 Bar", ldepth=.9, **{**_wt, "drive": .2, "cut": 5000})
P("Wavetable Morph", "Slow Evolve", wave="Morph", wt=.5, lshape="Smooth", ltarget="Morph", lrate=.12, ldepth=1.0, **{**_wt, "a": 30, "r": 400, "cut": 6000})
P("Wavetable Morph", "Harmonics Rise", wave="Harmonics", wt=.2, lshape="Ramp", ltarget="Morph", lsync="2 Bar", ldepth=.9, **_wt)
P("Wavetable Morph", "PWM Sweep", wave="PWM", wt=.5, lshape="Sine", ltarget="Morph", lrate=.35, ldepth=.8, **_wt)
P("Wavetable Morph", "Fold Evolve", wave="Fold", wt=.4, lshape="Tri", ltarget="Morph", lrate=.2, ldepth=.8, **_wt)
P("Wavetable Morph", "Sync Sweep", wave="Sync", wt=.3, lshape="Sine", ltarget="Morph", lsync="1/2", ldepth=.9, **_wt)
P("Wavetable Morph", "Vowel Cycle", wave="Vowel", wt=.5, lshape="Tri", ltarget="Morph", lsync="2 Bar", ldepth=1.0, **_wt)
P("Wavetable Morph", "FM Evolve", wave="FM", wt=.4, lshape="Smooth", ltarget="Morph", lrate=.25, ldepth=.9, **_wt)
P("Wavetable Morph", "Phase Morph", wave="Phase Dist", wt=.5, lshape="Sine", ltarget="Morph", lsync="1/4", ldepth=.8, **_wt)
P("Wavetable Morph", "Digital Crush Morph", wave="Digital", wt=.5, lshape="Smooth", ltarget="Morph", lsync="1/8", ldepth=.8,
  **{**_wt, "drive": .25, "dtype": "Hard"})

# ----------------------------------------------------------------------------- FX & Experimental
P("FX & Experimental", "Laser Drop", wave="Saw", sub=0, click=0, pamt=48, ptime=350, d=700, s=0, r=200, drive=.3, cut=9000, res=.2)
P("FX & Experimental", "Pitch Bomb", sub=.5, pamt=40, ptime=480, a=1, d=2500, s=0, r=800, drive=.2, cut=2500)
P("FX & Experimental", "Riser Saw", wave="Saw", wave2="Saw", lvl2=.6, det2=22, sub=.2, click=0, pamt=0, a=500, d=3000, s=1, r=800,
  lshape="Ramp", ltarget="Cutoff", lrate=.08, ldepth=1.0, drive=.3, cut=600, res=.4)
P("FX & Experimental", "Noise Hit", wave="Saw", click=1.0, sub=.2, pamt=20, ptime=25, d=150, s=0, r=60, dtype="Hard", drive=.5, cut=10000)
P("FX & Experimental", "Alarm", wave="Square", sub=0, click=0, pamt=0, a=1, s=1, d=500, r=100, lshape="Square", ltarget="Pitch", lsync="1/16",
  ldepth=.5, drive=.2, cut=3500, res=.2)
P("FX & Experimental", "Hoover Bass", wave="Saw", wave2="Saw", lvl2=1.0, det2=40, sub=0, click=0, pamt=6, ptime=120, glide=80, legato=1, a=2, d=400, s=.8,
  r=200, lshape="Sine", ltarget="Pitch", lrate=5.5, ldepth=.08, dtype="Fold", drive=.5, cut=4500, res=.3)


# ============================================================================= generowanie
def resolve(key, val):
    pid, lo, hi, names = KEYS[key]
    if isinstance(val, str):
        if names is None or val not in names:
            sys.exit(f"Nieznana wartość '{val}' dla '{key}'")
        val = names.index(val)
    if not (lo - 1e-9 <= val <= hi + 1e-9):
        sys.exit(f"Wartość {val} poza zakresem [{lo}, {hi}] dla '{key}'")
    return pid, float(val)


def fnum(v):
    """Literał float C++ (np. 14 -> 14.0f, 0.15 -> 0.15f)."""
    t = f"{v:.6g}"
    if "." not in t and "e" not in t:
        t += ".0"
    return t + "f"


def main():
    seen = set()
    for cat, name, _ in PRESETS:
        if cat not in CATS:
            sys.exit(f"Nieznana kategoria {cat}")
        if name in seen:
            sys.exit(f"Duplikat nazwy: {name}")
        seen.add(name)

    ordered = sorted(PRESETS, key=lambda p: CATS.index(p[0]))      # sort stabilny: kolejność wewnątrz kategorii zachowana

    out = ["// Plik wygenerowany przez tools/gen_presets.py - nie edytuj ręcznie.",
           "#pragma once", "", '#include "Parameters.h"', "#include <vector>", "",
           "namespace FactoryPresets", "{",
           "    struct Value  { const char* id; float value; };",
           "    struct Preset { const char* category; const char* name; const Value* values; int numValues; };", ""]

    rows = []
    for i, (cat, name, kw) in enumerate(ordered):
        vals = [resolve(k, v) for k, v in kw.items()]
        if vals:
            out.append(f"    inline constexpr Value v{i}[] = {{ " +
                       ", ".join(f'{{ IDs::{pid}, {fnum(v)} }}' for pid, v in vals) + " };")
            rows.append(f'        {{ "{cat}", "{name}", v{i}, {len(vals)} }},')
        else:
            rows.append(f'        {{ "{cat}", "{name}", nullptr, 0 }},')

    out += ["", "    inline const std::vector<Preset>& all()", "    {",
            "        static const std::vector<Preset> presets", "        {"] + rows + ["        };", "        return presets;", "    }", "}", ""]

    path = pathlib.Path(__file__).resolve().parent.parent / "Source" / "FactoryPresets.h"
    path.write_text("\n".join(out), encoding="utf-8")
    cats = {}
    for c, _, _ in ordered:
        cats[c] = cats.get(c, 0) + 1
    print(f"Zapisano {len(ordered)} presetów -> {path}")
    for c in CATS:
        print(f"  {c:20s} {cats.get(c, 0)}")


if __name__ == "__main__":
    main()
