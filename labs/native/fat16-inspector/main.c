/* Read-only FAT16 image inspector. Never writes the supplied path.
 * Author: Sammy Hegab / Umicom Foundation. Licence: MIT. */
#include "fat16.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char **argv){
 if(argc!=2){fputs("Usage: btb-fat16-inspect IMAGE\n",stderr);return 2;}
 FILE *f=fopen(argv[1],"rb");if(!f){perror("open image");return 1;}
 if(fseek(f,0,SEEK_END)!=0){fclose(f);return 1;}
 long n=ftell(f);if(n<0||n>32L*1024L*1024L){fputs("Image exceeds 32 MiB training limit\n",stderr);fclose(f);return 1;}
 rewind(f);uint8_t *bytes=malloc(n>0?(size_t)n:1U);if(!bytes){fclose(f);return 1;}
 size_t got=fread(bytes,1,(size_t)n,f);int extra=fgetc(f);int ok=ferror(f)==0 && got==(size_t)n && extra==EOF;
 fclose(f);if(!ok){free(bytes);return 1;}
 BtbFat16 fat;BtbFatStatus status=BtbFat16Open(bytes,got,&fat);
 if(status!=BTB_FAT_OK){fprintf(stderr,"FAT16 inspection refused: %s\n",BtbFat16StatusName(status));free(bytes);return 1;}
 printf("FAT16: %u bytes/sector; %u sectors/cluster; %u clusters\n",fat.bytesPerSector,fat.sectorsPerCluster,fat.dataClusters);
 printf("FAT sector: %u; root sector: %u; data sector: %u\n",fat.fatStart,fat.rootStart,fat.dataStart);
 char names[128][13];size_t count=0;status=BtbFat16RootNames(bytes,got,&fat,names,128,&count);
 if(status!=BTB_FAT_OK){fprintf(stderr,"Cannot read root directory: %s\n",BtbFat16StatusName(status));free(bytes);return 1;}
 printf("Root entries shown: %zu\n",count);for(size_t i=0;i<count;i++)printf("  %s\n",names[i]);
 free(bytes);return 0;
}
