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
#include <stdio.h>
#include <stdint.h>

/* Make Windows use printf_s. */
#ifdef _WIN32
#ifdef SECURE_CRT
#define printf printf_s
#endif
#endif

static int fail_count = 0;
static int success_count = 0;
FILE *fp;

static void assert_equals8(uint8_t a, uint8_t b, const char *func)
{
    if (a == b)
    {
        printf("%s Passed.\n", func);
        success_count += 1;
        return;
    }

    if (a != b)
    {
       printf("%s Failed.\n", func);
       fail_count += 1;
       return;
    }
}

static void assert_equals16(uint16_t a, uint16_t b, const char *func)
{
    if (a == b)
    {
        printf("%s Passed.\n", func);
        success_count += 1;
        return;
    }

    if (a != b)
    {
        printf("%s Failed.\n", func);
        fail_count += 1;
        return;
    }
}

static void assert_equals32(uint32_t a, uint32_t b, const char *func)
{
    if (a == b)
    {
        printf("%s Passed.\n", func);
        success_count += 1;
        return;
    }

    if (a != b)
    {
        printf("%s Failed.\n", func);
        fail_count += 1;
        return;
    }
}

static void hexedit(const int address, const uint8_t value)
{
    fseek(fp, address, SEEK_SET);
    fwrite(&value, sizeof(char), 1, fp);
}

static const uint8_t hexcheck8(const int address)
{
    uint8_t value;
    fseek(fp, address, SEEK_SET);
    fread(&value, sizeof(uint8_t) , 1, fp);
    return value;
}

/**
 * Obtain two bytes and represent them as a 16 bit unsigned integer.
 *
 * @param[in] int address The offset of the location to obtain.
 * @return The value shifted right by 8.
 */
static const uint16_t hexcheck16(const int address)
{
    uint16_t value;
    fseek(fp, address, SEEK_SET);
    fread(&value, sizeof(uint16_t), 1, fp);
    return value >> 8;
}

static const uint32_t hexcheck32(const int address)
{
    uint32_t value;
    fseek(fp, address, SEEK_SET);
    fread(&value, sizeof(uint32_t), 1, fp);
    return value >> 16;
}


static void test_value_timer_freeze(void)
{
    uint8_t value = hexcheck8(0x9C55E);

    if (value == 0x74)
    {
        assert_equals8(value, 0x74, "test_value_timer_freeze [normal value]");
        return;
    }

    assert_equals8(value, 0xEB, "test_value_timer_freeze [modified value]");
}

static void test_value_all_songs_unlock(void)
{
    uint16_t value = hexcheck16(0x58B3E);

    printf("value %d\n", value);

    if (value == 0x0A)
    {
        assert_equals16(value, 0x0A, "test_value_all_songs_unlock [normal value]");
        return;
    }

    assert_equals16(value, 0x90, "test_value_all_songs_unlock [modified value]");
}

static void test_value_song_delay(void)
{
    uint8_t value = hexcheck8(0x77CF6);

    if (value == 0x7C)
    {
        assert_equals8(value, 0x7C, "test_value_song_delay [normal value]");
        return;
    }

    assert_equals8(value, 0xEB, "test_value_song_delay [modified value]");
}

static void test_value_premium_free(void)
{
    uint8_t value = hexcheck8(0x5D31B);

    if (value == 0x75)
    {
        assert_equals8(value, 0x75, "test_value_premium_free [normal value]");
        return;
    }

    assert_equals8(value, 0xEB, "test_value_premium_free [modified value]");
}

static void test_value_premium_timer_freeze(void)
{
    uint8_t value = hexcheck8(0x563AD);

    if (value == 0x48)
    {
        assert_equals8(value, 0x48, "test_value_premium_timer_freeze [normal value]");
        return;
    }

    assert_equals8(value, 0x90, "test_value_premium_timer_freeze [modified value]");
}

static void test_value_remove_free_play_text(void)
{
    uint32_t value = hexcheck32(0x14C3A);

    if (value == 0x1012)
    {
        assert_equals32(value, 0x1012, "test_value_remove_free_play_text [normal value]");
        return;
    }

    assert_equals32(value, 0x1143, "test_value_remove_free_play_text [modified value]");
}

static void test_value_remove_free_play_text_led(void)
{
    uint32_t value = hexcheck32(0x14C3A);

    if (value == 0x1012)
    {
        assert_equals32(value, 0x1012, "test_value_remove_free_play_text_led [normal value]");
        return;
    }

    assert_equals32(value, 0x1143, "test_value_remove_free_play_text_led [modified value]");
}

static void test_value_leave_system_volume_alone(void)
{
    uint16_t value = hexcheck16(0xD5D09);

    if (value == 0x00)
    {
        assert_equals8(value, 0x00, "test_value_leave_system_volume_alone [normal value]");
        return;
    }

    printf("Value of system volume: %d\n", value);
    assert_equals8(value, 0x01, "test_value_leave_system_volume_alone [modified value]");
}

static void test_value_cs_style_select(void)
{
    uint16_t value = hexcheck16(0x6BF3A);

    printf("value of cs style %d", value);
    if (value == 0x23)
    {
        assert_equals16(value, 0x23, "test_value_cs_style_select [normal value]");
        return;
    }

    assert_equals16(value, 0x90, "test_value_cs_style_select [modified value]");
}

static void test_value_dark_mode(void)
{
    uint16_t value = hexcheck16(0x71182);

    if (value == 0x32)
    {
        assert_equals16(value, 0x32, "test_value_dark_mode [normal value]");
        return;
    }

    assert_equals16(value, 0x01, "test_value_dark_mode [modified value]");
}


static void write_changes(void)
{
    /* time freeze */
    hexedit(0x9C55E, 0xEB);
    // 2
    hexedit(0x58B3E, 0x90);
    hexedit(0x58B3F, 0x90);
    // 3
    hexedit(0x77CF6, 0xEB);
    // 4
    hexedit(0x6BF3A, 0x90);
    hexedit(0x6BF3B, 0x90);
    // 5
    hexedit(0x5D31B, 0xEB);
    // 6
    hexedit(0x563AD, 0x90);
    // 7
    hexedit(0x14C3A, 0x99);
    hexedit(0x14C3B, 0x3f);
    hexedit(0x14C3C, 0x12);
    hexedit(0x14C3D, 0x10);
    // 8
    hexedit(0x14C3A, 0x24);
    hexedit(0x14C3B, 0xAA);
    hexedit(0x14C3C, 0x43);
    hexedit(0x14C3D, 0x11);
    // 9 / 10
    hexedit(0xD5D09, 0x01);
}

static void reset_changes(void)
{
  // 1
  hexedit(0x9C55E, 0x74);
  // 2
  hexedit(0x58B3E, 0x75);
  hexedit(0x58B3F, 0x0A);
  // 3
  hexedit(0x77CF6, 0x7C);
  // 4
  hexedit(0x6BF3A, 0x74);
  hexedit(0x6BF3B, 0x23);
  // 5
  hexedit(0x5D31B, 0x75);
  // 6
  hexedit(0x563AD, 0x48);
  // 7
  hexedit(0x14C3A, 0x90);
  hexedit(0x14C3B, 0x3f);
  hexedit(0x14C3C, 0x12);
  hexedit(0x14C3D, 0x10);
  // 8
  hexedit(0x14C3A, 0x90);
  hexedit(0x14C3B, 0x3f);
  hexedit(0x14C3C, 0x12);
  hexedit(0x14C3D, 0x10);
  // 9 / 10
  hexedit(0xD5D09, 0xEB + '\0');
}

int main(int argc, char *argv[])
{
    fp = fopen("fake.bm2x.dll", "r+b");

    if (fp == NULL)
    {
        printf("File failed to open.\n");
        return 1;
    }

    printf("Unittest for Pendual.\n");
    printf("Written by: contrixed.\n");
    printf("Testing normal values.\n");
    printf("This case scenario is a untouched DLL.\n\n");

    test_value_timer_freeze();
    test_value_all_songs_unlock();
    test_value_song_delay();
    test_value_cs_style_select();
    test_value_dark_mode();
    test_value_leave_system_volume_alone();
    test_value_premium_free();
    test_value_premium_timer_freeze();
    test_value_remove_free_play_text();
    test_value_remove_free_play_text_led();

    printf("\n");
    printf("Writing changes to fake.bm2x.dll.\n");
    printf("Test will resume momentarily\n");
    write_changes();

    printf("Testing modified values.\n");
    printf("This case scenario is a modified DLL.\n\n");

    test_value_timer_freeze();
    test_value_all_songs_unlock();
    test_value_song_delay();
    test_value_cs_style_select();
    test_value_dark_mode();
    test_value_leave_system_volume_alone();
    test_value_premium_free();
    test_value_premium_timer_freeze();
    test_value_remove_free_play_text();
    test_value_remove_free_play_text_led();

    printf("\n");
    printf("Resetting changes back to an unmodified state.\n");
    reset_changes();

    printf("\n");
    printf("Unittest complete!\n");
    printf("Fails: %d ---------- Passes: %d\n", fail_count, success_count);
    printf("Bye bye.\n");
    return 0;
}
