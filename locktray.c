#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* ioctl() */
#include <stropts.h>
/* open() */
#include <sys/stat.h>
#include <fcntl.h>
/* close() */
#include <unistd.h>
/* ioctl flags */
#include <linux/cdrom.h>

/* NOTE: ioctl arguments and flags are documented in the linux kernel documentation cdrom.txt */

#define DEVICE  "/dev/cdrom"

int main(int argc, char *argv[])
{
    int fd;
    int retval = 0; /* return value */
    char mode = 0; /* default to unlock */

    /* argument parsing */
    if(argc < 2) {
        printf("usage: %s lock   - to lock the cd tray.\n",argv[0]);
        printf("       %s unlock - to unlock the cd tray\n", argv[0]);
        exit(1);
    }

    else {
        if((strcmp(argv[1], "lock")) == 0) {
            mode = 1;
        }

        if((strcmp(argv[1], "unlock")) == 0) {
            mode = 0;
        }
    }

    /* open device file */
    fd = open(DEVICE, O_RDWR|O_NONBLOCK);
    if(fd < 0) {
        fprintf(stderr, "could not open device file. :<\n");
        exit(1);
    }

    /* lock / unlock cd tray */
    if(ioctl(fd, CDROM_LOCKDOOR, mode) == -1) {
        fprintf(stderr, "*ouch*. ioctl error.\n");
    }

    else {
        switch(mode) {
            case 0:
                fprintf(stdout, "[\E[1;34mi\E[0m] cd tray \E[32munlocked\E[0m.\n");
                retval = 85; /* decimal 'L' */
                break;
            case 1:
                fprintf(stdout, "[\E[1;34mi\E[0m] cd tray \E[31mlocked\E[0m.\n");
                retval = 117; /* decimal 'u' */
                break;
            default:
                /* should never happen either */
                fprintf(stdout, "error. unknown mode\n");
                break;
        }
    }

    if(close(fd) == -1) {
        fprintf(stderr, "could not close device file.\n");
    }

    return(retval);
}

