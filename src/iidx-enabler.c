/*
 * This file is part of IIDX Enabler.
 *
 * Copyright (C) 2016  kclkcl
 * Copyright (C) 2015  contrixed
 *
 * IIDX Enabler is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.
 *
 * IIDX Enabler is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with IIDX Enabler.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "inc/iidx-enabler.h"

static const char *get_flag(uint8_t flag)
{
    return OF[flag];
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

static void toggles(iidx_flags_t *flags)
{
    //Check for Timer Freeze
    if (hexcheck8(0x8F98E) == 0x74)
    {
        flags->timer_freeze = 1 << 0;
    }

    //Check for All Song Unlock
    if (hexcheck16(0x4FD84) == 0x74)
    {
        flags->songs_unlock = 1 << 0;
    }

    //Check for CS Style Song Delay
    if (hexcheck8(0x6F3FF) == 0x7C)
    {
        flags->song_delay = 1 << 0;
    }

    //Check for Premium Free
    if (hexcheck8(0x562BA) == 0x75)
    {
        flags->premium_free = 1 << 0;
    }

    //Check for Premium Free Timer Freeze
    if (hexcheck8(0x4F8FD) == 0x48)
    {
        flags->premium_free_timer = 1 << 0;
    }

    //Check for REMOVE FREE PLAY TEXT; NOT AVAILABLE YET FOR COPULA
    /*
    if (hexcheck32(0x14C3A) == 0x1012)
    {
        flags->remove_play_free = 1 << 0;
    }
    */

    //Check for Replace FREE PLAY Text with LED Ticker. NOT YET AVAILABLE FOR COPULA
    /*
    if (hexcheck32(0x1379A) == 0x1012)
    {
        flags->replace_play_free = 1 << 0;
    }
    */

    //Check for Leave System Volume Alone
    if (hexcheck16(0xCB2B9) == 0x00)
    {
        flags->system_volume = 1 << 0;
    }

    //Check for Cursor Lock
    if (hexcheck16(0x63722) == 0x23)
    {
        flags->cursor_lock = 1 << 0;
    }

    //Check for dark mode. NOT YET AVAILABLE FOR COPULA
    /*
    if (hexcheck16(0x71182) == 0x32)
    {
        flags->darkmode = 1 << 0;
    }
    */
}

static void help(void)
{
    printf("Welcome to IIDX COPULA Enabler!\n");
    printf("By KcLKcL\n\n");
    printf("This tool will auto-magically patch your COPULA dll to enable\ncertain features and hacks!\n\n");
    printf("bm2dx.dll not found, put this on the same directory as bm2dx.dll, and make sure bm2dx.dll is not read-only.");
    getchar();
}

static void header(iidx_flags_t *flag)
{
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif
    printf("Welcome to COPULA Enabler!\n");
    printf("By KcLKcL\n");
    printf("Improved by contrixed\n\n");
    printf("This tool will auto-magically patch your COPULA dll to enable\ncertain features and hacks!\n\n");
    toggles(flag);
    printf("Available Hacks:\n");
    printf("1. Timer Freeze: %s\n", get_flag(flag->timer_freeze));
    printf("2. Unlock All Songs: %s\n", get_flag(flag->songs_unlock));
    printf("3. CS Style Song Delay: %s\n", get_flag(flag->song_delay));
    printf("4. Cursor Lock: %s\n", get_flag(flag->cursor_lock));
    printf("5. Premium Free: %s\n", get_flag(flag->premium_free));
    printf("6. Premium Free Timer Freeze: %s\n\n", get_flag(flag->premium_free_timer));
    printf("---FREE PLAY TEXT HACKS ARE CURRENTLY UNAVAILABLE---\n");
    //printf("7. Remove FREE PLAY Text: %s\n", get_flag(flag->remove_play_free));
    //printf("8. Replace FREE Play Text With LED Ticker: %s\n", get_flag(flag->replace_play_free));
    //printf("-----------------------------------------------------------\n\n");
    //printf("10. Dark Mode: %s\n", get_flag(flag->darkmode));
    printf("7. Leave System Volume Alone: %s\n", get_flag(flag->system_volume));
    printf("8. Exit\n\n");
    printf("Enter Selection to toggle: ");
}

static void operations(const int choice, iidx_flags_t *flag)
{
    if (choice == 0x01)
    {
        if (flag->timer_freeze)
        {
            hexedit(0x8F98E, 0xEB);
            fclose(fp);
        }
        else
        {
            hexedit(0x8F98E, 0x74);
            fclose(fp);
        }
    }

    if (choice == 0x02)
    {
        if (flag->songs_unlock)
        {
            hexedit(0x4FD84, 0x90);
            hexedit(0x4FD85, 0x90);
            fclose(fp);
        }
        else
        {
            hexedit(0x4FD84, 0x74);
            hexedit(0x4FD85, 0x16);
            fclose(fp);
        }
    }

    if (choice == 0x03)
    {
        if (flag->song_delay)
        {
            hexedit(0x6F3FF, 0xEB);
            fclose(fp);
        }
        else
        {
            hexedit(0x6F3FF, 0x7C);
            fclose(fp);
        }
    }

    if (choice == 0x04)
    {
        if (flag->cursor_lock)
        {
            hexedit(0x63722, 0x90);
            hexedit(0x63723, 0x90);
            fclose(fp);
        }
        else
        {
            hexedit(0x63722, 0x74);
            hexedit(0x63723, 0x23);
            fclose(fp);
       }
    }

    if (choice == 0x05)
    {
        if (flag->premium_free)
        {
            hexedit(0x562BA, 0xEB);
            fclose(fp);
        }
        else
        {
            hexedit(0x562BA, 0x75);
            fclose(fp);
        }
    }

    if (choice == 0x06)
    {
        if (flag->premium_free_timer)
        {
            hexedit(0x4F8FD, 0x90);
            fclose(fp);
         }
         else
         {
            hexedit(0x4F8FD, 0x48);
            fclose(fp);
         }
    }

    /*
    if (choice == 0x07)
    {
        if (!flag->replace_play_free)
        {
            return;
         }
         else if (flag->remove_play_free)
         {
            hexedit(0x14C3A, 0x99);
            hexedit(0x14C3B, 0x3f);
            hexedit(0x14C3C, 0x12);
            hexedit(0x14C3D, 0x10);
            fclose(fp);
         }
         else
         {
            hexedit(0x14C3A, 0x90);
            hexedit(0x14C3B, 0x3f);
            hexedit(0x14C3C, 0x12);
            hexedit(0x14C3D, 0x10);
            fclose(fp);
         }
    }

    if (choice == 0x08)
    {
        if (!flag->remove_play_free)
        {
            return;
        }
        else if (flag->replace_play_free)
        {
            hexedit(0x14C3A, 0x24);
            hexedit(0x14C3B, 0xAA);
            hexedit(0x14C3C, 0x43);
            hexedit(0x14C3D, 0x11);
            fclose(fp);
        }
        else
        {
            hexedit(0x14C3A, 0x90);
            hexedit(0x14C3B, 0x3f);
            hexedit(0x14C3C, 0x12);
            hexedit(0x14C3D, 0x10);
            fclose(fp);
        }
    }
    */

    if (choice == 0x0B)
    {
        if (flag->system_volume)
        {
            hexedit(0xCB2B9, 0x01);
            fclose(fp);
        }
        else
        {
            hexedit(0xCB2B9, 0xEB + '\0');
            fclose(fp);
       }
    }

    /*
    if (choice == 0x0A)
    {
        if (flag->darkmode)
        {
            hexedit(0xD5D09, 0x01);
            fclose(fp);
        }
        else
        {
            hexedit(0xD5D09, 0xEB + '\0');
            fclose(fp);
        }
    }
    */
}

int main(void)
{
    iidx_flags_t *flags;

    fp = fopen(filename, filemode);


    flags =  malloc(10);

    if (fp == NULL)
    {
        help();
    }
    else
    {
        do
        {
            fp = fopen(filename, filemode);
            header(flags);
            scanf("%d", &selection);
            fflush(stdin);
            operations(selection, flags);
        } while (selection != 0x08);
    }

    // release the struct.
    free(flags);
    return 0x00;
}
