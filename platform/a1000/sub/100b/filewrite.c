/*
 * filewrite.c - auto-generated by CHDK code_gen.
 */
#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 4 // filewritetask is prepared for this many chunks
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * pdc is always required
 * name is not currently used
 */
typedef struct
{
    int unkn1[5];
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    int unkn6;
    char name[32];                               // open stage: sub_FFDE69C0 (1.00f) --> "ADD     R0, R0, #0x38"
                                                 // offset of 'name' from start = 0x38 = 56 bytes = 14 words
} fwt_data_struct;

#include "../../../generic/filewrite.c"

/*************************************************************/
//** filewritetask @ 0xFFDD8BD4 - 0xFFDD8CB4, length=57
void __attribute__((naked,noinline)) filewritetask() {
asm volatile (
"    STMFD   SP!, {R1-R5,LR} \n"
"    LDR     R4, =0xAF50 \n"

"loc_FFDD8BDC:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #8 \n"
"    BL      sub_FFC1693C /*_ReceiveMessageQueue*/ \n"
"    CMP     R0, #0 \n"
"    BNE     loc_FFDD8C0C \n"
"    LDR     R0, [SP, #8] \n"
"    LDR     R1, [R0] \n"
"    CMP     R1, #1 \n"
"    BNE     loc_FFDD8C14 \n"
"    LDR     R0, [R4, #8] \n"
"    BL      _GiveSemaphore \n"

"loc_FFDD8C0C:\n"
"    BL      _ExitTask \n"
"    LDMFD   SP!, {R1-R5,PC} \n"

"loc_FFDD8C14:\n"
"    SUB     R1, R1, #2 \n"
"    CMP     R1, #5 \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FFDD8BDC \n"
"    B       loc_FFDD8C3C \n"
"    B       loc_FFDD8CA0 \n"
"    B       loc_FFDD8CA8 \n"
"    B       loc_FFDD8CA8 \n"
"    B       loc_FFDD8CA8 \n"
"    B       loc_FFDD8CB0 \n"

"loc_FFDD8C3C:\n"
"    MOV     R0, #0 \n"
"    STR     R0, [SP] \n"

"loc_FFDD8C44:\n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R1, SP \n"
"    BL      sub_FFC16B80 /*_GetNumberOfPostedMessages*/ \n"
"    LDR     R0, [SP] \n"
"    CMP     R0, #0 \n"
"    BEQ     loc_FFDD8C70 \n"
"    LDR     R0, [R4, #0x10] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FFC1693C /*_ReceiveMessageQueue*/ \n"
"    B       loc_FFDD8C44 \n"

"loc_FFDD8C70:\n"
"    LDR     R0, [R4] \n"
"    CMN     R0, #1 \n"
"    BEQ     loc_FFDD8C94 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    MVN     R0, #0 \n"
"    STR     R0, [R4] \n"
"    LDR     R0, =0xAA018 \n"
"    BL      sub_FFC400E4 \n"
"    BL      sub_FFC3E78C \n"

"loc_FFDD8C94:\n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      _GiveSemaphore \n"
"    B       loc_FFDD8BDC \n"

"loc_FFDD8CA0:\n"
"    BL      sub_FFDD8E74_my \n"  // --> Patched. Old value = 0xFFDD8E74. Open stage
"    B       loc_FFDD8BDC \n"

"loc_FFDD8CA8:\n"
"    BL      sub_FFDD8FB0_my \n"  // --> Patched. Old value = 0xFFDD8FB0. Write stage
"    B       loc_FFDD8BDC \n"

"loc_FFDD8CB0:\n"
"    BL      sub_FFDD90AC_my \n"  // --> Patched. Old value = 0xFFDD90AC. Close stage
"    B       loc_FFDD8BDC \n"
);
}

/*************************************************************/
//** sub_FFDD8E74_my @ 0xFFDD8E74 - 0xFFDD8EB4, length=17
void __attribute__((naked,noinline)) sub_FFDD8E74_my() {
asm volatile (
"    STMFD   SP!, {R4-R8,LR} \n"
"    MOV     R4, R0 \n"
"    ADD     R0, R0, #0x2C \n"
"    SUB     SP, SP, #0x38 \n"
"    BL      sub_FFC400E4 \n"
"    MOV     R1, #0 \n"
"    BL      sub_FFC3E73C \n"
"    LDR     R0, [R4, #0xC] \n"
"    BL      sub_FFC3CA4C \n"
"    LDR     R7, [R4, #8] \n"
"    LDR     R8, =0x1B6 \n"
"    ADD     R6, R4, #0x2C \n"
"    LDR     R5, [R4, #0xC] \n"
//hook start
"    STMFD SP!, {R4-R12,LR}\n"
"    MOV R0, R4\n"
"    BL filewrite_main_hook\n"
"    LDMFD SP!, {R4-R12,LR}\n"
//hook end
"    MOV     R0, R6 \n"
"    MOV     R1, R7 \n"
"    MOV     R2, R8 \n"
"    BL      fwt_open \n"  // --> Patched. Old value = _Open.
"    LDR     PC, =0xFFDD8EB8 \n"  // Continue in firmware
);
}

/*************************************************************/
//** sub_FFDD8FB0_my @ 0xFFDD8FB0 - 0xFFDD90A8, length=63
void __attribute__((naked,noinline)) sub_FFDD8FB0_my() {
asm volatile (
"    STMFD   SP!, {R4-R10,LR} \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R0] \n"
"    CMP     R0, #4 \n"
"    LDREQ   R6, [R4, #0x18] \n"
"    LDREQ   R7, [R4, #0x14] \n"
"    BEQ     loc_FFDD8FEC \n"
"    CMP     R0, #5 \n"
"    LDREQ   R6, [R4, #0x20] \n"
"    LDREQ   R7, [R4, #0x1C] \n"
"    BEQ     loc_FFDD8FEC \n"
"    CMP     R0, #6 \n"
"    BNE     loc_FFDD9000 \n"
"    LDR     R6, [R4, #0x28] \n"
"    LDR     R7, [R4, #0x24] \n"

"loc_FFDD8FEC:\n"
"    CMP     R6, #0 \n"
"    BNE     loc_FFDD9010 \n"

"loc_FFDD8FF4:\n"
"    MOV     R1, R4 \n"
"    MOV     R0, #7 \n"
"    B       loc_FFDD90A4 \n"

"loc_FFDD9000:\n"
"    LDR     R1, =0x205 \n"
"    LDR     R0, =0xFFDD8F90 \n"
"    BL      _DebugAssert \n"
"    B       loc_FFDD8FF4 \n"

"loc_FFDD9010:\n"
"    LDR     R9, =0xAF50 \n"
"    MOV     R5, R6 \n"

"loc_FFDD9018:\n"
"    LDR     R0, [R4, #4] \n"
"    CMP     R5, #0x1000000 \n"
"    MOVLS   R8, R5 \n"
"    MOVHI   R8, #0x1000000 \n"
"    BIC     R1, R0, #0xFF000000 \n"
"    CMP     R1, #0 \n"
"    BICNE   R0, R0, #0xFF000000 \n"
"    RSBNE   R0, R0, #0x1000000 \n"
"    CMPNE   R8, R0 \n"
"    MOVHI   R8, R0 \n"
"    LDR     R0, [R9] \n"
"    MOV     R2, R8 \n"
"    MOV     R1, R7 \n"
"    BL      fwt_write \n"  // --> Patched. Old value = _Write.
"    LDR     R1, [R4, #4] \n"
"    CMP     R8, R0 \n"
"    ADD     R1, R1, R0 \n"
"    STR     R1, [R4, #4] \n"
"    BEQ     loc_FFDD9078 \n"
"    LDR     R0, =0x10B1 \n"
"    BL      sub_FFC5CADC /*_IsControlEventActive_FW*/ \n"
"    LDR     R1, =0x9200005 \n"
"    STR     R1, [R4, #0x10] \n"
"    B       loc_FFDD8FF4 \n"

"loc_FFDD9078:\n"
"    SUB     R5, R5, R0 \n"
"    CMP     R5, R6 \n"
"    ADD     R7, R7, R0 \n"
"    LDRCS   R0, =0xFFDD8F90 \n"
"    MOVCS   R1, #0x234 \n"
"    BLCS    _DebugAssert \n"
"    CMP     R5, #0 \n"
"    BNE     loc_FFDD9018 \n"
"    LDR     R0, [R4] \n"
"    MOV     R1, R4 \n"
"    ADD     R0, R0, #1 \n"

"loc_FFDD90A4:\n"
"    LDMFD   SP!, {R4-R10,LR} \n"
"    B       sub_FFDD8B2C \n"
);
}

/*************************************************************/
//** sub_FFDD90AC_my @ 0xFFDD90AC - 0xFFDD90C8, length=8
void __attribute__((naked,noinline)) sub_FFDD90AC_my() {
asm volatile (
"    STMFD   SP!, {R4,R5,LR} \n"
"    LDR     R5, =0xAF50 \n"
"    MOV     R4, R0 \n"
"    LDR     R0, [R5] \n"
"    SUB     SP, SP, #0x1C \n"
"    CMN     R0, #1 \n"
"    BEQ     sub_FFDD90E0 \n"
"    BL      fwt_close \n"  // --> Patched. Old value = _Close.
"    LDR     PC, =0xFFDD90CC \n"  // Continue in firmware
);
}
