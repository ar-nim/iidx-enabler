/*
 * This file is part of Pendual Enabler.
 *
 * Copyright (C) 2015  kclkcl
 * Copyright (C) 2015  contrixed
 *
 * Pendual Enabler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.
 *
 * Pendual Enabler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Pendual Enabler.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PENDUAL_H
#define PENDUAL_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef SECURE_CRT
#define printf printf_s
#endif
#endif

#include <stdio.h>
#ifndef _WIN32
#include <stdint.h>
#else
typedef BYTE uint8_t;
typedef DWORD uint16_t;
typedef UINT32 uint32_t;
#endif
#include <stdlib.h>
#include <string.h>

FILE *fp;
static int selection;
static const char *filename = "bm2dx.dll";
static const char *filemode = "r+b";
static const char *OF[2] = {
    "ON", "OFF"
};

typedef struct {
    uint8_t timer_freeze;
    uint8_t songs_unlock;
    uint8_t song_delay;
    uint8_t premium_free;
    uint8_t premium_free_timer;
    uint8_t remove_play_free;
    uint8_t replace_play_free;
    uint8_t system_volume;
    uint8_t cs_style_song_select;
    uint8_t darkmode;
} pendual_flags_t;

/* Prototypes. */
static const char *get_flag(uint8_t flag);
static void hexedit(const int address, const uint8_t value);
static const uint8_t hexcheck8(const int address);
static const uint16_t hexcheck16(const int address);
static const uint32_t hexcheck32(const int address);
static void toggles(pendual_flags_t *flags);
static void help();
static void header(pendual_flags_t *flag);
static void operations(const int choice, pendual_flags_t *flag);
int main(void);
#endif
