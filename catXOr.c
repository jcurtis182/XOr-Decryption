#include <stdio.h>
#include <stdlib.h>

#define STEPCOUNT 128
long getFileSizeREAL(FILE*);

int main(int argc, char** argv){
    FILE* input = NULL;
    FILE* output = stdout;

    if(argc < 2){
        printf("[*] USAGE: $ %s src_file\n", argv[0]);
        return 0;
    }

    if((input = fopen(argv[1], "r")) == NULL){
        printf("[!] Error Opening File\n");
        return -1;
    }

    int numRead, numWrite;
    char* buf = (char *) malloc(sizeof(char) * (STEPCOUNT + 1));

    do {
        numRead = fread(buf, sizeof(char), STEPCOUNT, input);
        XORBuf(buf);
        numWrite = fwrite(buf, sizeof(char), STEPCOUNT, output);

        if(numWrite < numRead){
            printf("[!] Error writing file\n");
            return -1;
        }
    } while (numRead == STEPCOUNT);
    
    long size = getFileSizeREAL(input);
    printf("File size = %ld bytes.\n", size);

    fclose(input);
    return 0;
}

long getFileSizeREAL(FILE* fp){
    long pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    fseek(fp, pos, SEEK_SET);
    return end;
}

void XORBuf(char* buf){
    int key = 157;                              //given
    for(int i=0; i < STEPCOUNT; i++){
        buf[i] = buf[i] ^ key;
    }
}