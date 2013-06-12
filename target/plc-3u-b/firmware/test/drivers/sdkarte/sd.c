
/*
 * Copyright (c) 2006-2008 by Roland Riegel <feedback@roland-riegel.de>
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <stdint.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "fat16.h"
#include "partition.h"
#include "sd.h"
#include "sd_raw.h"

#include <string.h>

/**
 * \addtogroup sdcard
 *
 * @{
 *
 * \addtogroup sd MMC/SD memory card interface
 *
 * This module implements read and write support for MMC and SD cards.
 *
 * It includes
 * - low-level \link sd_raw MMC read/write routines \endlink
 * - \link partition partition table support \endlink
 * - a simple \link fat16 FAT16 read/write implementation \endlink
 *
 * @{
 */
/**
 * \file
 * MMC/SD handling (license: GPLv2)
 *
 * \author Roland Riegel
 */

static struct partition_struct* sd_partition;
static struct fat16_fs_struct* sd_fs;
static struct fat16_dir_struct* sd_dd;

int8_t sd_open()
{
    sd_close();

    /* setup sd card slot */
    if(!sd_raw_init())
        return SD_ERROR_INIT;

    /* open first partition */
    sd_partition = partition_open(sd_raw_read,
                                  sd_raw_read_interval,
                                  sd_raw_write,
                                  sd_raw_write_interval,
                                  0
                                 );

    printf_P(PSTR("\n\rOpened partition: %X\n\r"), sd_partition);

    if(!sd_partition)
    {
        /* If the partition did not open, assume the storage device
         * is a "superfloppy", i.e. has no MBR.
         */
        sd_partition = partition_open(sd_raw_read,
                                      sd_raw_read_interval,
                                      sd_raw_write,
                                      sd_raw_write_interval,
                                      -1
                                     );

        if(!sd_partition) {
            printf_P(PSTR("\n\rProblem opening no-mbr partition\n\r"));
            return SD_ERROR_PARTITION;
        }
    }

    /* open file system */
    sd_fs = fat16_open(sd_partition);
    printf_P(PSTR("\n\rsd_fs = %X\n\r"), sd_fs);

    if(!sd_fs)
    {
        printf_P(PSTR("\n\rProblem opening FS\n\r"));
        sd_close();
        return SD_ERROR_FS;
    }

    /* open root directory */
    struct fat16_dir_entry_struct directory;
    fat16_get_dir_entry_of_path(sd_fs, "/", &directory);

    sd_dd = fat16_open_dir(sd_fs, &directory);
    printf_P(PSTR("\n\rsd_dd = %X\n\r"), sd_dd);

    if(!sd_dd)
    {
        sd_close();
        return SD_ERROR_ROOTDIR;
    }

    return SD_ERROR_NONE;
}

void sd_close(void)
{
    fat16_close_dir(sd_dd);
    fat16_close(sd_fs);
    partition_close(sd_partition);
    sd_dd = 0;
    sd_fs = 0;
    sd_partition = 0;
}

struct fat16_fs_struct* sd_get_fs(void)
{
    return sd_fs;
}

struct fat16_dir_struct* sd_get_root_dir(void)
{
    return sd_dd;
}

uint8_t sd_find_file_in_dir(struct fat16_dir_struct* dd, const char* name, struct fat16_dir_entry_struct* dir_entry)
{
    while(fat16_read_dir(dd, dir_entry))
    {
        if(strcmp(dir_entry->long_name, name) == 0)
        {
            fat16_reset_dir(dd);
            return 1;
        }
    }

    return 0;
}

struct fat16_file_struct* sd_open_file_in_dir(struct fat16_dir_struct* dd, const char* name)
{
    struct fat16_dir_entry_struct file_entry;
    if(!sd_find_file_in_dir(dd, name, &file_entry))
        return 0;

    return fat16_open_file(sd_fs, &file_entry);
}

/**
 * @}
 * @}
 */

