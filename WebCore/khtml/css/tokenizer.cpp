/*
 * This file is part of the DOM implementation for KDE.
 *
 * Copyright (C) 2003 Lars Knoll (knoll@kde.org)
 *
 * $Id$
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/* This file is mostly data generated by flex. Unfortunately flex
   can't handle 16bit strings directly, so we just copy the part of
   the code we need and modify it to our needs.

   Most of the defines below are to make sure we can easily use the
   flex generated code, using as little editing as possible.

   The flex syntax to generate the lexer are more or less directly
   copied from the CSS2.1 specs, with some fixes for comments and
   the important symbol.

   To regenerate, run flex on tokenizer.flex. After this, copy the
   data tables and the YY_DECL method over to this file. Remove the
   init code from YY_DECL and change the YY_END_OF_BUFFER to only call
   yyterminate().

*/

// --------- begin generated code -------------------

#define YY_NUM_RULES 47
#define YY_END_OF_BUFFER 48
static yyconst short int yy_accept[304] =
    {   0,
        0,    0,   48,   46,    2,    2,   46,   46,   46,   46,
       46,   46,   46,   46,   46,   40,   46,   46,   46,   46,
       11,   11,   46,   46,    2,    0,    0,    0,   10,    0,
       12,    0,    8,    0,    0,    9,    0,   40,    0,   39,
        0,   40,    0,   38,   38,   38,   38,   38,   38,   38,
       38,   38,   38,   38,   38,   35,    0,    0,    0,    0,
        0,    0,    0,   11,   11,    7,   43,   11,    0,    0,
       11,    6,    5,    0,    0,    0,   10,    0,    0,   12,
       12,    0,    0,   10,    0,    0,    4,    0,    0,   38,
       38,   38,    0,   38,   26,   38,   22,   24,   38,   36,

       28,   38,   27,   34,   30,   29,   25,   38,    0,    0,
        0,    0,    0,    0,    0,   11,   11,   11,   44,   44,
       11,    0,    0,    0,   12,    0,    0,    0,    1,   38,
       38,   38,   38,   31,   38,   37,   32,    3,    0,    0,
        0,    0,    0,    0,   11,   11,    0,   44,   44,   44,
       43,    0,    0,   12,    0,    0,    0,   38,   38,   38,
       33,    0,    0,    0,    0,    0,   14,   11,   11,   45,
       44,   44,   44,   44,    0,    0,    0,    0,   42,    0,
        0,    0,   12,    0,   38,   38,   23,    0,    0,    0,
        0,   15,   11,   11,   45,   44,   44,   44,   44,   44,

        0,    0,    0,    0,    0,    0,    0,    0,    0,   42,
        0,    0,    0,    0,   12,    0,   38,   38,    0,    0,
        0,   13,   11,   11,   45,   44,   44,   44,   44,   44,
       44,    0,   41,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,   12,    0,   38,   38,
        0,    0,    0,   17,    0,   11,   45,   44,   44,   44,
       44,   44,   44,   44,    0,   41,    0,    0,    0,   41,
        0,    0,    0,    0,   38,    0,    0,    0,    0,   45,
        0,    0,    0,   21,    0,    0,    0,   16,   45,    0,
        0,    0,    0,   18,    0,    0,    0,    0,   19,   20,

        0,    0,    0
    } ;

static yyconst int yy_ec[256] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
        1,    4,    5,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    6,    7,    8,    9,   10,   11,   12,   13,   14,
       15,   16,   17,   12,   18,   19,   20,   21,   21,   21,
       21,   21,   21,   21,   21,   21,   21,   12,   12,   22,
       23,   24,   25,   26,   30,   31,   32,   33,   34,   35,
       36,   37,   38,   39,   40,   41,   42,   43,   44,   45,
       46,   47,   48,   49,   50,   51,   39,   52,   39,   53,
       12,   27,   12,   28,   29,   12,   30,   31,   32,   33,

       34,   35,   36,   37,   38,   39,   40,   41,   42,   43,
       44,   45,   46,   47,   48,   49,   50,   51,   39,   52,
       39,   53,   12,   54,   12,   55,    1,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,

       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56,   56,   56,   56,   56,   56,
       56,   56,   56,   56,   56
    } ;

static yyconst int yy_meta[57] =
    {   0,
        1,    2,    3,    3,    3,    4,    4,    4,    4,    4,
        4,    4,    4,    5,    4,    4,    4,    6,    4,    4,
        6,    4,    4,    4,    7,    4,    8,    4,    8,    6,
        6,    6,    6,    6,    6,    8,    8,    8,    8,    8,
        8,    8,    8,    8,    8,    8,    8,    8,    8,    8,
        8,    8,    8,    4,    4,    8
    } ;

static yyconst short int yy_base[330] =
    {   0,
        0,    0,  723, 1578,   55,   60,   65,   64,  694,  697,
       60,  696,  700,  683,  687,   93,  695,   57,   75,  678,
       63,   66,  677,  676,  113,  148,  656,   70, 1578,  185,
      670,  126, 1578,   61,  219, 1578,  659,   60,  666, 1578,
      658,    0,  134,   55,  651,   58,   67,  121,  135,  143,
      148,   49,  150,  151,  144,  650,  658,  622,  624,  597,
      598,  603,  606,   84,  253, 1578, 1578,  158,  204,  268,
      167, 1578, 1578,  590,  199,  168,  172,  302,  336,  607,
      370,  201,  184,  200,  404,  438, 1578,  609,  185,  596,
      472,  595,  321,  183,  594,  206,  593,  579,  214,  578,

      564,  216,  555,  554,  553,  552,  551,  233,  559,  532,
      544,  530,  527,  538,  534,  423,  234,  506,  245,  544,
      248,  513,  237,  498,  513,  252,  521,  534, 1578,  528,
      508,  562,  244,  499,  249,  498,  497, 1578,  480,  475,
      472,  476,  480,  483,  554,  569,  577,  272,  491,  490,
      611,  467,  597,  612,  618,  484,  252,  633,  639,  250,
      471,  451,  448,  477,  440,  456, 1578,  654,  660,  675,
      291,  459,  458,  457,  709,  735,  286,  268, 1578,  761,
      432,  695,  721,  768,  776,  783,  453,  461,  433,  395,
      380, 1578,  791,  798,  806,  293,  402,  394,  369,  368,

      343,  288,  375,  840,  299,  874,  908,  934,  960,  986,
     1012, 1046,  358,  825,  859,  894,  920,  946,  365,  338,
      335, 1578,  972, 1053, 1061,  296,  339,  337,  336,  335,
      334,  380, 1578,  316,  323,  418, 1095, 1129,  386,  401,
     1108, 1163, 1197, 1182,  287, 1204, 1212, 1219,  458, 1227,
      294,  277,  295, 1578,  290,  444, 1234,  302, 1578, 1578,
     1578, 1578, 1578, 1578,  486,  384,  388, 1242, 1276,  405,
      439, 1262, 1277,  268,  653,  259,  232,  206,  197, 1283,
     1298, 1304, 1319, 1578,  189,  175,  134, 1578, 1578, 1325,
     1340, 1346,  131, 1578,   87, 1361, 1367, 1382, 1578, 1578,

     1388, 1403, 1578, 1437, 1440, 1447, 1452, 1456, 1463, 1468,
     1475, 1483, 1488, 1491, 1496, 1504, 1509, 1512, 1519, 1522,
     1528, 1531, 1537, 1544, 1551, 1554, 1560, 1567, 1570
    } ;

static yyconst short int yy_def[330] =
    {   0,
      303,    1,  303,  303,  303,  303,  303,  304,  305,  303,
      306,  303,  303,  303,  303,  303,  303,  303,  307,  303,
      308,  308,  303,  303,  303,  303,  303,  304,  303,  309,
      305,  310,  303,  306,  311,  303,  303,   16,  312,  303,
      303,   16,  313,  314,  314,  314,  314,  314,  314,  314,
      314,  314,  314,  314,  314,  314,  303,  303,  303,  303,
      303,  303,  303,  308,  308,  303,  303,  308,  315,  303,
      308,  303,  303,  303,  304,  304,  304,  304,  309,  305,
      305,  306,  306,  306,  306,  311,  303,  312,  316,  314,
      314,  314,  317,  314,  314,  314,  314,  314,  314,  314,

      314,  314,  314,  314,  314,  314,  314,  314,  303,  303,
      303,  303,  303,  303,  303,   65,  308,   65,  318,  303,
      308,  303,  304,   78,   81,  306,   85,  319,  303,   91,
      314,   91,  314,  314,  314,  314,  314,  303,  303,  303,
      303,  303,  303,  303,   65,  118,  303,  320,  303,  303,
      321,  303,   78,   81,   85,  319,  316,   91,  132,  314,
      314,  303,  303,  303,  303,  303,  303,   65,  118,  303,
      322,  303,  303,  303,  321,  321,  323,  324,  303,  325,
      303,   78,   81,   85,   91,  132,  314,  303,  303,  303,
      303,  303,   65,  118,  303,  326,  303,  303,  303,  303,

      303,  323,  303,  327,  324,  328,  321,  321,  321,  321,
      321,  325,  303,   78,   81,   85,   91,  132,  303,  303,
      303,  303,   65,  118,  303,  329,  303,  303,  303,  303,
      303,  303,  303,  323,  323,  323,  323,  327,  324,  324,
      324,  324,  328,  211,  303,   78,   81,   85,  314,  132,
      303,  303,  303,  303,  303,  223,  303,  303,  303,  303,
      303,  303,  303,  303,  323,  323,  323,  237,  324,  324,
      324,  242,  211,  303,  314,  303,  303,  303,  303,  303,
      237,  242,  211,  303,  303,  303,  303,  303,  303,  237,
      242,  211,  303,  303,  303,  237,  242,  211,  303,  303,

      237,  242,    0,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303
    } ;

static yyconst short int yy_nxt[1635] =
    {   0,
        4,    5,    6,    5,    5,    5,    7,    8,    9,   10,
        4,    4,   11,    4,    4,   12,    4,   13,   14,   15,
       16,   17,    4,    4,    4,   18,   19,   20,   21,   21,
       21,   21,   21,   21,   21,   21,   21,   21,   21,   21,
       21,   21,   21,   21,   21,   21,   21,   21,   21,   22,
       21,   21,   21,   23,   24,   21,   25,   25,   25,   25,
       25,   25,   25,   25,   25,   25,   26,   26,   26,   26,
       26,   29,   29,   29,   58,   93,   67,   29,  303,   67,
       38,   93,   70,   94,   93,  102,   35,   35,   59,   69,
       30,   60,   69,   93,   61,   65,   30,   67,   62,   95,

       96,   63,   27,   40,   65,   65,   65,   65,   65,   65,
       69,   41,   71,   42,   25,   25,   25,   25,   25,   43,
      300,   44,   45,   45,   46,   47,   48,   45,   49,   50,
       51,   45,   52,   45,   53,   45,   45,   54,   45,   55,
       56,   45,   45,   45,   45,   45,   81,   93,   45,   26,
       26,   26,   26,   26,   91,   81,   81,   81,   81,   81,
       81,   93,   97,   91,   91,   91,   91,   91,   91,   93,
       93,   67,   98,  108,   93,   29,   93,   93,  299,   29,
       67,   99,  105,  295,   69,   27,   28,   28,   28,   75,
      101,  103,   77,   69,   30,  100,   29,  104,   30,  106,

       89,   28,  107,   34,  129,   78,   29,  121,  294,   93,
       35,   79,   29,   29,   78,   78,   78,   78,   78,   78,
       34,   34,   34,   82,  118,   30,   35,   35,  133,  293,
      288,   84,   93,  118,  118,  118,  118,  118,  118,   85,
       93,  134,   93,  135,   29,   86,  287,   67,   85,   85,
       85,   85,   85,   85,   64,   64,   64,   64,   64,   93,
       69,  151,  147,   30,   29,  137,   67,  157,  136,  149,
       93,  129,  286,  116,   69,   93,   93,  160,   35,   69,
      203,  161,  116,  116,  116,  116,  116,  116,  119,  147,
      285,  187,  120,  203,  206,  203,  172,  119,  119,  119,

      119,  119,  119,   76,  123,  123,  123,   76,  147,   29,
      147,  203,  204,  147,  204,  197,  284,  227,  202,  147,
      259,  279,  124,  203,  278,  206,  277,  276,   30,  274,
      203,  124,  124,  124,  124,  124,  124,   28,   28,   28,
       75,  132,  204,   77,  201,  201,  201,  201,  201,  204,
      132,  132,  132,  132,  132,  132,   78,  179,  264,  263,
      262,  261,   79,  260,  255,   78,   78,   78,   78,   78,
       78,   80,   80,   80,   80,   80,  232,  232,  232,  232,
      232,  232,  232,  232,  232,  232,  254,  245,  205,  233,
      125,  203,  231,  230,  233,  203,   32,  251,  203,  125,

      125,  125,  125,  125,  125,   83,  126,  126,  126,   83,
      204,  252,  206,  203,  204,  253,   29,  203,  229,  265,
      232,  232,  232,  265,  127,  203,  228,  206,  222,  221,
       35,  206,  266,  127,  127,  127,  127,  127,  127,   34,
       34,   34,   82,  145,  204,  117,  117,  117,  117,  117,
       84,  203,  145,  145,  145,  145,  145,  145,   85,   90,
       90,   90,   90,   90,   86,  206,  220,   85,   85,   85,
       85,   85,   85,   90,   90,   90,   90,   90,  219,   93,
      213,  200,  199,  198,   93,  192,  191,  265,  232,  232,
      232,  265,  130,  203,  190,  189,  188,   93,   93,  157,

      266,  130,  130,  130,  130,  130,  130,  117,  117,  117,
      117,  117,  204,  181,  174,  173,  167,  166,  153,  165,
      164,  163,  162,   93,   93,   93,  146,  153,  153,  153,
      153,  153,  153,  154,   93,  146,  146,  146,  146,  146,
      146,  155,  154,  154,  154,  154,  154,  154,  158,  157,
      155,  155,  155,  155,  155,  155,  152,  158,  158,  158,
      158,  158,  158,  131,  131,  131,  131,  131,  150,  144,
      143,  142,  141,  140,  168,  139,  138,   93,   93,   93,
       93,   93,  159,  168,  168,  168,  168,  168,  168,  169,
       93,  159,  159,  159,  159,  159,  159,  170,  169,  169,

      169,  169,  169,  169,   93,   93,  170,  170,  170,  170,
      170,  170,  175,  175,  175,  175,  175,  182,  177,   93,
       93,   93,   93,  178,   89,  179,  182,  182,  182,  182,
      182,  182,  183,   32,  122,  115,  114,  180,  184,  113,
      112,  183,  183,  183,  183,  183,  183,  184,  184,  184,
      184,  184,  184,  185,  131,  131,  131,  131,  131,  186,
      111,  110,  185,  185,  185,  185,  185,  185,  186,  186,
      186,  186,  186,  186,  193,  109,   93,   93,   38,   93,
      194,   89,   87,  193,  193,  193,  193,  193,  193,  194,
      194,  194,  194,  194,  194,  195,   32,   74,   73,   72,

       66,   57,   39,   38,  195,  195,  195,  195,  195,  195,
      175,  175,  175,  175,  175,  214,  177,   37,   36,   33,
       32,  178,  303,  179,  214,  214,  214,  214,  214,  214,
      303,  303,  303,  303,  303,  180,  201,  201,  201,  201,
      201,  215,  303,  303,  303,  303,  303,  303,  303,  179,
      215,  215,  215,  215,  215,  215,  303,  303,  303,  303,
      303,  180,  201,  201,  201,  201,  207,  303,  209,  303,
      303,  303,  303,  209,  209,  210,  303,  303,  303,  303,
      303,  211,  303,  303,  303,  303,  303,  212,  216,  303,
      211,  211,  211,  211,  211,  211,  217,  216,  216,  216,

      216,  216,  216,  218,  303,  217,  217,  217,  217,  217,
      217,  223,  218,  218,  218,  218,  218,  218,  224,  303,
      223,  223,  223,  223,  223,  223,  225,  224,  224,  224,
      224,  224,  224,  303,  303,  225,  225,  225,  225,  225,
      225,  202,  202,  202,  234,  246,  303,  236,  303,  303,
      303,  303,  303,  303,  246,  246,  246,  246,  246,  246,
      237,  303,  303,  303,  303,  303,  238,  303,  303,  237,
      237,  237,  237,  237,  237,  205,  205,  205,  239,  247,
      303,  303,  303,  303,  303,  303,  241,  303,  247,  247,
      247,  247,  247,  247,  242,  303,  303,  303,  303,  303,

      243,  303,  303,  242,  242,  242,  242,  242,  242,  201,
      201,  201,  201,  201,  248,  303,  303,  303,  303,  303,
      303,  303,  179,  248,  248,  248,  248,  248,  248,  303,
      303,  303,  303,  303,  180,  201,  201,  201,  201,  201,
      249,  303,  303,  303,  303,  303,  303,  303,  179,  249,
      249,  249,  249,  249,  249,  303,  303,  303,  303,  303,
      180,  201,  201,  201,  201,  201,  250,  303,  303,  303,
      303,  303,  303,  303,  179,  250,  250,  250,  250,  250,
      250,  303,  303,  303,  303,  303,  180,  201,  201,  201,
      201,  201,   68,  303,  303,  303,  303,  303,  303,  303,

      179,   68,   68,   68,   68,   68,   68,  303,  303,  303,
      303,  303,  180,  207,  207,  207,  207,  207,  303,  303,
      303,  303,  303,  303,  303,  303,  179,  303,  303,  303,
      303,  303,  244,  303,  303,  303,  303,  303,  180,  303,
      303,  244,  244,  244,  244,  244,  244,  201,  201,  201,
      201,  207,  303,  209,  303,  303,  303,  303,  209,  209,
      210,  303,  303,  303,  303,  303,  211,  303,  303,  303,
      303,  303,  212,  256,  303,  211,  211,  211,  211,  211,
      211,  257,  256,  256,  256,  256,  256,  256,  303,  303,
      257,  257,  257,  257,  257,  257,  235,  267,  267,  267,

      235,  303,  203,  303,  303,  303,  303,  303,  303,  269,
      232,  232,  232,  269,  303,  268,  303,  303,  303,  303,
      203,  204,  270,  303,  268,  268,  268,  268,  268,  268,
      202,  202,  202,  234,  206,  303,  236,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  237,
      303,  303,  303,  303,  303,  238,  303,  303,  237,  237,
      237,  237,  237,  237,  240,  271,  271,  271,  240,  303,
      303,  303,  303,  303,  303,  203,  303,  303,  303,  303,
      303,  303,  303,  272,  303,  303,  303,  303,  303,  206,
      303,  303,  272,  272,  272,  272,  272,  272,  205,  205,

      205,  239,  273,  303,  303,  303,  303,  303,  303,  241,
      303,  273,  273,  273,  273,  273,  273,  242,  303,  303,
      303,  303,  303,  243,   28,  303,  242,  242,  242,  242,
      242,  242,   31,   28,   28,   28,   28,   28,   28,   34,
      303,   31,   31,   31,   31,   31,   31,  275,   34,   34,
       34,   34,   34,   34,  280,  303,  275,  275,  275,  275,
      275,  275,  281,  280,  280,  280,  280,  280,  280,  303,
      303,  281,  281,  281,  281,  281,  281,  269,  232,  232,
      232,  269,  282,  303,  303,  303,  303,  303,  203,  303,
      270,  282,  282,  282,  282,  282,  282,  283,  303,  303,

      303,  303,  206,  289,  303,  303,  283,  283,  283,  283,
      283,  283,  289,  289,  289,  289,  289,  289,  290,  303,
      303,  303,  303,  303,  291,  303,  303,  290,  290,  290,
      290,  290,  290,  291,  291,  291,  291,  291,  291,  292,
      303,  303,  303,  303,  303,  296,  303,  303,  292,  292,
      292,  292,  292,  292,  296,  296,  296,  296,  296,  296,
      297,  303,  303,  303,  303,  303,  298,  303,  303,  297,
      297,  297,  297,  297,  297,  298,  298,  298,  298,  298,
      298,  301,  303,  303,  303,  303,  303,  302,  303,  303,
      301,  301,  301,  301,  301,  301,  302,  302,  302,  302,

      302,  302,  176,  303,  303,  303,  303,  303,  202,  303,
      303,  176,  176,  176,  176,  176,  176,  202,  202,  202,
      202,  202,  202,  205,  303,  303,  303,  303,  303,  303,
      303,  303,  205,  205,  205,  205,  205,  205,   28,  303,
       28,   28,   28,   28,   28,   31,  303,   31,   34,  303,
       34,   34,   34,   34,   34,   64,   64,   64,   64,   64,
       68,   68,  303,   68,   76,   76,   76,   76,   76,   76,
       76,   80,   80,   80,   80,   80,   83,   83,   83,   83,
       83,   83,   83,   88,   88,   88,   88,   88,   88,   88,
       88,   90,   90,   90,   90,   90,   92,  303,   92,  117,

      117,  117,  117,  117,  128,  128,  128,  128,  128,  128,
      128,  128,  131,  131,  131,  131,  131,  148,  148,  156,
      156,  156,  156,  156,  156,  156,  156,  171,  171,  176,
      176,  176,  303,  176,  176,  176,  196,  196,  202,  303,
      202,  202,  202,  202,  202,  205,  303,  205,  205,  205,
      205,  205,  208,  208,  208,  208,  208,  208,  208,  226,
      226,  235,  235,  235,  235,  235,  235,  235,  240,  240,
      240,  240,  240,  240,  240,  258,  258,    3,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,

      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303
    } ;

static yyconst short int yy_chk[1635] =
    {   0,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    5,    5,    5,    5,
        5,    6,    6,    6,    6,    6,    7,    7,    7,    7,
        7,    8,   11,   34,   18,   52,   21,   28,   38,   22,
       38,   44,   22,   44,   46,   52,   11,   34,   18,   21,
        8,   18,   22,   47,   18,   19,   28,   64,   18,   46,

       47,   18,    7,   16,   19,   19,   19,   19,   19,   19,
       64,   16,   22,   16,   25,   25,   25,   25,   25,   16,
      295,   16,   16,   16,   16,   16,   16,   16,   16,   16,
       16,   16,   16,   16,   16,   16,   16,   16,   16,   16,
       16,   16,   16,   16,   16,   16,   32,   48,   16,   26,
       26,   26,   26,   26,   43,   32,   32,   32,   32,   32,
       32,   49,   48,   43,   43,   43,   43,   43,   43,   50,
       55,   68,   48,   55,   51,   76,   53,   54,  293,   77,
       71,   49,   54,  287,   68,   26,   30,   30,   30,   30,
       51,   53,   30,   71,   76,   50,   83,   53,   77,   54,

       89,   75,   54,   82,   89,   30,   75,   71,  286,   94,
       83,   30,   84,   82,   30,   30,   30,   30,   30,   30,
       35,   35,   35,   35,   69,   75,   84,   82,   94,  285,
      279,   35,   96,   69,   69,   69,   69,   69,   69,   35,
       99,   96,  102,   99,  123,   35,  278,  117,   35,   35,
       35,   35,   35,   35,   65,   65,   65,   65,   65,  108,
      117,  121,  119,  123,  126,  108,   65,  157,  102,  119,
      133,  157,  277,   65,  121,  135,  160,  133,  126,   65,
      178,  135,   65,   65,   65,   65,   65,   65,   70,  148,
      276,  160,   70,  177,  178,  202,  148,   70,   70,   70,

       70,   70,   70,   78,   78,   78,   78,   78,  171,   78,
      196,  205,  177,  226,  202,  171,  274,  196,  234,  258,
      226,  255,   78,  234,  253,  205,  252,  251,   78,  245,
      235,   78,   78,   78,   78,   78,   78,   79,   79,   79,
       79,   93,  234,   79,  201,  201,  201,  201,  201,  235,
       93,   93,   93,   93,   93,   93,   79,  201,  231,  230,
      229,  228,   79,  227,  221,   79,   79,   79,   79,   79,
       79,   81,   81,   81,   81,   81,  203,  203,  203,  203,
      203,  232,  232,  232,  232,  232,  220,  213,  239,  203,
       81,  266,  200,  199,  232,  267,   81,  219,  239,   81,

       81,   81,   81,   81,   81,   85,   85,   85,   85,   85,
      266,  219,  239,  240,  267,  219,   85,  270,  198,  236,
      236,  236,  236,  236,   85,  236,  197,  240,  191,  190,
       85,  270,  236,   85,   85,   85,   85,   85,   85,   86,
       86,   86,   86,  116,  236,  256,  256,  256,  256,  256,
       86,  271,  116,  116,  116,  116,  116,  116,   86,  249,
      249,  249,  249,  249,   86,  271,  189,   86,   86,   86,
       86,   86,   86,   91,   91,   91,   91,   91,  188,  187,
      181,  174,  173,  172,  249,  166,  165,  265,  265,  265,
      265,  265,   91,  265,  164,  163,  162,  161,   91,  156,

      265,   91,   91,   91,   91,   91,   91,  118,  118,  118,
      118,  118,  265,  152,  150,  149,  144,  143,  124,  142,
      141,  140,  139,  137,  136,  134,  118,  124,  124,  124,
      124,  124,  124,  125,  131,  118,  118,  118,  118,  118,
      118,  127,  125,  125,  125,  125,  125,  125,  130,  128,
      127,  127,  127,  127,  127,  127,  122,  130,  130,  130,
      130,  130,  130,  132,  132,  132,  132,  132,  120,  115,
      114,  113,  112,  111,  145,  110,  109,  107,  106,  105,
      104,  103,  132,  145,  145,  145,  145,  145,  145,  146,
      101,  132,  132,  132,  132,  132,  132,  147,  146,  146,

      146,  146,  146,  146,  100,   98,  147,  147,  147,  147,
      147,  147,  151,  151,  151,  151,  151,  153,  151,   97,
       95,   92,   90,  151,   88,  151,  153,  153,  153,  153,
      153,  153,  154,   80,   74,   63,   62,  151,  155,   61,
       60,  154,  154,  154,  154,  154,  154,  155,  155,  155,
      155,  155,  155,  158,  275,  275,  275,  275,  275,  159,
       59,   58,  158,  158,  158,  158,  158,  158,  159,  159,
      159,  159,  159,  159,  168,   57,   56,   45,   41,  275,
      169,   39,   37,  168,  168,  168,  168,  168,  168,  169,
      169,  169,  169,  169,  169,  170,   31,   27,   24,   23,

       20,   17,   15,   14,  170,  170,  170,  170,  170,  170,
      175,  175,  175,  175,  175,  182,  175,   13,   12,   10,
        9,  175,    3,  175,  182,  182,  182,  182,  182,  182,
        0,    0,    0,    0,    0,  175,  176,  176,  176,  176,
      176,  183,  176,    0,    0,    0,    0,  176,    0,  176,
      183,  183,  183,  183,  183,  183,    0,    0,    0,    0,
        0,  176,  180,  180,  180,  180,  180,    0,  180,    0,
        0,    0,    0,  180,  180,  180,    0,    0,    0,    0,
        0,  180,    0,    0,    0,    0,    0,  180,  184,    0,
      180,  180,  180,  180,  180,  180,  185,  184,  184,  184,

      184,  184,  184,  186,    0,  185,  185,  185,  185,  185,
      185,  193,  186,  186,  186,  186,  186,  186,  194,    0,
      193,  193,  193,  193,  193,  193,  195,  194,  194,  194,
      194,  194,  194,    0,    0,  195,  195,  195,  195,  195,
      195,  204,  204,  204,  204,  214,    0,  204,    0,    0,
        0,    0,    0,    0,  214,  214,  214,  214,  214,  214,
      204,    0,    0,    0,    0,    0,  204,    0,    0,  204,
      204,  204,  204,  204,  204,  206,  206,  206,  206,  215,
        0,    0,    0,    0,    0,    0,  206,    0,  215,  215,
      215,  215,  215,  215,  206,    0,    0,    0,    0,    0,

      206,    0,    0,  206,  206,  206,  206,  206,  206,  207,
      207,  207,  207,  207,  216,  207,    0,    0,    0,    0,
      207,    0,  207,  216,  216,  216,  216,  216,  216,    0,
        0,    0,    0,    0,  207,  208,  208,  208,  208,  208,
      217,  208,    0,    0,    0,    0,  208,    0,  208,  217,
      217,  217,  217,  217,  217,    0,    0,    0,    0,    0,
      208,  209,  209,  209,  209,  209,  218,  209,    0,    0,
        0,    0,  209,    0,  209,  218,  218,  218,  218,  218,
      218,    0,    0,    0,    0,    0,  209,  210,  210,  210,
      210,  210,  223,  210,    0,    0,    0,    0,  210,    0,

      210,  223,  223,  223,  223,  223,  223,    0,    0,    0,
        0,    0,  210,  211,  211,  211,  211,  211,    0,  211,
        0,    0,    0,    0,  211,    0,  211,    0,    0,    0,
        0,    0,  211,    0,    0,    0,    0,    0,  211,    0,
        0,  211,  211,  211,  211,  211,  211,  212,  212,  212,
      212,  212,    0,  212,    0,    0,    0,    0,  212,  212,
      212,    0,    0,    0,    0,    0,  212,    0,    0,    0,
        0,    0,  212,  224,    0,  212,  212,  212,  212,  212,
      212,  225,  224,  224,  224,  224,  224,  224,    0,    0,
      225,  225,  225,  225,  225,  225,  237,  237,  237,  237,

      237,    0,  237,    0,    0,    0,    0,    0,    0,  241,
      241,  241,  241,  241,    0,  237,    0,    0,    0,    0,
      241,  237,  241,    0,  237,  237,  237,  237,  237,  237,
      238,  238,  238,  238,  241,    0,  238,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,  238,
        0,    0,    0,    0,    0,  238,    0,    0,  238,  238,
      238,  238,  238,  238,  242,  242,  242,  242,  242,    0,
        0,    0,    0,    0,    0,  242,    0,    0,    0,    0,
        0,    0,    0,  242,    0,    0,    0,    0,    0,  242,
        0,    0,  242,  242,  242,  242,  242,  242,  243,  243,

      243,  243,  244,    0,    0,    0,    0,    0,    0,  243,
        0,  244,  244,  244,  244,  244,  244,  243,    0,    0,
        0,    0,    0,  243,  246,    0,  243,  243,  243,  243,
      243,  243,  247,  246,  246,  246,  246,  246,  246,  248,
        0,  247,  247,  247,  247,  247,  247,  250,  248,  248,
      248,  248,  248,  248,  257,    0,  250,  250,  250,  250,
      250,  250,  268,  257,  257,  257,  257,  257,  257,    0,
        0,  268,  268,  268,  268,  268,  268,  269,  269,  269,
      269,  269,  272,    0,    0,    0,    0,    0,  269,    0,
      269,  272,  272,  272,  272,  272,  272,  273,    0,    0,

        0,    0,  269,  280,    0,    0,  273,  273,  273,  273,
      273,  273,  280,  280,  280,  280,  280,  280,  281,    0,
        0,    0,    0,    0,  282,    0,    0,  281,  281,  281,
      281,  281,  281,  282,  282,  282,  282,  282,  282,  283,
        0,    0,    0,    0,    0,  290,    0,    0,  283,  283,
      283,  283,  283,  283,  290,  290,  290,  290,  290,  290,
      291,    0,    0,    0,    0,    0,  292,    0,    0,  291,
      291,  291,  291,  291,  291,  292,  292,  292,  292,  292,
      292,  296,    0,    0,    0,    0,    0,  297,    0,    0,
      296,  296,  296,  296,  296,  296,  297,  297,  297,  297,

      297,  297,  298,    0,    0,    0,    0,    0,  301,    0,
        0,  298,  298,  298,  298,  298,  298,  301,  301,  301,
      301,  301,  301,  302,    0,    0,    0,    0,    0,    0,
        0,    0,  302,  302,  302,  302,  302,  302,  304,    0,
      304,  304,  304,  304,  304,  305,    0,  305,  306,    0,
      306,  306,  306,  306,  306,  307,  307,  307,  307,  307,
      308,  308,    0,  308,  309,  309,  309,  309,  309,  309,
      309,  310,  310,  310,  310,  310,  311,  311,  311,  311,
      311,  311,  311,  312,  312,  312,  312,  312,  312,  312,
      312,  313,  313,  313,  313,  313,  314,    0,  314,  315,

      315,  315,  315,  315,  316,  316,  316,  316,  316,  316,
      316,  316,  317,  317,  317,  317,  317,  318,  318,  319,
      319,  319,  319,  319,  319,  319,  319,  320,  320,  321,
      321,  321,    0,  321,  321,  321,  322,  322,  323,    0,
      323,  323,  323,  323,  323,  324,    0,  324,  324,  324,
      324,  324,  325,  325,  325,  325,  325,  325,  325,  326,
      326,  327,  327,  327,  327,  327,  327,  327,  328,  328,
      328,  328,  328,  328,  328,  329,  329,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,

      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
      303,  303,  303,  303
    } ;


YY_DECL
	{
	register yy_state_type yy_current_state;
	register unsigned short *yy_cp, *yy_bp;
	register int yy_act;
	while ( 1 )		/* loops until end-of-file is reached */
		{
		yy_cp = yy_c_buf_p;

		/* Support of yytext. */
		*yy_cp = yy_hold_char;

		/* yy_bp points to the position in yy_ch_buf of the start of
		 * the current run.
		 */
		yy_bp = yy_cp;

		yy_current_state = yy_start;
		do
			{
			register YY_CHAR yy_c = yy_ec[YY_SC_TO_UI(*yy_cp)];
			if ( yy_accept[yy_current_state] )
				{
				yy_last_accepting_state = yy_current_state;
				yy_last_accepting_cpos = yy_cp;
				}
			while ( yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state )
				{
				yy_current_state = (int) yy_def[yy_current_state];
				if ( yy_current_state >= 304 )
					yy_c = yy_meta[(unsigned int) yy_c];
				}
			yy_current_state = yy_nxt[yy_base[yy_current_state] + (unsigned int) yy_c];
			++yy_cp;
			}
		while ( yy_base[yy_current_state] != 1578 );

yy_find_action:
		yy_act = yy_accept[yy_current_state];
		if ( yy_act == 0 )
			{ /* have to back up */
			yy_cp = yy_last_accepting_cpos;
			yy_current_state = yy_last_accepting_state;
			yy_act = yy_accept[yy_current_state];
			}

		YY_DO_BEFORE_ACTION;


		switch ( yy_act )
	{ /* beginning of action switch */
			case 0: /* must back up */
			/* undo the effects of YY_DO_BEFORE_ACTION */
			*yy_cp = yy_hold_char;
			yy_cp = yy_last_accepting_cpos;
			yy_current_state = yy_last_accepting_state;
			goto yy_find_action;

case 1:
YY_RULE_SETUP
#line 25 "tokenizer.flex"
/* ignore comments */
	YY_BREAK
case 2:
YY_RULE_SETUP
#line 27 "tokenizer.flex"
{yyTok = S; return yyTok;}
	YY_BREAK
case 3:
YY_RULE_SETUP
#line 29 "tokenizer.flex"
{yyTok = SGML_CD; return yyTok;}
	YY_BREAK
case 4:
YY_RULE_SETUP
#line 30 "tokenizer.flex"
{yyTok = SGML_CD; return yyTok;}
	YY_BREAK
case 5:
YY_RULE_SETUP
#line 31 "tokenizer.flex"
{yyTok = INCLUDES; return yyTok;}
	YY_BREAK
case 6:
YY_RULE_SETUP
#line 32 "tokenizer.flex"
{yyTok = DASHMATCH; return yyTok;}
	YY_BREAK
case 7:
YY_RULE_SETUP
#line 33 "tokenizer.flex"
{yyTok = BEGINSWITH; return yyTok;}
	YY_BREAK
case 8:
YY_RULE_SETUP
#line 34 "tokenizer.flex"
{yyTok = ENDSWITH; return yyTok;}
	YY_BREAK
case 9:
YY_RULE_SETUP
#line 35 "tokenizer.flex"
{yyTok = CONTAINS; return yyTok;}
	YY_BREAK
case 10:
YY_RULE_SETUP
#line 37 "tokenizer.flex"
{yyTok = STRING; return yyTok;}
	YY_BREAK
case 11:
YY_RULE_SETUP
#line 39 "tokenizer.flex"
{yyTok = IDENT; return yyTok;}
	YY_BREAK
case 12:
YY_RULE_SETUP
#line 41 "tokenizer.flex"
{yyTok = HASH; return yyTok;}
	YY_BREAK
case 13:
YY_RULE_SETUP
#line 43 "tokenizer.flex"
{yyTok = IMPORT_SYM; return yyTok;}
	YY_BREAK
case 14:
YY_RULE_SETUP
#line 44 "tokenizer.flex"
{yyTok = PAGE_SYM; return yyTok;}
	YY_BREAK
case 15:
YY_RULE_SETUP
#line 45 "tokenizer.flex"
{yyTok = MEDIA_SYM; return yyTok;}
	YY_BREAK
case 16:
YY_RULE_SETUP
#line 46 "tokenizer.flex"
{yyTok = FONT_FACE_SYM; return yyTok;}
	YY_BREAK
case 17:
YY_RULE_SETUP
#line 47 "tokenizer.flex"
{yyTok = CHARSET_SYM; return yyTok;}
	YY_BREAK
case 18:
YY_RULE_SETUP
#line 48 "tokenizer.flex"
{yyTok = KONQ_RULE_SYM; return yyTok; }
	YY_BREAK
case 19:
YY_RULE_SETUP
#line 49 "tokenizer.flex"
{yyTok = KONQ_DECLS_SYM; return yyTok; }
	YY_BREAK
case 20:
YY_RULE_SETUP
#line 50 "tokenizer.flex"
{yyTok = KONQ_VALUE_SYM; return yyTok; }
	YY_BREAK
case 21:
YY_RULE_SETUP
#line 52 "tokenizer.flex"
{yyTok = IMPORTANT_SYM; return yyTok;}
	YY_BREAK
case 22:
YY_RULE_SETUP
#line 54 "tokenizer.flex"
{yyTok = EMS; return yyTok;}
	YY_BREAK
case 23:
YY_RULE_SETUP
#line 55 "tokenizer.flex"
{yyTok = QEMS; return yyTok;} /* quirky ems */
	YY_BREAK
case 24:
YY_RULE_SETUP
#line 56 "tokenizer.flex"
{yyTok = EXS; return yyTok;}
	YY_BREAK
case 25:
YY_RULE_SETUP
#line 57 "tokenizer.flex"
{yyTok = PXS; return yyTok;}
	YY_BREAK
case 26:
YY_RULE_SETUP
#line 58 "tokenizer.flex"
{yyTok = CMS; return yyTok;}
	YY_BREAK
case 27:
YY_RULE_SETUP
#line 59 "tokenizer.flex"
{yyTok = MMS; return yyTok;}
	YY_BREAK
case 28:
YY_RULE_SETUP
#line 60 "tokenizer.flex"
{yyTok = INS; return yyTok;}
	YY_BREAK
case 29:
YY_RULE_SETUP
#line 61 "tokenizer.flex"
{yyTok = PTS; return yyTok;}
	YY_BREAK
case 30:
YY_RULE_SETUP
#line 62 "tokenizer.flex"
{yyTok = PCS; return yyTok;}
	YY_BREAK
case 31:
YY_RULE_SETUP
#line 63 "tokenizer.flex"
{yyTok = DEGS; return yyTok;}
	YY_BREAK
case 32:
YY_RULE_SETUP
#line 64 "tokenizer.flex"
{yyTok = RADS; return yyTok;}
	YY_BREAK
case 33:
YY_RULE_SETUP
#line 65 "tokenizer.flex"
{yyTok = GRADS; return yyTok;}
	YY_BREAK
case 34:
YY_RULE_SETUP
#line 66 "tokenizer.flex"
{yyTok = MSECS; return yyTok;}
	YY_BREAK
case 35:
YY_RULE_SETUP
#line 67 "tokenizer.flex"
{yyTok = SECS; return yyTok;}
	YY_BREAK
case 36:
YY_RULE_SETUP
#line 68 "tokenizer.flex"
{yyTok = HERZ; return yyTok;}
	YY_BREAK
case 37:
YY_RULE_SETUP
#line 69 "tokenizer.flex"
{yyTok = KHERZ; return yyTok;}
	YY_BREAK
case 38:
YY_RULE_SETUP
#line 70 "tokenizer.flex"
{yyTok = DIMEN; return yyTok;}
	YY_BREAK
case 39:
YY_RULE_SETUP
#line 71 "tokenizer.flex"
{yyTok = PERCENTAGE; return yyTok;}
	YY_BREAK
case 40:
YY_RULE_SETUP
#line 72 "tokenizer.flex"
{yyTok = NUMBER; return yyTok;}
	YY_BREAK
case 41:
YY_RULE_SETUP
#line 74 "tokenizer.flex"
{yyTok = URI; return yyTok;}
	YY_BREAK
case 42:
YY_RULE_SETUP
#line 75 "tokenizer.flex"
{yyTok = URI; return yyTok;}
	YY_BREAK
case 43:
YY_RULE_SETUP
#line 76 "tokenizer.flex"
{yyTok = FUNCTION; return yyTok;}
	YY_BREAK
case 44:
YY_RULE_SETUP
#line 78 "tokenizer.flex"
{yyTok = UNICODERANGE; return yyTok;}
	YY_BREAK
case 45:
YY_RULE_SETUP
#line 79 "tokenizer.flex"
{yyTok = UNICODERANGE; return yyTok;}
	YY_BREAK
case 46:
YY_RULE_SETUP
#line 81 "tokenizer.flex"
{yyTok = *yytext; return yyTok;}
	YY_BREAK
case 47:
YY_RULE_SETUP
#line 83 "tokenizer.flex"
ECHO;
	YY_BREAK
#line 1304 "lex.yy.c"
case YY_STATE_EOF(INITIAL):
	case YY_END_OF_BUFFER:
	yyterminate();

	default:
		YY_FATAL_ERROR(
			"fatal flex scanner internal error--no action found" );
	} /* end of action switch */
		} /* end of scanning one token */
	} /* end of yylex */


