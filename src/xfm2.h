/*
 * XFM2 Synth Controller
 *
 * This is a user-friendly controller for the excellent XFM2 synth hardware designed by Futur3soundz
 * https://www.futur3soundz.com/xfm2
 *
 *
 * This file is part of the XFM2Controller distribution (https://github.com/ataristdude/xfm2controller).
 * Copyright (c) 2020 Don Fletcher
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef XFM2_H
#define XFM2_H

// This is a list of XFM2 parameter numbers so that
// the rest of the app can reference them by name instead
// of hard-coding the numbers

enum XFM2Parameter {
    // Operators/Program
    ALGO1=1,        // 1 = ALGO1
    ALGO2=2,          // 2 = ALGO2
    ALGO3=3,          // 3 = ALGO3
    ALGO4=4,          // 4 = ALGO4
    ALGO5=5,          // 5 = ALGO5
    ALGO6=6,          // 6 = ALGO6
    OP_FEEDBACK1=7,    // 7 = FEEDBACK1
    OP_FEEDBACK2=8,    // 8 = FEEDBACK2
    OP_FEEDBACK3=9,    // 9 = FEEDBACK3
    OP_FEEDBACK4=10,    // 10 = FEEDBACK4
    OP_FEEDBACK5=11,    // 11 = FEEDBACK5
    OP_FEEDBACK6=12,    // 12 = FEEDBACK6
    OP_SYNC=13,         // 13 = OPSYNC
    OP_MODE=14,         // 14 = MODE
    OP_RATIO1=15,       // 15 = OPRATIO1
    OP_RATIO2=16,       // 16
    OP_RATIO3=17,       // 17
    OP_RATIO4=18,       // 18
    OP_RATIO5=19,       // 19
    OP_RATIO6=20,       // 20
    OP_RATIOFINE1=21,   // 21
    OP_RATIOFINE2=22,   // 22
    OP_RATIOFINE3=23,   // 23
    OP_RATIOFINE4=24,   // 24
    OP_RATIOFINE5=25,   // 25
    OP_RATIOFINE6=26,   // 26
    OP_FINE1=27,        // 27
    OP_FINE2=28,        // 28
    OP_FINE3=29,        // 29
    OP_FINE4=30,        // 30
    OP_FINE5=31,        // 31
    OP_FINE6=32,        // 32
    OP_LEVEL1=33,       // 33
    OP_LEVEL2=34,       // 34
    OP_LEVEL3=35,       // 35
    OP_LEVEL4=36,       // 36
    OP_LEVEL5=37,       // 37
    OP_LEVEL6=38,       // 38
    OP_VELO_SENS1=39,   // 39
    OP_VELO_SENS2=40,   // 40
    OP_VELO_SENS3=41,   // 41
    OP_VELO_SENS4=42,   // 42
    OP_VELO_SENS5=43,   // 43
    OP_VELO_SENS6=44,   // 44
    OP_KEY_BP1=45,         // 45
    OP_KEY_BP2=46,         // 46
    OP_KEY_BP3=47,         // 47
    OP_KEY_BP4=48,         // 48
    OP_KEY_BP5=49,         // 49
    OP_KEY_BP6=50,         // 50
    OP_KEY_LDEPTH1=51,     // 51
    OP_KEY_LDEPTH2=52,     // 52
    OP_KEY_LDEPTH3=53,     // 53
    OP_KEY_LDEPTH4=54,     // 54
    OP_KEY_LDEPTH5=55,     // 55
    OP_KEY_LDEPTH6=56,     // 56
    OP_KEY_RDEPTH1=57,     // 57
    OP_KEY_RDEPTH2=58,     // 58
    OP_KEY_RDEPTH3=59,     // 59
    OP_KEY_RDEPTH4=60,     // 60
    OP_KEY_RDEPTH5=61,     // 61
    OP_KEY_RDEPTH6=62,     // 62
    OP_KEY_LCURVE1=63,     // 63
    OP_KEY_LCURVE2=64,     // 64
    OP_KEY_LCURVE3=65,     // 65
    OP_KEY_LCURVE4=66,     // 66
    OP_KEY_LCURVE5=67,     // 67
    OP_KEY_LCURVE6=68,     // 68
    OP_KEY_RCURVE1=69,     // 69
    OP_KEY_RCURVE2=70,     // 70
    OP_KEY_RCURVE3=71,     // 71
    OP_KEY_RCURVE4=72,     // 72
    OP_KEY_RCURVE5=73,     // 73
    OP_KEY_RCURVE6=74,     // 74
    OP_LEVEL1_1=75,        // 75
    OP_LEVEL1_2=76,        // 76
    OP_LEVEL1_3=77,        // 77
    OP_LEVEL1_4=78,        // 78
    OP_LEVEL1_5=79,        // 79
    OP_LEVEL1_6=80,        // 80
    OP_LEVEL2_1=82,        // 82
    OP_LEVEL2_2=83,        // 83
    OP_LEVEL2_3=84,        // 84
    OP_LEVEL2_4=85,        // 85
    OP_LEVEL2_5=86,        // 86
    OP_LEVEL2_6=87,        // 87
    OP_LEVEL3_1=89,        // 89
    OP_LEVEL3_2=90,        // 90
    OP_LEVEL3_3=91,        // 91
    OP_LEVEL3_4=92,        // 92
    OP_LEVEL3_5=93,        // 93
    OP_LEVEL3_6=94,        // 94
    OP_LEVEL4_1=96,        // 96
    OP_LEVEL4_2=97,        // 97
    OP_LEVEL4_3=98,        // 98
    OP_LEVEL4_4=99,        // 99
    OP_LEVEL4_5=100,        // 100
    OP_LEVEL4_6=101,        // 101
    OP_RATE1_1=103,         // 103
    OP_RATE1_2=104,         // 104
    OP_RATE1_3=105,         // 105
    OP_RATE1_4=106,         // 106
    OP_RATE1_5=107,         // 107
    OP_RATE1_6=108,         // 108
    OP_RATE2_1=110,         // 110
    OP_RATE2_2=111,         // 111
    OP_RATE2_3=112,         // 112
    OP_RATE2_4=113,         // 113
    OP_RATE2_5=114,         // 114
    OP_RATE2_6=115,         // 115
    OP_RATE3_1=117,         // 117
    OP_RATE3_2=118,         // 118
    OP_RATE3_3=119,         // 119
    OP_RATE3_4=120,         // 120
    OP_RATE3_5=121,         // 121
    OP_RATE3_6=122,         // 122
    OP_RATE4_1=124,         // 124
    OP_RATE4_2=125,         // 125
    OP_RATE4_3=126,         // 126
    OP_RATE4_4=127,         // 127
    OP_RATE4_5=128,         // 128
    OP_RATE4_6=129,         // 129

    PITCH_EG_L1=130,        // 130
    PITCH_EG_L2=131,        // 131
    PITCH_EG_L3=132,        // 132
    PITCH_EG_L4=133,        // 133
    PITCH_EG_R1=134,        // 134
    PITCH_EG_R2=135,        // 135
    PITCH_EG_R3=136,        // 136
    PITCH_EG_R4=137,        // 137
    PITCH_EG_RANGE=138,     // 138
    PITCH_EG_VELO=139,      // 139

    OP_RATE_KEY1=140,       // 140
    OP_RATE_KEY2=141,       // 141
    OP_RATE_KEY3=142,       // 142
    OP_RATE_KEY4=143,       // 143
    OP_RATE_KEY5=144,       // 144
    OP_RATE_KEY6=145,       // 145

    PITCH_EG_RATE_KEY=146,  // 146

    LFO_DEPTH_PITCH=149,    // 149
    LFO_DEPTH_AMP=150,      // 150
    LFO_SPEED=151,          // 151
    LFO_SYNC=152,           // 152
    LFO_WAVE=153,           // 153
    LFO_FADE=154,           // 154

    MOD_PITCH_LFO_WHEEL=155,    // 155
    MOD_AMP_LFO_WHEEL=156,      // 156
    MOD_PITCH_LFO_AFTER=157,    // 157
    MOD_AMP_LFO_AFTER=158,      // 158

    OP_AMS1=159,            // 159
    OP_AMS2=160,            // 160
    OP_AMS3=161,            // 161
    OP_AMS4=162,            // 162
    OP_AMS5=163,            // 163
    OP_AMS6=164,            // 164

    MASTER_PITCHBEND_UP=172,       // 172
    MASTER_PITCHBEND_DOWN=173,     // 173
    MASTER_TRANSPOSE=174,          // 174
    MASTER_VOLUME=180,       // 180

    OP_LEVEL0_1=181,        // 181
    OP_LEVEL0_2=182,        // 182
    OP_LEVEL0_3=183,        // 183
    OP_LEVEL0_4=184,        // 184
    OP_LEVEL0_5=185,        // 185
    OP_LEVEL0_6=186,        // 186
    OP_DELAY_1=187,         // 187
    OP_DELAY_2=188,         // 188
    OP_DELAY_3=189,         // 189
    OP_DELAY_4=190,         // 190
    OP_DELAY_5=191,         // 191
    OP_DELAY_6=192,         // 192
    OP_LEVEL5_1=193,        // 193
    OP_LEVEL5_2=194,        // 194
    OP_LEVEL5_3=195,        // 195
    OP_LEVEL5_4=196,        // 196
    OP_LEVEL5_5=197,        // 197
    OP_LEVEL5_6=198,        // 198
    OP_RATE5_1=199,         // 199
    OP_RATE5_2=200,         // 200
    OP_RATE5_3=201,         // 201
    OP_RATE5_4=202,         // 202
    OP_RATE5_5=203,         // 203
    OP_RATE5_6=204,         // 204

    PITCH_EG_L0=205,        // 205
    PITCH_EG_DELAY=206,     // 206
    PITCH_EG_L5=207,        // 207
    PITCH_EG_R5=208,        // 208

    MOD_PITCH_LFO_BREATH=209,   // 209
    MOD_AMP_LFO_BREATH=210,     // 210
    MOD_PITCH_LFO_FOOT=211,     // 211
    MOD_AMP_LFO_FOOT=212,       // 212

    MOD_EG_BIAS_AFTER=213,      // 213
    MOD_EG_BIAS_WHEEL=214,      // 214
    MOD_EG_BIAS_BREATH=215,     // 215
    MOD_EG_BIAS_FOOT=216,       // 216

    MOD_PITCH_AFTER=217,        // 217
    MOD_PITCH_BREATH=218,       // 218
    MOD_PITCH_FOOT=219,         // 219
    MOD_PITCH_RANDOM=220,       // 220

    MASTER_PAN=221,              // 221

    OP_PMS_1=222,               // 222
    OP_PMS_2=223,               // 223
    OP_PMS_3=224,               // 224
    OP_PMS_4=225,               // 225
    OP_PMS_5=226,               // 226
    OP_PMS_6=227,               // 227

    MASTER_LEGATO=228,          // 228
    MASTER_PORTAMENTO_MODE=229, // 229
    MASTER_PORTAMENTO_TIME=230, // 230

    OP_WAVE1_1=236,             // 236
    OP_WAVE1_2=237,             // 237
    OP_WAVE1_3=238,             // 238
    OP_WAVE1_4=239,             // 239
    OP_WAVE1_5=240,             // 240
    OP_WAVE1_6=241,             // 241

    MASTER_VELOCITY_OFFSET=242, // 242

    OP_EG_LOOP=244,             // 244
    OP_EG_LOOP_SEG=245,         // 245

    MASTER_EG_RESTART=246,      // 246

    MASTER_TUNING=251,          // 251

    OP_LEVEL_LEFT1=256,         // 256
    OP_LEVEL_RIGHT1=257,        // 257
    OP_LEVEL_LEFT2=258,         // 258
    OP_LEVEL_RIGHT2=259,        // 259
    OP_LEVEL_LEFT3=260,         // 260
    OP_LEVEL_RIGHT3=261,        // 261
    OP_LEVEL_LEFT4=262,         // 262
    OP_LEVEL_RIGHT4=263,        // 263
    OP_LEVEL_LEFT5=264,         // 264
    OP_LEVEL_RIGHT5=265,        // 265
    OP_LEVEL_LEFT6=266,         // 266
    OP_LEVEL_RIGHT6=267,        // 267

    OP_WAVE2_1=268,             // 268
    OP_WAVE2_2=269,             // 269
    OP_WAVE2_3=270,             // 270
    OP_WAVE2_4=271,             // 271
    OP_WAVE2_5=272,             // 272
    OP_WAVE2_6=273,             // 273

    OP_WMODE_1=274,             // 274
    OP_WMODE_2=275,             // 275
    OP_WMODE_3=276,             // 276
    OP_WMODE_4=277,             // 277
    OP_WMODE_5=278,             // 278
    OP_WMODE_6=279,             // 279
    OP_WRATIO_1=280,            // 280
    OP_WRATIO_2=281,            // 281
    OP_WRATIO_3=282,            // 282
    OP_WRATIO_4=283,            // 283
    OP_WRATIO_5=284,            // 284
    OP_WRATIO_6=285,            // 285
    OP_PHASE1=286,              // 286
    OP_PHASE2=287,              // 287
    OP_PHASE3=288,              // 288
    OP_PHASE4=289,              // 289
    OP_PHASE5=290,              // 290
    OP_PHASE6=291,              // 291

    FX_DELAY_DRY=300,           // 300
    FX_DELAY_WET=301,           // 301
    FX_DELAY_MODE=302,          // 302
    FX_DELAY_TIME=303,          // 303
    FX_DELAY_FEEDBACK=304,      // 304
    FX_DELAY_LO=305,            // 305
    FX_DELAY_HI=306,            // 306
    FX_DELAY_TEMPO=307,         // 307
    FX_DELAY_MUL=308,           // 308
    FX_DELAY_DIV=309,           // 309

    FX_PHASER_DRY=310,          // 310
    FX_PHASER_WET=311,          // 311
    FX_PHASER_MODE=312,         // 312
    FX_PHASER_DEPTH=313,        // 313
    FX_PHASER_SPEED=314,        // 314
    FX_PHASER_FEEDBACK=315,     // 315
    FX_PHASER_OFFSET=316,       // 316
    FX_PHASER_STAGES=317,       // 317
    FX_PHASER_LRPHASE=318,      // 318

    FX_FILTER_LO=320,           // 320
    FX_FILTER_HI=321,           // 321

    FX_AM_SPEED=330,            // 330
    FX_AM_RANGE=331,            // 331
    FX_AM_DEPTH=332,            // 332
    FX_AM_LRPHASE=333,          // 333

    FX_CHORUS_DRY=360,          // 360
    FX_CHORUS_WET=361,          // 361
    FX_CHORUS_MODE=362,         // 362
    FX_CHORUS_SPEED=363,        // 363
    FX_CHORUS_DEPTH=364,        // 364
    FX_CHORUS_FEEDBACK=365,     // 365
    FX_CHORUS_LRPHASE=366,      // 366

    FX_DECIMATOR_DEPTH=370,     // 370
    FX_BITCRUSHER_DEPTH=380,    // 380

    FX_REVERB_DRY=390,          // 390
    FX_REVERB_WET=391,          // 391
    FX_REVERB_MODE=392,         // 392
    FX_REVERB_DECAY=393,        // 393
    FX_REVERB_DAMP=394,         // 394

    FX_ROUTING=410,             // 410
    MASTER_OUTPUT=411,          // 411

    PERFORMANCE_CTRL1_HI=420,   // 420
    PERFORMANCE_CTRL1_LO=421,   // 421
    PERFORMANCE_CTRL2_HI=422,   // 422
    PERFORMANCE_CTRL2_LO=423,   // 423
    PERFORMANCE_CTRL3_HI=424,   // 424
    PERFORMANCE_CTRL3_LO=425,   // 425
    PERFORMANCE_CTRL4_HI=426,   // 426
    PERFORMANCE_CTRL4_LO=427,   // 427

    ARPEGGIATOR_MODE=450,       // 450
    ARPEGGIATOR_TEMPO=451,      // 451
    ARPEGGIATOR_RESERVED=452,   // 452
    ARPEGGIATOR_MUL=453,        // 453
    ARPEGGIATOR_OCTAVES=454     // 454
};

#endif // XFM2_H
