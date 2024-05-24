/**
 * @file mp3_metadata.c
 * @brief Implementation of MP3 metadata extraction functions.
 *
 * This source file includes detailed implementations of functions declared in mp3_metadata.h.
 * It provides mechanisms to read and parse both ID3v1 and ID3v2 tags found in MP3 files.
 * Functions handle file operations, data extraction, and error checking to ensure accurate metadata retrieval.
 *
 * Usage:
 * A file pointer to an open MP3 file should be passed to these functions, which will then
 * extract and print the metadata such as title, artist, and album.
 * 
 * @author Kalin Borodzhijski
 * @date May 24, 2024
 */

#include "mp3_metadata.h"


int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <file_location> <action>\n", argv[0]);
        fprintf(stderr, "Action must be 'play' or 'metadata'\n");
        return 1;
    }

    char *file_location = argv[1];
    char *action = argv[2];  
    
    FILE *file = fopen(file_location, "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    int use_id3v2 = has_id3v2(file);
    int use_id3v1 = !use_id3v2 ? has_id3v1(file) : 0;
 
    if (!strcmp(action, "metadata"))
    {
        if (use_id3v2) {
            read_id3v2(file);
        } else if (use_id3v1) {
            read_id3v1(file);
        } else {
            printf("No ID3 metadata found.\n");
        }
    }
    else if(!strcmp(action, "play"))
    {
        printf("TBD!\n");
    }
    else
    {
        fprintf(stderr, "Invalid action '%s'. Use 'play' or 'metadata'.\n", argv[2]);
        fclose(file);
        return 1;
    }

}
//--------------------------------------------------------------------------------------------
void read_id3v1(FILE *file) 
{
    fseek(file, -128, SEEK_END);
    char buffer[128] = { 0 };
    if (fread(buffer, 1, 128, file) == 128)
    {
        printf("Title of the song: '%s'\n", buffer[ID3V1_TITLE_START]);
        printf("Artist of the song: '%s'\n", buffer[ID3V1_ARTIST_START]);
        printf("Album of the song: '%s'\n", buffer[ID3V1_ALBUM_START]);
        printf("Year of the song: '%s'\n", buffer[ID3V1_YEAR_START]);
        printf("Comment of the song: '%s'\n", buffer[ID3V1_COMMENT_START]);
        printf("Genre of the song: '%s'\n", buffer[ID3V1_GENRE_START]);
    }
    else
    {
        fprintf(stderr, "Metadata could not be read.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
}
//--------------------------------------------------------------------------------------------
// Helper function to compute synchsafe integer for ID3v2.4
unsigned int synchsafe_to_int(unsigned char *sizeBytes) {
    return (sizeBytes[0] << 21) | (sizeBytes[1] << 14) | (sizeBytes[2] << 7) | sizeBytes[3];
}
//--------------------------------------------------------------------------------------------
// Helper function to read regular integer (for ID3v2.3 and earlier)
unsigned int regular_int(unsigned char *sizeBytes) {
    return (sizeBytes[0] << 24) | (sizeBytes[1] << 16) | (sizeBytes[2] << 8) | sizeBytes[3];
}
//--------------------------------------------------------------------------------------------
void read_id3v2(FILE *file) 
{
    char header[10];
    fseek(file, 0, SEEK_SET);
    
    if (fread(header, 1, 10, file) < 10) {
        fprintf(stderr, "Failed to read ID3v2 header\n");
        return;
    }
    
    int version = header[3];
    unsigned int size = synchsafe_to_int((unsigned char *)&header[6]);
    
    unsigned char *tagData = malloc(size);
    if (!tagData) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    if (fread(tagData, 1, size, file) < size) {
        fprintf(stderr, "Failed to read the full ID3v2 tag\n");
        free(tagData);
        return;
    }

    unsigned int pos = 0;
    while (pos < size) {
        if (tagData[pos] == 0) {
            break;
        }
        
        char frameId[5];
        memcpy(frameId, tagData + pos, 4);
        frameId[4] = '\0';
        pos += 4;
        
        unsigned int frameSize = version == 4 ? synchsafe_to_int(tagData + pos) : regular_int(tagData + pos);
        pos += 4;
        
        unsigned short frameFlags = (tagData[pos] << 8) | tagData[pos + 1];
        pos += 2;
        
        if (pos + frameSize > size) {
            break;
        }
        
        printf("Frame: %s, Size: %u, Flags: %04x\n", frameId, frameSize, frameFlags);
        
        if (frameId[0] == 'T' && frameSize > 1) 
        {
            char *text = malloc(frameSize);
            if (!text) continue;
            
            memcpy(text, tagData + pos, frameSize);
            text[frameSize - 1] = '\0';

            printf("Text: %s\n", text + 1);
            free(text);
        }
        
        pos += frameSize;
    }
    
    free(tagData);

}
//--------------------------------------------------------------------------------------------
int has_id3v1(FILE *file)
{
    fseek(file, -128, SEEK_END);
    char buffer[3];


    if (fread(buffer, 1, 3, file) == 3) {
        return strncmp(buffer, "TAG", 3) == 0;
    }
    return 0;
}
//--------------------------------------------------------------------------------------------
int has_id3v2(FILE *file) 
{
    char header[10];
    fseek(file, 0, SEEK_SET);
    if (fread(header, 1, 10, file) < 10) {
        return 0;
    }
    return strncmp(header, "ID3", 3) == 0;
}
//--------------------------------------------------------------------------------------------

