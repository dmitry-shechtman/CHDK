#ifndef PLATFORM_KBD_H
#define PLATFORM_KBD_H
// plaform specific keyboard defines, see core/kbd_common.c for documentation

#define KEYS_MASK0 (0x00002000) //Logic OR of group 0 Keymap values
#define KEYS_MASK1 (0x00000000) //Logic OR of group 1 Keymap values
#define KEYS_MASK2 (0x0000F0FF) //Logic OR of group 2 Keymap values

#define SD_READONLY_FLAG    0x00020000 // Found @0xffb5d574, levent 0x90a
#define SD_READONLY_IDX     2

#define USB_MASK            0x04000000 // Found @0xffb5d594, levent 0x902
#define USB_IDX 2

#endif
