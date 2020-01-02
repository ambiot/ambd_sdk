// img_pad.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
    FILE *rdHdl, *wr1Hdl;
    int ret, i, wb;
    char buffer[1024];
    unsigned int pad_file_size;
    unsigned int file_size;
    unsigned int write_bytes;
    unsigned int remain_bytes;

    if(argc < 2) {
        printf("Usage: %s <input-filename>\n", argv[0]);
        return -1;
    }

	rdHdl = fopen(argv[1], "rb");
    if(!rdHdl) {
        printf("Error opening file %s.  Error %d:%s\n", argv[1], errno, strerror(errno));
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, argv[1], sizeof(buffer));
    strcat(buffer, ".pad");

    if((wr1Hdl = fopen(buffer, "wb")) == NULL) {
        printf("Error opening file %s ,  Error %d:%s\n", buffer, errno, strerror(errno));
        fclose(rdHdl);
        return -1;
    }

//    printf("opening file %s OK!\n", buffer);

    /* Input file and two output files are now open */
    /* Read input and put into output */
    file_size = 0;
    while((ret = fread(&buffer[0], 1, sizeof(buffer), rdHdl)) > 0) {

        wb = fwrite(&buffer[0], 1, ret, wr1Hdl);
//        printf("Copy to file: ret=%d len=%d\n", wb, ret);
        if (wb < 0) {
            printf("write error: Error %d:%s\n", errno, strerror(errno));
            break;
        }
        file_size += ret;
    }

	memset(buffer, 0xff, sizeof(buffer));

    pad_file_size = atoi(argv[2]);

//    printf("Start to pad to size=%d\n", pad_file_size);
    while (file_size < pad_file_size) {
        remain_bytes = pad_file_size - file_size;
        if ( remain_bytes > sizeof(buffer)) {
            write_bytes = sizeof(buffer);
        }
        else {
            write_bytes = remain_bytes;
        }

        wb = fwrite(&buffer[0], 1, write_bytes, wr1Hdl);
//        printf("Write dummy to file: ret=%d len=%d\n", wb, write_bytes);
        if (wb < 0) {
            printf("write error: Error %d:%s\n", errno, strerror(errno));
            break;
        }
        file_size += write_bytes;
    }

//    printf("All done!!\n");
    fclose(rdHdl);
    fclose(wr1Hdl);
    // print success
//    printf("Exit!!\n");
    return 0;
}
