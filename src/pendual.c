#include "inc/pendual.h"

static const char *get_flag(uint8_t flag)
{
    printf("FLAG to string: %s\n", OF[flag]);
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

static void toggles(pendual_flags_t *flags)
{
    printf("uint8: %d", (uint8_t) 1 << 0);

    //Check for Timer Freeze
    if (hexcheck8(0x9C55E) == 0x74)
    {
        printf("OFF\n");
        flags->timer_freeze = 1 << 0;
        printf("Value of struct. %d\n", flags->timer_freeze);
        printf("OF %s\n", OF[1]);
    }

    //Check for All Song Unlock
    if (hexcheck16(0x58B3E) == 0x0A)
    {
        flags->songs_unlock = 1 << 0;
    }

    //Check for CS Style Song Delay
    if (hexcheck8(0x77CF6) == 0x7C)
    {
        flags->song_delay = 1 << 0;
    }

    //Check for Premium Free
    if (hexcheck8(0x5D31B) == 0x75)
    {
        flags->premium_free = 1 << 0;
    }

    //Check for Premium Free Timer Freeze
    if (hexcheck8(0x563AD) == 0x48)
    {
        flags->premium_free_timer = 1 << 0;
    }

    //Check for REMOVE FREE PLAY TEXT
    if (hexcheck32(0x14C3A) == 0x1012)
    {
        flags->remove_play_free = 1 << 0;
    }

    //Check for Replace FREE PLAY Text with LED Ticker
    if (hexcheck32(0x14C3A) == 0x1012)
    {
        flags->replace_play_free = 1 << 0;
    }

    //Check for Leave System Volume Alone
    if (hexcheck16(0xD5D09) == 0x00)
    {
        flags->system_volume = 1 << 0;
    }

    //Check for CS Style Song Select
    if (hexcheck16(0x6BF3A) == 0x23)
    {
        flags->cs_style_song_select = 1 << 0;
    }

    //Check for dark mode
    if (hexcheck16(0x71182) == 0x32)
    {
        flags->darkmode = 1 << 0;
    }

    //free(flags);
}

static void help(void)
{
    printf("Welcome to PENDUAL Enabler!\n");
    printf("By KcLKcL\n\n");
    printf("This tool will auto-magically patch your PENDUAL dll to enable\ncertain features and hacks!\n\n");
    printf("bm2dx.dll not found, put this on the same directory as bm2dx.dll, and make sure bm2dx.dll is not read-only.");
    getchar();
}

static void header(pendual_flags_t *flag)
{
    #ifdef _WIN32
      system("cls");
    #else
      system("clear");
    #endif
    printf("Welcome to PENDUAL Enabler!\n");
    printf("By KcLKcL\n");
    printf("Improved by contrixed\n\n");
    printf("This tool will auto-magically patch your PENDUAL dll to enable\ncertain features and hacks!\n\n");
    toggles(flag);
    printf("Available Hacks:\n");
    printf("1. Timer Freeze: %s\n", get_flag(flag->timer_freeze));
    printf("2. Unlock All Songs: %s\n", get_flag(flag->songs_unlock));
    printf("3. CS Style Song Delay: %s\n", get_flag(flag->song_delay));
    printf("4. CS Style Song Select: %s\n", get_flag(flag->cs_style_song_select));
    printf("5. Premium Free: %s\n", get_flag(flag->premium_free));
    printf("6. Premium Free Timer Freeze: %s\n\n", get_flag(flag->premium_free_timer));
    printf("---Only one FREE PLAY hacks may be used at the same time---\n");
    printf("7. Remove FREE PLAY Text: %s\n", get_flag(flag->remove_play_free));
    printf("8. Replace FREE Play Text With LED Ticker: %s\n", get_flag(flag->replace_play_free));
    printf("-----------------------------------------------------------\n\n");
    printf("10. Dark Mode: %s\n", get_flag(flag->darkmode));
    printf("11. Leave System Volume Alone: %s\n", get_flag(flag->system_volume));
    printf("9. Exit\n\n");
    printf("Enter Selection to toggle: ");
}

static void operations(const int choice, pendual_flags_t *flag)
{
    if (choice == 0x01)
    {
        if (flag->timer_freeze)
        {
            hexedit(0x9C55E, 0xEB);
            fclose(fp);
        }
        else
        {
            hexedit(0x9C55E, 0x74);
            fclose(fp);
        }
    }

    if (choice == 0x02)
    {
        if (flag->songs_unlock)
        {
            hexedit(0x58B3E, 0x90);
            hexedit(0x58B3F, 0x90);
            fclose(fp);
        }
        else
        {
            hexedit(0x58B3E, 0x75);
            hexedit(0x58B3F, 0x0A);
            fclose(fp);
        }
    }

    if (choice == 0x03)
    {
        if (flag->song_delay)
        {
            hexedit(0x77CF6, 0xEB);
            fclose(fp);
        }
        else
        {
            hexedit(0x77CF6, 0x7C);
            fclose(fp);
        }
    }

    if (choice == 0x04)
    {
        if (flag->cs_style_song_select)
        {
            hexedit(0x6BF3A, 0x90);
            hexedit(0x6BF3B, 0x90);
            fclose(fp);
        }
        else
        {
            hexedit(0x6BF3A, 0x74);
            hexedit(0x6BF3B, 0x23);
            fclose(fp);
       }
    }

    if (choice == 0x05)
    {
        if (flag->premium_free)
        {
            hexedit(0x5D31B, 0xEB);
            fclose(fp);
        }
        else
        {
            hexedit(0x5D31B, 0x75);
            fclose(fp);
        }
    }

    if (choice == 0x06)
    {
        if (flag->premium_free_timer)
        {
            hexedit(0x563AD, 0x90);
            fclose(fp);
         }
         else
         {
            hexedit(0x563AD, 0x48);
            fclose(fp);
         }
    }

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

    if (choice == 0x0B)
    {
        if (flag->system_volume)
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
}

int main(void)
{
    fp = fopen(filename, filemode);
    pendual_flags_t *flags =  malloc(10);
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
        } while (selection != 0x09);
    }

    // release the struct.
    free(flags);
    return 0x00;
}
