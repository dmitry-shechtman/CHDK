#ifndef PLATFORM_KBD_H
#define PLATFORM_KBD_H
// plaform specific keyboard defines, see core/kbd_common.c for documentation

#define KEYS_MASK0 (0x0000000F)
#define KEYS_MASK1 (0x00084800)
#define KEYS_MASK2 (0x00007041)

#define SD_READONLY_FLAG (0x20000)
#define SD_READONLY_IDX 2

#define USB_MASK (0x80000)
#define USB_IDX  2
#endif
