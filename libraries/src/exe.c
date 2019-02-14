/** 
 * Copyright (c) 2019 EKA2L1 Project. All rights reserved.
 * 
 * This work is licensed under the terms of the MIT license.  
 * For a copy, see <https://opensource.org/licenses/MIT>.
 */

#include <epoc/common.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
#define	__EH_FRAME_ADDRESS(reg,offset)	FRAME ADDRESS reg, offset
#define __EH_FRAME_PUSH2(reg1,reg2) FRAME PUSH {reg1, reg2}
#define __EH_FRAME_SAVE1(reg,offset) FRAME SAVE {reg}, offset
#else
#define	__EH_FRAME_ADDRESS(reg,offset)
#define __EH_FRAME_PUSH2(reg1,reg2)
#define __EH_FRAME_SAVE1(reg,offset)
#endif

void xxxx_call_user_handle_exception()
{
    // TODO:
}

void _xxxx_call_user_invariant(void *exception_dat)
{
    // TODO:
}

extern void e32_run_thread(bool is_not_first_thread_created, void *thread_info);

__attribute__((naked)) E32_API _E32Startup()
{
    // Process entry point
    // R4 = entry reason
    // 0 = Enter Process - first thread of process, 1 = Enter new thread
    // 4 = Exception handling
    //
    // SP points to information block
    asm("tst pc, #0");  // DUMMY INSTRUCTION TO INDICATE EKA2 ENTRY POINT
    asm("cmp r4, #1");
    asm("b 1f ");   // branch over space for unique ID

    asm(".word 0 ");    // loader will replace with code seg unique ID
                        // for RAM-loaded code segment
                        // MUST BE AT OFFSET 12 FROM ENTRY POINT

    asm("1: ");
    asm("movls r0, r4 ");       // r0 = aNotFirst
    asm("movls r1, sp ");       // r1 -> parameter block
    asm("bls e32_run_thread");  // process or thread init

    // This will never be reached if e32_run_thread is called
    // e32_run_thread will call e32_thread_kill, so real run thread will not enter here
    // From this block now on, is the exception handler.
    asm("cmp r4, #4");

    asm("bne _xxxx_call_user_invariant" );	// invalid entry reason

    // exception entry
    // NOTE: THUMB only works on ARMv5 and above
    asm("mov r0, sp ");	        // r0->parameter block
    asm("ldr r4, [sp, #16]");   // r4 = saved CPSR
    asm("tst r4, #0x20 ");      // test for THUMB
    asm("ldrne r1, [sp, #80] ");    // r1 = saved return addr
    asm("orrne r1, r1, #1 ");
    asm("strne r1, [sp, #80] ");    // if THUMB, set bit 0 of return addr

    asm("mov r11, sp ");    // save stack pointer

    // The frame starts 84 bytes (up) from r11 i.e. CFA is r11 + 84
    __EH_FRAME_ADDRESS(r11, 84)
    // we can only restore callee-save values, but that's what we want if we 'leave'
    // saved link is -8 bytes from CFA (= r11 + 0x24 + 0x20 + 0x8)
    __EH_FRAME_SAVE1(lr, -8)

    asm("bic sp, sp, #4 ");		// align stack to 8 byte boundary
    asm("bl _xxxx_call_user_handle_exception");
    asm("add sp, r11, #16 ");	// skip exc type, exc code, FAR, FSR
    asm("ldr r4, [sp], #4 ");	// r4 = saved CPSR
    asm("bic r4, r4, #0x20 ");	// clear THUMB bit
    asm("msr cpsr, r4 ");		// restore flags
    asm("ldmia sp, {r0-r15} ");	// restore r0-r15
}

#ifdef __cplusplus
}
#endif
