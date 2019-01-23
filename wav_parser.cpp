#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "wav_parser.h"

#define WAV_PRINT_MSG

const char *WAV_P_FmtString(uint16_t fmt)
{
    switch (fmt) {
    case WAV_FMT_PCM:
        return "PCM";
        break;
    case WAV_FMT_IEEE_FLOAT:
        return "IEEE FLOAT";
        break;
    case WAV_FMT_DOLBY_AC3_SPDIF:
        return "DOLBY AC3 SPDIF";
        break;
    case WAV_FMT_EXTENSIBLE:
        return "EXTENSIBLE";
        break;
    default:
        break;
    }

    return "NON Support Fmt";
}

void WAV_P_PrintHeader(WAVContainer_t *container)
{
    printf("+++++++++++++++++++++++++++/n");
    printf("/n");

    printf("File Magic:         [%c%c%c%c]/n",
           (char)(container->header.magic),
           (char)(container->header.magic>>8),
           (char)(container->header.magic>>16),
           (char)(container->header.magic>>24));
    printf("File Length:        [%d]/n", container->header.length);
    printf("File Type:          [%c%c%c%c]/n",
           (char)(container->header.type),
           (char)(container->header.type>>8),
           (char)(container->header.type>>16),
           (char)(container->header.type>>24));
    printf("/n");
    printf("Fmt Magic:          [%c%c%c%c]/n",
           (char)(container->format.magic),
           (char)(container->format.magic>>8),
           (char)(container->format.magic>>16),
           (char)(container->format.magic>>24));
    printf("Fmt Size:           [%d]/n", container->format.fmt_size);
    printf("Fmt Format:         [%s]/n", WAV_P_FmtString(container->format.format));
    printf("Fmt Channels:       [%d]/n", container->format.channels);
    printf("Fmt Sample_rate:    [%d](HZ)/n", container->format.sample_rate);
    printf("Fmt Bytes_p_second: [%d]/n", container->format.bytes_p_second);
    printf("Fmt Blocks_align:   [%d]/n", container->format.blocks_align);
    printf("Fmt Sample_length:  [%d]/n", container->format.sample_length);

    printf("/n");

    printf("Chunk Type:         [%c%c%c%c]/n",
           (char)(container->chunk.type),
           (char)(container->chunk.type>>8),
           (char)(container->chunk.type>>16),
           (char)(container->chunk.type>>24));
    printf("Chunk Length: [%d]/n", container->chunk.length);

    printf("/n");
    printf("++++++++++++++++++++++++++++++++++++++/n");
}

int WAV_P_CheckValid(WAVContainer_t *container)
{
    if (container->header.magic != WAV_RIFF ||
            container->header.type != WAV_WAVE ||
            container->format.magic != WAV_FMT ||
            container->format.fmt_size != LE_INT(16) ||
            (container->format.channels != LE_SHORT(1) && container->format.channels != LE_SHORT(2))
            || container->chunk.type != WAV_DATA) {
        //fprintf(stderr, "non standard wav file./n");
        return -1;
    }

    return 0;
}

int WAV_ReadHeader(FILE* fd, WAVContainer_t *container)
{
    assert((fd !=0) && container);

    size_t ret = fread(&container->header,1, sizeof(container->header),fd);
    
    if (ret ==sizeof(container->header))
    {
        ret = fread(&container->format,1, sizeof(container->format),fd);
        if(ret ==sizeof(container->format))
        {
            ret = fread(&container->chunk,1, sizeof(container->chunk),fd);
            if(ret == sizeof(container->chunk))
            {
                if (WAV_P_CheckValid(container) >=0)
                {
                    return 0;
                }
            }
        }
    }

        //fprintf(stderr, "Error WAV_ReadHeader/n");
    return -1;
}
