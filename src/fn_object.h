/*******************************************************************
 *
 * Project: FreeNukum 2D Jump'n Run
 * File:    Object functions
 *
 * *****************************************************************
 *
 * Copyright 2007-2008 Wolfgang Silbermayr
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
 * Freenukum is distributed in the hope that it will be useful,
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

#define BACKGROUND_START                            (0)
#define BACKGROUND_END                         (4 * 48)

/* --------------------------------------------------------------- */

#define SOLID_START                      BACKGROUND_END
#define SOLID_END                              (8 * 48)

#define SOLID_EXPANDINGFLOOR     (SOLID_END -        1)

/* --------------------------------------------------------------- */

#define ANIM_START                            SOLID_END

#define ANIM_FLYBOT               (ANIM_START +      0)
#define ANIM_FOOTBOT              (ANIM_START +     10)
#define ANIM_CARBOT               (ANIM_START +     34)
#define ANIM_EXPLODE              (ANIM_START +     42)
#define ANIM_FIREWHEEL_OFF        (ANIM_START +     48)
#define ANIM_FIREWHEEL_ON         (ANIM_START +     64)
#define ANIM_ROBOT                (ANIM_START +     80)
#define ANIM_BOMBFIRE             (ANIM_START +     90)
#define ANIM_EXITDOOR             (ANIM_START +     96)
#define ANIM_BOMB                 (ANIM_START +    112)
#define ANIM_RABBIT1              (ANIM_START +    116)
#define ANIM_BALLWORM             (ANIM_START +    122)
#define ANIM_SODA                 (ANIM_START +    128)
#define ANIM_SODAFLY              (ANIM_START +    132)
#define ANIM_WALLCRAWLERBOT_LEFT  (ANIM_START +    136)
#define ANIM_WALLCRAWLERBOT_RIGHT (ANIM_START +    140)
#define ANIM_FLOOR_UNSTABLE       (ANIM_START +    146)
#define ANIM_CRAP                 (ANIM_START +    148)
#define ANIM_FAN                  (ANIM_START +    158)
#define ANIM_HELICOPTER           (ANIM_START +    166)
#define ANIM_CAMERA_LEFT          (ANIM_START +    200)
#define ANIM_CAMERA_CENTER        (ANIM_START +    201)
#define ANIM_CAMERA_RIGHT         (ANIM_START +    202)
#define ANIM_BROKENWALLBG         (ANIM_START +    203)
#define ANIM_STONEBG              (ANIM_START +    204)
#define ANIM_STONEWINDOWBG        (ANIM_START +    206)
#define ANIM_WHITEBALLSMALL       (ANIM_START +    209)
#define ANIM_WHITEBALLBIG         (ANIM_START +    210)
#define ANIM_TELEPORTER1          (ANIM_START +    212)
#define ANIM_MINE                 (ANIM_START +    223)
#define ANIM_TELEPORTER2          (ANIM_START +    226)
#define ANIM_RABBIT2              (ANIM_START +    230)
#define ANIM_TELEPORTER3          (ANIM_START +    240)
#define ANIM_FIREGNOME            (ANIM_START +    242)
#define ANIM_FENCEBG              (ANIM_START +    256)
#define ANIM_WINDOWBG             (ANIM_START +    253)
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
#define OBJ_BOOT                  (OBJ_START  +     10)
#define OBJ_ROCKET                (OBJ_START  +     11)
#define OBJ_CLAMP                 (OBJ_START  +     18)
#define OBJ_DUST                  (OBJ_START  +     19)
#define OBJ_FIRERIGHT             (OBJ_START  +     24)
#define OBJ_FIRELEFT              (OBJ_START  +     29)
#define OBJ_STEAM                 (OBJ_START  +     34)
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
#define OBJ_ROBOHAND              (OBJ_START  +     63)
#define OBJ_ACCESS_CARD           (OBJ_START  +     64)
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
#define OBJ_ACCESS_CARD_SLOT      (OBJ_START  +    105)
#define OBJ_GLOVE_SLOT            (OBJ_START  +    114)
#define OBJ_DUKE_WORD             (OBJ_START  +    118)
#define OBJ_LETTER_D              (OBJ_START  +    118)
#define OBJ_LETTER_U              (OBJ_START  +    119)
#define OBJ_LETTER_K              (OBJ_START  +    120)
#define OBJ_LETTER_E              (OBJ_START  +    121)
#define OBJ_EMPTY                 (OBJ_START  +    122)
#define OBJ_NOTE                  (OBJ_START  +    123)
#define OBJ_KEY_RED               (OBJ_START  +    124)
#define OBJ_KEY_GREEN             (OBJ_START  +    125)
#define OBJ_KEY_BLUE              (OBJ_START  +    126)
#define OBJ_KEY_PINK              (OBJ_START  +    127)
#define OBJ_DOOR                  (OBJ_START  +    128)
#define OBJ_KEYHOLE_BLACK         (OBJ_START  +    136)
#define OBJ_KEYHOLE_RED           (OBJ_START  +    137)
#define OBJ_KEYHOLE_GREEN         (OBJ_START  +    138)
#define OBJ_KEYHOLE_BLUE          (OBJ_START  +    139)
#define OBJ_KEYHOLE_PINK          (OBJ_START  +    140)
#define OBJ_BADGUY_SMALL          (OBJ_START  +    141)
#define OBJ_SPIKES_UP             (OBJ_START  +    148)
#define OBJ_SPIKES_DOWN           (OBJ_START  +    149)

/* --------------------------------------------------------------- */

#define HERO_START                (OBJ_START  +    150)

#define HERO_NUM_ANIM_WALKING     (4)
#define HERO_WALKING_LEFT         (HERO_START +      0)
#define HERO_WALKING_RIGHT        (HERO_START +   0x10)
#define HERO_NUM_ANIM_JUMPING     (1)
#define HERO_JUMPING_LEFT         (HERO_START +   0x20)
#define HERO_JUMPING_RIGHT        (HERO_START +   0x24)
#define HERO_NUM_ANIM_FALLING     (1)
#define HERO_FALLING_LEFT         (HERO_START +   0x28)
#define HERO_FALLING_RIGHT        (HERO_START +   0x2C)
#define HERO_NUM_ANIM_STANDING    (1)
#define HERO_STANDING_LEFT        (HERO_START +   0x30)
#define HERO_STANDING_RIGHT       (HERO_START +   0x34)
#define HERO_SKELETON_LEFT        (HERO_START +   0xB0)
#define HERO_SKELETON_RIGHT       (HERO_START +   0xB4)

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
#define NUMB_10000                (NUMB_START +     12)
#define NUMB_BONUS_1_LEFT         (NUMB_START +     14)
#define NUMB_BONUS_1_RIGHT        (NUMB_START +     16)
#define NUMB_BONUS_2_LEFT         (NUMB_START +     18)
#define NUMB_BONUS_2_RIGHT        (NUMB_START +     20)
#define NUMB_BONUS_3_LEFT         (NUMB_START +     22)
#define NUMB_BONUS_3_RIGHT        (NUMB_START +     24)
#define NUMB_BONUS_4_LEFT         (NUMB_START +     26)
#define NUMB_BONUS_4_RIGHT        (NUMB_START +     28)
#define NUMB_BONUS_5_LEFT         (NUMB_START +     30)
#define NUMB_BONUS_5_RIGHT        (NUMB_START +     32)
#define NUMB_BONUS_6_LEFT         (NUMB_START +     34)
#define NUMB_BONUS_6_RIGHT        (NUMB_START +     36)
#define NUMB_BONUS_7_LEFT         (NUMB_START +     38)
#define NUMB_BONUS_7_RIGHT        (NUMB_START +     40)

/* --------------------------------------------------------------- */

#endif /* FN_OBJECT */

