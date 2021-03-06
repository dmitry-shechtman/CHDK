/*
 * movie_rec.c - auto-generated by CHDK code_gen.
 */
#include "conf.h"

void change_video_tables(int a, int b){
}

void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

/*************************************************************/
//** movie_record_task @ 0xFF986690 - 0xFF9867F0, length=89
void __attribute__((naked,noinline)) movie_record_task() {
asm volatile (
"    STMFD   SP!, {R2-R10,LR} \n"
"    LDR     R9, =0x2710 \n"
"    LDR     R7, =0xFF98582C \n"
"    LDR     R4, =0x7898 \n"
"    MOV     R8, #1 \n"
"    LDR     R6, =0xFF98607C \n"
"    MOV     R5, #0 \n"

"loc_FF9866AC:\n"
"    LDR     R0, [R4, #0x24] \n"
"    MOV     R2, #0 \n"
"    ADD     R1, SP, #4 \n"
"    BL      sub_FF83AE20 /*_ReceiveMessageQueue*/ \n"
"    LDR     R0, [R4, #0x2C] \n"
"    CMP     R0, #0 \n"
"    LDRNE   R0, [R4, #0xC] \n"
"    CMPNE   R0, #2 \n"
"    LDRNE   R0, [R4, #0x44] \n"
"    CMPNE   R0, #6 \n"
"    BNE     loc_FF9867D0 \n"
"    LDR     R0, [SP, #4] \n"
"    LDR     R1, [R0] \n"
"    SUB     R1, R1, #2 \n"
"    CMP     R1, #0xA \n"
"    ADDLS   PC, PC, R1, LSL#2 \n"
"    B       loc_FF9867D0 \n"
"    B       loc_FF986780 \n"
"    B       loc_FF9867A4 \n"
"    B       loc_FF9867B4 \n"
"    B       loc_FF9867BC \n"
"    B       loc_FF986788 \n"
"    B       loc_FF9867C4 \n"
"    B       loc_FF986794 \n"
"    B       loc_FF9867D0 \n"
"    B       loc_FF9867CC \n"
"    B       loc_FF98674C \n"
"    B       loc_FF98671C \n"

"loc_FF98671C:\n"
"    STR     R5, [R4, #0x40] \n"
"    STR     R5, [R4, #0x30] \n"
"    STR     R5, [R4, #0x34] \n"
"    STRH    R5, [R4, #6] \n"
"    STR     R6, [R4, #0xCC] \n"
"    STR     R7, [R4, #0xB4] \n"
"    LDR     R0, [R4, #0xC] \n"
"    ADD     R0, R0, #1 \n"
"    STR     R0, [R4, #0xC] \n"
"    MOV     R0, #6 \n"
"    STR     R0, [R4, #0x44] \n"
"    B       loc_FF98676C \n"

"loc_FF98674C:\n"
"    STR     R5, [R4, #0x40] \n"
"    STR     R5, [R4, #0x30] \n"
"    STR     R6, [R4, #0xCC] \n"
"    STR     R7, [R4, #0xB4] \n"
"    LDR     R0, [R4, #0xC] \n"
"    ADD     R0, R0, #1 \n"
"    STR     R0, [R4, #0xC] \n"
"    STR     R8, [R4, #0x44] \n"

"loc_FF98676C:\n"
"    LDR     R2, =0xFF985008 \n"
"    LDR     R1, =0xB0300 \n"
"    LDR     R0, =0xFF98511C \n"
"    BL      sub_FF8530AC \n"
"    B       loc_FF9867D0 \n"

"loc_FF986780:\n"
"    BL      sub_FF985D58 \n"
"    B       loc_FF9867D0 \n"

"loc_FF986788:\n"

"    LDR     R0, =video_compression_rate\n" //added
"    BL      set_quality\n"                 //added

"    LDR     R1, [R4, #0xCC] \n"
"    BLX     R1 \n"
"    B       loc_FF9867D0 \n"

"loc_FF986794:\n"
"    LDR     R1, [R0, #0x18] \n"
"    LDR     R0, [R0, #4] \n"
"    BL      sub_FFAD9B70 \n"
"    B       loc_FF9867D0 \n"

"loc_FF9867A4:\n"
"    LDR     R0, [R4, #0x44] \n"
"    CMP     R0, #5 \n"
"    STRNE   R8, [R4, #0x34] \n"
"    B       loc_FF9867D0 \n"

"loc_FF9867B4:\n"
"    BL      sub_FF9854D8 \n"
"    B       loc_FF9867D0 \n"

"loc_FF9867BC:\n"
"    BL      sub_FF985168 \n"
"    B       loc_FF9867D0 \n"

"loc_FF9867C4:\n"
"    BL      sub_FF984F94 \n"
"    B       loc_FF9867D0 \n"

"loc_FF9867CC:\n"
"    BL      sub_FF986BC4 \n"

"loc_FF9867D0:\n"
"    LDR     R1, [SP, #4] \n"
"    MOV     R3, #0x5F0 \n"
"    STR     R5, [R1] \n"
"    STR     R3, [SP] \n"
"    LDR     R0, [R4, #0x28] \n"
"    LDR     R3, =0xFF984C60 /*'MovieRecorder.c'*/ \n"
"    MOV     R2, R9 \n"
"    BL      sub_FF83B774 /*_PostMessageQueueStrictly*/ \n"
"    B       loc_FF9866AC \n"
);
}
