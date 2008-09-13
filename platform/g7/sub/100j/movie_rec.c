#include "conf.h"

int *video_quality = &conf.video_quality;
int *video_mode    = &conf.video_mode;

long def_table1[12]={0x2000,0x38D,0x788,0x5800,0x9C5,0x14B8,0x10000,0x1C6A,0x3C45,0x20000,0x387A,0x7813};

long def_table2[12]={0x1CCD,-0x2E1,-0x579,0x4F33,-0x7EB,-0xF0C,0xE666,-0x170A,-0x2BC6,0x1CC39,-0x2F5B,-0x59F0};

long table1[12], table2[12];

void change_video_tables(int a, int b){
 int i;
 for (i=0;i<12;i++) {table1[i]=(def_table1[i]*a)/b; table2[i]=(def_table2[i]*a)/b;}
}

long CompressionRateTable[]={0x60, 0x5D, 0x5A, 0x57, 0x54, 0x51, 0x4D, 0x48, 0x42, 0x3B, 0x32, 0x29, 0x22, 0x1D, 0x17, 0x14, 0x10, 0xE, 0xB, 9, 7, 6, 5, 4, 3, 2, 1};


void __attribute__((naked,noinline)) movie_record_task(){
 asm volatile(
                "STMFD   SP!, {R4,R5,LR}\n" 
                "SUB     SP, SP, #4\n"      
                "MOV     R5, SP\n"          
                "MOV     R4, #0\n"          
"loc_FF9907AC:\n"                           
                "LDR     R3, =0x770FC\n"    
                "MOV     R2, #0\n"          
                "LDR     R0, [R3]\n"        
                "MOV     R1, R5\n"          
                "BL      sub_FF8213F8\n" 
                "LDR     R3, =0x771D0\n"    
                "LDR     R2, [R3]\n"        
                "CMP     R2, #0\n"          
                "BNE     loc_FF990858\n"    
                "LDR     R1, [SP]\n"        
                "LDR     R3, [R1]\n"        
                "SUB     R3, R3, #2\n"      
                "MOV     R0, R1\n"          
                "CMP     R3, #9\n"          
                "LDRLS   PC, [PC,R3,LSL#2]\n" 
                "B       loc_FF99085C\n"    
                ".long loc_FF99081C\n"
                ".long loc_FF990834\n"
                ".long loc_FF99083C\n"
                ".long loc_FF990844\n"
                ".long loc_FF990824\n"
                ".long loc_FF99084C\n"
                ".long loc_FF99082C\n"
                ".long loc_FF99085C\n"
                ".long loc_FF990854\n"
                ".long loc_FF990814\n"
"loc_FF990814:\n"                           
                                        
                "BL      sub_FF9908C8\n"    
                "B       loc_FF990858\n"    
"loc_FF99081C:\n"                           

                "BL      unlock_optical_zoom\n"                        
                "BL      sub_FF990AAC\n"    
                "B       loc_FF990858\n"    
"loc_FF990824:\n"                           
                                        
                "BL      sub_FF990F74_my\n"   //--------------------> 
                "B       loc_FF990858\n"    
"loc_FF99082C:\n"                           
                                        
                "BL      sub_FF991660\n"    
                "B       loc_FF990858\n"    
"loc_FF990834:\n"                           
                                        
                "BL      sub_FF991244\n"    
                "B       loc_FF990858\n"    
"loc_FF99083C:\n"                           
                                        
                "BL      sub_FF9917FC\n"    
                "B       loc_FF990858\n"    
"loc_FF990844:\n"                           
                                        
                "BL      sub_FF991A2C\n"    
                "B       loc_FF990858\n"    
"loc_FF99084C:\n"                           
                                        
                "BL      sub_FF9916E8\n"    
                "B       loc_FF990858\n"    
"loc_FF990854:\n"                           
                                        
                "BL      sub_FF991294\n"    
"loc_FF990858:\n"                           
                                        
                "LDR     R1, [SP]\n"        
"loc_FF99085C:\n"                           
                                        
                "LDR     R3, =0x77100\n"    
                "STR     R4, [R1]\n"        
                "LDR     R0, [R3]\n"        
                "MOV     R2, R4\n"          
                "BL      sub_FF821810\n" 
                "B       loc_FF9907AC\n"    
 );
}


void __attribute__((naked,noinline)) sub_FF990F74_my(){
 asm volatile(
                "STMFD   SP!, {R4-R11,LR}\n" 
                "LDR     R5, =0x771E8\n"    
                "SUB     SP, SP, #0x34\n"   
                "LDR     R3, [R5]\n"        
                "MOV     R2, #0\n"          
                "CMP     R3, #3\n"          
                "STR     R2, [SP,#0x24]\n"  
                "MOV     R4, R0\n"          
                "STR     R2, [SP,#0x2C]\n"  
                "MOVEQ   R3, #4\n"          
                "STREQ   R3, [R5]\n"        
                "LDR     R3, =0x77284\n"    
                "MOV     LR, PC\n"          
                "LDR     PC, [R3]\n"        
                "LDR     R2, [R5]\n"        
                "CMP     R2, #4\n"          
                "BNE     loc_FF99116C\n"    
                "ADD     R0, SP, #0x30\n"   
                "ADD     R1, SP, #0x2C\n"   
                "ADD     R2, SP, #0x28\n"   
                "ADD     R3, SP, #0x24\n"   
                "BL      sub_FF992A98\n"    
                "CMP     R0, #0\n"         	 
                "BNE     loc_FF990FFC\n"    
                "LDR     R3, =0x771D8\n"    
                "LDR     R2, [R3]\n"        
                "CMP     R2, #1\n"          
                "BNE     loc_FF991010\n"    
                "LDR     R2, =0x77214\n"    
                "LDR     R1, =0x771EC\n"    
                "LDR     R12, [R2]\n"       
                "LDR     R3, [R1]\n"        
                "CMP     R12, R3\n"         
                "BCC     loc_FF991010\n"    
"loc_FF990FFC:\n"                           
                "BL      sub_FF9911BC\n"    
                "BL      sub_FF991620\n"    
                "MOV     R3, #5\n"          
                "STR     R3, [R5]\n"        
                "B       loc_FF99116C\n"    
"loc_FF991010:\n"                           
                                        
                "LDR     R8, [SP,#0x2C]\n"  
                "CMP     R8, #0\n"          
                "BEQ     loc_FF9910EC\n"    
                "LDR     R12, =0x7721C\n"   
                "LDR     R9, =0x77228\n"    
                "LDR     R11, =0x771DC\n"   
                "LDR     R7, [R12]\n"       
                "ADD     R5, SP, #0x24\n"   
                "LDMIA   R5, {R5,LR}\n"     
                "LDR     R6, [R9]\n"        
                "MOV     R10, #1\n"         
                "LDMIB   R4, {R0-R2}\n"     
                "LDR     R3, [SP,#0x30]\n"  
                "ADD     R12, SP, #0x20\n"  
                "STR     R10, [R11]\n"      
                "ADD     R4, SP, #0x1C\n"   
                "STMEA   SP, {R8,LR}\n"     
                "STR     R5, [SP,#8]\n"     
                "STR     R12, [SP,#0xC]\n"  
                "STR     R7, [SP,#0x10]\n"  
                "STR     R6, [SP,#0x14]\n"  
                "STR     R4, [SP,#0x18]\n"  
                "BL      sub_FF8A8CB0\n"    
                "LDR     R3, =0x770F4\n"    
                "MOV     R1, #0x3E8\n"      
                "LDR     R0, [R3]\n"        
                "BL      sub_FF821FA4\n"   
                "CMP     R0, #9\n"          
                "BNE     loc_FF991094\n"    
                "BL      sub_FF993328\n"    
                "LDR     R3, =0x771E8\n"    
                "LDR     R0, =0xFF990F5C\n" 
                "B       loc_FF9910AC\n"    
"loc_FF991094:\n"                           
                "LDR     R4, [SP,#0x1C]\n"  
                "CMP     R4, #0\n"          
                "BEQ     loc_FF9910B8\n"    
                "BL      sub_FF993328\n"    
                "LDR     R3, =0x771E8\n"    
                "LDR     R0, =0xFF990F68\n" 
"loc_FF9910AC:\n"                           
                "STR     R10, [R3]\n"       
                "BL      sub_FF9AD184\n"    
                "B       loc_FF99116C\n"    
"loc_FF9910B8:\n"                           
                "BL      sub_FF8A8E0C\n"    
                "LDR     R0, [SP,#0x30]\n"  
                "LDR     R1, [SP,#0x20]\n"  
                "BL      sub_FF992F80\n"    
                "LDR     R12, =0x77210\n"   
                "LDR     R3, [R12]\n"       
                "ADD     R3, R3, #1\n"      
                "LDR     R0, [SP,#0x20]\n"  
                "MOV     R1, R9\n"          
                "MOV     R2, R4\n"          
                "STR     R3, [R12]\n"       
                "BL      sub_FF991E24_my\n"   //-------------------> 
                "B       loc_FF9910F0\n"    
"loc_FF9910EC:\n"                           
                "LDR     R11, =0x771DC\n"   
"loc_FF9910F0:\n"                           
                "LDR     R4, =0x77214\n"    
                "LDR     R2, =0x77234\n"    
                "LDR     R3, [R4]\n"        
                "LDR     R1, [R2]\n"        
                "LDR     R12, =0x77230\n"   
                "ADD     R3, R3, #1\n"      
                "MUL     R0, R1, R3\n"      
                "LDR     R1, [R12]\n"       
                "STR     R3, [R4]\n"        
                "BL      sub_FFB928F4\n"       
                "LDR     R6, =0x7722C\n"    
                "MOV     R4, R0\n"          
                "BL      sub_FF993364\n"    
                "LDR     R3, [R6]\n"        
                "CMP     R3, R4\n"          
                "BNE     loc_FF991144\n"    
                "LDR     R5, =0x771E0\n"    
                "LDR     R3, [R5]\n"        
                "CMP     R3, #1\n"          
                "BNE     loc_FF991164\n"    
                "B       loc_FF991148\n"    
"loc_FF991144:\n"                           
                "LDR     R5, =0x771E0\n"    
"loc_FF991148:\n"                           
                "LDR     R2, =0x77268\n"    
                "MOV     R0, R4\n"          
                "MOV     LR, PC\n"          
                "LDR     PC, [R2]\n"        
                "MOV     R3, #0\n"          
                "STR     R3, [R5]\n"        
                "STR     R4, [R6]\n"        
"loc_FF991164:\n"                           
                "MOV     R3, #0\n"          
                "STR     R3, [R11]\n"       
"loc_FF99116C:\n"                           
                                        
                "ADD     SP, SP, #0x34\n"   
                "LDMFD   SP!, {R4-R11,PC}\n" 

 );
}

void __attribute__((naked,noinline)) sub_FF991E24_my(){
 asm volatile(
                "CMP     R2, #1\n"          
                "STMFD   SP!, {R4-R7,LR}\n" 
                "MOV     R7, R0\n"          
                "MOV     R6, R1\n"          
                "MOVEQ   R3, #0x79\n"       
                "STREQ   R3, [R6]\n"        
                "LDMEQFD SP!, {R4-R7,PC}\n" 
                "LDR     R12, =0x772C8\n"   
                "LDR     R0, [R12]\n"       
                "LDR     R3, =0x772D0\n"    
                "CMP     R0, #0\n"          
                "LDR     R1, [R3]\n"        
                "BEQ     loc_FF991E6C\n"    
                "LDR     R2, =0x772D4\n"    
                "LDR     R3, [R2]\n"        
                "CMP     R3, #1\n"          
                "BNE     loc_FF991E80\n"    
                "B       loc_FF991E70\n"    
"loc_FF991E6C:\n"                           
                "LDR     R2, =0x772D4\n"    
"loc_FF991E70:\n"                           
                "MOV     R3, #0\n"          
                "STR     R3, [R2]\n"        
                "STR     R7, [R12]\n"       
                "B       loc_FF991F38\n"    
"loc_FF991E80:\n"                           
                "LDR     R2, =0x772CC\n"    
                "LDR     R3, [R2]\n"        
                "LDR     R5, =table1\n"  // + 0xFF991C6C
                "ADD     R3, R3, R3,LSL#1\n" 
                "MOV     LR, R3,LSL#2\n"    
                "LDR     R2, [R5,LR]\n"     
                "LDR     R4, =table2\n"  // + 0xFF991C9C
                "RSB     R12, R2, R0\n"     
                "LDR     R3, [R4,LR]\n"     
                "CMP     R12, #0\n"         
                "RSB     R0, R3, R0\n"      
                "BLE     loc_FF991EE4\n"    
                "ADD     R3, R5, #4\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R12\n"         
                "ADDGE   R1, R1, #1\n"      
                "BGE     loc_FF991ED8\n"    
                "ADD     R3, R5, #8\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R12\n"         
                "ADDGE   R1, R1, #2\n"      
                "ADDLT   R1, R1, #3\n"      
"loc_FF991ED8:\n"                           
           //   "CMP     R1, #0xE\n"    // -
           //   "MOVGE   R1, #0xE\n"    // -
                "CMP     R1, #0x1A\n"   // +
                "MOVGE   R1, #0x1A\n"   // +

                "B       loc_FF991F1C\n"    
"loc_FF991EE4:\n"                           
                "CMP     R0, #0\n"          
                "BGE     loc_FF991F1C\n"    
                "ADD     R3, R4, #4\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R0\n"          
                "SUBLE   R1, R1, #1\n"      
                "BLE     loc_FF991F14\n"    
                "ADD     R3, R4, #8\n"      
                "LDR     R2, [R3,LR]\n"     
                "CMP     R2, R0\n"          
                "SUBLE   R1, R1, #2\n"      
                "SUBGT   R1, R1, #3\n"      
"loc_FF991F14:\n"                           
                "CMP     R1, #0\n"          
                "MOVLT   R1, #0\n"          
"loc_FF991F1C:\n"                           
                                        
                "LDR     R0, =0x772D0\n"    
                "LDR     R3, [R0]\n"        
                "CMP     R1, R3\n"          
                "LDRNE   R2, =0x772D4\n"    
                "MOVNE   R3, #1\n"          
                "STRNE   R1, [R0]\n"        
                "STRNE   R3, [R2]\n"        
"loc_FF991F38:\n"                           
                "LDR     R3, =0x772D0\n"    
        //      "LDR     R1, =0x6DAC\n"    // -
                "LDR     R1, =video_mode\n"  //+
                "LDR     R0, [R3]\n"        
                "LDR     R2, =CompressionRateTable\n" 
                "LDR     R12, [R1]\n"
                "LDR     R12, [R12]\n"    //+      
                "LDR     LR, [R2,R0,LSL#2]\n" 
                "LDR     R3, =0x772C8\n"    
                "CMP     R12, #1\n"         
                "STR     R7, [R3]\n"        
                "STR     LR, [R6]\n"        
            //  "MOVEQ   R3, #0xB\n"    //-

                "LDREQ   R3, =video_quality\n"   //+     
                "LDREQ   R3, [R3]\n"   //+     
                "LDREQ   R3, [R3]\n"   //+     
             
                "STREQ   R3, [R6]\n"        
                "LDMFD   SP!, {R4-R7,PC}\n" 
 );
}

