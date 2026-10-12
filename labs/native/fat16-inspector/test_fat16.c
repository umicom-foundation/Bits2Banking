#include "fat16.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(c) do{if(!(c)){fprintf(stderr,"FAIL line %d: %s\n",__LINE__,#c);return 1;}}while(0)
static void W16(uint8_t*p,unsigned v){p[0]=(uint8_t)v;p[1]=(uint8_t)(v>>8);}
/* 5000 sectors * 512 B = 2.56 MiB; 4977 clusters => FAT16. */
static void MakeImage(uint8_t *p,size_t n){
 memset(p,0,n);W16(p+11,512);p[13]=1;W16(p+14,1);p[16]=1;W16(p+17,32);
 W16(p+19,5000);p[21]=0xF8;W16(p+22,20);p[510]=0x55;p[511]=0xAA;
 /* two entries in a 20-sector FAT: cluster 2 -> 3 -> EOF */
 W16(p+512+2*2,3);W16(p+512+3*2,0xFFFF);
 size_t root=21U*512U;memcpy(p+root,"NOTES   TXT",11);p[root+11]=0x20;
}
int main(void){
 size_t n=5000U*512U;uint8_t *p=malloc(n);CHECK(p!=NULL);MakeImage(p,n);
 BtbFat16 f={0};CHECK(BtbFat16Open(p,n,&f)==BTB_FAT_OK);
 CHECK(f.dataClusters==4977U); /* 1 reserved + 20 FAT + 2 root = 23 */
 char names[2][13]={{0}};size_t count=0;
 CHECK(BtbFat16RootNames(p,n,&f,names,2,&count)==BTB_FAT_OK);
 CHECK(count==1 && strcmp(names[0],"NOTES.TXT")==0);
 uint16_t chain[8]={0};CHECK(BtbFat16Follow(p,n,&f,2,chain,8,&count)==BTB_FAT_OK);
 CHECK(count==2 && chain[0]==2 && chain[1]==3);
 W16(p+512+3*2,2);CHECK(BtbFat16Follow(p,n,&f,2,chain,8,&count)==BTB_FAT_CHAIN);
 W16(p+512+3*2,0xFFFF);
 p[510]=0;CHECK(BtbFat16Open(p,n,&f)==BTB_FAT_INVALID);p[510]=0x55;
 CHECK(BtbFat16Open(p,511,&f)==BTB_FAT_TRUNCATED);
 CHECK(BtbFat16Open(p,n-1,&f)==BTB_FAT_TRUNCATED);
 /* bounded mutations of the critical BPB geometry must never succeed as FAT16 */
 for(unsigned i=0;i<1000U;i++){uint8_t old=p[13];p[13]=(uint8_t)(3U+(i%200U));
  if(!((p[13]&(p[13]-1U))==0U && p[13]<=128U))CHECK(BtbFat16Open(p,n,&f)!=BTB_FAT_OK);
  p[13]=old;}
 FILE *out=fopen("fixture-fat16.img","wb");CHECK(out!=NULL);
 CHECK(fwrite(p,1,n,out)==n);CHECK(fclose(out)==0);
 free(p);puts("FAT16 parser: valid image, loop detection, bounds and 1000 mutations OK");return 0;
}
