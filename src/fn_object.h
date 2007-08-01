/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Object functions
 *
 * *****************************************************************
 *
 * Copyright 2007 Wolfgang Silbermayr
 *
 * *****************************************************************
 *
 * This file is part of Freenukum.
 * 
 * Freenukum is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *******************************************************************/

#ifndef FN_OBJECT
#define FN_OBJECT

/* --------------------------------------------------------------- */

#define ANIM_START                             (8 * 48)

#define ANIM_FLYBOT               (ANIM_START +      0)
#define ANIM_JUMPBOT              (ANIM_START +     10)
#define ANIM_CARBOT               (ANIM_START +     34)
#define ANIM_EXPLODE              (ANIM_START +     42)
#define ANIM_FIREWHEEL_OFF        (ANIM_START +     48)
#define ANIM_FIREWHEEL_ON         (ANIM_START +     64)
#define ANIM_SIMPLEBOT            (ANIM_START +     80)
#define ANIM_BOMBFIRE             (ANIM_START +     90)
#define ANIM_EXITDOOR             (ANIM_START +     98)
#define ANIM_BOMB                 (ANIM_START +    114)
#define ANIM_RABBIT1              (ANIM_START +    116)
#define ANIM_BALLWORM             (ANIM_START +    122)
#define ANIM_SODA                 (ANIM_START +    130)
#define ANIM_SODAFLY              (ANIM_START +    134)
#define ANIM_CRABBOT_LEFT         (ANIM_START +    138)
#define ANIM_CRABBOT_RIGHT        (ANIM_START +    142)
#define ANIM_FLOOR_UNSTABLE       (ANIM_START +    146)
#define ANIM_CRAP                 (ANIM_START +    148)
#define ANIM_FAN                  (ANIM_START +    158)
#define ANIM_HELICOPTER           (ANIM_START +    166)
#define ANIM_CAMERA               (ANIM_START +    202)
#define ANIM_BROKENWALLBG         (ANIM_START +    205)
#define ANIM_STONEBG              (ANIM_START +    206)
#define ANIM_STONEWINDOWBG        (ANIM_START +    208)
#define ANIM_WHITEBALLSMALL       (ANIM_START +    209)
#define ANIM_WHITEBALLBIG         (ANIM_START +    210)
#define ANIM_TELEPORTER1          (ANIM_START +    214)
#define ANIM_MINE                 (ANIM_START +    225)
#define ANIM_TELEPORTER2          (ANIM_START +    226)
#define ANIM_RABBIT2              (ANIM_START +    230)
#define ANIM_TELEPORTER3          (ANIM_START +    240)
#define ANIM_FIREGNOME            (ANIM_START +    242)
#define ANIM_FENCEBG              (ANIM_START +    256)
#define ANIM_WINDOWBG             (ANIM_START +    257)
#define ANIM_BADGUYSCREEN         (ANIM_START +    260)
#define ANIM_BADGUY               (ANIM_START +    274)

/* --------------------------------------------------------------- */

#define OBJ_START                 (ANIM_START + 6 * 48)

#define OBJ_BOX_GREY              (OBJ_START  +      0)
#define OBJ_SPARK_PINK            (OBJ_START  +      1)
#define OBJ_SPARK_BLUE            (OBJ_START  +      2)
#define OBJ_SPARK_WHITE           (OBJ_START  +      3)
#define OBJ_SPARK_GREEN           (OBJ_START  +      4)
#define OBJ_ELEVATOR              (OBJ_START  +      5)
#define OBJ_SHOT                  (OBJ_START  +      6)
#define OBJ_SHOE                  (OBJ_START  +     10)
#define OBJ_ROCKET                (OBJ_START  +     11)
#define OBJ_CLAMP                 (OBJ_START  +     18)
#define OBJ_DUST                  (OBJ_START  +     19)
#define OBJ_FIRERIGHT             (OBJ_START  +     24)
#define OBJ_FIRELEFT              (OBJ_START  +     29)
#define OBJ_SMOKE                 (OBJ_START  +     34)
#define OBJ_BADSHOT               (OBJ_START  +     39)
#define OBJ_GUN                   (OBJ_START  +     43)
#define OBJ_CHICKEN_SINGLE        (OBJ_START  +     44)
#define OBJ_CHICKEN_DOUBLE        (OBJ_START  +     45)
#define OBJ_BEFORESHOT            (OBJ_START  +     46)
#define OBJ_SHOTEXPLOSION         (OBJ_START  +     48)
#define OBJ_ELECTRICFENCE         (OBJ_START  +     50)
#define OBJ_ELECTRICFENCE_ACTIVE  (OBJ_START  +     54)
#define OBJ_FOOTBALL              (OBJ_START  +     58)
#define OBJ_JOYSTICK              (OBJ_START  +     59)
#define OBJ_DISK                  (OBJ_START  +     60)
#define OBJ_HEALTH                (OBJ_START  +     61)
#define OBJ_NONHEALTH             (OBJ_START  +     62)
#define OBJ_GLOVE                 (OBJ_START  +     63)
#define OBJ_CIRCUITBOARD          (OBJ_START  +     64)
#define OBJ_LASERBEAM             (OBJ_START  +     65)
#define OBJ_BALLOON               (OBJ_START  +     69)
#define OBJ_NUCLEARMOLECULE       (OBJ_START  +     74)
#define OBJ_FALLINGBLOCK          (OBJ_START  +     83)
#define OBJ_POINT                 (OBJ_START  +     85)
#define OBJ_ROTATECYLINDER        (OBJ_START  +     90)
#define OBJ_SPIKE                 (OBJ_START  +     95)
#define OBJ_FLAG                  (OBJ_START  +     97)
#define OBJ_BOX_BLUE              (OBJ_START  +    100)
#define OBJ_BOX_RED               (OBJ_START  +    101)
#define OBJ_RADIO                 (OBJ_START  +    102)
#define OBJ_CIRCUITBOARD_SLOT     (OBJ_START  +    105)
#define OBJ_GLOVE_SWITCH          (OBJ_START  +    114)
#define OBJ_DUKE_WORD             (OBJ_START  +    118)
#define OBJ_EMPTY                 (OBJ_START  +    122)
#define OBJ_NOTE                  (OBJ_START  +    123)
#define OBJ_KEY_RED               (OBJ_START  +    124)
#define OBJ_KEY_GREEN             (OBJ_START  +    125)
#define OBJ_KEY_BLUE              (OBJ_START  +    126)
#define OBJ_KEY_VIOLET            (OBJ_START  +    127)
#define OBJ_DOOR                  (OBJ_START  +    128)
#define OBJ_KEYHOLE_BLACK         (OBJ_START  +    136)
#define OBJ_KEYHOLE_RED           (OBJ_START  +    137)
#define OBJ_KEYHOLE_GREEN         (OBJ_START  +    138)
#define OBJ_KEYHOLE_BLUE          (OBJ_START  +    139)
#define OBJ_KEYHOLE_VIOLET        (OBJ_START  +    140)
#define OBJ_BADGUY_SMALL          (OBJ_START  +    141)
#define OBJ_SPIKES_UP             (OBJ_START  +    148)
#define OBJ_SPIKES_DOWN           (OBJ_START  +    149)

/* --------------------------------------------------------------- */

#define MAN_START                 (OBJ_START  +    150)

/* --------------------------------------------------------------- */

#define FONT_START                (19 * 48 + 3 * 50)

#define FONT_ARROW_RIGHT_THIN     (FONT_START +      0)
#define FONT_ARROW_UP             (FONT_START +      2)
#define FONT_ARROW_DOWN           (FONT_START +      3)
#define FONT_ARROW_RIGHT          (FONT_START +      4)
#define FONT_ARROW_LEFT           (FONT_START +      5)
#define FONT_ASCII_UPPERCASE      (FONT_START +     10)
#define FONT_ASCII_LOWERCASE      (FONT_START +     69)
#define FONT_ROTATING_QUESTMARK   (FONT_START +     95)

/* --------------------------------------------------------------- */

#define BORD_START                (19 * 48 + 5 * 50)


#define BORD_GREY_START           (BORD_START +      0)
#define BORD_BLUE_START           (BORD_START +     17)
#define BORD_BLUE_MIDDLE          (BORD_START +     17)
#define BORD_BLUE_TOPLEFT         (BORD_START +     18)
#define BORD_BLUE_TOPRIGHT        (BORD_START +     19)
#define BORD_BLUE_BOTTOMLEFT      (BORD_START +     20)
#define BORD_BLUE_BOTTOMRIGHT     (BORD_START +     21)
#define BORD_BLUE_LEFT            (BORD_START +     22)
#define BORD_BLUE_RIGHT           (BORD_START +     23)
#define BORD_BLUE_TOP             (BORD_START +     24)
#define BORD_BLUE_BOTTOM          (BORD_START +     25)
#define BORD_GREY_LABEL_HELP      (BORD_START +     26)
#define BORD_GREY_LABEL_INVENTORY (BORD_START +     30)
#define BORD_GREY_LABEL_FIREPOWER (BORD_START +     33)
#define BORD_GREY_LABEL_HEALTH    (BORD_START +     36)
#define BORD_GREY_LABEL_SCORE     (BORD_START +     38)
#define BORD_GREY_LABEL_P         (BORD_START +     40)
#define BORD_GREY_LABEL_S         (BORD_START +     41)
#define BORD_GREY_LABEL_HEALTH2   (BORD_START +     42)

/* --------------------------------------------------------------- */

#define NUMB_START                (BORD_START +     48)

#define NUMB_100                  (NUMB_START +      0)
#define NUMB_200                  (NUMB_START +      2)
#define NUMB_500                  (NUMB_START +      4)
#define NUMB_1000                 (NUMB_START +      6)
#define NUMB_2000                 (NUMB_START +      8)
#define NUMB_5000                 (NUMB_START +     10)
#define NUMB_MEGA                 (NUMB_START +     12)
#define NUMB_BONUS_1              (NUMB_START +     14)
#define NUMB_BONUS_2              (NUMB_START +     18)
#define NUMB_BONUS_3              (NUMB_START +     22)
#define NUMB_BONUS_4              (NUMB_START +     26)
#define NUMB_BONUS_5              (NUMB_START +     30)
#define NUMB_BONUS_6              (NUMB_START +     34)
#define NUMB_BONUS_7              (NUMB_START +     38)

/* --------------------------------------------------------------- */

#endif // FN_OBJECT

