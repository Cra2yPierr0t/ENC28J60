#include<stdio.h>
#include<stdint.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    uint8_t *line_buffer = (uint8_t *)malloc(1024*sizeof(uint8_t));
    uint16_t instr = 0;
    uint16_t cnt = 0;

    uint8_t *head = line_buffer;

    if((fp = fopen(argv[1], "r")) == NULL){
        exit(1);
    }

    while(fgets(line_buffer, 1024, fp) != NULL){
        while(*line_buffer){
            if(isspace(*line_buffer)){
                line_buffer++;
            } else if(strncmp(line_buffer, "SRC", 3) == 0){
                instr |= 0xff << 8;
                printf("%x:%8x;\n", cnt, instr);
                cnt++;
                instr = 0;
                line_buffer = head;
                break;
            } else if(strncmp(line_buffer, "RCR", 3) == 0){
                instr |= 0x00 << 13;
                line_buffer += 3;
            } else if(strncmp(line_buffer, "WBM", 3) == 0){
                instr |= 0x7a << 8;
                line_buffer += 3;
            } else if(strncmp(line_buffer, "RBM", 3) == 0){
                instr |= 0x01 << 13;
                line_buffer += 3;
            } else if(strncmp(line_buffer, "WCR", 3) == 0){
                instr |= 0x02 << 13;
                line_buffer += 3;
            } else if(strncmp(line_buffer, "ERDPTL", 6) == 0){
                instr |= 0x00 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ERDPTH", 6) == 0){
                instr |= 0x01 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ETXSTL", 6) == 0){
                instr |= 0x04 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ETXSTH", 6) == 0){
                instr |= 0x05 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ETXNDL", 6) == 0){
                instr |= 0x06 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ETXNDH", 6) == 0){
                instr |= 0x07 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ERXSTL", 6) == 0){
                instr |= 0x08 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ERXSTH", 6) == 0){
                instr |= 0x09 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ERXNDL", 6) == 0){
                instr |= 0x0a << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ERXNDH", 6) == 0){
                instr |= 0x0b << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "ERXRDPTL", 8) == 0){
                instr |= 0x0c << 8;
                line_buffer += 8;
            } else if(strncmp(line_buffer, "ERXRDPTL", 8) == 0){
                instr |= 0x0d << 8;
                line_buffer += 8;
            } else if(strncmp(line_buffer, "ECON1", 5) == 0){
                instr |= 0x1f << 8;
                line_buffer += 5;
            } else if(strncmp(line_buffer, "EWRPTL", 6) == 0){
                instr |= 0x02 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "EWRPTH", 6) == 0){
                instr |= 0x03 << 8;
                line_buffer += 6;
            } else if(strncmp(line_buffer, "EIR", 3) == 0){
                instr |= 0x1c << 8;
                line_buffer += 3;
            } else if(strncmp(line_buffer, "EIE", 3) == 0){
                instr |= 0x1b << 8;
                line_buffer += 3;
            } else if(strncmp(line_buffer, "'", 1) == 0){
                line_buffer += 1;
                instr |= *line_buffer;
                line_buffer += 1;
                if(strncmp(line_buffer, "'", 1) != 0){
                    exit(1);
                }
                printf("%x: %8x;\n", cnt, instr);
                cnt++;
                instr = 0;
                line_buffer = head;
                break;
            } else if(strncmp(line_buffer, "0", 1) == 0){
                instr |= strtol(line_buffer, NULL, 0);
                printf("%x: %8x;\n", cnt, instr);
                cnt++;
                instr = 0;
                line_buffer = head;
                break;
            } else {
                exit(1);
            }
        }
    }


    free(line_buffer);
    fclose(fp);
    return 0;
}
