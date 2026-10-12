/* Bits2Banking — bounded FAT16 learning parser (read only).
 * Author: Sammy Hegab / Umicom Foundation. Licence: MIT. */
#include "fat16.h"
#include <string.h>
#include <limits.h>
static uint16_t Le16(const uint8_t *p){return (uint16_t)((unsigned)p[0]|((unsigned)p[1]<<8));}
static uint32_t Le32(const uint8_t *p){return (uint32_t)p[0]|((uint32_t)p[1]<<8)|((uint32_t)p[2]<<16)|((uint32_t)p[3]<<24);}
static int Span(size_t total,uint64_t start,uint64_t count){return start<=total && count<=total-start;}
static int PowerOfTwo(unsigned n){return n!=0U && (n&(n-1U))==0U;}
BtbFatStatus BtbFat16Open(const uint8_t *bytes,size_t length,BtbFat16 *out){
 if(!bytes||!out)return BTB_FAT_ARGUMENT;
 if(length<512U)return BTB_FAT_TRUNCATED;
 if(bytes[510]!=0x55U||bytes[511]!=0xAAU)return BTB_FAT_INVALID;
 BtbFat16 x={0};
 x.bytesPerSector=Le16(bytes+11);x.sectorsPerCluster=bytes[13];
 x.reservedSectors=Le16(bytes+14);x.fatCount=bytes[16];
 x.rootEntries=Le16(bytes+17);x.sectorsPerFat=Le16(bytes+22);
 const uint16_t s16=Le16(bytes+19);
 x.totalSectors=s16?s16:Le32(bytes+32);
 if((x.bytesPerSector!=512U&&x.bytesPerSector!=1024U&&x.bytesPerSector!=2048U&&x.bytesPerSector!=4096U)
  ||!PowerOfTwo(x.sectorsPerCluster)||x.sectorsPerCluster>128U||!x.reservedSectors
  ||!x.fatCount||x.fatCount>2U||!x.rootEntries||!x.sectorsPerFat||!x.totalSectors)
  return BTB_FAT_INVALID;
 const uint64_t rootSectors=((uint64_t)x.rootEntries*32U+x.bytesPerSector-1U)/x.bytesPerSector;
 const uint64_t fatStart=x.reservedSectors;
 const uint64_t rootStart=fatStart+(uint64_t)x.fatCount*x.sectorsPerFat;
 const uint64_t dataStart=rootStart+rootSectors;
 if(dataStart>=x.totalSectors)return BTB_FAT_INVALID;
 uint64_t clusters=((uint64_t)x.totalSectors-dataStart)/x.sectorsPerCluster;
 /* FAT16's classification is determined by actual cluster count, not its text label. */
 if(clusters<4085U||clusters>=65525U)return BTB_FAT_UNSUPPORTED;
 if(clusters+2U>((uint64_t)x.sectorsPerFat*x.bytesPerSector)/2U)return BTB_FAT_INVALID;
 if(!Span(length,0,(uint64_t)x.totalSectors*x.bytesPerSector))return BTB_FAT_TRUNCATED;
 if(rootStart>UINT32_MAX||dataStart>UINT32_MAX)return BTB_FAT_RANGE;
 x.dataClusters=(uint32_t)clusters;x.fatStart=(uint32_t)fatStart;
 x.rootStart=(uint32_t)rootStart;x.dataStart=(uint32_t)dataStart;
 *out=x;return BTB_FAT_OK;
}
BtbFatStatus BtbFat16FatEntry(const uint8_t *bytes,size_t length,const BtbFat16 *fat,uint16_t cluster,uint16_t *entry){
 if(!bytes||!fat||!entry)return BTB_FAT_ARGUMENT;
 if(cluster<2U || (uint32_t)cluster>=fat->dataClusters+2U)return BTB_FAT_RANGE;
 uint64_t offset=(uint64_t)fat->fatStart*fat->bytesPerSector+(uint64_t)cluster*2U;
 if(!Span(length,offset,2U))return BTB_FAT_TRUNCATED;
 uint16_t decoded=Le16(bytes+(size_t)offset);
 *entry=decoded;return BTB_FAT_OK;
}
BtbFatStatus BtbFat16RootNames(const uint8_t *bytes,size_t length,const BtbFat16 *fat,
 char names[][13],size_t capacity,size_t *count){
 if(!bytes||!fat||!count||(capacity&& !names))return BTB_FAT_ARGUMENT;
 uint64_t base=(uint64_t)fat->rootStart*fat->bytesPerSector;
 if(!Span(length,base,(uint64_t)fat->rootEntries*32U))return BTB_FAT_TRUNCATED;
 size_t used=0U;
 for(uint32_t i=0;i<fat->rootEntries;i++){
  const uint8_t *e=bytes+(size_t)base+(size_t)i*32U;
  if(e[0]==0U)break;
  if(e[0]==0xE5U || e[11]==0x0FU || (e[11]&0x08U))continue;
  if(used>=capacity)return BTB_FAT_RANGE;
  char temp[13];size_t at=0;
  for(size_t j=0;j<8U;j++)if(e[j]!=' ')temp[at++]=(char)e[j];
  if(e[8]!=' '){temp[at++]='.';for(size_t j=8;j<11U;j++)if(e[j]!=' ')temp[at++]=(char)e[j];}
  temp[at]='\0';memcpy(names[used],temp,at+1U);used++;
 }
 *count=used;return BTB_FAT_OK;
}
BtbFatStatus BtbFat16Follow(const uint8_t *bytes,size_t length,const BtbFat16 *fat,
 uint16_t first,uint16_t *result,size_t capacity,size_t *count){
 if(!bytes||!fat||!count||(capacity&&!result))return BTB_FAT_ARGUMENT;
 if(first<2U||(uint32_t)first>=fat->dataClusters+2U)return BTB_FAT_RANGE;
 /* A loop is rejected by checking previous positions; no malloc and no out-of-bounds reads. */
 size_t n=0U;uint16_t current=first;
 for(;;){
  if(n>=capacity)return BTB_FAT_RANGE;
  for(size_t i=0;i<n;i++)if(result[i]==current)return BTB_FAT_CHAIN;
  result[n++]=current;
  uint16_t next=0;BtbFatStatus s=BtbFat16FatEntry(bytes,length,fat,current,&next);
  if(s!=BTB_FAT_OK)return s;
  if(next>=0xFFF8U){*count=n;return BTB_FAT_OK;}
  if(next<2U || next==0xFFF7U || (uint32_t)next>=fat->dataClusters+2U)return BTB_FAT_CHAIN;
  current=next;
 }
}
const char *BtbFat16StatusName(BtbFatStatus s){
 switch(s){case BTB_FAT_OK:return "OK";case BTB_FAT_ARGUMENT:return "invalid argument";
 case BTB_FAT_TRUNCATED:return "truncated image";case BTB_FAT_INVALID:return "invalid FAT metadata";
 case BTB_FAT_UNSUPPORTED:return "not FAT16";case BTB_FAT_RANGE:return "capacity or range";
 case BTB_FAT_CHAIN:return "invalid FAT chain";default:return "unknown";}
}
