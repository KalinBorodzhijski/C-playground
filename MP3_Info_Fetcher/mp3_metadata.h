/**
 * @file mp3_metadata.h
 * @brief Header file for MP3 metadata extraction functions.
 *
 * This file declares functions and structures used for extracting metadata
 * from MP3 files. It supports both ID3v1 and ID3v2 tags. The functions allow
 * reading of properties such as the title, artist, album, and more from an MP3 file.
 *
 * @author Kalin Borodzhijski
 * @date May 24, 2024
 */

#ifndef MP3_METADATA_H
#define MP3_METADATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ID3V2_HEADER_SIZE       10

#define ID3V1_TITLE_START       3
#define ID3V1_ARTIST_START      33
#define ID3V1_ALBUM_START       63
#define ID3V1_YEAR_START        93
#define ID3V1_COMMENT_START     97
#define ID3V1_GENRE_START       127

/**
 * Checks if an MP3 file contains an ID3v2 tag.
 * @param file Pointer to a FILE object that has been opened in binary read mode.
 * @return int Returns 1 if an ID3v2 tag is found at the beginning of the file, 0 otherwise.
 */
int has_id3v2(FILE *file);

/**
 * Checks if an MP3 file contains an ID3v1 tag.
 * @param file Pointer to a FILE object that has been opened in binary read mode.
 * @return int Returns 1 if an ID3v1 tag is found at the end of the file, 0 otherwise.
 */
int has_id3v1(FILE *file);

/**
 * Reads and displays ID3v2 tag information from an MP3 file.
 * @param file Pointer to a FILE object that has been opened in binary read mode.
 * This function seeks to the beginning of the file and reads the ID3v2 tag data,
 * printing out the metadata such as title, artist, and album.
 */
void read_id3v2(FILE *file);

/**
 * Reads and displays ID3v1 tag information from an MP3 file.
 * @param file Pointer to a FILE object that has been opened in binary read mode.
 * This function reads the ID3v1 tag data, printing out the metadata such as title, artist, and album.
 */
void read_id3v1(FILE *file);


#endif // MP3_METADATA_H
