#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int rdHdl, wr1Hdl, ret, i, wb;
    char buffer[1024];
    unsigned int pad_file_size;
    unsigned int file_size;
    unsigned int write_bytes;
    unsigned int remain_bytes;

    if(argc < 2) {
        printf("Usage: %s <input-filename>\n", argv[0]);
        return -1;
    }

    if((rdHdl = open(argv[1], O_RDONLY | O_NONBLOCK)) < 0) {
        printf("Error opening file %s.  Error %d:%s\n", argv[1], errno, strerror(errno));
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));
    strncpy(buffer, argv[1], sizeof(buffer));
    strcat(buffer, ".pad");

    if((wr1Hdl = open(buffer, O_WRONLY | O_CREAT | O_NONBLOCK)) < 0) {
        printf("Error opening file %s ,  Error %d:%s\n", buffer, errno, strerror(errno));
        return -1;
    }

//    printf("opening file %s OK!\n", buffer);

    /* Input file and two output files are now open */
    /* Read input and put into output */
    file_size = 0;
    while((ret = read(rdHdl, &buffer[0], sizeof(buffer))) > 0) {
        wb = write(wr1Hdl, &buffer[0], ret);
//        printf("Copy to file: ret=%d len=%d\n", wb, ret);
        if (wb < 0) {
            printf("write error: Error %d:%s\n", errno, strerror(errno));
            break;
        }
        file_size += ret;
    }

    for (i=0;i<sizeof(buffer);i++) {
        buffer[i] = 0xff;
    }

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

        wb = write(wr1Hdl, &buffer[0], write_bytes);
//        printf("Write dummy to file: ret=%d len=%d\n", wb, write_bytes);
        if (wb < 0) {
            printf("write error: Error %d:%s\n", errno, strerror(errno));
            break;
        }
        file_size += write_bytes;
    }

//    printf("All done!!\n");
    close(rdHdl);
    close(wr1Hdl);
    // print success
//    printf("Exit!!\n");
    return 0;
}
