#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 4096

void usage()
{
    printf("shmtest [--token=TOKEN] [--read=IDX] [--write=IDX]\n");
}

int main(int argc, char *argv[])
{
    int c;
    int read_idx = -1;
    int write_idx = -1;
    const char *token = NULL;
    while (1) {
        static struct option long_options[] = {
            {"token", required_argument, 0, 't'},
            {"read",  required_argument, 0, 'r'},
            {"write", required_argument, 0, 'w'},
            {0, 0, 0, 0}
        };

        int option_index = 0;

        c = getopt_long (argc, argv, "r:w:", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)
            break;

        switch (c) {
          case 0:
            break;

          case 't':
            token = optarg;
            break;

          case 'r':
            read_idx = atoi(optarg);
            break;

          case 'w':
            write_idx = atoi(optarg);
            break;

          default:
            abort ();
          }
    }

    key_t key;
    int shmid;
    char *data;

    /* make the key: */
    if ((key = ftok(token, 't')) == -1) {
        perror("ftok");
        exit(1);
    }

    /*  create the segment: */
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    /* attach to the segment to get a pointer to it: */
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    if (read_idx != -1) {
        char value = data[read_idx];
        printf("read at u=idx: 0x%hhX\n", value);
    }

    if (write_idx != -1) {
        printf("write at u=idx: 0xFF\n");
        data[write_idx] = 0xFF;
    }
    /* detach from the segment: */
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
