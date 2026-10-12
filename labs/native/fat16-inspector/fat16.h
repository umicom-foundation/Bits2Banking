/* Bits2Banking — FAT16 read-only training inspector.
 * Author: Sammy Hegab / Umicom Foundation. Licence: MIT.
 * Input is a complete caller-owned byte span; inspection never mutates it. */
#ifndef BITS2BANKING_FAT16_H
#define BITS2BANKING_FAT16_H
#include <stddef.h>
#include <stdint.h>
typedef enum BtbFatStatus { BTB_FAT_OK=0, BTB_FAT_ARGUMENT, BTB_FAT_TRUNCATED,
 BTB_FAT_INVALID, BTB_FAT_UNSUPPORTED, BTB_FAT_RANGE, BTB_FAT_CHAIN } BtbFatStatus;
typedef struct BtbFat16 {
 uint16_t bytesPerSector, reservedSectors, rootEntries, sectorsPerFat;
 uint8_t sectorsPerCluster, fatCount;
 uint32_t totalSectors, dataClusters, fatStart, rootStart, dataStart;
} BtbFat16;
BtbFatStatus BtbFat16Open(const uint8_t *bytes,size_t length,BtbFat16 *out);
BtbFatStatus BtbFat16FatEntry(const uint8_t *bytes,size_t length,
 const BtbFat16 *fat,uint16_t cluster,uint16_t *entry);
BtbFatStatus BtbFat16RootNames(const uint8_t *bytes,size_t length,
 const BtbFat16 *fat,char names[][13],size_t capacity,size_t *count);
BtbFatStatus BtbFat16Follow(const uint8_t *bytes,size_t length,
 const BtbFat16 *fat,uint16_t first,uint16_t *result,size_t capacity,size_t *count);
const char *BtbFat16StatusName(BtbFatStatus status);
#endif
