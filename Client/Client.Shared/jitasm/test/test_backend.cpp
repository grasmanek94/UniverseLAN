#include "jitasm.h"
#include "test.h"


//----------------------------------------
// SAL
//----------------------------------------
extern "C" void masm_test_sal();
struct test_sal : jitasm::function<void, test_sal>
{
	void naked_main()
	{
		sal(al, cl);
		sal(al, 1);
		sal(al, 2);
		sal(al, (jitasm::uint8) -1);
		sal(ax, cl);
		sal(ax, 1);
		sal(ax, 2);
		sal(eax, cl);
		sal(eax, 1);
		sal(eax, 2);
		sal(byte_ptr[eax], cl);
		sal(byte_ptr[eax], 1);
		sal(byte_ptr[eax], 2);
		sal(word_ptr[eax], cl);
		sal(word_ptr[eax], 1);
		sal(word_ptr[eax], 2);
		sal(dword_ptr[eax], cl);
		sal(dword_ptr[eax], 1);
		sal(dword_ptr[eax], 2);
#ifdef JITASM64
		sal(r8b, cl);
		sal(r8b, 1);
		sal(r8b, 2);
		sal(r8w, cl);
		sal(r8w, 1);
		sal(r8w, 2);
		sal(r8d, cl);
		sal(r8d, 1);
		sal(r8d, 2);
		sal(r8, cl);
		sal(r8, 1);
		sal(r8, 2);
		sal(qword_ptr[rax], cl);
		sal(qword_ptr[rax], 1);
		sal(qword_ptr[rax], 2);
#endif
	}
};

//----------------------------------------
// SAR
//----------------------------------------
extern "C" void masm_test_sar();
struct test_sar : jitasm::function<void, test_sar>
{
	void naked_main()
	{
		sar(al, cl);
		sar(al, 1);
		sar(al, 2);
		sar(al, (jitasm::uint8) -1);
		sar(ax, cl);
		sar(ax, 1);
		sar(ax, 2);
		sar(eax, cl);
		sar(eax, 1);
		sar(eax, 2);
		sar(byte_ptr[eax], cl);
		sar(byte_ptr[eax], 1);
		sar(byte_ptr[eax], 2);
		sar(word_ptr[eax], cl);
		sar(word_ptr[eax], 1);
		sar(word_ptr[eax], 2);
		sar(dword_ptr[eax], cl);
		sar(dword_ptr[eax], 1);
		sar(dword_ptr[eax], 2);
#ifdef JITASM64
		sar(r8b, cl);
		sar(r8b, 1);
		sar(r8b, 2);
		sar(r8w, cl);
		sar(r8w, 1);
		sar(r8w, 2);
		sar(r8d, cl);
		sar(r8d, 1);
		sar(r8d, 2);
		sar(r8, cl);
		sar(r8, 1);
		sar(r8, 2);
		sar(qword_ptr[rax], cl);
		sar(qword_ptr[rax], 1);
		sar(qword_ptr[rax], 2);
#endif
	}
};

//----------------------------------------
// SHL
//----------------------------------------
extern "C" void masm_test_shl();
struct test_shl : jitasm::function<void, test_shl>
{
	void naked_main()
	{
		shl(al, cl);
		shl(al, 1);
		shl(al, 2);
		shl(al, (jitasm::uint8) -1);
		shl(ax, cl);
		shl(ax, 1);
		shl(ax, 2);
		shl(eax, cl);
		shl(eax, 1);
		shl(eax, 2);
		shl(byte_ptr[eax], cl);
		shl(byte_ptr[eax], 1);
		shl(byte_ptr[eax], 2);
		shl(word_ptr[eax], cl);
		shl(word_ptr[eax], 1);
		shl(word_ptr[eax], 2);
		shl(dword_ptr[eax], cl);
		shl(dword_ptr[eax], 1);
		shl(dword_ptr[eax], 2);
#ifdef JITASM64
		shl(r8b, cl);
		shl(r8b, 1);
		shl(r8b, 2);
		shl(r8w, cl);
		shl(r8w, 1);
		shl(r8w, 2);
		shl(r8d, cl);
		shl(r8d, 1);
		shl(r8d, 2);
		shl(r8, cl);
		shl(r8, 1);
		shl(r8, 2);
		shl(qword_ptr[rax], cl);
		shl(qword_ptr[rax], 1);
		shl(qword_ptr[rax], 2);
#endif
	}
};

//----------------------------------------
// SHR
//----------------------------------------
extern "C" void masm_test_shr();
struct test_shr : jitasm::function<void, test_shr>
{
	void naked_main()
	{
		shr(al, cl);
		shr(al, 1);
		shr(al, 2);
		shr(al, (jitasm::uint8) -1);
		shr(ax, cl);
		shr(ax, 1);
		shr(ax, 2);
		shr(eax, cl);
		shr(eax, 1);
		shr(eax, 2);
		shr(byte_ptr[eax], cl);
		shr(byte_ptr[eax], 1);
		shr(byte_ptr[eax], 2);
		shr(word_ptr[eax], cl);
		shr(word_ptr[eax], 1);
		shr(word_ptr[eax], 2);
		shr(dword_ptr[eax], cl);
		shr(dword_ptr[eax], 1);
		shr(dword_ptr[eax], 2);
#ifdef JITASM64
		shr(r8b, cl);
		shr(r8b, 1);
		shr(r8b, 2);
		shr(r8w, cl);
		shr(r8w, 1);
		shr(r8w, 2);
		shr(r8d, cl);
		shr(r8d, 1);
		shr(r8d, 2);
		shr(r8, cl);
		shr(r8, 1);
		shr(r8, 2);
		shr(qword_ptr[rax], cl);
		shr(qword_ptr[rax], 1);
		shr(qword_ptr[rax], 2);
#endif
	}
};

//----------------------------------------
// RCL
//----------------------------------------
extern "C" void masm_test_rcl();
struct test_rcl : jitasm::function<void, test_rcl>
{
	void naked_main()
	{
		rcl(al, cl);
		rcl(al, 1);
		rcl(al, 2);
		rcl(al, (jitasm::uint8) -1);
		rcl(ax, cl);
		rcl(ax, 1);
		rcl(ax, 2);
		rcl(eax, cl);
		rcl(eax, 1);
		rcl(eax, 2);
		rcl(byte_ptr[eax], cl);
		rcl(byte_ptr[eax], 1);
		rcl(byte_ptr[eax], 2);
		rcl(word_ptr[eax], cl);
		rcl(word_ptr[eax], 1);
		rcl(word_ptr[eax], 2);
		rcl(dword_ptr[eax], cl);
		rcl(dword_ptr[eax], 1);
		rcl(dword_ptr[eax], 2);
#ifdef JITASM64
		rcl(r8b, cl);
		rcl(r8b, 1);
		rcl(r8b, 2);
		rcl(r8w, cl);
		rcl(r8w, 1);
		rcl(r8w, 2);
		rcl(r8d, cl);
		rcl(r8d, 1);
		rcl(r8d, 2);
		rcl(r8, cl);
		rcl(r8, 1);
		rcl(r8, 2);
		rcl(qword_ptr[rax], cl);
		rcl(qword_ptr[rax], 1);
		rcl(qword_ptr[rax], 2);
#endif
	}
};

//----------------------------------------
// RCR
//----------------------------------------
extern "C" void masm_test_rcr();
struct test_rcr : jitasm::function<void, test_rcr>
{
	void naked_main()
	{
		rcr(al, cl);
		rcr(al, 1);
		rcr(al, 2);
		rcr(al, (jitasm::uint8) -1);
		rcr(ax, cl);
		rcr(ax, 1);
		rcr(ax, 2);
		rcr(eax, cl);
		rcr(eax, 1);
		rcr(eax, 2);
		rcr(byte_ptr[eax], cl);
		rcr(byte_ptr[eax], 1);
		rcr(byte_ptr[eax], 2);
		rcr(word_ptr[eax], cl);
		rcr(word_ptr[eax], 1);
		rcr(word_ptr[eax], 2);
		rcr(dword_ptr[eax], cl);
		rcr(dword_ptr[eax], 1);
		rcr(dword_ptr[eax], 2);
#ifdef JITASM64
		rcr(r8b, cl);
		rcr(r8b, 1);
		rcr(r8b, 2);
		rcr(r8w, cl);
		rcr(r8w, 1);
		rcr(r8w, 2);
		rcr(r8d, cl);
		rcr(r8d, 1);
		rcr(r8d, 2);
		rcr(r8, cl);
		rcr(r8, 1);
		rcr(r8, 2);
		rcr(qword_ptr[rax], cl);
		rcr(qword_ptr[rax], 1);
		rcr(qword_ptr[rax], 2);
#endif
	}
};

//----------------------------------------
// ROL
//----------------------------------------
extern "C" void masm_test_rol();
struct test_rol : jitasm::function<void, test_rol>
{
	void naked_main()
	{
		rol(al, cl);
		rol(al, 1);
		rol(al, 2);
		rol(al, (jitasm::uint8) -1);
		rol(ax, cl);
		rol(ax, 1);
		rol(ax, 2);
		rol(eax, cl);
		rol(eax, 1);
		rol(eax, 2);
		rol(byte_ptr[eax], cl);
		rol(byte_ptr[eax], 1);
		rol(byte_ptr[eax], 2);
		rol(word_ptr[eax], cl);
		rol(word_ptr[eax], 1);
		rol(word_ptr[eax], 2);
		rol(dword_ptr[eax], cl);
		rol(dword_ptr[eax], 1);
		rol(dword_ptr[eax], 2);
#ifdef JITASM64
		rol(r8b, cl);
		rol(r8b, 1);
		rol(r8b, 2);
		rol(r8w, cl);
		rol(r8w, 1);
		rol(r8w, 2);
		rol(r8d, cl);
		rol(r8d, 1);
		rol(r8d, 2);
		rol(r8, cl);
		rol(r8, 1);
		rol(r8, 2);
		rol(qword_ptr[rax], cl);
		rol(qword_ptr[rax], 1);
		rol(qword_ptr[rax], 2);
#endif
	}
};

//----------------------------------------
// ROR
//----------------------------------------
extern "C" void masm_test_ror();
struct test_ror : jitasm::function<void, test_ror>
{
	void naked_main()
	{
		ror(al, cl);
		ror(al, 1);
		ror(al, 2);
		ror(al, (jitasm::uint8) -1);
		ror(ax, cl);
		ror(ax, 1);
		ror(ax, 2);
		ror(eax, cl);
		ror(eax, 1);
		ror(eax, 2);
		ror(byte_ptr[eax], cl);
		ror(byte_ptr[eax], 1);
		ror(byte_ptr[eax], 2);
		ror(word_ptr[eax], cl);
		ror(word_ptr[eax], 1);
		ror(word_ptr[eax], 2);
		ror(dword_ptr[eax], cl);
		ror(dword_ptr[eax], 1);
		ror(dword_ptr[eax], 2);
#ifdef JITASM64
		ror(r8b, cl);
		ror(r8b, 1);
		ror(r8b, 2);
		ror(r8w, cl);
		ror(r8w, 1);
		ror(r8w, 2);
		ror(r8d, cl);
		ror(r8d, 1);
		ror(r8d, 2);
		ror(r8, cl);
		ror(r8, 1);
		ror(r8, 2);
		ror(qword_ptr[rax], cl);
		ror(qword_ptr[rax], 1);
		ror(qword_ptr[rax], 2);
#endif
	}
};

//----------------------------------------
// INC/DEC
//----------------------------------------
extern "C" void masm_test_inc_dec();
struct test_inc_dec : jitasm::function<void, test_inc_dec>
{
	void naked_main()
	{
		inc(al);
		inc(ax);
		inc(eax);
		inc(byte_ptr[eax]);
		inc(word_ptr[eax]);
		inc(dword_ptr[eax]);
		dec(al);
		dec(ax);
		dec(eax);
		dec(byte_ptr[eax]);
		dec(word_ptr[eax]);
		dec(dword_ptr[eax]);
#ifdef JITASM64
		inc(r8b);
		inc(r8w);
		inc(r8d);
		inc(rax);
		inc(r8);
		inc(qword_ptr[rax]);
		dec(r8b);
		dec(r8w);
		dec(r8d);
		dec(rax);
		dec(r8);
		dec(qword_ptr[rax]);
#endif
	}
};

//----------------------------------------
// PUSH/POP
//----------------------------------------
extern "C" void masm_test_push_pop();
struct test_push_pop : jitasm::function<void, test_push_pop>
{
	void naked_main()
	{
		push(ax);
		push(word_ptr[eax]);
		push(0x1);
		push(0x100);
		push(0x10000);
		push((jitasm::uint32) -0x1);
		push((jitasm::uint32) -0x100);
		push((jitasm::uint32) -0x10000);
		pop(ax);
		pop(word_ptr[eax]);
#ifndef JITASM64
		push(eax);
		push(dword_ptr[eax]);
		pop(eax);
		pop(dword_ptr[eax]);
#else
		push(rax);
		push(r8);
		push(qword_ptr[rax]);
		push(qword_ptr[r8]);
		pop(rax);
		pop(r8);
		pop(qword_ptr[rax]);
		pop(qword_ptr[r8]);
#endif
	}
};

//----------------------------------------
// ADD
//----------------------------------------
extern "C" void masm_test_add();
struct test_add : jitasm::function<void, test_add>
{
	void naked_main()
	{
		add(al, al);
		add(ax, ax);
		add(eax, eax);
		add(al, 0x1);
		add(al, (jitasm::uint8) -0x1);
		add(ax, 0x1);
		add(ax, 0x100);
		add(ax, (jitasm::uint16) -0x1);
		add(ax, (jitasm::uint16) -0x100);
		add(eax, 0x1);
		add(eax, 0x100);
		add(eax, 0x10000);
		add(eax, (jitasm::uint32) -0x1);
		add(eax, (jitasm::uint32) -0x100);
		add(eax, (jitasm::uint32) -0x10000);
		add(cl, 0x1);
		add(cl, (jitasm::uint8) -0x1);
		add(cx, 0x1);
		add(cx, 0x100);
		add(cx, (jitasm::uint16) -0x1);
		add(cx, (jitasm::uint16) -0x100);
		add(ecx, 0x1);
		add(ecx, 0x100);
		add(ecx, 0x10000);
		add(ecx, (jitasm::uint32) -0x1);
		add(ecx, (jitasm::uint32) -0x100);
		add(ecx, (jitasm::uint32) -0x10000);
		add(byte_ptr[eax], 1);
		add(word_ptr[eax], 1);
		add(dword_ptr[eax], 1);
		add(al, byte_ptr[eax]);
		add(ax, word_ptr[eax]);
		add(eax, dword_ptr[eax]);
		add(byte_ptr[eax], al);
		add(word_ptr[eax], ax);
		add(dword_ptr[eax], eax);
#ifdef JITASM64
		add(rax, rax);
		add(rax, 0x1);
		add(rax, 0x100);
		add(rax, 0x10000);
		add(rax, (jitasm::uint32) -0x1);
		add(rax, (jitasm::uint32) -0x100);
		add(rax, (jitasm::uint32) -0x10000);
		add(r8, 0x1);
		add(r8, 0x100);
		add(r8, 0x10000);
		add(r8, (jitasm::uint32) -0x1);
		add(r8, (jitasm::uint32) -0x100);
		add(r8, (jitasm::uint32) -0x10000);
		add(qword_ptr[rax], 1);
		add(rax, qword_ptr[rax]);
		add(qword_ptr[rax], rax);
#endif
	}
};

//----------------------------------------
// OR
//----------------------------------------
extern "C" void masm_test_or();
struct test_or : jitasm::function<void, test_or>
{
	void naked_main()
	{
		or(al, al);
		or(ax, ax);
		or(eax, eax);
		or(al, 0x1);
		or(al, (jitasm::uint8) -0x1);
		or(ax, 0x1);
		or(ax, 0x100);
		or(ax, (jitasm::uint16) -0x1);
		or(ax, (jitasm::uint16) -0x100);
		or(eax, 0x1);
		or(eax, 0x100);
		or(eax, 0x10000);
		or(eax, (jitasm::uint32) -0x1);
		or(eax, (jitasm::uint32) -0x100);
		or(eax, (jitasm::uint32) -0x10000);
		or(cl, 0x1);
		or(cl, (jitasm::uint8) -0x1);
		or(cx, 0x1);
		or(cx, 0x100);
		or(cx, (jitasm::uint16) -0x1);
		or(cx, (jitasm::uint16) -0x100);
		or(ecx, 0x1);
		or(ecx, 0x100);
		or(ecx, 0x10000);
		or(ecx, (jitasm::uint32) -0x1);
		or(ecx, (jitasm::uint32) -0x100);
		or(ecx, (jitasm::uint32) -0x10000);
		or(byte_ptr[eax], 1);
		or(word_ptr[eax], 1);
		or(dword_ptr[eax], 1);
		or(al, byte_ptr[eax]);
		or(ax, word_ptr[eax]);
		or(eax, dword_ptr[eax]);
		or(byte_ptr[eax], al);
		or(word_ptr[eax], ax);
		or(dword_ptr[eax], eax);
#ifdef JITASM64
		or(rax, rax);
		or(rax, 0x1);
		or(rax, 0x100);
		or(rax, 0x10000);
		or(rax, (jitasm::uint32) -0x1);
		or(rax, (jitasm::uint32) -0x100);
		or(rax, (jitasm::uint32) -0x10000);
		or(r8, 0x1);
		or(r8, 0x100);
		or(r8, 0x10000);
		or(r8, (jitasm::uint32) -0x1);
		or(r8, (jitasm::uint32) -0x100);
		or(r8, (jitasm::uint32) -0x10000);
		or(qword_ptr[rax], 1);
		or(rax, qword_ptr[rax]);
		or(qword_ptr[rax], rax);
#endif
	}
};

//----------------------------------------
// ADC
//----------------------------------------
extern "C" void masm_test_adc();
struct test_adc : jitasm::function<void, test_adc>
{
	void naked_main()
	{
		adc(al, al);
		adc(ax, ax);
		adc(eax, eax);
		adc(al, 0x1);
		adc(al, (jitasm::uint8) -0x1);
		adc(ax, 0x1);
		adc(ax, 0x100);
		adc(ax, (jitasm::uint16) -0x1);
		adc(ax, (jitasm::uint16) -0x100);
		adc(eax, 0x1);
		adc(eax, 0x100);
		adc(eax, 0x10000);
		adc(eax, (jitasm::uint32) -0x1);
		adc(eax, (jitasm::uint32) -0x100);
		adc(eax, (jitasm::uint32) -0x10000);
		adc(cl, 0x1);
		adc(cl, (jitasm::uint8) -0x1);
		adc(cx, 0x1);
		adc(cx, 0x100);
		adc(cx, (jitasm::uint16) -0x1);
		adc(cx, (jitasm::uint16) -0x100);
		adc(ecx, 0x1);
		adc(ecx, 0x100);
		adc(ecx, 0x10000);
		adc(ecx, (jitasm::uint32) -0x1);
		adc(ecx, (jitasm::uint32) -0x100);
		adc(ecx, (jitasm::uint32) -0x10000);
		adc(byte_ptr[eax], 1);
		adc(word_ptr[eax], 1);
		adc(dword_ptr[eax], 1);
		adc(al, byte_ptr[eax]);
		adc(ax, word_ptr[eax]);
		adc(eax, dword_ptr[eax]);
		adc(byte_ptr[eax], al);
		adc(word_ptr[eax], ax);
		adc(dword_ptr[eax], eax);
#ifdef JITASM64
		adc(rax, rax);
		adc(rax, 0x1);
		adc(rax, 0x100);
		adc(rax, 0x10000);
		adc(rax, (jitasm::uint32) -0x1);
		adc(rax, (jitasm::uint32) -0x100);
		adc(rax, (jitasm::uint32) -0x10000);
		adc(r8, 0x1);
		adc(r8, 0x100);
		adc(r8, 0x10000);
		adc(r8, (jitasm::uint32) -0x1);
		adc(r8, (jitasm::uint32) -0x100);
		adc(r8, (jitasm::uint32) -0x10000);
		adc(qword_ptr[rax], 1);
		adc(rax, qword_ptr[rax]);
		adc(qword_ptr[rax], rax);
#endif
	}
};

//----------------------------------------
// SBB
//----------------------------------------
extern "C" void masm_test_sbb();
struct test_sbb : jitasm::function<void, test_sbb>
{
	void naked_main()
	{
		sbb(al, al);
		sbb(ax, ax);
		sbb(eax, eax);
		sbb(al, 0x1);
		sbb(al, (jitasm::uint8) -0x1);
		sbb(ax, 0x1);
		sbb(ax, 0x100);
		sbb(ax, (jitasm::uint16) -0x1);
		sbb(ax, (jitasm::uint16) -0x100);
		sbb(eax, 0x1);
		sbb(eax, 0x100);
		sbb(eax, 0x10000);
		sbb(eax, (jitasm::uint32) -0x1);
		sbb(eax, (jitasm::uint32) -0x100);
		sbb(eax, (jitasm::uint32) -0x10000);
		sbb(cl, 0x1);
		sbb(cl, (jitasm::uint8) -0x1);
		sbb(cx, 0x1);
		sbb(cx, 0x100);
		sbb(cx, (jitasm::uint16) -0x1);
		sbb(cx, (jitasm::uint16) -0x100);
		sbb(ecx, 0x1);
		sbb(ecx, 0x100);
		sbb(ecx, 0x10000);
		sbb(ecx, (jitasm::uint32) -0x1);
		sbb(ecx, (jitasm::uint32) -0x100);
		sbb(ecx, (jitasm::uint32) -0x10000);
		sbb(byte_ptr[eax], 1);
		sbb(word_ptr[eax], 1);
		sbb(dword_ptr[eax], 1);
		sbb(al, byte_ptr[eax]);
		sbb(ax, word_ptr[eax]);
		sbb(eax, dword_ptr[eax]);
		sbb(byte_ptr[eax], al);
		sbb(word_ptr[eax], ax);
		sbb(dword_ptr[eax], eax);
#ifdef JITASM64
		sbb(rax, rax);
		sbb(rax, 0x1);
		sbb(rax, 0x100);
		sbb(rax, 0x10000);
		sbb(rax, (jitasm::uint32) -0x1);
		sbb(rax, (jitasm::uint32) -0x100);
		sbb(rax, (jitasm::uint32) -0x10000);
		sbb(r8, 0x1);
		sbb(r8, 0x100);
		sbb(r8, 0x10000);
		sbb(r8, (jitasm::uint32) -0x1);
		sbb(r8, (jitasm::uint32) -0x100);
		sbb(r8, (jitasm::uint32) -0x10000);
		sbb(qword_ptr[rax], 1);
		sbb(rax, qword_ptr[rax]);
		sbb(qword_ptr[rax], rax);
#endif
	}
};

//----------------------------------------
// AND
//----------------------------------------
extern "C" void masm_test_and();
struct test_and : jitasm::function<void, test_and>
{
	void naked_main()
	{
		and(al, al);
		and(ax, ax);
		and(eax, eax);
		and(al, 0x1);
		and(al, (jitasm::uint8) -0x1);
		and(ax, 0x1);
		and(ax, 0x100);
		and(ax, (jitasm::uint16) -0x1);
		and(ax, (jitasm::uint16) -0x100);
		and(eax, 0x1);
		and(eax, 0x100);
		and(eax, 0x10000);
		and(eax, (jitasm::uint32) -0x1);
		and(eax, (jitasm::uint32) -0x100);
		and(eax, (jitasm::uint32) -0x10000);
		and(cl, 0x1);
		and(cl, (jitasm::uint8) -0x1);
		and(cx, 0x1);
		and(cx, 0x100);
		and(cx, (jitasm::uint16) -0x1);
		and(cx, (jitasm::uint16) -0x100);
		and(ecx, 0x1);
		and(ecx, 0x100);
		and(ecx, 0x10000);
		and(ecx, (jitasm::uint32) -0x1);
		and(ecx, (jitasm::uint32) -0x100);
		and(ecx, (jitasm::uint32) -0x10000);
		and(byte_ptr[eax], 1);
		and(word_ptr[eax], 1);
		and(dword_ptr[eax], 1);
		and(al, byte_ptr[eax]);
		and(ax, word_ptr[eax]);
		and(eax, dword_ptr[eax]);
		and(byte_ptr[eax], al);
		and(word_ptr[eax], ax);
		and(dword_ptr[eax], eax);
#ifdef JITASM64
		and(rax, rax);
		and(rax, 0x1);
		and(rax, 0x100);
		and(rax, 0x10000);
		and(rax, (jitasm::uint32) -0x1);
		and(rax, (jitasm::uint32) -0x100);
		and(rax, (jitasm::uint32) -0x10000);
		and(r8, 0x1);
		and(r8, 0x100);
		and(r8, 0x10000);
		and(r8, (jitasm::uint32) -0x1);
		and(r8, (jitasm::uint32) -0x100);
		and(r8, (jitasm::uint32) -0x10000);
		and(qword_ptr[rax], 1);
		and(rax, qword_ptr[rax]);
		and(qword_ptr[rax], rax);
#endif
	}
};

//----------------------------------------
// SUB
//----------------------------------------
extern "C" void masm_test_sub();
struct test_sub : jitasm::function<void, test_sub>
{
	void naked_main()
	{
		sub(al, al);
		sub(ax, ax);
		sub(eax, eax);
		sub(al, 0x1);
		sub(al, (jitasm::uint8) -0x1);
		sub(ax, 0x1);
		sub(ax, 0x100);
		sub(ax, (jitasm::uint16) -0x1);
		sub(ax, (jitasm::uint16) -0x100);
		sub(eax, 0x1);
		sub(eax, 0x100);
		sub(eax, 0x10000);
		sub(eax, (jitasm::uint32) -0x1);
		sub(eax, (jitasm::uint32) -0x100);
		sub(eax, (jitasm::uint32) -0x10000);
		sub(cl, 0x1);
		sub(cl, (jitasm::uint8) -0x1);
		sub(cx, 0x1);
		sub(cx, 0x100);
		sub(cx, (jitasm::uint16) -0x1);
		sub(cx, (jitasm::uint16) -0x100);
		sub(ecx, 0x1);
		sub(ecx, 0x100);
		sub(ecx, 0x10000);
		sub(ecx, (jitasm::uint32) -0x1);
		sub(ecx, (jitasm::uint32) -0x100);
		sub(ecx, (jitasm::uint32) -0x10000);
		sub(byte_ptr[eax], 1);
		sub(word_ptr[eax], 1);
		sub(dword_ptr[eax], 1);
		sub(al, byte_ptr[eax]);
		sub(ax, word_ptr[eax]);
		sub(eax, dword_ptr[eax]);
		sub(byte_ptr[eax], al);
		sub(word_ptr[eax], ax);
		sub(dword_ptr[eax], eax);
#ifdef JITASM64
		sub(rax, rax);
		sub(rax, 0x1);
		sub(rax, 0x100);
		sub(rax, 0x10000);
		sub(rax, (jitasm::uint32) -0x1);
		sub(rax, (jitasm::uint32) -0x100);
		sub(rax, (jitasm::uint32) -0x10000);
		sub(r8, 0x1);
		sub(r8, 0x100);
		sub(r8, 0x10000);
		sub(r8, (jitasm::uint32) -0x1);
		sub(r8, (jitasm::uint32) -0x100);
		sub(r8, (jitasm::uint32) -0x10000);
		sub(qword_ptr[rax], 1);
		sub(rax, qword_ptr[rax]);
		sub(qword_ptr[rax], rax);
#endif
	}
};

//----------------------------------------
// XOR
//----------------------------------------
extern "C" void masm_test_xor();
struct test_xor : jitasm::function<void, test_xor>
{
	void naked_main()
	{
		xor(al, al);
		xor(ax, ax);
		xor(eax, eax);
		xor(al, 0x1);
		xor(al, (jitasm::uint8) -0x1);
		xor(ax, 0x1);
		xor(ax, 0x100);
		xor(ax, (jitasm::uint16) -0x1);
		xor(ax, (jitasm::uint16) -0x100);
		xor(eax, 0x1);
		xor(eax, 0x100);
		xor(eax, 0x10000);
		xor(eax, (jitasm::uint32) -0x1);
		xor(eax, (jitasm::uint32) -0x100);
		xor(eax, (jitasm::uint32) -0x10000);
		xor(cl, 0x1);
		xor(cl, (jitasm::uint8) -0x1);
		xor(cx, 0x1);
		xor(cx, 0x100);
		xor(cx, (jitasm::uint16) -0x1);
		xor(cx, (jitasm::uint16) -0x100);
		xor(ecx, 0x1);
		xor(ecx, 0x100);
		xor(ecx, 0x10000);
		xor(ecx, (jitasm::uint32) -0x1);
		xor(ecx, (jitasm::uint32) -0x100);
		xor(ecx, (jitasm::uint32) -0x10000);
		xor(byte_ptr[eax], 1);
		xor(word_ptr[eax], 1);
		xor(dword_ptr[eax], 1);
		xor(al, byte_ptr[eax]);
		xor(ax, word_ptr[eax]);
		xor(eax, dword_ptr[eax]);
		xor(byte_ptr[eax], al);
		xor(word_ptr[eax], ax);
		xor(dword_ptr[eax], eax);
#ifdef JITASM64
		xor(rax, rax);
		xor(rax, 0x1);
		xor(rax, 0x100);
		xor(rax, 0x10000);
		xor(rax, (jitasm::uint32) -0x1);
		xor(rax, (jitasm::uint32) -0x100);
		xor(rax, (jitasm::uint32) -0x10000);
		xor(r8, 0x1);
		xor(r8, 0x100);
		xor(r8, 0x10000);
		xor(r8, (jitasm::uint32) -0x1);
		xor(r8, (jitasm::uint32) -0x100);
		xor(r8, (jitasm::uint32) -0x10000);
		xor(qword_ptr[rax], 1);
		xor(rax, qword_ptr[rax]);
		xor(qword_ptr[rax], rax);
#endif
	}
};

//----------------------------------------
// CMP
//----------------------------------------
extern "C" void masm_test_cmp();
struct test_cmp : jitasm::function<void, test_cmp>
{
	void naked_main()
	{
		cmp(al, al);
		cmp(ax, ax);
		cmp(eax, eax);
		cmp(al, 0x1);
		cmp(al, (jitasm::uint8) -0x1);
		cmp(ax, 0x1);
		cmp(ax, 0x100);
		cmp(ax, (jitasm::uint16) -0x1);
		cmp(ax, (jitasm::uint16) -0x100);
		cmp(eax, 0x1);
		cmp(eax, 0x100);
		cmp(eax, 0x10000);
		cmp(eax, (jitasm::uint32) -0x1);
		cmp(eax, (jitasm::uint32) -0x100);
		cmp(eax, (jitasm::uint32) -0x10000);
		cmp(cl, 0x1);
		cmp(cl, (jitasm::uint8) -0x1);
		cmp(cx, 0x1);
		cmp(cx, 0x100);
		cmp(cx, (jitasm::uint16) -0x1);
		cmp(cx, (jitasm::uint16) -0x100);
		cmp(ecx, 0x1);
		cmp(ecx, 0x100);
		cmp(ecx, 0x10000);
		cmp(ecx, (jitasm::uint32) -0x1);
		cmp(ecx, (jitasm::uint32) -0x100);
		cmp(ecx, (jitasm::uint32) -0x10000);
		cmp(byte_ptr[eax], 1);
		cmp(word_ptr[eax], 1);
		cmp(dword_ptr[eax], 1);
		cmp(al, byte_ptr[eax]);
		cmp(ax, word_ptr[eax]);
		cmp(eax, dword_ptr[eax]);
		cmp(byte_ptr[eax], al);
		cmp(word_ptr[eax], ax);
		cmp(dword_ptr[eax], eax);
#ifdef JITASM64
		cmp(rax, rax);
		cmp(rax, 0x1);
		cmp(rax, 0x100);
		cmp(rax, 0x10000);
		cmp(rax, (jitasm::uint32) -0x1);
		cmp(rax, (jitasm::uint32) -0x100);
		cmp(rax, (jitasm::uint32) -0x10000);
		cmp(r8, 0x1);
		cmp(r8, 0x100);
		cmp(r8, 0x10000);
		cmp(r8, (jitasm::uint32) -0x1);
		cmp(r8, (jitasm::uint32) -0x100);
		cmp(r8, (jitasm::uint32) -0x10000);
		cmp(qword_ptr[rax], 1);
		cmp(rax, qword_ptr[rax]);
		cmp(qword_ptr[rax], rax);
#endif
	}
};

//----------------------------------------
// XCHG
//----------------------------------------
extern "C" void masm_test_xchg();
struct test_xchg : jitasm::function<void, test_xchg>
{
	void naked_main()
	{
		xchg(al, al);
		xchg(ax, ax);
		xchg(eax, eax);
		xchg(al, cl);
		xchg(cl, al);
		xchg(ax, cx);
		xchg(cx, ax);
		xchg(eax, ecx);
		xchg(ecx, eax);
		xchg(ecx, edx);
		xchg(edx, ecx);
		xchg(al, byte_ptr[ecx]);
		xchg(byte_ptr[ecx], al);
		xchg(cl, byte_ptr[eax]);
		xchg(byte_ptr[eax], cl);
		xchg(ax, word_ptr[ecx]);
		xchg(word_ptr[ecx], ax);
		xchg(cx, word_ptr[eax]);
		xchg(word_ptr[eax], cx);
		xchg(eax, dword_ptr[ecx]);
		xchg(dword_ptr[ecx], eax);
		xchg(ecx, dword_ptr[eax]);
		xchg(dword_ptr[eax], ecx);
#ifdef JITASM64
		xchg(rax, rax);
		xchg(rax, r8);
		xchg(r8, rax);
		xchg(rax, qword_ptr[r8]);
		xchg(qword_ptr[r8], rax);
		xchg(r8, qword_ptr[rax]);
		xchg(qword_ptr[rax], r8);
#endif
	}
};

//----------------------------------------
// test
//----------------------------------------
extern "C" void masm_test_test();
struct test_test : jitasm::function<void, test_test>
{
	void naked_main()
	{
		test(al, al);
		test(ax, ax);
		test(eax, eax);
		test(al, 1);
		test(ax, 1);
		test(eax, 1);
		test(al, (jitasm::uint8) -1);
		test(ax, (jitasm::uint16) -1);
		test(eax, (jitasm::uint32) -1);
		test(cl, 1);
		test(cx, 1);
		test(ecx, 1);
		test(cl, (jitasm::uint8) -1);
		test(cx, (jitasm::uint16) -1);
		test(ecx, (jitasm::uint32) -1);
		test(al, cl);
		test(ax, cx);
		test(eax, ecx);
		test(cl, al);
		test(cx, ax);
		test(ecx, eax);
		test(byte_ptr[eax], 1);
		test(word_ptr[eax], 1);
		test(dword_ptr[eax], 1);
		test(byte_ptr[eax], cl);
		test(word_ptr[eax], cx);
		test(dword_ptr[eax], ecx);
#ifdef JITASM64
		test(rax, rax);
		test(rax, 1);
		test(rax, (jitasm::uint32) -1);
		test(r8, 1);
		test(r8, (jitasm::uint32) -1);
		test(rax, r8);
		test(r8, rax);
		test(qword_ptr[eax], 1);
		test(qword_ptr[eax], r8);
#endif
	}
};

//----------------------------------------
// MOV/MOVZX
//----------------------------------------
extern "C" void masm_test_mov();
struct test_mov : jitasm::function<void, test_mov>
{
	void naked_main()
	{
		mov(al, al);
		mov(ax, ax);
		mov(eax, eax);
		mov(al, cl);
		mov(ax, cx);
		mov(eax, ecx);
		mov(byte_ptr[eax], cl);
		mov(word_ptr[eax], cx);
		mov(dword_ptr[eax], ecx);
		mov(al, byte_ptr[ecx]);
		mov(ax, word_ptr[ecx]);
		mov(eax, dword_ptr[ecx]);
		mov(al, 1);
		mov(al, (jitasm::uint8) -1);
		mov(ax, 1);
		mov(ax, (jitasm::uint16) -1);
		mov(eax, 1);
		mov(eax, (jitasm::uint32) -1);
		mov(byte_ptr[eax], 1);
		mov(word_ptr[eax], 1);
		mov(dword_ptr[eax], 1);
		movzx(ax, cl);
		movzx(eax, cl);
		movzx(eax, cx);
		movzx(ax, byte_ptr[ecx]);
		movzx(eax, byte_ptr[ecx]);
		movzx(eax, word_ptr[ecx]);
#ifdef JITASM64
		mov(rax, rax);
		mov(r8b, bl);
		mov(r8w, bx);
		mov(rax, r8);
		mov(qword_ptr[rax], r8);
		mov(rax, qword_ptr[r8]);
		mov(rax, 1);
		mov(rax, (jitasm::uint64) -1);
		mov(qword_ptr[rax], 1);
		movzx(rax, cl);
		movzx(rax, cx);
		movzx(rax, byte_ptr[rcx]);
		movzx(rax, word_ptr[rcx]);
#endif
	}
};

//----------------------------------------
// LEA
//----------------------------------------
extern "C" void masm_test_lea();
struct test_lea : jitasm::function<void, test_lea>
{
	void naked_main()
	{
		lea(eax, dword_ptr[eax]);
		lea(eax, dword_ptr[esp]);
		lea(eax, dword_ptr[ebp]);
		lea(eax, dword_ptr[eax + ecx]);
		lea(eax, dword_ptr[ecx + eax]);
		lea(eax, dword_ptr[esp + ecx]);
		lea(eax, dword_ptr[ecx + esp]);
		lea(eax, dword_ptr[ebp + ecx]);
		lea(eax, dword_ptr[ecx + ebp]);
		lea(eax, dword_ptr[esp + ebp]);
		lea(eax, dword_ptr[ebp + esp]);
		lea(eax, dword_ptr[eax + 0x1]);
		lea(eax, dword_ptr[esp + 0x1]);
		lea(eax, dword_ptr[ebp + 0x1]);
		lea(eax, dword_ptr[eax + 0x100]);
		lea(eax, dword_ptr[esp + 0x100]);
		lea(eax, dword_ptr[ebp + 0x100]);
		lea(eax, dword_ptr[eax + 0x10000]);
		lea(eax, dword_ptr[esp + 0x10000]);
		lea(eax, dword_ptr[ebp + 0x10000]);
		lea(eax, dword_ptr[eax * 2]);
		lea(eax, dword_ptr[ebp * 2]);
		lea(eax, dword_ptr[eax * 4]);
		lea(eax, dword_ptr[ebp * 4]);
		lea(eax, dword_ptr[eax * 8]);
		lea(eax, dword_ptr[ebp * 8]);
		lea(eax, dword_ptr[eax * 2 + 0x1]);
		lea(eax, dword_ptr[ebp * 2 + 0x1]);
		lea(eax, dword_ptr[eax * 2 + 0x100]);
		lea(eax, dword_ptr[ebp * 2 + 0x100]);
		lea(eax, dword_ptr[eax * 2 + 0x10000]);
		lea(eax, dword_ptr[ebp * 2 + 0x10000]);
		lea(eax, dword_ptr[eax + ecx * 2]);
		lea(eax, dword_ptr[ecx + eax * 2]);
		lea(eax, dword_ptr[esp + ecx * 2]);
		lea(eax, dword_ptr[ebp + ecx * 2]);
		lea(eax, dword_ptr[ecx + ebp * 2]);
		lea(eax, dword_ptr[esp + ebp * 2]);
		lea(eax, dword_ptr[eax + ecx + 0x1]);
		lea(eax, dword_ptr[ecx + eax + 0x1]);
		lea(eax, dword_ptr[esp + ecx + 0x1]);
		lea(eax, dword_ptr[ecx + esp + 0x1]);
		lea(eax, dword_ptr[ebp + ecx + 0x1]);
		lea(eax, dword_ptr[ecx + ebp + 0x1]);
		lea(eax, dword_ptr[esp + ebp + 0x1]);
		lea(eax, dword_ptr[ebp + esp + 0x1]);
		lea(eax, dword_ptr[eax + ecx + 0x100]);
		lea(eax, dword_ptr[ecx + eax + 0x100]);
		lea(eax, dword_ptr[esp + ecx + 0x100]);
		lea(eax, dword_ptr[ecx + esp + 0x100]);
		lea(eax, dword_ptr[ebp + ecx + 0x100]);
		lea(eax, dword_ptr[ecx + ebp + 0x100]);
		lea(eax, dword_ptr[esp + ebp + 0x100]);
		lea(eax, dword_ptr[ebp + esp + 0x100]);
		lea(eax, dword_ptr[eax + ecx + 0x10000]);
		lea(eax, dword_ptr[ecx + eax + 0x10000]);
		lea(eax, dword_ptr[esp + ecx + 0x10000]);
		lea(eax, dword_ptr[ecx + esp + 0x10000]);
		lea(eax, dword_ptr[ebp + ecx + 0x10000]);
		lea(eax, dword_ptr[ecx + ebp + 0x10000]);
		lea(eax, dword_ptr[esp + ebp + 0x10000]);
		lea(eax, dword_ptr[ebp + esp + 0x10000]);
		lea(eax, dword_ptr[eax + ecx * 2 + 0x1]);
		lea(eax, dword_ptr[ecx + eax * 2 + 0x1]);
		lea(eax, dword_ptr[esp + ecx * 2 + 0x1]);
		lea(eax, dword_ptr[ebp + ecx * 2 + 0x1]);
		lea(eax, dword_ptr[ecx + ebp * 2 + 0x1]);
		lea(eax, dword_ptr[esp + ebp * 2 + 0x1]);
		lea(eax, dword_ptr[eax + ecx * 2 + 0x100]);
		lea(eax, dword_ptr[ecx + eax * 2 + 0x100]);
		lea(eax, dword_ptr[esp + ecx * 2 + 0x100]);
		lea(eax, dword_ptr[ebp + ecx * 2 + 0x100]);
		lea(eax, dword_ptr[ecx + ebp * 2 + 0x100]);
		lea(eax, dword_ptr[esp + ebp * 2 + 0x100]);
		lea(eax, dword_ptr[eax + ecx * 2 + 0x10000]);
		lea(eax, dword_ptr[ecx + eax * 2 + 0x10000]);
		lea(eax, dword_ptr[esp + ecx * 2 + 0x10000]);
		lea(eax, dword_ptr[ebp + ecx * 2 + 0x10000]);
		lea(eax, dword_ptr[ecx + ebp * 2 + 0x10000]);
		lea(eax, dword_ptr[esp + ebp * 2 + 0x10000]);
		lea(eax, dword_ptr[eax - 0x1]);
		lea(eax, dword_ptr[eax - 0x100]);
		lea(eax, dword_ptr[eax - 0x10000]);
#ifdef JITASM64
		lea(rax, qword_ptr[rax]);
		lea(rax, qword_ptr[rsp]);
		lea(rax, qword_ptr[rbp]);
		lea(rax, qword_ptr[rax + rcx]);
		lea(rax, qword_ptr[rcx + rax]);
		lea(rax, qword_ptr[rsp + rcx]);
		lea(rax, qword_ptr[rcx + rsp]);
		lea(rax, qword_ptr[rbp + rcx]);
		lea(rax, qword_ptr[rcx + rbp]);
		lea(rax, qword_ptr[rsp + rbp]);
		lea(rax, qword_ptr[rbp + rsp]);
		lea(rax, qword_ptr[rax + 0x1]);
		lea(rax, qword_ptr[rsp + 0x1]);
		lea(rax, qword_ptr[rbp + 0x1]);
		lea(rax, qword_ptr[rax + 0x100]);
		lea(rax, qword_ptr[rsp + 0x100]);
		lea(rax, qword_ptr[rbp + 0x100]);
		lea(rax, qword_ptr[rax + 0x10000]);
		lea(rax, qword_ptr[rsp + 0x10000]);
		lea(rax, qword_ptr[rbp + 0x10000]);
		lea(rax, qword_ptr[rax * 2]);
		lea(rax, qword_ptr[rbp * 2]);
		lea(rax, qword_ptr[rax * 4]);
		lea(rax, qword_ptr[rbp * 4]);
		lea(rax, qword_ptr[rax * 8]);
		lea(rax, qword_ptr[rbp * 8]);
		lea(rax, qword_ptr[rax * 2 + 0x1]);
		lea(rax, qword_ptr[rbp * 2 + 0x1]);
		lea(rax, qword_ptr[rax * 2 + 0x100]);
		lea(rax, qword_ptr[rbp * 2 + 0x100]);
		lea(rax, qword_ptr[rax * 2 + 0x10000]);
		lea(rax, qword_ptr[rbp * 2 + 0x10000]);
		lea(rax, qword_ptr[rax + rcx * 2]);
		lea(rax, qword_ptr[rcx + rax * 2]);
		lea(rax, qword_ptr[rsp + rcx * 2]);
		lea(rax, qword_ptr[rbp + rcx * 2]);
		lea(rax, qword_ptr[rcx + rbp * 2]);
		lea(rax, qword_ptr[rsp + rbp * 2]);
		lea(rax, qword_ptr[rax + rcx + 0x1]);
		lea(rax, qword_ptr[rcx + rax + 0x1]);
		lea(rax, qword_ptr[rsp + rcx + 0x1]);
		lea(rax, qword_ptr[rcx + rsp + 0x1]);
		lea(rax, qword_ptr[rbp + rcx + 0x1]);
		lea(rax, qword_ptr[rcx + rbp + 0x1]);
		lea(rax, qword_ptr[rsp + rbp + 0x1]);
		lea(rax, qword_ptr[rbp + rsp + 0x1]);
		lea(rax, qword_ptr[rax + rcx + 0x100]);
		lea(rax, qword_ptr[rcx + rax + 0x100]);
		lea(rax, qword_ptr[rsp + rcx + 0x100]);
		lea(rax, qword_ptr[rbp + rcx + 0x100]);
		lea(rax, qword_ptr[rcx + rbp + 0x100]);
		lea(rax, qword_ptr[rsp + rbp + 0x100]);
		lea(rax, qword_ptr[rbp + rsp + 0x100]);
		lea(rax, qword_ptr[rax + rcx + 0x10000]);
		lea(rax, qword_ptr[rcx + rax + 0x10000]);
		lea(rax, qword_ptr[rsp + rcx + 0x10000]);
		lea(rax, qword_ptr[rbp + rcx + 0x10000]);
		lea(rax, qword_ptr[rcx + rbp + 0x10000]);
		lea(rax, qword_ptr[rsp + rbp + 0x10000]);
		lea(rax, qword_ptr[rbp + rsp + 0x10000]);
		lea(rax, qword_ptr[rax + rcx * 2 + 0x1]);
		lea(rax, qword_ptr[rcx + rax * 2 + 0x1]);
		lea(rax, qword_ptr[rsp + rcx * 2 + 0x1]);
		lea(rax, qword_ptr[rbp + rcx * 2 + 0x1]);
		lea(rax, qword_ptr[rcx + rbp * 2 + 0x1]);
		lea(rax, qword_ptr[rsp + rbp * 2 + 0x1]);
		lea(rax, qword_ptr[rax + rcx * 2 + 0x100]);
		lea(rax, qword_ptr[rcx + rax * 2 + 0x100]);
		lea(rax, qword_ptr[rsp + rcx * 2 + 0x100]);
		lea(rax, qword_ptr[rbp + rcx * 2 + 0x100]);
		lea(rax, qword_ptr[rcx + rbp * 2 + 0x100]);
		lea(rax, qword_ptr[rsp + rbp * 2 + 0x100]);
		lea(rax, qword_ptr[rax + rcx * 2 + 0x10000]);
		lea(rax, qword_ptr[rcx + rax * 2 + 0x10000]);
		lea(rax, qword_ptr[rsp + rcx * 2 + 0x10000]);
		lea(rax, qword_ptr[rbp + rcx * 2 + 0x10000]);
		lea(rax, qword_ptr[rcx + rbp * 2 + 0x10000]);
		lea(rax, qword_ptr[rsp + rbp * 2 + 0x10000]);
#endif
	}
};

//----------------------------------------
// FLD
//----------------------------------------
extern "C" void masm_test_fld();
struct test_fld : jitasm::function<void, test_fld>
{
	void naked_main()
	{
		fld(real4_ptr[esp]);
		fld(real8_ptr[esp]);
		fld(real10_ptr[esp]);
		fld(st0);
		fld(st7);
#ifdef JITASM64
		fld(real4_ptr[rsp]);
		fld(real8_ptr[rsp]);
		fld(real10_ptr[rsp]);
#endif
	}
};

//----------------------------------------
// JMP
//----------------------------------------
extern "C" void masm_test_jmp();
struct test_jmp : jitasm::function<void, test_jmp>
{
	void naked_main()
	{
		// jump short
		loop("L1");
		loope("L1");
		loopne("L1");
		jmp("L1");
		ja("L1");
		jae("L1");
		jb("L1");
		jbe("L1");
		jc("L1");
#ifdef JITASM64
		jrcxz("L1");
#else
		jcxz("L1");
#endif
		jecxz("L1");
		je("L1");
		jg("L1");
		jge("L1");
		jl("L1");
		jle("L1");
		jna("L1");
		jnae("L1");
		jnb("L1");
		jnbe("L1");
		jnc("L1");
		jne("L1");
		jng("L1");
		jnge("L1");
		jnl("L1");
		jnle("L1");
		jno("L1");
		jnp("L1");
		jns("L1");
		jnz("L1");
		jo("L1");
		jp("L1");
		jpe("L1");
		jpo("L1");
		js("L1");
		jz("L1");
	L("L1");
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		pabsb(xmm0, xmmword_ptr[zsp + zcx + 0x100]);	// 10 bytes
		// jump near
		jmp("L1");
		ja("L1");
		jae("L1");
		jb("L1");
		jbe("L1");
		jc("L1");
		je("L1");
		jg("L1");
		jge("L1");
		jl("L1");
		jle("L1");
		jna("L1");
		jnae("L1");
		jnb("L1");
		jnbe("L1");
		jnc("L1");
		jne("L1");
		jng("L1");
		jnge("L1");
		jnl("L1");
		jnle("L1");
		jno("L1");
		jnp("L1");
		jns("L1");
		jnz("L1");
		jo("L1");
		jp("L1");
		jpe("L1");
		jpo("L1");
		js("L1");
		jz("L1");
	}
};

//----------------------------------------
// MOVSB/MOVSW/MOVSD/MOVSQ
//----------------------------------------
extern "C" void masm_test_movs();
struct test_movs : jitasm::function<void, test_movs>
{
	void naked_main()
	{
		movsb(zdi, zsi);
		movsw(zdi, zsi);
		movsd(zdi, zsi);
		rep_movsb();
		rep_movsw();
		rep_movsd();
#ifdef JITASM64
		movsq(rdi, rsi);
		rep_movsq();
#endif
		lodsb(al, zsi);
		lodsw(ax, zsi);
		lodsd(eax, zsi);
		rep_lodsb(al, zsi, zcx);
		rep_lodsw(ax, zsi, zcx);
		rep_lodsd(eax, zsi, zcx);
#ifdef JITASM64
		lodsq(rax, rsi);
		rep_lodsq(rax, rsi, rcx);
#endif
		stosb(zdi, al);
		stosw(zdi, ax);
		stosd(zdi, eax);
		rep_stosb(zdi, al, zcx);
		rep_stosw(zdi, ax, zcx);
		rep_stosd(zdi, eax, zcx);
#ifdef JITASM64
		stosq(zdi, rax);
		rep_stosq(zdi, rax, rcx);
#endif
		cmpsb();
		cmpsw();
		cmpsd();
#ifdef JITASM64
		cmpsq();
#endif
	}
};

//----------------------------------------
// mov withsp
//----------------------------------------
extern "C" void nasm_test_mov_disp();
struct test_mov_disp : jitasm::function<void, test_mov_disp>
{
	void naked_main()
	{
		mov(al, byte_ptr[1]);
		mov(cl, byte_ptr[1]);
		mov(ax, word_ptr[1]);
		mov(cx, word_ptr[1]);
		mov(eax, dword_ptr[1]);
		mov(ecx, dword_ptr[1]);
		mov(byte_ptr[1], al);
		mov(byte_ptr[1], cl);
		mov(word_ptr[1], ax);
		mov(word_ptr[1], cx);
		mov(dword_ptr[1], eax);
		mov(dword_ptr[1], ecx);
#ifdef JITASM64
		mov(rax, qword_ptr[1]);
		mov(qword_ptr[1], rax);
		mov(rax, qword_ptr[0x100000000LL]);
		mov(qword_ptr[0x100000000LL], rax);
#endif
	}
};

//----------------------------------------
// NEG/NOT
//----------------------------------------
extern "C" void masm_test_neg_not();
struct test_neg_not : jitasm::function<void, test_neg_not>
{
	void naked_main()
	{
		neg(al);
		neg(ax);
		neg(eax);
		neg(byte_ptr[esp]);
		neg(word_ptr[esp]);
		neg(dword_ptr[esp]);
		not(al);
		not(ax);
		not(eax);
		not(byte_ptr[esp]);
		not(word_ptr[esp]);
		not(dword_ptr[esp]);
#ifdef JITASM64
		neg(r8w);
		neg(rax);
		neg(r8);
		neg(qword_ptr[rsp]);
		not(r8w);
		not(rax);
		not(r8);
		not(qword_ptr[rsp]);
#endif
	}
};

//----------------------------------------
// DIV/IDIV/MUL
//----------------------------------------
extern "C" void masm_test_div_idiv_mul();
struct test_div_idiv_mul : jitasm::function<void, test_div_idiv_mul>
{
	void naked_main()
	{
		div(al);
		div(ax);
		div(eax);
		div(byte_ptr[esp]);
		div(word_ptr[esp]);
		div(dword_ptr[esp]);
		idiv(al);
		idiv(ax);
		idiv(eax);
		idiv(byte_ptr[esp]);
		idiv(word_ptr[esp]);
		idiv(dword_ptr[esp]);
		mul(al);
		mul(ax);
		mul(eax);
		mul(byte_ptr[esp]);
		mul(word_ptr[esp]);
		mul(dword_ptr[esp]);
#ifdef JITASM64
		div(r8w);
		div(rax);
		div(r8);
		div(qword_ptr[rsp]);
		idiv(r8w);
		idiv(rax);
		idiv(r8);
		idiv(qword_ptr[rsp]);
		mul(r8w);
		mul(rax);
		mul(r8);
		mul(qword_ptr[rsp]);
#endif
	}
};

//----------------------------------------
// IMUL
//----------------------------------------
extern "C" void masm_test_imul();
struct test_imul : jitasm::function<void, test_imul>
{
	void naked_main()
	{
		imul(al);
		imul(ax);
		imul(eax);
		imul(byte_ptr[esp]);
		imul(word_ptr[esp]);
		imul(dword_ptr[esp]);
		imul(ax, ax);
		imul(ax, word_ptr[esp]);
		imul(eax, eax);
		imul(eax, dword_ptr[esp]);
		imul(ax, ax, 0x1);
		imul(ax, ax, (jitasm::uint16) -0x1);
		imul(ax, ax, 0x100);
		imul(eax, eax, 0x1);
		imul(eax, eax, (jitasm::uint32) -0x1);
		imul(eax, eax, 0x100);
#ifdef JITASM64
		imul(r8w);
		imul(rax);
		imul(r8);
		imul(qword_ptr[rsp]);
		imul(rax, rax);
		imul(rax, qword_ptr[rsp]);
		imul(rax, rax, 0x1);
		imul(rax, rax, (jitasm::uint32) -0x1);
		imul(rax, rax, 0x100);
#endif
	}
};

//----------------------------------------
// FST/FSTP
//----------------------------------------
extern "C" void masm_test_fst();
struct test_fst : jitasm::function<void, test_fst>
{
	void naked_main()
	{
		fst(real4_ptr[esp]);
		fst(real8_ptr[esp]);
		fst(st0);
		fst(st7);
		fstp(real4_ptr[esp]);
		fstp(real8_ptr[esp]);
		fstp(real10_ptr[esp]);
		fstp(st0);
		fstp(st7);
#ifdef JITASM64
		fst(real4_ptr[rsp]);
		fst(real8_ptr[rsp]);
		fstp(real4_ptr[rsp]);
		fstp(real8_ptr[rsp]);
		fstp(real10_ptr[rsp]);
#endif
	}
};

//----------------------------------------
// setcc
//----------------------------------------
extern "C" void masm_test_setcc();
struct test_setcc : jitasm::function<void, test_setcc>
{
	void naked_main()
	{
		seta(bl);
		seta(byte_ptr[esp]);
		setae(bl);
		setae(byte_ptr[esp]);
		setb(bl);
		setb(byte_ptr[esp]);
		setbe(bl);
		setbe(byte_ptr[esp]);
		setc(bl);
		setc(byte_ptr[esp]);
		sete(bl);
		sete(byte_ptr[esp]);
		setg(bl);
		setg(byte_ptr[esp]);
		setge(bl);
		setge(byte_ptr[esp]);
		setl(bl);
		setl(byte_ptr[esp]);
		setle(bl);
		setle(byte_ptr[esp]);
		setna(bl);
		setna(byte_ptr[esp]);
		setnae(bl);
		setnae(byte_ptr[esp]);
		setnb(bl);
		setnb(byte_ptr[esp]);
		setnbe(bl);
		setnbe(byte_ptr[esp]);
		setnc(bl);
		setnc(byte_ptr[esp]);
		setne(bl);
		setne(byte_ptr[esp]);
		setng(bl);
		setng(byte_ptr[esp]);
		setnge(bl);
		setnge(byte_ptr[esp]);
		setnl(bl);
		setnl(byte_ptr[esp]);
		setnle(bl);
		setnle(byte_ptr[esp]);
		setno(bl);
		setno(byte_ptr[esp]);
		setnp(bl);
		setnp(byte_ptr[esp]);
		setns(bl);
		setns(byte_ptr[esp]);
		setnz(bl);
		setnz(byte_ptr[esp]);
		seto(bl);
		seto(byte_ptr[esp]);
		setp(bl);
		setp(byte_ptr[esp]);
		setpe(bl);
		setpe(byte_ptr[esp]);
		setpo(bl);
		setpo(byte_ptr[esp]);
		sets(bl);
		sets(byte_ptr[esp]);
		setz(bl);
		setz(byte_ptr[esp]);
	}
};

//----------------------------------------
// cmovcc
//----------------------------------------
extern "C" void masm_test_cmovcc();
struct test_cmovcc : jitasm::function<void, test_cmovcc>
{
	void naked_main()
	{
		cmova(bx, dx);
		cmova(bx, word_ptr[esp]);
		cmovae(bx, dx);
		cmovae(bx, word_ptr[esp]);
		cmovb(bx, dx);
		cmovb(bx, word_ptr[esp]);
		cmovbe(bx, dx);
		cmovbe(bx, word_ptr[esp]);
		cmovc(bx, dx);
		cmovc(bx, word_ptr[esp]);
		cmove(bx, dx);
		cmove(bx, word_ptr[esp]);
		cmovg(bx, dx);
		cmovg(bx, word_ptr[esp]);
		cmovge(bx, dx);
		cmovge(bx, word_ptr[esp]);
		cmovl(bx, dx);
		cmovl(bx, word_ptr[esp]);
		cmovle(bx, dx);
		cmovle(bx, word_ptr[esp]);
		cmovna(bx, dx);
		cmovna(bx, word_ptr[esp]);
		cmovnae(bx, dx);
		cmovnae(bx, word_ptr[esp]);
		cmovnb(bx, dx);
		cmovnb(bx, word_ptr[esp]);
		cmovnbe(bx, dx);
		cmovnbe(bx, word_ptr[esp]);
		cmovnc(bx, dx);
		cmovnc(bx, word_ptr[esp]);
		cmovne(bx, dx);
		cmovne(bx, word_ptr[esp]);
		cmovng(bx, dx);
		cmovng(bx, word_ptr[esp]);
		cmovnge(bx, dx);
		cmovnge(bx, word_ptr[esp]);
		cmovnl(bx, dx);
		cmovnl(bx, word_ptr[esp]);
		cmovnle(bx, dx);
		cmovnle(bx, word_ptr[esp]);
		cmovno(bx, dx);
		cmovno(bx, word_ptr[esp]);
		cmovnp(bx, dx);
		cmovnp(bx, word_ptr[esp]);
		cmovns(bx, dx);
		cmovns(bx, word_ptr[esp]);
		cmovnz(bx, dx);
		cmovnz(bx, word_ptr[esp]);
		cmovo(bx, dx);
		cmovo(bx, word_ptr[esp]);
		cmovp(bx, dx);
		cmovp(bx, word_ptr[esp]);
		cmovpe(bx, dx);
		cmovpe(bx, word_ptr[esp]);
		cmovpo(bx, dx);
		cmovpo(bx, word_ptr[esp]);
		cmovs(bx, dx);
		cmovs(bx, word_ptr[esp]);
		cmovz(bx, dx);
		cmovz(bx, word_ptr[esp]);
		cmova(ebx, edx);
		cmova(ebx, dword_ptr[esp]);
		cmovae(ebx, edx);
		cmovae(ebx, dword_ptr[esp]);
		cmovb(ebx, edx);
		cmovb(ebx, dword_ptr[esp]);
		cmovbe(ebx, edx);
		cmovbe(ebx, dword_ptr[esp]);
		cmovc(ebx, edx);
		cmovc(ebx, dword_ptr[esp]);
		cmove(ebx, edx);
		cmove(ebx, dword_ptr[esp]);
		cmovg(ebx, edx);
		cmovg(ebx, dword_ptr[esp]);
		cmovge(ebx, edx);
		cmovge(ebx, dword_ptr[esp]);
		cmovl(ebx, edx);
		cmovl(ebx, dword_ptr[esp]);
		cmovle(ebx, edx);
		cmovle(ebx, dword_ptr[esp]);
		cmovna(ebx, edx);
		cmovna(ebx, dword_ptr[esp]);
		cmovnae(ebx, edx);
		cmovnae(ebx, dword_ptr[esp]);
		cmovnb(ebx, edx);
		cmovnb(ebx, dword_ptr[esp]);
		cmovnbe(ebx, edx);
		cmovnbe(ebx, dword_ptr[esp]);
		cmovnc(ebx, edx);
		cmovnc(ebx, dword_ptr[esp]);
		cmovne(ebx, edx);
		cmovne(ebx, dword_ptr[esp]);
		cmovng(ebx, edx);
		cmovng(ebx, dword_ptr[esp]);
		cmovnge(ebx, edx);
		cmovnge(ebx, dword_ptr[esp]);
		cmovnl(ebx, edx);
		cmovnl(ebx, dword_ptr[esp]);
		cmovnle(ebx, edx);
		cmovnle(ebx, dword_ptr[esp]);
		cmovno(ebx, edx);
		cmovno(ebx, dword_ptr[esp]);
		cmovnp(ebx, edx);
		cmovnp(ebx, dword_ptr[esp]);
		cmovns(ebx, edx);
		cmovns(ebx, dword_ptr[esp]);
		cmovnz(ebx, edx);
		cmovnz(ebx, dword_ptr[esp]);
		cmovo(ebx, edx);
		cmovo(ebx, dword_ptr[esp]);
		cmovp(ebx, edx);
		cmovp(ebx, dword_ptr[esp]);
		cmovpe(ebx, edx);
		cmovpe(ebx, dword_ptr[esp]);
		cmovpo(ebx, edx);
		cmovpo(ebx, dword_ptr[esp]);
		cmovs(ebx, edx);
		cmovs(ebx, dword_ptr[esp]);
		cmovz(ebx, edx);
		cmovz(ebx, dword_ptr[esp]);
#ifdef JITASM64
		cmova(rbx, rdx);
		cmova(rbx, qword_ptr[esp]);
		cmovae(rbx, rdx);
		cmovae(rbx, qword_ptr[esp]);
		cmovb(rbx, rdx);
		cmovb(rbx, qword_ptr[esp]);
		cmovbe(rbx, rdx);
		cmovbe(rbx, qword_ptr[esp]);
		cmovc(rbx, rdx);
		cmovc(rbx, qword_ptr[esp]);
		cmove(rbx, rdx);
		cmove(rbx, qword_ptr[esp]);
		cmovg(rbx, rdx);
		cmovg(rbx, qword_ptr[esp]);
		cmovge(rbx, rdx);
		cmovge(rbx, qword_ptr[esp]);
		cmovl(rbx, rdx);
		cmovl(rbx, qword_ptr[esp]);
		cmovle(rbx, rdx);
		cmovle(rbx, qword_ptr[esp]);
		cmovna(rbx, rdx);
		cmovna(rbx, qword_ptr[esp]);
		cmovnae(rbx, rdx);
		cmovnae(rbx, qword_ptr[esp]);
		cmovnb(rbx, rdx);
		cmovnb(rbx, qword_ptr[esp]);
		cmovnbe(rbx, rdx);
		cmovnbe(rbx, qword_ptr[esp]);
		cmovnc(rbx, rdx);
		cmovnc(rbx, qword_ptr[esp]);
		cmovne(rbx, rdx);
		cmovne(rbx, qword_ptr[esp]);
		cmovng(rbx, rdx);
		cmovng(rbx, qword_ptr[esp]);
		cmovnge(rbx, rdx);
		cmovnge(rbx, qword_ptr[esp]);
		cmovnl(rbx, rdx);
		cmovnl(rbx, qword_ptr[esp]);
		cmovnle(rbx, rdx);
		cmovnle(rbx, qword_ptr[esp]);
		cmovno(rbx, rdx);
		cmovno(rbx, qword_ptr[esp]);
		cmovnp(rbx, rdx);
		cmovnp(rbx, qword_ptr[esp]);
		cmovns(rbx, rdx);
		cmovns(rbx, qword_ptr[esp]);
		cmovnz(rbx, rdx);
		cmovnz(rbx, qword_ptr[esp]);
		cmovo(rbx, rdx);
		cmovo(rbx, qword_ptr[esp]);
		cmovp(rbx, rdx);
		cmovp(rbx, qword_ptr[esp]);
		cmovpe(rbx, rdx);
		cmovpe(rbx, qword_ptr[esp]);
		cmovpo(rbx, rdx);
		cmovpo(rbx, qword_ptr[esp]);
		cmovs(rbx, rdx);
		cmovs(rbx, qword_ptr[esp]);
		cmovz(rbx, rdx);
		cmovz(rbx, qword_ptr[esp]);
#endif
	}
};

//----------------------------------------
// General-Purpose Instructions B~
//----------------------------------------
extern "C" void masm_test_gpi_b();
struct test_gpi_b : jitasm::function<void, test_gpi_b>
{
	void naked_main()
	{
		bsf(bx, dx);
		bsf(bx, word_ptr[esp]);
		bsf(ebx, edx);
		bsf(ebx, dword_ptr[esp]);
#ifdef JITASM64
		bsf(rbx, r11);
		bsf(rbx, qword_ptr[rsp]);
#endif
		bsr(bx, dx);
		bsr(bx, word_ptr[esp]);
		bsr(ebx, edx);
		bsr(ebx, dword_ptr[esp]);
#ifdef JITASM64
		bsr(rbx, r11);
		bsr(rbx, qword_ptr[rsp]);
#endif
		bswap(ebx);
#ifdef JITASM64
		bswap(ebx);
#endif
		bt(bx, dx);
		bt(word_ptr[eax], dx);
		bt(ebx, edx);
		bt(dword_ptr[ecx], edx);
		bt(bx, 0x55);
		bt(word_ptr[eax], 0x55);
		bt(ebx, 0x55);
		bt(dword_ptr[ecx], 0x55);
#ifdef JITASM64
		bt(rbx, r11);
		bt(qword_ptr[ecx], r11);
		bt(rbx, 0x55);
		bt(qword_ptr[ecx], 0x55);
#endif
		btc(bx, dx);
		btc(word_ptr[eax], dx);
		btc(ebx, edx);
		btc(dword_ptr[ecx], edx);
		btc(bx, 0x55);
		btc(word_ptr[eax], 0x55);
		btc(ebx, 0x55);
		btc(dword_ptr[ecx], 0x55);
#ifdef JITASM64
		btc(rbx, r11);
		btc(qword_ptr[ecx], r11);
		btc(rbx, 0x55);
		btc(qword_ptr[ecx], 0x55);
#endif
		btr(bx, dx);
		btr(word_ptr[eax], dx);
		btr(ebx, edx);
		btr(dword_ptr[ecx], edx);
		btr(bx, 0x55);
		btr(word_ptr[eax], 0x55);
		btr(ebx, 0x55);
		btr(dword_ptr[ecx], 0x55);
#ifdef JITASM64
		btr(rbx, r11);
		btr(qword_ptr[ecx], r11);
		btr(rbx, 0x55);
		btr(qword_ptr[ecx], 0x55);
#endif
		bts(bx, dx);
		bts(word_ptr[eax], dx);
		bts(ebx, edx);
		bts(dword_ptr[ecx], edx);
		bts(bx, 0x55);
		bts(word_ptr[eax], 0x55);
		bts(ebx, 0x55);
		bts(dword_ptr[ecx], 0x55);
#ifdef JITASM64
		bts(rbx, r11);
		bts(qword_ptr[ecx], r11);
		bts(rbx, 0x55);
		bts(qword_ptr[ecx], 0x55);
#endif
#ifndef JITASM64
		call(bx);
		call(ebx);
#else
		call(rbx);
#endif
		cbw();
		cwde();
#ifdef JITASM64
		cdqe();
#endif
		clc();
		cld();
		cli();
#ifdef JITASM64
		clts();
#endif
		cmc();
		cmpxchg(bl, dl, al);
		cmpxchg(byte_ptr[esp], dl, al);
		cmpxchg(bx, dx, ax);
		cmpxchg(word_ptr[eax], dx, ax);
		cmpxchg(ebx, edx, eax);
		cmpxchg(dword_ptr[ecx], edx, eax);
#ifdef JITASM64
		cmpxchg(rbx, r11, rax);
		cmpxchg(qword_ptr[ecx], r11, rax);
#endif
		cmpxchg8b(qword_ptr[ecx]);
#ifdef JITASM64
		cmpxchg16b(xmmword_ptr[esp]);
#endif
		cpuid();
		cwd();
		cdq();
#ifdef JITASM64
		cqo();
#endif
	}
};

//----------------------------------------
// General-Purpose Instructions E~
//----------------------------------------
extern "C" void masm_test_gpi_e();
struct test_gpi_e : jitasm::function<void, test_gpi_e>
{
	void naked_main()
	{
		enter(0x100, 0);
		enter(0x100, 1);
		enter(0x100, 2);
		hlt();
		in(al, 0xAA);
		in(ax, 0xAA);
		in(eax, 0xAA);
		in(al, dx);
		in(ax, dx);
		in(eax, dx);
		insb(zdi, dx);
		insw(zdi, dx);
		insd(zdi, dx);
		rep_insb(zdi, dx, zcx);
		rep_insw(zdi, dx, zcx);
		rep_insd(zdi, dx, zcx);
		int3();
		intn(1);
#ifndef JITASM64
		into();
#endif
		invd();
		invlpg(dword_ptr[esp]);
		iret();
		iretd();
#ifdef JITASM64
		iretq();
#endif
		lar(bx, dx);
		lar(bx, word_ptr[esp]);
		lar(ebx, edx);
		lar(ebx, word_ptr[esp]);
#ifdef JITASM64
		lar(rbx, rdx);
		lar(rbx, word_ptr[esp]);
#endif
		leave();
		lldt(cx);
		lldt(word_ptr[ecx]);
		lmsw(cx);
		lmsw(word_ptr[ecx]);
		//movbe(bx, word_ptr[esp]);
		//movbe(ebx, dword_ptr[esp]);
		//movbe(word_ptr[esp], bx);
		//movbe(dword_ptr[esp], ebx);
#ifdef JITASM64
		//movbe(rbx, qword_ptr[esp]);
		//movbe(qword_ptr[esp], rbx);
#endif
		movsx(bx, dl);
		movsx(bx, byte_ptr[esp]);
		movsx(ebx, dl);
		movsx(ebx, byte_ptr[esp]);
		movsx(ebx, dx);
		movsx(ebx, word_ptr[esp]);
#ifdef JITASM64
		movsx(rbx, dl);
		movsx(rbx, byte_ptr[esp]);
		movsx(rbx, dx);
		movsx(rbx, word_ptr[esp]);
		movsxd(rbx, edx);
		movsxd(rbx, dword_ptr[esp]);
#endif
		nop();
		out(0xAA, al);
		out(0xAA, ax);
		out(0xAA, eax);
		out(dx, al);
		out(dx, ax);
		out(dx, eax);
		outsb(dx, zsi);
		outsw(dx, zsi);
		outsd(dx, zsi);
		rep_outsb(dx, zsi, zcx);
		rep_outsw(dx, zsi, zcx);
		rep_outsd(dx, zsi, zcx);
#ifndef JITASM64
		popa();
		popad();
#endif
		popf();
#ifndef JITASM64
		popfd();
#else
		popfq();
#endif
#ifndef JITASM64
		pusha();
		pushad();
#endif
		pushf();
#ifndef JITASM64
		pushfd();
#else
		pushfq();
#endif
		rdmsr();
		rdpmc();
		rdtsc();
		ret();
		ret(1);
		ret((jitasm::uint16) -1);
		rsm();
		scasb();
		scasw();
		scasd();
#ifdef JITASM64
		scasq();
#endif
		sgdt(dword_ptr[esp]);
		shld(bx, dx, 1);
		shld(word_ptr[esp], dx, 1);
		shld(bx, dx, cl);
		shld(word_ptr[esp], dx, cl);
		shld(ebx, edx, 1);
		shld(dword_ptr[esp], edx, 1);
		shld(ebx, edx, cl);
		shld(dword_ptr[esp], edx, cl);
#ifdef JITASM64
		shld(rbx, rdx, 1);
		shld(qword_ptr[esp], rdx, 1);
		shld(rbx, rdx, cl);
		shld(qword_ptr[esp], rdx, cl);
#endif
		shrd(bx, dx, 1);
		shrd(word_ptr[esp], dx, 1);
		shrd(bx, dx, cl);
		shrd(word_ptr[esp], dx, cl);
		shrd(ebx, edx, 1);
		shrd(dword_ptr[esp], edx, 1);
		shrd(ebx, edx, cl);
		shrd(dword_ptr[esp], edx, cl);
#ifdef JITASM64
		shrd(rbx, rdx, 1);
		shrd(qword_ptr[esp], rdx, 1);
		shrd(rbx, rdx, cl);
		shrd(qword_ptr[esp], rdx, cl);
#endif
		sidt(dword_ptr[esp]);
		sldt(bx);
		sldt(word_ptr[esp]);
#ifdef JITASM64
		sldt(r8);
#endif
		smsw(bx);
		smsw(word_ptr[esp]);
#ifdef JITASM64
		smsw(r8);
#endif
		stc();
		std();
		sti();
#ifndef JITASM64
		sysenter();
		sysexit();
#else
		swapgs();
		syscall();
		sysret();
#endif
		ud2();
		verr(bx);
		verr(word_ptr[esp]);
		verw(bx);
		verw(word_ptr[esp]);
		wait();
		xadd(bl, dl);
		xadd(byte_ptr[esp], dl);
		xadd(bx, dx);
		xadd(word_ptr[esp], dx);
		xadd(ebx, edx);
		xadd(dword_ptr[esp], edx);
#ifdef JITASM64
		xadd(rbx, rdx);
		xadd(qword_ptr[esp], rdx);
#endif
		wbinvd();
		wrmsr();
		xgetbv();
		xlatb();
	}
};

//----------------------------------------
// FPU
//----------------------------------------
extern "C" void masm_test_fpu();
struct test_fpu : jitasm::function<void, test_fpu>
{
	void naked_main()
	{
		f2xm1();
		fabs();
		fadd(st0, st2);
		fadd(st1, st0);
		fadd(real4_ptr[ebx]);
		fadd(real8_ptr[edx]);
		faddp();
		faddp(st1, st0);
		fiadd(word_ptr[esp]);
		fiadd(real4_ptr[ebx]);
		fbld(real10_ptr[edi]);
		fbstp(real10_ptr[edi]);
		fchs();
		fclex();
		fnclex();
		fcmovb(st0, st2);
		fcmovbe(st0, st2);
		fcmove(st0, st2);
		fcmovnb(st0, st2);
		fcmovnbe(st0, st2);
		fcmovne(st0, st2);
		fcmovnu(st0, st2);
		fcmovu(st0, st2);
		fcom();
		fcom(st1);
		fcom(real4_ptr[ebx]);
		fcom(real8_ptr[edx]);
		fcomp();
		fcomp(st1);
		fcomp(real4_ptr[ebx]);
		fcomp(real8_ptr[edx]);
		fcompp();
		fcomi(st0, st2);
		fcomip(st0, st2);
		fcos();
		fdecstp();
		fdiv(st0, st2);
		fdiv(st1, st0);
		fdiv(real4_ptr[ebx]);
		fdiv(real8_ptr[edx]);
		fdivp();
		fdivp(st1, st0);
		fidiv(word_ptr[esp]);
		fidiv(real4_ptr[ebx]);
		fdivr(st0, st2);
		fdivr(st1, st0);
		fdivr(real4_ptr[ebx]);
		fdivr(real8_ptr[edx]);
		fdivrp();
		fdivrp(st1, st0);
		fidivr(word_ptr[esp]);
		fidivr(real4_ptr[ebx]);
		ffree(st1);
		ficom(word_ptr[esp]);
		ficom(real4_ptr[ebx]);
		ficomp(word_ptr[esp]);
		ficomp(real4_ptr[ebx]);
		fild(word_ptr[esp]);
		fild(real4_ptr[ebx]);
		fild(real8_ptr[edx]);
		fincstp();
		finit();
		fninit();
		fist(word_ptr[esp]);
		fist(real4_ptr[ebx]);
		fistp(word_ptr[esp]);
		fistp(real4_ptr[ebx]);
		fistp(real8_ptr[edx]);
		fisttp(word_ptr[esp]);
		fisttp(real4_ptr[ebx]);
		fisttp(real8_ptr[edx]);
		fld(real4_ptr[ecx]);
		fld(real8_ptr[esi]);
		fld(real10_ptr[esp]);
		fld(st2);
		fld1();
		fldcw(word_ptr[ebp]);
		fldenv(m28byte_ptr[ebp]);
		fldl2e();
		fldl2t();
		fldlg2();
		fldln2();
		fldpi();
		fldz();
		fmul(st0, st2);
		fmul(st1, st0);
		fmul(real4_ptr[ebx]);
		fmul(real8_ptr[edx]);
		fmulp();
		fmulp(st1, st0);
		fimul(word_ptr[esp]);
		fimul(real4_ptr[ebx]);
		fnop();
		fpatan();
		fprem();
		fprem1();
		fptan();
		frndint();
		frstor(m108byte_ptr[ebp]);
		fsave(m108byte_ptr[edi]);
		fnsave(m108byte_ptr[edi]);
		fscale();
		fsin();
		fsincos();
		fsqrt();
		fst(real4_ptr[ebx]);
		fst(real8_ptr[edx]);
		fst(st1);
		fstp(st1);
		fstp(real4_ptr[ebx]);
		fstp(real8_ptr[edx]);
		fstp(real10_ptr[edi]);
		fstcw(word_ptr[esp]);
		fnstcw(word_ptr[esp]);
		fstenv(m28byte_ptr[ebp]);
		fnstenv(m28byte_ptr[ebp]);
		fstsw(word_ptr[esp]);
		fstsw(ax);
		fnstsw(word_ptr[esp]);
		fnstsw(ax);
		fsub(st0, st2);
		fsub(st1, st0);
		fsub(real4_ptr[ebx]);
		fsub(real8_ptr[edx]);
		fsubp();
		fsubp(st1, st0);
		fisub(word_ptr[esp]);
		fisub(real4_ptr[ebx]);
		fsubr(st0, st2);
		fsubr(st1, st0);
		fsubr(real4_ptr[ebx]);
		fsubr(real8_ptr[edx]);
		fsubrp();
		fsubrp(st1, st0);
		fisubr(word_ptr[esp]);
		fisubr(real4_ptr[ebx]);
		ftst();
		fucom();
		fucom(st1);
		fucomp();
		fucomp(st1);
		fucompp();
		fucomi(st0, st2);
		fucomip(st0, st2);
		fwait();
		fxam();
		fxch();
		fxch(st1);
		fxrstor(m512byte_ptr[esp]);
		fxsave(m512byte_ptr[esp]);
		fxtract();
		fyl2x();
		fyl2xp1();
	}
};

//----------------------------------------
// MMX
//----------------------------------------
extern "C" void masm_test_mmx();
struct test_mmx : jitasm::function<void, test_mmx>
{
	void naked_main()
	{
		emms();
		packsswb(mm1, mm2);
		packsswb(mm1, qword_ptr[ebp]);
		packssdw(mm1, mm2);
		packssdw(mm1, qword_ptr[ebp]);
		packuswb(mm1, mm2);
		packuswb(mm1, qword_ptr[ebp]);
		paddb(mm1, mm2);
		paddb(mm1, qword_ptr[ebp]);
		paddw(mm1, mm2);
		paddw(mm1, qword_ptr[ebp]);
		paddd(mm1, mm2);
		paddd(mm1, qword_ptr[ebp]);
		paddsb(mm1, mm2);
		paddsb(mm1, qword_ptr[ebp]);
		paddsw(mm1, mm2);
		paddsw(mm1, qword_ptr[ebp]);
		paddusb(mm1, mm2);
		paddusb(mm1, qword_ptr[ebp]);
		paddusw(mm1, mm2);
		paddusw(mm1, qword_ptr[ebp]);
		pand(mm1, mm2);
		pand(mm1, qword_ptr[ebp]);
		pandn(mm1, mm2);
		pandn(mm1, qword_ptr[ebp]);
		pcmpeqb(mm1, mm2);
		pcmpeqb(mm1, qword_ptr[ebp]);
		pcmpeqw(mm1, mm2);
		pcmpeqw(mm1, qword_ptr[ebp]);
		pcmpeqd(mm1, mm2);
		pcmpeqd(mm1, qword_ptr[ebp]);
		pcmpgtb(mm1, mm2);
		pcmpgtb(mm1, qword_ptr[ebp]);
		pcmpgtw(mm1, mm2);
		pcmpgtw(mm1, qword_ptr[ebp]);
		pcmpgtd(mm1, mm2);
		pcmpgtd(mm1, qword_ptr[ebp]);
		pmaddwd(mm1, mm2);
		pmaddwd(mm1, qword_ptr[ebp]);
		pmulhw(mm1, mm2);
		pmulhw(mm1, qword_ptr[ebp]);
		pmullw(mm1, mm2);
		pmullw(mm1, qword_ptr[ebp]);
		por(mm1, mm2);
		por(mm1, qword_ptr[ebp]);
		psllw(mm1, mm3);
		psllw(mm1, qword_ptr[ebp + ecx]);
		psllw(mm1, 2);
		pslld(mm1, mm3);
		pslld(mm1, qword_ptr[ebp + ecx]);
		pslld(mm1, 2);
		psllq(mm1, mm3);
		psllq(mm1, qword_ptr[ebp + ecx]);
		psllq(mm1, 2);
		psraw(mm1, mm3);
		psraw(mm1, qword_ptr[ebp + ecx]);
		psraw(mm1, 2);
		psrad(mm1, mm3);
		psrad(mm1, qword_ptr[ebp + ecx]);
		psrad(mm1, 2);
		psrlw(mm1, mm3);
		psrlw(mm1, qword_ptr[ebp + ecx]);
		psrlw(mm1, 2);
		psrld(mm1, mm3);
		psrld(mm1, qword_ptr[ebp + ecx]);
		psrld(mm1, 2);
		psrlq(mm1, mm3);
		psrlq(mm1, qword_ptr[ebp + ecx]);
		psrlq(mm1, 2);
		psubb(mm1, mm2);
		psubb(mm1, qword_ptr[ebp]);
		psubw(mm1, mm2);
		psubw(mm1, qword_ptr[ebp]);
		psubd(mm1, mm2);
		psubd(mm1, qword_ptr[ebp]);
		psubsb(mm1, mm2);
		psubsb(mm1, qword_ptr[ebp]);
		psubsw(mm1, mm2);
		psubsw(mm1, qword_ptr[ebp]);
		psubusb(mm1, mm2);
		psubusb(mm1, qword_ptr[ebp]);
		psubusw(mm1, mm2);
		psubusw(mm1, qword_ptr[ebp]);
		punpckhbw(mm2, mm3);
		punpckhbw(mm2, qword_ptr[esp]);
		punpckhwd(mm2, mm3);
		punpckhwd(mm2, qword_ptr[esp]);
		punpckhdq(mm2, mm3);
		punpckhdq(mm2, qword_ptr[esp]);
		punpcklbw(mm2, mm3);
		punpcklbw(mm2, dword_ptr[esp]);
		punpcklwd(mm2, mm3);
		punpcklwd(mm2, dword_ptr[esp]);
		punpckldq(mm2, mm3);
		punpckldq(mm2, dword_ptr[esp]);
		pxor(mm2, mm3);
		pxor(mm2, qword_ptr[esp]);
#ifdef JITASM64
		packsswb(mm1, qword_ptr[r8]);
		packssdw(mm1, qword_ptr[r8]);
		packuswb(mm1, qword_ptr[r8]);
		paddb(mm1, qword_ptr[r8]);
		paddw(mm1, qword_ptr[r8]);
		paddd(mm1, qword_ptr[r8]);
		paddsb(mm1, qword_ptr[r8]);
		paddsw(mm1, qword_ptr[r8]);
		paddusb(mm1, qword_ptr[r8]);
		paddusw(mm1, qword_ptr[r8]);
		pand(mm1, qword_ptr[r8]);
		pandn(mm1, qword_ptr[r8]);
		pcmpeqb(mm1, qword_ptr[r8]);
		pcmpeqw(mm1, qword_ptr[r8]);
		pcmpeqd(mm1, qword_ptr[r8]);
		pcmpgtb(mm1, qword_ptr[r8]);
		pcmpgtw(mm1, qword_ptr[r8]);
		pcmpgtd(mm1, qword_ptr[r8]);
		pmaddwd(mm1, qword_ptr[r8]);
		pmulhw(mm1, qword_ptr[r8]);
		pmullw(mm1, qword_ptr[r8]);
		por(mm1, qword_ptr[r8]);
		psllw(mm1, qword_ptr[r8 + rcx]);
		pslld(mm1, qword_ptr[r8 + rcx]);
		psllq(mm1, qword_ptr[r8 + rcx]);
		psraw(mm1, qword_ptr[r8 + rcx]);
		psrad(mm1, qword_ptr[r8 + rcx]);
		psrlw(mm1, qword_ptr[r8 + rcx]);
		psrld(mm1, qword_ptr[r8 + rcx]);
		psrlq(mm1, qword_ptr[r8 + rcx]);
		psubb(mm1, qword_ptr[r8]);
		psubw(mm1, qword_ptr[r8]);
		psubd(mm1, qword_ptr[r8]);
		psubsb(mm1, qword_ptr[r8]);
		psubsw(mm1, qword_ptr[r8]);
		psubusb(mm1, qword_ptr[r8]);
		psubusw(mm1, qword_ptr[r8]);
		punpckhbw(mm2, qword_ptr[rsp]);
		punpckhwd(mm2, qword_ptr[rsp]);
		punpckhdq(mm2, qword_ptr[rsp]);
		punpcklbw(mm2, dword_ptr[rsp]);
		punpcklwd(mm2, dword_ptr[rsp]);
		punpckldq(mm2, dword_ptr[rsp]);
		pxor(mm2, qword_ptr[rsp]);
#endif
	}
};

//----------------------------------------
// MMX2
//----------------------------------------
extern "C" void masm_test_mmx2();
struct test_mmx2 : jitasm::function<void, test_mmx2>
{
	void naked_main()
	{
		pavgb(mm1, mm2);
		pavgb(mm1, qword_ptr[ebp]);
		pavgw(mm1, mm2);
		pavgw(mm1, qword_ptr[ebp]);
		pextrw(ecx, mm2, 1);
		pinsrw(mm1, ecx, 2);
		pinsrw(mm1, word_ptr[esp], 1);
		pmaxsw(mm1, mm2);
		pmaxsw(mm1, qword_ptr[ebp]);
		pmaxub(mm1, mm2);
		pmaxub(mm1, qword_ptr[ebp]);
		pminsw(mm1, mm2);
		pminsw(mm1, qword_ptr[ebp]);
		pminub(mm1, mm2);
		pminub(mm1, qword_ptr[ebp]);
		pmovmskb(eax, mm2);
		pmulhuw(mm1, mm2);
		pmulhuw(mm1, qword_ptr[ebp]);
		psadbw(mm1, mm2);
		psadbw(mm1, qword_ptr[ebp]);
		pshufw(mm1, mm2, 0x10);
		pshufw(mm1, qword_ptr[ebp], 1);
#ifdef JITASM64
		pavgb(mm1, qword_ptr[rbp]);
		pavgw(mm1, qword_ptr[rbp]);
		pextrw(rax, mm2, 2);
		pextrw(r9, mm2, 3);
		pextrw(r10d, mm2, 0);
		pinsrw(mm1, rcx, 3);
		pinsrw(mm1, r9, 0);
		pinsrw(mm1, r10d, 1);
		pmaxsw(mm1, qword_ptr[rbp]);
		pmaxub(mm1, qword_ptr[rbp]);
		pminsw(mm1, qword_ptr[rbp]);
		pminub(mm1, qword_ptr[rbp]);
		pmovmskb(rcx, mm2);
		pmovmskb(r9, mm2);
		pmulhuw(mm1, qword_ptr[rbp]);
		psadbw(mm1, qword_ptr[rbp]);
		pshufw(mm1, qword_ptr[r9], 1);
#endif
	}
};

//----------------------------------------
// SSE
//----------------------------------------
extern "C" void masm_test_sse();
struct test_sse : jitasm::function<void, test_sse>
{
	void naked_main()
	{
		addps(xmm1, xmm2);
		addps(xmm1, xmmword_ptr[ebp]);
		addss(xmm1, xmm2);
		addss(xmm1, dword_ptr[esi]);
		andps(xmm1, xmm2);
		andps(xmm1, xmmword_ptr[ebp]);
		andnps(xmm1, xmm2);
		andnps(xmm1, xmmword_ptr[ebp]);
		cmpeqps(xmm1, xmm2);
		cmpeqps(xmm1, xmmword_ptr[ebp]);
		cmpltps(xmm1, xmm2);
		cmpltps(xmm1, xmmword_ptr[ebp]);
		cmpleps(xmm1, xmm2);
		cmpleps(xmm1, xmmword_ptr[ebp]);
		cmpunordps(xmm1, xmm2);
		cmpunordps(xmm1, xmmword_ptr[ebp]);
		cmpneqps(xmm1, xmm2);
		cmpneqps(xmm1, xmmword_ptr[ebp]);
		cmpnltps(xmm1, xmm2);
		cmpnltps(xmm1, xmmword_ptr[ebp]);
		cmpnleps(xmm1, xmm2);
		cmpnleps(xmm1, xmmword_ptr[ebp]);
		cmpordps(xmm1, xmm2);
		cmpordps(xmm1, xmmword_ptr[ebp]);
		cmpeqss(xmm1, xmm2);
		cmpeqss(xmm1, dword_ptr[esi]);
		cmpltss(xmm1, xmm2);
		cmpltss(xmm1, dword_ptr[esi]);
		cmpless(xmm1, xmm2);
		cmpless(xmm1, dword_ptr[esi]);
		cmpunordss(xmm1, xmm2);
		cmpunordss(xmm1, dword_ptr[esi]);
		cmpneqss(xmm1, xmm2);
		cmpneqss(xmm1, dword_ptr[esi]);
		cmpnltss(xmm1, xmm2);
		cmpnltss(xmm1, dword_ptr[esi]);
		cmpnless(xmm1, xmm2);
		cmpnless(xmm1, dword_ptr[esi]);
		cmpordss(xmm1, xmm2);
		cmpordss(xmm1, dword_ptr[esi]);
		comiss(xmm1, xmm2);
		comiss(xmm1, dword_ptr[esi]);
		cvtpi2ps(xmm1, mm3);
		cvtpi2ps(xmm1, qword_ptr[esi]);
		cvtps2pi(mm1, xmm2);
		cvtps2pi(mm1, qword_ptr[esi]);
		cvtsi2ss(xmm1, ecx);
		cvtsi2ss(xmm1, dword_ptr[esi]);
		cvtss2si(eax, xmm2);
		cvtss2si(ecx, dword_ptr[esi]);
		cvttps2pi(mm1, xmm2);
		cvttps2pi(mm1, qword_ptr[esi]);
		cvttss2si(eax, xmm2);
		cvttss2si(ecx, dword_ptr[esi]);
		divps(xmm1, xmm2);
		divps(xmm1, xmmword_ptr[ebp]);
		divss(xmm1, xmm2);
		divss(xmm1, dword_ptr[esi]);
		ldmxcsr(dword_ptr[esi]);
		maskmovq(mm1, mm2, zdi);
		maxps(xmm1, xmm2);
		maxps(xmm1, xmmword_ptr[ebp]);
		maxss(xmm1, xmm2);
		maxss(xmm1, dword_ptr[esi]);
		minps(xmm1, xmm2);
		minps(xmm1, xmmword_ptr[ebp]);
		minss(xmm1, xmm2);
		minss(xmm1, dword_ptr[esi]);
		movaps(xmm1, xmm2);
		movaps(xmm1, xmmword_ptr[ebp]);
		movaps(xmmword_ptr[esp], xmm2);
		movhlps(xmm1, xmm2);
		movhps(xmm1, qword_ptr[esi]);
		movhps(qword_ptr[edi], xmm2);
		movlhps(xmm1, xmm2);
		movlps(xmm1, qword_ptr[esi]);
		movlps(qword_ptr[edi], xmm2);
		movmskps(eax, xmm2);
		movntps(xmmword_ptr[esp], xmm2);
		movntq(qword_ptr[edi], mm2);
		movss(xmm1, xmm2);
		movss(xmm1, dword_ptr[esi]);
		movss(dword_ptr[ebp], xmm2);
		movups(xmm1, xmm2);
		movups(xmm1, xmmword_ptr[ebp]);
		movups(xmmword_ptr[esp], xmm2);
		mulps(xmm1, xmm2);
		mulps(xmm1, xmmword_ptr[ebp]);
		mulss(xmm1, xmm2);
		mulss(xmm1, dword_ptr[esi]);
		orps(xmm1, xmm2);
		orps(xmm1, xmmword_ptr[ebp]);
		prefetcht0(byte_ptr[ebp]);
		prefetcht1(byte_ptr[ebp]);
		prefetcht2(byte_ptr[ebp]);
		prefetchnta(byte_ptr[ebp]);
		rcpps(xmm1, xmm2);
		rcpps(xmm1, xmmword_ptr[ebp]);
		rcpss(xmm1, xmm2);
		rcpss(xmm1, dword_ptr[esi]);
		rsqrtps(xmm1, xmm2);
		rsqrtps(xmm1, xmmword_ptr[ebp]);
		rsqrtss(xmm1, xmm2);
		rsqrtss(xmm1, dword_ptr[esi]);
		sfence();
		shufps(xmm1, xmm2, 0x10);
		shufps(xmm1, xmmword_ptr[ebp], 0x20);
		sqrtps(xmm1, xmm2);
		sqrtps(xmm1, xmmword_ptr[ebp]);
		sqrtss(xmm1, xmm2);
		sqrtss(xmm1, dword_ptr[esi]);
		stmxcsr(dword_ptr[esi]);
		subps(xmm1, xmm2);
		subps(xmm1, xmmword_ptr[ebp]);
		subss(xmm1, xmm2);
		subss(xmm1, dword_ptr[esi]);
		ucomiss(xmm1, xmm2);
		ucomiss(xmm1, dword_ptr[esi]);
		unpckhps(xmm1, xmm2);
		unpckhps(xmm1, xmmword_ptr[ebp]);
		unpcklps(xmm1, xmm2);
		unpcklps(xmm1, xmmword_ptr[ebp]);
		xorps(xmm1, xmm2);
		xorps(xmm1, xmmword_ptr[ebp]);

#ifdef JITASM64
		addps(xmm8, xmm9);
		addps(xmm8, xmmword_ptr[rbp]);
		addss(xmm8, xmm9);
		addss(xmm8, dword_ptr[r9]);
		andps(xmm8, xmm9);
		andps(xmm8, xmmword_ptr[rbp]);
		andnps(xmm8, xmm9);
		andnps(xmm8, xmmword_ptr[rbp]);
		cmpeqps(xmm8, xmm9);
		cmpeqps(xmm8, xmmword_ptr[rbp]);
		cmpltps(xmm8, xmm9);
		cmpltps(xmm8, xmmword_ptr[rbp]);
		cmpleps(xmm8, xmm9);
		cmpleps(xmm8, xmmword_ptr[rbp]);
		cmpunordps(xmm8, xmm9);
		cmpunordps(xmm8, xmmword_ptr[rbp]);
		cmpneqps(xmm8, xmm9);
		cmpneqps(xmm8, xmmword_ptr[rbp]);
		cmpnltps(xmm8, xmm9);
		cmpnltps(xmm8, xmmword_ptr[rbp]);
		cmpnleps(xmm8, xmm9);
		cmpnleps(xmm8, xmmword_ptr[rbp]);
		cmpordps(xmm8, xmm9);
		cmpordps(xmm8, xmmword_ptr[rbp]);
		cmpeqss(xmm8, xmm9);
		cmpeqss(xmm8, dword_ptr[r9]);
		cmpltss(xmm8, xmm9);
		cmpltss(xmm8, dword_ptr[r9]);
		cmpless(xmm8, xmm9);
		cmpless(xmm8, dword_ptr[r9]);
		cmpunordss(xmm8, xmm9);
		cmpunordss(xmm8, dword_ptr[r9]);
		cmpneqss(xmm8, xmm9);
		cmpneqss(xmm8, dword_ptr[r9]);
		cmpnltss(xmm8, xmm9);
		cmpnltss(xmm8, dword_ptr[r9]);
		cmpnless(xmm8, xmm9);
		cmpnless(xmm8, dword_ptr[r9]);
		cmpordss(xmm8, xmm9);
		cmpordss(xmm8, dword_ptr[r9]);
		comiss(xmm8, xmm9);
		comiss(xmm8, dword_ptr[r9]);
		cvtpi2ps(xmm8, mm3);
		cvtpi2ps(xmm8, qword_ptr[r9]);
		cvtps2pi(mm1, xmm9);
		cvtps2pi(mm1, qword_ptr[r9]);
		cvtsi2ss(xmm8, ecx);
		cvtsi2ss(xmm8, dword_ptr[r9]);
		cvtss2si(eax, xmm9);
		cvtss2si(ecx, dword_ptr[r9]);
		cvttps2pi(mm1, xmm9);
		cvttps2pi(mm1, qword_ptr[r9]);
		cvttss2si(eax, xmm9);
		cvttss2si(ecx, dword_ptr[r9]);
		cvtsi2ss(xmm8, rax);
		cvtsi2ss(xmm8, r9);
		cvtsi2ss(xmm8, qword_ptr[r9]);
		cvtss2si(r9d, xmm9);
		cvtss2si(rcx, xmm9);
		cvtss2si(r8, xmm9);
		cvtss2si(rax, dword_ptr[r9]);
		cvttss2si(r9, xmm9);
		cvttss2si(r10, dword_ptr[r9]);
		divps(xmm8, xmm9);
		divps(xmm8, xmmword_ptr[rbp]);
		divss(xmm8, xmm9);
		divss(xmm8, dword_ptr[r9]);
		ldmxcsr(dword_ptr[r9]);
		maskmovq(mm1, mm2, rdi);
		maxps(xmm8, xmm9);
		maxps(xmm8, xmmword_ptr[rbp]);
		maxss(xmm8, xmm9);
		maxss(xmm8, dword_ptr[r9]);
		minps(xmm8, xmm9);
		minps(xmm8, xmmword_ptr[rbp]);
		minss(xmm8, xmm9);
		minss(xmm8, dword_ptr[r9]);
		movaps(xmm8, xmm9);
		movaps(xmm8, xmmword_ptr[rbp]);
		movaps(xmmword_ptr[rsp], xmm9);
		movhlps(xmm8, xmm9);
		movhps(xmm8, qword_ptr[r9]);
		movhps(qword_ptr[rdi], xmm9);
		movlhps(xmm8, xmm9);
		movlps(xmm8, qword_ptr[r9]);
		movlps(qword_ptr[rdi], xmm9);
		movmskps(eax, xmm9);
		movmskps(r9d, xmm9);
		movmskps(rax, xmm9);
		movmskps(r9, xmm3);
		movntps(xmmword_ptr[rsp], xmm9);
		movntq(qword_ptr[rdi], mm7);
		movss(xmm8, xmm9);
		movss(xmm8, dword_ptr[r9]);
		movss(dword_ptr[rbp], xmm9);
		movups(xmm8, xmm9);
		movups(xmm8, xmmword_ptr[rbp]);
		movups(xmmword_ptr[rsp], xmm9);
		mulps(xmm8, xmm9);
		mulps(xmm8, xmmword_ptr[rbp]);
		mulss(xmm8, xmm9);
		mulss(xmm8, dword_ptr[r9]);
		orps(xmm8, xmm9);
		orps(xmm8, xmmword_ptr[rbp]);
		prefetcht0(byte_ptr[rbp]);
		prefetcht1(byte_ptr[rbp]);
		prefetcht2(byte_ptr[rbp]);
		prefetchnta(byte_ptr[rbp]);
		rcpps(xmm8, xmm9);
		rcpps(xmm8, xmmword_ptr[rbp]);
		rcpss(xmm8, xmm9);
		rcpss(xmm8, dword_ptr[r9]);
		rsqrtps(xmm8, xmm9);
		rsqrtps(xmm8, xmmword_ptr[rbp]);
		rsqrtss(xmm8, xmm9);
		rsqrtss(xmm8, dword_ptr[r9]);
		sfence();
		shufps(xmm8, xmm9, 0x10);
		shufps(xmm8, xmmword_ptr[rbp], 0x20);
		sqrtps(xmm8, xmm9);
		sqrtps(xmm8, xmmword_ptr[rbp]);
		sqrtss(xmm8, xmm9);
		sqrtss(xmm8, dword_ptr[r9]);
		stmxcsr(dword_ptr[r9]);
		subps(xmm8, xmm9);
		subps(xmm8, xmmword_ptr[rbp]);
		subss(xmm8, xmm9);
		subss(xmm8, dword_ptr[r9]);
		ucomiss(xmm8, xmm9);
		ucomiss(xmm8, dword_ptr[r9]);
		unpckhps(xmm8, xmm9);
		unpckhps(xmm8, xmmword_ptr[rbp]);
		unpcklps(xmm8, xmm9);
		unpcklps(xmm8, xmmword_ptr[rbp]);
		xorps(xmm8, xmm9);
		xorps(xmm8, xmmword_ptr[rbp]);
#endif
	}
};

//----------------------------------------
// SSE2 A~
//----------------------------------------
extern "C" void masm_test_sse2_a();
struct test_sse2_a : jitasm::function<void, test_sse2_a>
{
	void naked_main()
	{
		addpd(xmm0, xmmword_ptr[esp]);
		addpd(xmm0, xmm0);
		addsd(xmm0, qword_ptr[esp]);
		addsd(xmm0, xmm0);
		andpd(xmm0, xmmword_ptr[esp]);
		andpd(xmm0, xmm0);
		andnpd(xmm0, xmmword_ptr[esp]);
		andnpd(xmm0, xmm0);
#ifdef JITASM64
		addpd(xmm8, xmmword_ptr[rsp]);
		addpd(xmm8, xmmword_ptr[r8]);
		addpd(xmm8, xmm8);
		addsd(xmm8, qword_ptr[rsp]);
		addsd(xmm8, qword_ptr[r8]);
		addsd(xmm8, xmm8);
		andpd(xmm8, xmmword_ptr[rsp]);
		andpd(xmm8, xmmword_ptr[r8]);
		andpd(xmm8, xmm8);
		andnpd(xmm8, xmmword_ptr[rsp]);
		andnpd(xmm8, xmmword_ptr[r8]);
		andnpd(xmm8, xmm8);
#endif

		clflush(byte_ptr[esp]);
#ifdef JITASM64
		clflush(byte_ptr[r8]);
#endif

		cmpeqpd(xmm0, xmmword_ptr[esp]);
		cmpeqpd(xmm0, xmm0);
		cmpltpd(xmm0, xmmword_ptr[esp]);
		cmpltpd(xmm0, xmm0);
		cmplepd(xmm0, xmmword_ptr[esp]);
		cmplepd(xmm0, xmm0);
		cmpunordpd(xmm0, xmmword_ptr[esp]);
		cmpunordpd(xmm0, xmm0);
		cmpneqpd(xmm0, xmmword_ptr[esp]);
		cmpneqpd(xmm0, xmm0);
		cmpnltpd(xmm0, xmmword_ptr[esp]);
		cmpnltpd(xmm0, xmm0);
		cmpnlepd(xmm0, xmmword_ptr[esp]);
		cmpnlepd(xmm0, xmm0);
		cmpordpd(xmm0, xmmword_ptr[esp]);
		cmpordpd(xmm0, xmm0);

		cmpeqsd(xmm0, qword_ptr[esp]);
		cmpeqsd(xmm0, xmm0);
		cmpltsd(xmm0, qword_ptr[esp]);
		cmpltsd(xmm0, xmm0);
		cmplesd(xmm0, qword_ptr[esp]);
		cmplesd(xmm0, xmm0);
		cmpunordsd(xmm0, qword_ptr[esp]);
		cmpunordsd(xmm0, xmm0);
		cmpneqsd(xmm0, qword_ptr[esp]);
		cmpneqsd(xmm0, xmm0);
		cmpnltsd(xmm0, qword_ptr[esp]);
		cmpnltsd(xmm0, xmm0);
		cmpnlesd(xmm0, qword_ptr[esp]);
		cmpnlesd(xmm0, xmm0);
		cmpordsd(xmm0, qword_ptr[esp]);
		cmpordsd(xmm0, xmm0);

		comisd(xmm0, qword_ptr[esp]);
		comisd(xmm0, xmm0);
#ifdef JITASM64
		cmpeqpd(xmm8, xmmword_ptr[rsp]);
		cmpeqpd(xmm8, xmm8);
		cmpltpd(xmm8, xmmword_ptr[r8]);
		cmpltpd(xmm8, xmm8);
		cmplepd(xmm8, xmmword_ptr[rsp]);
		cmplepd(xmm8, xmm8);
		cmpunordpd(xmm8, xmmword_ptr[r8]);
		cmpunordpd(xmm8, xmm8);
		cmpneqpd(xmm8, xmmword_ptr[rsp]);
		cmpneqpd(xmm8, xmm8);
		cmpnltpd(xmm8, xmmword_ptr[r8]);
		cmpnltpd(xmm8, xmm8);
		cmpnlepd(xmm8, xmmword_ptr[rsp]);
		cmpnlepd(xmm8, xmm8);
		cmpordpd(xmm8, xmmword_ptr[r8]);
		cmpordpd(xmm8, xmm8);

		cmpeqsd(xmm8, qword_ptr[rsp]);
		cmpeqsd(xmm8, xmm8);
		cmpltsd(xmm8, qword_ptr[r8]);
		cmpltsd(xmm8, xmm8);
		cmplesd(xmm8, qword_ptr[rsp]);
		cmplesd(xmm8, xmm8);
		cmpunordsd(xmm8, qword_ptr[r8]);
		cmpunordsd(xmm8, xmm8);
		cmpneqsd(xmm8, qword_ptr[rsp]);
		cmpneqsd(xmm8, xmm8);
		cmpnltsd(xmm8, qword_ptr[r8]);
		cmpnltsd(xmm8, xmm8);
		cmpnlesd(xmm8, qword_ptr[rsp]);
		cmpnlesd(xmm8, xmm8);
		cmpordsd(xmm8, qword_ptr[r8]);
		cmpordsd(xmm8, xmm8);

		comisd(xmm8, qword_ptr[rsp]);
		comisd(xmm8, qword_ptr[r8]);
		comisd(xmm8, xmm8);

#endif
		cvtdq2pd(xmm0, xmm1);
		cvtdq2pd(xmm0, qword_ptr[esp]);
		cvtpd2dq(xmm0, xmm1);
		cvtpd2dq(xmm0, xmmword_ptr[esp]);
		cvtpd2pi(mm0, xmm1);
		cvtpd2pi(mm0, xmmword_ptr[esp]);
		cvtpd2ps(xmm0, xmm1);
		cvtpd2ps(xmm0, xmmword_ptr[esp]);
		cvtpi2pd(xmm0, mm1);
		cvtpi2pd(xmm0, qword_ptr[esp]);
		cvtps2dq(xmm0, xmm1);
		cvtps2dq(xmm0, xmmword_ptr[esp]);
		cvtdq2ps(xmm0, xmm1);
		cvtdq2ps(xmm0, xmmword_ptr[esp]);
		cvtps2pd(xmm0, xmm1);
		cvtps2pd(xmm0, qword_ptr[esp]);
		cvtsd2si(eax, xmm1);
		cvtsd2si(ecx, qword_ptr[esp]);
		cvtsd2ss(xmm0, xmm1);
		cvtsd2ss(xmm0, qword_ptr[esp]);
		cvtsi2sd(xmm0, eax);
		cvtsi2sd(xmm0, dword_ptr[esp]);
		cvtss2sd(xmm0, xmm1);
		cvtss2sd(xmm0, dword_ptr[esp]);
		cvttpd2dq(xmm0, xmm1);
		cvttpd2dq(xmm0, xmmword_ptr[esp]);
		cvttpd2pi(mm0, xmm1);
		cvttpd2pi(mm0, xmmword_ptr[esp]);
		cvttps2dq(xmm0, xmm1);
		cvttps2dq(xmm0, xmmword_ptr[esp]);
		cvttsd2si(eax, xmm1);
		cvttsd2si(eax, qword_ptr[esp]);
#ifdef JITASM64
		cvtdq2pd(xmm8, xmm9);
		cvtdq2pd(xmm8, qword_ptr[r8]);
		cvtpd2dq(xmm8, xmm9);
		cvtpd2dq(xmm8, xmmword_ptr[r8]);
		cvtpd2pi(mm0, xmm9);
		cvtpd2pi(mm0, xmmword_ptr[r8]);
		cvtpd2ps(xmm8, xmm9);
		cvtpd2ps(xmm8, xmmword_ptr[r8]);
		cvtpi2pd(xmm8, mm1);
		cvtpi2pd(xmm8, qword_ptr[r8]);
		cvtps2dq(xmm8, xmm9);
		cvtps2dq(xmm8, xmmword_ptr[r8]);
		cvtdq2ps(xmm8, xmm9);
		cvtdq2ps(xmm8, xmmword_ptr[r8]);
		cvtps2pd(xmm8, xmm9);
		cvtps2pd(xmm8, qword_ptr[r8]);
		cvtsd2si(r8d, xmm9);
		cvtsd2si(r9d, qword_ptr[r8]);
		cvtsd2si(r8, xmm9);
		cvtsd2si(r9, qword_ptr[r8]);
		cvtsd2ss(xmm8, xmm9);
		cvtsd2ss(xmm8, qword_ptr[r8]);
		cvtsi2sd(xmm8, r8);
		cvtsi2sd(xmm8, dword_ptr[r8]);
		cvtss2sd(xmm8, xmm9);
		cvtss2sd(xmm8, dword_ptr[r8]);
		cvttpd2dq(xmm8, xmm9);
		cvttpd2dq(xmm8, xmmword_ptr[r8]);
		cvttpd2pi(mm0, xmm9);
		cvttpd2pi(mm0, xmmword_ptr[r8]);
		cvttps2dq(xmm8, xmm9);
		cvttps2dq(xmm8, xmmword_ptr[r8]);
		cvttsd2si(rax, xmm1);
		cvttsd2si(rax, qword_ptr[r8]);
		cvttsd2si(r8, xmm1);
		cvttsd2si(r8, qword_ptr[r8]);
#endif
	}
};

//----------------------------------------
// SSE2 D~
//----------------------------------------
extern "C" void masm_test_sse2_d();
struct test_sse2_d : jitasm::function<void, test_sse2_d>
{
	void naked_main()
	{
		divpd(xmm0, xmm1);
		divpd(xmm0, xmmword_ptr[esp]);
		divsd(xmm0, xmm1);
		divsd(xmm0, qword_ptr[esp]);
		lfence();
		maskmovdqu(xmm0, xmm1, zdi);
		maxpd(xmm0, xmm1);
		maxpd(xmm0, xmmword_ptr[esp]);
		maxsd(xmm0, xmm1);
		maxsd(xmm0, qword_ptr[esp]);
		mfence();
		minpd(xmm0, xmm1);
		minpd(xmm0, xmmword_ptr[esp]);
		minsd(xmm0, xmm1);
		minsd(xmm0, qword_ptr[esp]);
#ifdef JITASM64
		divpd(xmm8, xmm9);
		divpd(xmm8, xmmword_ptr[r8]);
		divsd(xmm8, xmm9);
		divsd(xmm8, qword_ptr[r8]);
		maskmovdqu(xmm8, xmm9, rdi);
		maxpd(xmm8, xmm9);
		maxpd(xmm8, xmmword_ptr[r8]);
		maxsd(xmm8, xmm9);
		maxsd(xmm8, qword_ptr[r8]);
		minpd(xmm8, xmm9);
		minpd(xmm8, xmmword_ptr[r8]);
		minsd(xmm8, xmm9);
		minsd(xmm8, qword_ptr[r8]);
#endif

		movapd(xmm0, xmm1);
		movapd(xmm0, xmmword_ptr[esp]);
		movapd(xmmword_ptr[esp], xmm0);
		movdqa(xmm0, xmm1);
		movdqa(xmm0, xmmword_ptr[esp]);
		movdqa(xmmword_ptr[esp], xmm0);
		movdqu(xmm0, xmm1);
		movdqu(xmm0, xmmword_ptr[esp]);
		movdqu(xmmword_ptr[esp], xmm0);
		movdq2q(mm0, xmm1);
		movhpd(qword_ptr[esp], xmm1);
		movhpd(xmm0, qword_ptr[esp]);
		movlpd(qword_ptr[esp], xmm1);
		movlpd(xmm0, qword_ptr[esp]);
		movmskpd(eax, xmm1);
		movntdq(xmmword_ptr[esp], xmm1);
		movnti(dword_ptr[esp], eax);
		movntpd(xmmword_ptr[esp], xmm1);
		movq2dq(xmm0, mm1);
		movupd(xmm0, xmm1);
		movupd(xmm0, xmmword_ptr[esp]);
		movupd(xmmword_ptr[esp], xmm0);
		mulpd(xmm0, xmm1);
		mulpd(xmm0, xmmword_ptr[esp]);
		mulsd(xmm0, xmm1);
		mulsd(xmm0, qword_ptr[esp]);
		orpd(xmm0, xmm1);
		orpd(xmm0, xmmword_ptr[esp]);
#ifdef JITASM64
		movapd(xmm8, xmm9);
		movapd(xmm8, xmmword_ptr[r8]);
		movapd(xmmword_ptr[r8], xmm8);
		movdqa(xmm8, xmm9);
		movdqa(xmm8, xmmword_ptr[r8]);
		movdqa(xmmword_ptr[r8], xmm8);
		movdqu(xmm8, xmm9);
		movdqu(xmm8, xmmword_ptr[r8]);
		movdqu(xmmword_ptr[r8], xmm8);
		movdq2q(mm0, xmm9);
		movhpd(qword_ptr[r8], xmm9);
		movhpd(xmm8, qword_ptr[r8]);
		movlpd(qword_ptr[r8], xmm9);
		movlpd(xmm8, qword_ptr[r8]);
		movmskpd(eax, xmm9);
		movmskpd(rax, xmm9);
		movntdq(xmmword_ptr[r8], xmm9);
		movnti(dword_ptr[r8], ecx);
		movnti(qword_ptr[r8], rcx);
		movntpd(xmmword_ptr[r8], xmm9);
		movq2dq(xmm8, mm1);
		movupd(xmm8, xmm9);
		movupd(xmm8, xmmword_ptr[r8]);
		movupd(xmmword_ptr[r8], xmm8);
		mulpd(xmm8, xmm9);
		mulpd(xmm8, xmmword_ptr[r8]);
		mulsd(xmm8, xmm9);
		mulsd(xmm8, qword_ptr[r8]);
		orpd(xmm8, xmm9);
		orpd(xmm8, xmmword_ptr[r8]);
#endif
	}
};

//----------------------------------------
// SSE2 P~
//----------------------------------------
extern "C" void masm_test_sse2_p();
struct test_sse2_p : jitasm::function<void, test_sse2_p>
{
	void naked_main()
	{
		packsswb(xmm0, xmm1);
		packsswb(xmm0, xmmword_ptr[esp]);
		packssdw(xmm0, xmm1);
		packssdw(xmm0, xmmword_ptr[esp]);
		packuswb(xmm0, xmm1);
		packuswb(xmm0, xmmword_ptr[esp]);
		paddb(xmm0, xmm1);
		paddb(xmm0, xmmword_ptr[esp]);
		paddw(xmm0, xmm1);
		paddw(xmm0, xmmword_ptr[esp]);
		paddd(xmm0, xmm1);
		paddd(xmm0, xmmword_ptr[esp]);
		paddq(mm0, mm1);
		paddq(mm0, qword_ptr[esp]);
		paddq(xmm0, xmm1);
		paddq(xmm0, xmmword_ptr[esp]);
		paddsb(xmm0, xmm1);
		paddsb(xmm0, xmmword_ptr[esp]);
		paddsw(xmm0, xmm1);
		paddsw(xmm0, xmmword_ptr[esp]);
		paddusb(xmm0, xmm1);
		paddusb(xmm0, xmmword_ptr[esp]);
		paddusw(xmm0, xmm1);
		paddusw(xmm0, xmmword_ptr[esp]);
		pand(xmm0, xmm1);
		pand(xmm0, xmmword_ptr[esp]);
		pandn(xmm0, xmm1);
		pandn(xmm0, xmmword_ptr[esp]);
		pause();
		pavgb(xmm0, xmm1);
		pavgb(xmm0, xmmword_ptr[esp]);
		pavgw(xmm0, xmm1);
		pavgw(xmm0, xmmword_ptr[esp]);
		pcmpeqb(xmm0, xmm1);
		pcmpeqb(xmm0, xmmword_ptr[esp]);
		pcmpeqw(xmm0, xmm1);
		pcmpeqw(xmm0, xmmword_ptr[esp]);
		pcmpeqd(xmm0, xmm1);
		pcmpeqd(xmm0, xmmword_ptr[esp]);
		pcmpgtb(xmm0, xmm1);
		pcmpgtb(xmm0, xmmword_ptr[esp]);
		pcmpgtw(xmm0, xmm1);
		pcmpgtw(xmm0, xmmword_ptr[esp]);
		pcmpgtd(xmm0, xmm1);
		pcmpgtd(xmm0, xmmword_ptr[esp]);
		pextrw(eax, xmm1, 1);
		pinsrw(xmm0, ecx, 3);
		pinsrw(xmm0, word_ptr[esp], 4);
		pmaddwd(xmm0, xmm1);
		pmaddwd(xmm0, xmmword_ptr[esp]);
		pmaxsw(xmm0, xmm1);
		pmaxsw(xmm0, xmmword_ptr[esp]);
		pmaxub(xmm0, xmm1);
		pmaxub(xmm0, xmmword_ptr[esp]);
		pminsw(xmm0, xmm1);
		pminsw(xmm0, xmmword_ptr[esp]);
		pminub(xmm0, xmm1);
		pminub(xmm0, xmmword_ptr[esp]);
		pmovmskb(eax, xmm1);
		pmulhuw(xmm0, xmm1);
		pmulhuw(xmm0, xmmword_ptr[esp]);
		pmulhw(xmm0, xmm1);
		pmulhw(xmm0, xmmword_ptr[esp]);
		pmullw(xmm0, xmm1);
		pmullw(xmm0, xmmword_ptr[esp]);
		pmuludq(mm0, mm1);
		pmuludq(mm0, qword_ptr[esp]);
		pmuludq(xmm0, xmm1);
		pmuludq(xmm0, xmmword_ptr[esp]);
		por(xmm0, xmm1);
		por(xmm0, xmmword_ptr[esp]);
		psadbw(xmm0, xmm1);
		psadbw(xmm0, xmmword_ptr[esp]);
		pshufd(xmm0, xmm1, 0x1B);
		pshufd(xmm0, xmmword_ptr[esp], 0x0B);
		pshufhw(xmm0, xmm1, 0x1A);
		pshufhw(xmm0, xmmword_ptr[esp], 0x18);
		pshuflw(xmm0, xmm1, 0x14);
		pshuflw(xmm0, xmmword_ptr[esp], 0x12);
		psllw(xmm0, xmm1);
		psllw(xmm0, xmmword_ptr[ebp]);
		psllw(xmm0, 2);
		pslld(xmm0, xmm1);
		pslld(xmm0, xmmword_ptr[ebp]);
		pslld(xmm0, 2);
		psllq(xmm0, xmm1);
		psllq(xmm0, xmmword_ptr[ebp]);
		psllq(xmm0, 2);
		pslldq(xmm0, 2);
		psraw(xmm0, xmm1);
		psraw(xmm0, xmmword_ptr[ebp]);
		psraw(xmm0, 2);
		psrad(xmm0, xmm1);
		psrad(xmm0, xmmword_ptr[ebp]);
		psrad(xmm0, 2);
		psrlw(xmm0, xmm1);
		psrlw(xmm0, xmmword_ptr[ebp]);
		psrlw(xmm0, 2);
		psrld(xmm0, xmm1);
		psrld(xmm0, xmmword_ptr[ebp]);
		psrld(xmm0, 2);
		psrlq(xmm0, xmm1);
		psrlq(xmm0, xmmword_ptr[ebp]);
		psrlq(xmm0, 2);
		psrldq(xmm0, 2);
		psubb(xmm0, xmm1);
		psubb(xmm0, xmmword_ptr[esp]);
		psubw(xmm0, xmm1);
		psubw(xmm0, xmmword_ptr[esp]);
		psubd(xmm0, xmm1);
		psubd(xmm0, xmmword_ptr[esp]);
		psubq(mm0, mm1);
		psubq(mm0, qword_ptr[esp]);
		psubq(xmm0, xmm1);
		psubq(xmm0, xmmword_ptr[esp]);
		psubsb(xmm0, xmm1);
		psubsb(xmm0, xmmword_ptr[esp]);
		psubsw(xmm0, xmm1);
		psubsw(xmm0, xmmword_ptr[esp]);
		psubusb(xmm0, xmm1);
		psubusb(xmm0, xmmword_ptr[esp]);
		psubusw(xmm0, xmm1);
		psubusw(xmm0, xmmword_ptr[esp]);
		punpckhbw(xmm0, xmm1);
		punpckhbw(xmm0, xmmword_ptr[esp]);
		punpckhwd(xmm0, xmm1);
		punpckhwd(xmm0, xmmword_ptr[esp]);
		punpckhdq(xmm0, xmm1);
		punpckhdq(xmm0, xmmword_ptr[esp]);
		punpckhqdq(xmm0, xmm1);
		punpckhqdq(xmm0, xmmword_ptr[esp]);
		punpcklbw(xmm0, xmm1);
		punpcklbw(xmm0, xmmword_ptr[esp]);
		punpcklwd(xmm0, xmm1);
		punpcklwd(xmm0, xmmword_ptr[esp]);
		punpckldq(xmm0, xmm1);
		punpckldq(xmm0, xmmword_ptr[esp]);
		punpcklqdq(xmm0, xmm1);
		punpcklqdq(xmm0, xmmword_ptr[esp]);
		pxor(xmm0, xmm1);
		pxor(xmm0, xmmword_ptr[esp]);
#ifdef JITASM64
		packsswb(xmm8, xmm9);
		packsswb(xmm8, xmmword_ptr[r8]);
		packssdw(xmm8, xmm9);
		packssdw(xmm8, xmmword_ptr[r8]);
		packuswb(xmm8, xmm9);
		packuswb(xmm8, xmmword_ptr[r8]);
		paddb(xmm8, xmm9);
		paddb(xmm8, xmmword_ptr[r8]);
		paddw(xmm8, xmm9);
		paddw(xmm8, xmmword_ptr[r8]);
		paddd(xmm8, xmm9);
		paddd(xmm8, xmmword_ptr[r8]);
		paddq(mm0, mm1);
		paddq(mm0, qword_ptr[r8]);
		paddq(xmm8, xmm9);
		paddq(xmm8, xmmword_ptr[r8]);
		paddsb(xmm8, xmm9);
		paddsb(xmm8, xmmword_ptr[r8]);
		paddsw(xmm8, xmm9);
		paddsw(xmm8, xmmword_ptr[r8]);
		paddusb(xmm8, xmm9);
		paddusb(xmm8, xmmword_ptr[r8]);
		paddusw(xmm8, xmm9);
		paddusw(xmm8, xmmword_ptr[r8]);
		pand(xmm8, xmm9);
		pand(xmm8, xmmword_ptr[r8]);
		pandn(xmm8, xmm9);
		pandn(xmm8, xmmword_ptr[r8]);
		pause();
		pavgb(xmm8, xmm9);
		pavgb(xmm8, xmmword_ptr[r8]);
		pavgw(xmm8, xmm9);
		pavgw(xmm8, xmmword_ptr[r8]);
		pcmpeqb(xmm8, xmm9);
		pcmpeqb(xmm8, xmmword_ptr[r8]);
		pcmpeqw(xmm8, xmm9);
		pcmpeqw(xmm8, xmmword_ptr[r8]);
		pcmpeqd(xmm8, xmm9);
		pcmpeqd(xmm8, xmmword_ptr[r8]);
		pcmpgtb(xmm8, xmm9);
		pcmpgtb(xmm8, xmmword_ptr[r8]);
		pcmpgtw(xmm8, xmm9);
		pcmpgtw(xmm8, xmmword_ptr[r8]);
		pcmpgtd(xmm8, xmm9);
		pcmpgtd(xmm8, xmmword_ptr[r8]);
		pextrw(eax, xmm9, 1);
		pextrw(rax, xmm9, 2);
		pextrw(r8, xmm9, 2);
		pinsrw(xmm8, ecx, 3);
		pinsrw(xmm8, word_ptr[r8], 4);
		pinsrw(xmm8, rcx, 1);
		pinsrw(xmm8, r8, 1);
		pmaddwd(xmm8, xmm9);
		pmaddwd(xmm8, xmmword_ptr[r8]);
		pmaxsw(xmm8, xmm9);
		pmaxsw(xmm8, xmmword_ptr[r8]);
		pmaxub(xmm8, xmm9);
		pmaxub(xmm8, xmmword_ptr[r8]);
		pminsw(xmm8, xmm9);
		pminsw(xmm8, xmmword_ptr[r8]);
		pminub(xmm8, xmm9);
		pminub(xmm8, xmmword_ptr[r8]);
		pmovmskb(eax, xmm9);
		pmovmskb(rax, xmm9);
		pmovmskb(r8, xmm9);
		pmulhuw(xmm8, xmm9);
		pmulhuw(xmm8, xmmword_ptr[r8]);
		pmulhw(xmm8, xmm9);
		pmulhw(xmm8, xmmword_ptr[r8]);
		pmullw(xmm8, xmm9);
		pmullw(xmm8, xmmword_ptr[r8]);
		pmuludq(mm0, mm1);
		pmuludq(mm0, qword_ptr[r8]);
		pmuludq(xmm8, xmm9);
		pmuludq(xmm8, xmmword_ptr[r8]);
		por(xmm8, xmm9);
		por(xmm8, xmmword_ptr[r8]);
		psadbw(xmm8, xmm9);
		psadbw(xmm8, xmmword_ptr[r8]);
		pshufd(xmm8, xmm9, 0x1B);
		pshufd(xmm8, xmmword_ptr[r8], 0x0B);
		pshufhw(xmm8, xmm9, 0x1A);
		pshufhw(xmm8, xmmword_ptr[r8], 0x18);
		pshuflw(xmm8, xmm9, 0x14);
		pshuflw(xmm8, xmmword_ptr[r8], 0x12);
		psllw(xmm8, xmm9);
		psllw(xmm8, xmmword_ptr[rbp]);
		psllw(xmm8, 2);
		pslld(xmm8, xmm9);
		pslld(xmm8, xmmword_ptr[rbp]);
		pslld(xmm8, 2);
		psllq(xmm8, xmm9);
		psllq(xmm8, xmmword_ptr[rbp]);
		psllq(xmm8, 2);
		pslldq(xmm8, 2);
		psraw(xmm8, xmm9);
		psraw(xmm8, xmmword_ptr[rbp]);
		psraw(xmm8, 2);
		psrad(xmm8, xmm9);
		psrad(xmm8, xmmword_ptr[rbp]);
		psrad(xmm8, 2);
		psrlw(xmm8, xmm9);
		psrlw(xmm8, xmmword_ptr[rbp]);
		psrlw(xmm8, 2);
		psrld(xmm8, xmm9);
		psrld(xmm8, xmmword_ptr[rbp]);
		psrld(xmm8, 2);
		psrlq(xmm8, xmm9);
		psrlq(xmm8, xmmword_ptr[rbp]);
		psrlq(xmm8, 2);
		psrldq(xmm8, 2);
		psubb(xmm8, xmm9);
		psubb(xmm8, xmmword_ptr[r8]);
		psubw(xmm8, xmm9);
		psubw(xmm8, xmmword_ptr[r8]);
		psubd(xmm8, xmm9);
		psubd(xmm8, xmmword_ptr[r8]);
		psubq(mm0, mm1);
		psubq(mm0, qword_ptr[r8]);
		psubq(xmm8, xmm9);
		psubq(xmm8, xmmword_ptr[r8]);
		psubsb(xmm8, xmm9);
		psubsb(xmm8, xmmword_ptr[r8]);
		psubsw(xmm8, xmm9);
		psubsw(xmm8, xmmword_ptr[r8]);
		psubusb(xmm8, xmm9);
		psubusb(xmm8, xmmword_ptr[r8]);
		psubusw(xmm8, xmm9);
		psubusw(xmm8, xmmword_ptr[r8]);
		punpckhbw(xmm8, xmm9);
		punpckhbw(xmm8, xmmword_ptr[r8]);
		punpckhwd(xmm8, xmm9);
		punpckhwd(xmm8, xmmword_ptr[r8]);
		punpckhdq(xmm8, xmm9);
		punpckhdq(xmm8, xmmword_ptr[r8]);
		punpckhqdq(xmm8, xmm9);
		punpckhqdq(xmm8, xmmword_ptr[r8]);
		punpcklbw(xmm8, xmm9);
		punpcklbw(xmm8, xmmword_ptr[r8]);
		punpcklwd(xmm8, xmm9);
		punpcklwd(xmm8, xmmword_ptr[r8]);
		punpckldq(xmm8, xmm9);
		punpckldq(xmm8, xmmword_ptr[r8]);
		punpcklqdq(xmm8, xmm9);
		punpcklqdq(xmm8, xmmword_ptr[r8]);
		pxor(xmm8, xmm9);
		pxor(xmm8, xmmword_ptr[r8]);
#endif
	}
};

//----------------------------------------
// SSE2 S~
//----------------------------------------
extern "C" void masm_test_sse2_s();
struct test_sse2_s : jitasm::function<void, test_sse2_s>
{
	void naked_main()
	{
		shufpd(xmm0, xmm1, 2);
		shufpd(xmm0, xmmword_ptr[esp], 1);
		sqrtpd(xmm0, xmm1);
		sqrtpd(xmm0, xmmword_ptr[esp]);
		sqrtsd(xmm0, xmm1);
		sqrtsd(xmm0, qword_ptr[ebp]);
		subpd(xmm0, xmm1);
		subpd(xmm0, xmmword_ptr[esp]);
		subsd(xmm0, xmm1);
		subsd(xmm0, qword_ptr[ebp]);
		ucomisd(xmm0, xmm1);
		ucomisd(xmm0, qword_ptr[ebp]);
		unpckhpd(xmm0, xmm1);
		unpckhpd(xmm0, xmmword_ptr[esp]);
		unpcklpd(xmm0, xmm1);
		unpcklpd(xmm0, xmmword_ptr[esp]);
		xorpd(xmm0, xmm1);
		xorpd(xmm0, xmmword_ptr[esp]);
#ifdef JITASM64
		shufpd(xmm8, xmm9, 2);
		shufpd(xmm8, xmmword_ptr[r8], 1);
		sqrtpd(xmm8, xmm9);
		sqrtpd(xmm8, xmmword_ptr[r8]);
		sqrtsd(xmm8, xmm9);
		sqrtsd(xmm8, qword_ptr[rbp]);
		subpd(xmm8, xmm9);
		subpd(xmm8, xmmword_ptr[r8]);
		subsd(xmm8, xmm9);
		subsd(xmm8, qword_ptr[rbp]);
		ucomisd(xmm8, xmm9);
		ucomisd(xmm8, qword_ptr[rbp]);
		unpckhpd(xmm8, xmm9);
		unpckhpd(xmm8, xmmword_ptr[r8]);
		unpcklpd(xmm8, xmm9);
		unpcklpd(xmm8, xmmword_ptr[r8]);
		xorpd(xmm8, xmm9);
		xorpd(xmm8, xmmword_ptr[r8]);
#endif
	}
};

//----------------------------------------
// MOVD/MOVQ
//----------------------------------------
extern "C" void masm_test_movd_movq();
struct test_movd_movq : jitasm::function<void, test_movd_movq>
{
	void naked_main()
	{
		movd(mm0, dword_ptr[eax]);
		movd(mm0, eax);
		movq(mm0, qword_ptr[eax]);
		movd(dword_ptr[eax], mm0);
		movd(eax, mm0);
		movq(qword_ptr[eax], mm0);
		movd(xmm0, dword_ptr[eax]);
		movd(xmm0, eax);
		movq(xmm0, qword_ptr[eax]);
		movd(dword_ptr[eax], xmm0);
		movd(eax, xmm0);
		movq(qword_ptr[eax], xmm0);
		movq(mm0, mm1);
		movq(mm0, qword_ptr[eax]);
		movq(qword_ptr[eax], mm0);
		movq(xmm0, xmm0);
		movq(xmm0, qword_ptr[eax]);
		movq(qword_ptr[eax], xmm0);
#ifdef JITASM64
		movd(mm0, rax);				// movq
		movd(rax, mm0);				// movq
		movd(xmm0, rax);			// movq
		movd(rax, xmm0);			// movq
		movd(mm0, dword_ptr[rax]);
		movq(mm0, qword_ptr[rax]);
		movd(dword_ptr[rax], mm0);
		movq(qword_ptr[rax], mm0);
		movd(xmm0, dword_ptr[rax]);
		movq(xmm0, qword_ptr[rax]);
		movd(dword_ptr[rax], xmm0);
		movq(qword_ptr[rax], xmm0);
		movq(mm0, qword_ptr[rax]);
		movq(qword_ptr[rax], mm0);
		movq(xmm0, qword_ptr[rax]);
		movq(qword_ptr[rax], xmm0);
		// test REX
		movd(mm0, r8);				// movq
		movd(r8, mm0);				// movq
		movd(xmm0, rax);			// movq
		movd(xmm0, r8);				// movq
		movd(xmm8, rax);			// movq
		movd(xmm8, r8);				// movq
		movd(rax, xmm0);			// movq
		movd(rax, xmm8);			// movq
		movd(r8, xmm0);				// movq
		movd(r8, xmm8);				// movq
		movd(mm0, dword_ptr[r8]);
		movq(mm0, qword_ptr[r8]);
		movd(dword_ptr[r8], mm0);
		movq(qword_ptr[r8], mm0);
		movd(xmm0, dword_ptr[rax]);
		movd(xmm0, dword_ptr[r8]);
		movd(xmm1, dword_ptr[rax]);
		movd(xmm1, dword_ptr[r8]);
		movq(xmm0, qword_ptr[rax]);
		movq(xmm0, qword_ptr[r8]);
		movq(xmm1, qword_ptr[rax]);
		movq(xmm1, qword_ptr[r8]);
		movd(dword_ptr[rax], xmm0);
		movd(dword_ptr[rax], xmm1);
		movd(dword_ptr[r8], xmm0);
		movd(dword_ptr[r8], xmm1);
		movq(qword_ptr[rax], xmm0);
		movq(qword_ptr[rax], xmm1);
		movq(qword_ptr[r8], xmm0);
		movq(qword_ptr[r8], xmm1);
#endif
	}
};

//----------------------------------------
// MOVSD/MOVSS
//----------------------------------------
extern "C" void masm_test_movsd_movss();
struct test_movsd_movss : jitasm::function<void, test_movsd_movss>
{
	void naked_main()
	{
		movsd(xmm0, xmm1);
		movsd(xmm0, qword_ptr[esp]);
		movsd(qword_ptr[esp], xmm0);
		movss(xmm0, xmm1);
		movss(xmm0, dword_ptr[esp]);
		movss(dword_ptr[esp], xmm0);
#ifdef JITASM64
		movsd(xmm8, xmm1);
		movsd(xmm8, qword_ptr[rsp]);
		movsd(qword_ptr[r8], xmm8);
		movss(xmm8, xmm1);
		movss(xmm8, dword_ptr[rsp]);
		movss(dword_ptr[r8], xmm8);
#endif
	}
};

//----------------------------------------
// SSE3
//----------------------------------------
extern "C" void masm_test_sse3();
struct test_sse3 : jitasm::function<void, test_sse3>
{
	void naked_main()
	{
		addsubps(xmm0, xmm1);
		addsubps(xmm0, xmmword_ptr[ebp]);
		addsubpd(xmm0, xmm1);
		addsubpd(xmm0, xmmword_ptr[ebp]);
		fisttp(word_ptr[ebp]);
		fisttp(dword_ptr[ebp]);
		fisttp(qword_ptr[ebp]);
		haddps(xmm0, xmm1);
		haddps(xmm0, xmmword_ptr[ebp]);
		haddpd(xmm0, xmm1);
		haddpd(xmm0, xmmword_ptr[ebp]);
		hsubps(xmm0, xmm1);
		hsubps(xmm0, xmmword_ptr[ebp]);
		hsubpd(xmm0, xmm1);
		hsubpd(xmm0, xmmword_ptr[ebp]);
		lddqu(xmm0, xmmword_ptr[ebp]);
		movddup(xmm0, xmm1);
		movddup(xmm0, qword_ptr[ebp]);
		movshdup(xmm0, xmm1);
		movshdup(xmm0, xmmword_ptr[ebp]);
		movsldup(xmm0, xmm1);
		movsldup(xmm0, xmmword_ptr[ebp]);
		monitor();
		mwait();
#ifdef JITASM64
		addsubps(xmm9, xmm10);
		addsubps(xmm9, xmmword_ptr[r9]);
		addsubpd(xmm9, xmm10);
		addsubpd(xmm9, xmmword_ptr[r9]);
		fisttp(word_ptr[r9]);
		fisttp(dword_ptr[r9]);
		fisttp(qword_ptr[r9]);
		haddps(xmm9, xmm10);
		haddps(xmm9, xmmword_ptr[r9]);
		haddpd(xmm9, xmm10);
		haddpd(xmm9, xmmword_ptr[r9]);
		hsubps(xmm9, xmm10);
		hsubps(xmm9, xmmword_ptr[r9]);
		hsubpd(xmm9, xmm10);
		hsubpd(xmm9, xmmword_ptr[r9]);
		lddqu(xmm9, xmmword_ptr[r9]);
		movddup(xmm9, xmm10);
		movddup(xmm9, qword_ptr[rbp]);
		movshdup(xmm9, xmm10);
		movshdup(xmm9, xmmword_ptr[r9]);
		movsldup(xmm9, xmm10);
		movsldup(xmm9, xmmword_ptr[r9]);
#endif
	}
};

//----------------------------------------
// SSSE3
//----------------------------------------
extern "C" void masm_test_ssse3();
struct test_ssse3 : jitasm::function<void, test_ssse3>
{
	void naked_main()
	{
		pabsb(mm0, mm1);
		pabsb(mm0, qword_ptr[esp]);
		pabsb(xmm0, xmm1);
		pabsb(xmm0, xmmword_ptr[esp]);
		pabsw(mm0, mm1);
		pabsw(mm0, qword_ptr[esp]);
		pabsw(xmm0, xmm1);
		pabsw(xmm0, xmmword_ptr[esp]);
		pabsd(mm0, mm1);
		pabsd(mm0, qword_ptr[esp]);
		pabsd(xmm0, xmm1);
		pabsd(xmm0, xmmword_ptr[esp]);
		palignr(mm0, mm1, 2);
		palignr(mm0, qword_ptr[esp], 3);
		palignr(xmm0, xmm1, 4);
		palignr(xmm0, xmmword_ptr[esp], 5);
		phaddw(mm0, mm1);
		phaddw(mm0, qword_ptr[esp]);
		phaddw(xmm0, xmm1);
		phaddw(xmm0, xmmword_ptr[esp]);
		phaddd(mm0, mm1);
		phaddd(mm0, qword_ptr[esp]);
		phaddd(xmm0, xmm1);
		phaddd(xmm0, xmmword_ptr[esp]);
		phaddsw(mm0, mm1);
		phaddsw(mm0, qword_ptr[esp]);
		phaddsw(xmm0, xmm1);
		phaddsw(xmm0, xmmword_ptr[esp]);
		phsubw(mm0, mm1);
		phsubw(mm0, qword_ptr[esp]);
		phsubw(xmm0, xmm1);
		phsubw(xmm0, xmmword_ptr[esp]);
		phsubd(mm0, mm1);
		phsubd(mm0, qword_ptr[esp]);
		phsubd(xmm0, xmm1);
		phsubd(xmm0, xmmword_ptr[esp]);
		phsubsw(mm0, mm1);
		phsubsw(mm0, qword_ptr[esp]);
		phsubsw(xmm0, xmm1);
		phsubsw(xmm0, xmmword_ptr[esp]);
		pmaddubsw(mm0, mm1);
		pmaddubsw(mm0, qword_ptr[esp]);
		pmaddubsw(xmm0, xmm1);
		pmaddubsw(xmm0, xmmword_ptr[esp]);
		pmulhrsw(mm0, mm1);
		pmulhrsw(mm0, qword_ptr[esp]);
		pmulhrsw(xmm0, xmm1);
		pmulhrsw(xmm0, xmmword_ptr[esp]);
		pshufb(mm0, mm1);
		pshufb(mm0, qword_ptr[esp]);
		pshufb(xmm0, xmm1);
		pshufb(xmm0, xmmword_ptr[esp]);
		psignb(mm0, mm1);
		psignb(mm0, qword_ptr[esp]);
		psignb(xmm0, xmm1);
		psignb(xmm0, xmmword_ptr[esp]);
		psignw(mm0, mm1);
		psignw(mm0, qword_ptr[esp]);
		psignw(xmm0, xmm1);
		psignw(xmm0, xmmword_ptr[esp]);
		psignd(mm0, mm1);
		psignd(mm0, qword_ptr[esp]);
		psignd(xmm0, xmm1);
		psignd(xmm0, xmmword_ptr[esp]);
	}
};

//----------------------------------------
// SSE4.1
//----------------------------------------
extern "C" void masm_test_sse4_1();
struct test_sse4_1 : jitasm::function<void, test_sse4_1>
{
	void naked_main()
	{
		blendps(xmm1, xmm2, 1);
		blendps(xmm1, xmmword_ptr[esp], 2);
		blendpd(xmm1, xmm2, 3);
		blendpd(xmm1, xmmword_ptr[esp], 4);
		blendvps(xmm1, xmm2, xmm0);
		blendvps(xmm1, xmmword_ptr[esp], xmm0);
		blendvpd(xmm1, xmm2, xmm0);
		blendvpd(xmm1, xmmword_ptr[esp], xmm0);
		dpps(xmm1, xmm2, 1);
		dpps(xmm1, xmmword_ptr[esp], 2);
		dppd(xmm1, xmm2, 0);
		dppd(xmm1, xmmword_ptr[esp], 1);
		extractps(eax, xmm2, 1);
		extractps(dword_ptr[esp], xmm2, 0);
		insertps(xmm1, xmm2, 0x68);
		insertps(xmm1, dword_ptr[esp], 0);
		movntdqa(xmm1, xmmword_ptr[esp]);
		mpsadbw(xmm1, xmm2, 1);
		mpsadbw(xmm1, xmmword_ptr[esp], 4);
		packusdw(xmm1, xmm2);
		packusdw(xmm1, xmmword_ptr[esp]);
		pblendvb(xmm1, xmm2, xmm0);
		pblendvb(xmm1, xmmword_ptr[esp], xmm0);
		pblendw(xmm1, xmm2, 1);
		pblendw(xmm1, xmmword_ptr[esp], 2);
		pcmpeqq(xmm1, xmm2);
		pcmpeqq(xmm1, xmmword_ptr[esp]);
		pextrb(eax, xmm2, 1);
		pextrb(byte_ptr[esp], xmm2, 2);
		pextrw(word_ptr[esp], xmm2, 1);
		pextrd(eax, xmm2, 3);
		pextrd(dword_ptr[esp], xmm2, 2);
		phminposuw(xmm2, xmm4);
		phminposuw(xmm3, xmmword_ptr[zsp]);
		pinsrb(xmm1, eax, 0);
		pinsrb(xmm1, byte_ptr[esp], 2);
		pinsrd(xmm1, eax, 1);
		pinsrd(xmm1, dword_ptr[esp], 0);
		pmaxsb(xmm1, xmm2);
		pmaxsb(xmm1, xmmword_ptr[esp]);
		pmaxsd(xmm1, xmm2);
		pmaxsd(xmm1, xmmword_ptr[esp]);
		pmaxuw(xmm1, xmm2);
		pmaxuw(xmm1, xmmword_ptr[esp]);
		pmaxud(xmm1, xmm2);
		pmaxud(xmm1, xmmword_ptr[esp]);
		pminsb(xmm1, xmm2);
		pminsb(xmm1, xmmword_ptr[esp]);
		pminsd(xmm1, xmm2);
		pminsd(xmm1, xmmword_ptr[esp]);
		pminuw(xmm1, xmm2);
		pminuw(xmm1, xmmword_ptr[esp]);
		pminud(xmm1, xmm2);
		pminud(xmm1, xmmword_ptr[esp]);
		pmovsxbw(xmm1, xmm2);
		pmovsxbw(xmm1, qword_ptr[esp]);
		pmovsxbd(xmm1, xmm2);
		pmovsxbd(xmm1, dword_ptr[esp]);
		pmovsxbq(xmm1, xmm2);
		pmovsxbq(xmm1, word_ptr[esp]);
		pmovsxwd(xmm1, xmm2);
		pmovsxwd(xmm1, qword_ptr[esp]);
		pmovsxwq(xmm1, xmm2);
		pmovsxwq(xmm1, dword_ptr[esp]);
		pmovsxdq(xmm1, xmm2);
		pmovsxdq(xmm1, qword_ptr[esp]);
		pmovzxbw(xmm1, xmm2);
		pmovzxbw(xmm1, qword_ptr[esp]);
		pmovzxbd(xmm1, xmm2);
		pmovzxbd(xmm1, dword_ptr[esp]);
		pmovzxbq(xmm1, xmm2);
		pmovzxbq(xmm1, word_ptr[esp]);
		pmovzxwd(xmm1, xmm2);
		pmovzxwd(xmm1, qword_ptr[esp]);
		pmovzxwq(xmm1, xmm2);
		pmovzxwq(xmm1, dword_ptr[esp]);
		pmovzxdq(xmm1, xmm2);
		pmovzxdq(xmm1, qword_ptr[esp]);
		pmuldq(xmm1, xmm2);
		pmuldq(xmm1, xmmword_ptr[esp]);
		pmulld(xmm1, xmm2);
		pmulld(xmm1, xmmword_ptr[esp]);
		ptest(xmm1, xmm2);
		ptest(xmm1, xmmword_ptr[esp]);
		roundps(xmm1, xmm2, 0);
		roundps(xmm1, xmmword_ptr[esp], 1);
		roundpd(xmm1, xmm2, 2);
		roundpd(xmm1, xmmword_ptr[esp], 3);
		roundss(xmm1, xmm2, 0);
		roundss(xmm1, dword_ptr[esp], 1);
		roundsd(xmm1, xmm2, 2);
		roundsd(xmm1, qword_ptr[esp], 3);
#ifdef JITASM64
		blendps(xmm8, xmm9, 1);
		blendps(xmm8, xmmword_ptr[r8], 2);
		blendpd(xmm8, xmm9, 3);
		blendpd(xmm8, xmmword_ptr[r8], 4);
		blendvps(xmm8, xmm9, xmm0);
		blendvps(xmm8, xmmword_ptr[r8], xmm0);
		blendvpd(xmm8, xmm9, xmm0);
		blendvpd(xmm8, xmmword_ptr[r8], xmm0);
		dpps(xmm8, xmm9, 1);
		dpps(xmm8, xmmword_ptr[r8], 2);
		dppd(xmm8, xmm9, 0);
		dppd(xmm8, xmmword_ptr[r8], 1);
		extractps(r9d, xmm10, 1);
		extractps(dword_ptr[r8], xmm9, 0);
		extractps(rcx, xmm10, 2);
		extractps(r8, xmm9, 3);
		insertps(xmm8, xmm9, 0x68);
		insertps(xmm8, dword_ptr[r8], 0);
		movntdqa(xmm8, xmmword_ptr[r8]);
		mpsadbw(xmm8, xmm9, 1);
		mpsadbw(xmm8, xmmword_ptr[r8], 4);
		packusdw(xmm8, xmm9);
		packusdw(xmm8, xmmword_ptr[r8]);
		pblendvb(xmm8, xmm9, xmm0);
		pblendvb(xmm8, xmmword_ptr[r8], xmm0);
		pblendw(xmm8, xmm9, 3);
		pblendw(xmm8, xmmword_ptr[r8], 4);
		pcmpeqq(xmm8, xmm9);
		pcmpeqq(xmm8, xmmword_ptr[r8]);
		pextrb(r10d, xmm9, 1);
		pextrb(byte_ptr[r8], xmm9, 2);
		pextrw(word_ptr[r8], xmm9, 1);
		pextrd(r9d, xmm9, 3);
		pextrd(dword_ptr[r8], xmm9, 2);
		pextrb(rax, xmm9, 2);
		pextrd(r8, xmm9, 3);
		pextrq(r9, xmm9, 1);
		pextrq(qword_ptr[r8], xmm9, 1);
		phminposuw(xmm9, xmm4);
		phminposuw(xmm10, xmmword_ptr[r10]);
		pinsrb(xmm8, r8d, 0);
		pinsrb(xmm8, byte_ptr[r8], 2);
		pinsrd(xmm8, r9d, 1);
		pinsrd(xmm8, dword_ptr[r8], 0);
		pinsrb(xmm8, rax, 10);
		pinsrd(xmm6, r8, 2);
		pinsrq(xmm8, r10, 1);
		pinsrq(xmm8, qword_ptr[r8], 0);
		pmaxsb(xmm8, xmm9);
		pmaxsb(xmm8, xmmword_ptr[r8]);
		pmaxsd(xmm8, xmm9);
		pmaxsd(xmm8, xmmword_ptr[r8]);
		pmaxuw(xmm8, xmm9);
		pmaxuw(xmm8, xmmword_ptr[r8]);
		pmaxud(xmm8, xmm9);
		pmaxud(xmm8, xmmword_ptr[r8]);
		pminsb(xmm8, xmm9);
		pminsb(xmm8, xmmword_ptr[r8]);
		pminsd(xmm8, xmm9);
		pminsd(xmm8, xmmword_ptr[r8]);
		pminuw(xmm8, xmm9);
		pminuw(xmm8, xmmword_ptr[r8]);
		pminud(xmm8, xmm9);
		pminud(xmm8, xmmword_ptr[r8]);
		pmovsxbw(xmm8, xmm9);
		pmovsxbw(xmm8, qword_ptr[r8]);
		pmovsxbd(xmm8, xmm9);
		pmovsxbd(xmm8, dword_ptr[r8]);
		pmovsxbq(xmm8, xmm9);
		pmovsxbq(xmm8, word_ptr[r8]);
		pmovsxwd(xmm8, xmm9);
		pmovsxwd(xmm8, qword_ptr[r8]);
		pmovsxwq(xmm8, xmm9);
		pmovsxwq(xmm8, dword_ptr[r8]);
		pmovsxdq(xmm8, xmm9);
		pmovsxdq(xmm8, qword_ptr[r8]);
		pmovzxbw(xmm8, xmm9);
		pmovzxbw(xmm8, qword_ptr[r8]);
		pmovzxbd(xmm8, xmm9);
		pmovzxbd(xmm8, dword_ptr[r8]);
		pmovzxbq(xmm8, xmm9);
		pmovzxbq(xmm8, word_ptr[r8]);
		pmovzxwd(xmm8, xmm9);
		pmovzxwd(xmm8, qword_ptr[r8]);
		pmovzxwq(xmm8, xmm9);
		pmovzxwq(xmm8, dword_ptr[r8]);
		pmovzxdq(xmm8, xmm9);
		pmovzxdq(xmm8, qword_ptr[r8]);
		pmuldq(xmm8, xmm9);
		pmuldq(xmm8, xmmword_ptr[r8]);
		pmulld(xmm8, xmm9);
		pmulld(xmm8, xmmword_ptr[r8]);
		ptest(xmm8, xmm9);
		ptest(xmm8, xmmword_ptr[r8]);
		roundps(xmm8, xmm9, 0);
		roundps(xmm8, xmmword_ptr[r8], 1);
		roundpd(xmm8, xmm9, 2);
		roundpd(xmm8, xmmword_ptr[r8], 3);
		roundss(xmm8, xmm9, 0);
		roundss(xmm8, dword_ptr[r8], 1);
		roundsd(xmm8, xmm9, 2);
		roundsd(xmm8, qword_ptr[r8], 3);
#endif
	}
};

//----------------------------------------
// SSE4.2
//----------------------------------------
extern "C" void masm_test_sse4_2();
struct test_sse4_2 : jitasm::function<void, test_sse4_2>
{
	void naked_main()
	{
		crc32(eax, bh);
		crc32(eax, byte_ptr[esi]);
		crc32(eax, bx);
		crc32(eax, word_ptr[esi]);
		crc32(eax, ecx);
		crc32(eax, dword_ptr[esi]);
		pcmpestri(zcx, xmm2, zax, xmm1, zdx, 0);
		pcmpestri(zcx, xmm2, zax, xmmword_ptr[esi], zdx, 0);
		pcmpestrm(xmm0, xmm2, zax, xmm1, zdx, 1);
		pcmpestrm(xmm0, xmm2, zax, xmmword_ptr[esi], zdx, 1);
		pcmpistri(zcx, xmm2, xmm1, 0);
		pcmpistri(zcx, xmm2, xmmword_ptr[esi], 0);
		pcmpistrm(xmm0, xmm2, xmm1, 1);
		pcmpistrm(xmm0, xmm2, xmmword_ptr[esi], 1);
		pcmpgtq(xmm0, xmm1);
		pcmpgtq(xmm0, xmmword_ptr[esi]);
		popcnt(ax, cx);
		popcnt(bx, word_ptr[esi]);
		popcnt(eax, ecx);
		popcnt(eax, dword_ptr[esi]);

#ifdef JITASM64
		crc32(eax, r9b);
		crc32(r8d, byte_ptr[rsi]);
		crc32(eax, r9w);
		crc32(r8d, word_ptr[esp]);
		crc32(eax, r9d);
		crc32(r8d, dword_ptr[rsi]);
		crc32(rax, bl);
		crc32(r8, byte_ptr[rsi]);
		crc32(r9, r10);
		crc32(r9, qword_ptr[rsi]);
		pcmpestri(zcx, xmm10, rax, xmm9, rdx, 0);
		pcmpestri(zcx, xmm10, rax, xmmword_ptr[r8d], rdx, 0);
		pcmpestrm(xmm0, xmm10, rax, xmm9, rdx, 1);
		pcmpestrm(xmm0, xmm10, rax, xmmword_ptr[esi], rdx, 1);
		pcmpistri(zcx, xmm10, xmm9, 0);
		pcmpistri(zcx, xmm10, xmmword_ptr[esi], 0);
		pcmpistrm(xmm0, xmm10, xmm9, 1);
		pcmpistrm(xmm0, xmm10, xmmword_ptr[esi], 1);
		pcmpgtq(xmm8, xmm9);
		pcmpgtq(xmm8, xmmword_ptr[esi]);
		popcnt(r8w, cx);
		popcnt(r9w, word_ptr[esp]);
		popcnt(r8d, r9d);
		popcnt(r8d, dword_ptr[rsi]);
		popcnt(r9, rax);
		popcnt(r9, qword_ptr[rsi]);
#endif
	}
};

//----------------------------------------
// AVX A~
//----------------------------------------
extern "C" void masm_test_avx_a();
struct test_avx_a : jitasm::function<void, test_avx_a>
{
	void naked_main()
	{
		vaddpd(xmm1, xmm2, xmm3);
		vaddpd(xmm1, xmm2, xmmword_ptr[edx]);
		vaddpd(ymm1, ymm2, ymm3);
		vaddpd(ymm1, ymm2, ymmword_ptr[edx]);
		vaddps(xmm1, xmm2, xmm3);
		vaddps(xmm1, xmm2, xmmword_ptr[edx]);
		vaddps(ymm1, ymm2, ymm3);
		vaddps(ymm1, ymm2, ymmword_ptr[edx]);
		vaddsd(xmm1, xmm2, xmm4);
		vaddsd(xmm1, xmm2, qword_ptr[edx]);
		vaddss(xmm1, xmm2, xmm5);
		vaddss(xmm1, xmm2, dword_ptr[edx]);
		vaddsubpd(xmm1, xmm2, xmm3);
		vaddsubpd(xmm1, xmm2, xmmword_ptr[edx]);
		vaddsubpd(ymm1, ymm2, ymm3);
		vaddsubpd(ymm1, ymm2, ymmword_ptr[edx]);
		vaddsubps(xmm1, xmm2, xmm3);
		vaddsubps(xmm1, xmm2, xmmword_ptr[edx]);
		vaddsubps(ymm1, ymm2, ymm3);
		vaddsubps(ymm1, ymm2, ymmword_ptr[edx]);
		aesenc(xmm1, xmm2);
		aesenc(xmm1, xmmword_ptr[zdx]);
		vaesenc(xmm1, xmm2, xmm3);
		vaesenc(xmm1, xmm2, xmmword_ptr[edx]);
		aesenclast(xmm1, xmm2);
		aesenclast(xmm1, xmmword_ptr[zdx]);
		vaesenclast(xmm1, xmm2, xmm3);
		vaesenclast(xmm1, xmm2, xmmword_ptr[edx]);
		aesdec(xmm1, xmm2);
		aesdec(xmm1, xmmword_ptr[zdx]);
		vaesdec(xmm1, xmm2, xmm3);
		vaesdec(xmm1, xmm2, xmmword_ptr[edx]);
		aesdeclast(xmm1, xmm2);
		aesdeclast(xmm1, xmmword_ptr[zdx]);
		vaesdeclast(xmm1, xmm2, xmm3);
		vaesdeclast(xmm1, xmm2, xmmword_ptr[edx]);
		aesimc(xmm1, xmm2);
		aesimc(xmm1, xmmword_ptr[zdx]);
		vaesimc(xmm1, xmm2);
		vaesimc(xmm1, xmmword_ptr[edx]);
		aeskeygenassist(xmm1, xmm2, 3);
		aeskeygenassist(xmm1, xmmword_ptr[zdx], 3);
		vaeskeygenassist(xmm1, xmm2, 3);
		vaeskeygenassist(xmm1, xmmword_ptr[edx], 3);
		vandpd(xmm1, xmm2, xmm3);
		vandpd(xmm1, xmm2, xmmword_ptr[edx]);
		vandpd(ymm1, ymm2, ymm3);
		vandpd(ymm1, ymm2, ymmword_ptr[edx]);
		vandps(xmm1, xmm2, xmm3);
		vandps(xmm1, xmm2, xmmword_ptr[edx]);
		vandps(ymm1, ymm2, ymm3);
		vandps(ymm1, ymm2, ymmword_ptr[edx]);
		vandnpd(xmm1, xmm2, xmm3);
		vandnpd(xmm1, xmm2, xmmword_ptr[edx]);
		vandnpd(ymm1, ymm2, ymm3);
		vandnpd(ymm1, ymm2, ymmword_ptr[edx]);
		vandnps(xmm1, xmm2, xmm3);
		vandnps(xmm1, xmm2, xmmword_ptr[edx]);
		vandnps(ymm1, ymm2, ymm3);
		vandnps(ymm1, ymm2, ymmword_ptr[edx]);
#ifdef JITASM64
		vaddpd(xmm9, xmm10, xmm11);
		vaddpd(xmm9, xmm10, xmmword_ptr[r11]);
		vaddpd(ymm9, ymm10, ymm11);
		vaddpd(ymm9, ymm10, ymmword_ptr[r11]);
		vaddps(xmm9, xmm10, xmm11);
		vaddps(xmm9, xmm10, xmmword_ptr[r11]);
		vaddps(ymm9, ymm10, ymm11);
		vaddps(ymm9, ymm10, ymmword_ptr[r11]);
		vaddsd(xmm9, xmm10, qword_ptr[r11]);
		vaddss(xmm9, xmm10, dword_ptr[r11]);
		vaddsubpd(xmm9, xmm10, xmm11);
		vaddsubpd(xmm9, xmm10, xmmword_ptr[r11]);
		vaddsubpd(ymm9, ymm10, ymm11);
		vaddsubpd(ymm9, ymm10, ymmword_ptr[r11]);
		vaddsubps(xmm9, xmm10, xmm11);
		vaddsubps(xmm9, xmm10, xmmword_ptr[r11]);
		vaddsubps(ymm9, ymm10, ymm11);
		vaddsubps(ymm9, ymm10, ymmword_ptr[r11]);
		vaesenc(xmm9, xmm10, xmm11);
		vaesenc(xmm9, xmm10, xmmword_ptr[r11]);
		vaesenclast(xmm9, xmm10, xmm11);
		vaesenclast(xmm9, xmm10, xmmword_ptr[r11]);
		vaesdec(xmm9, xmm10, xmm11);
		vaesdec(xmm9, xmm10, xmmword_ptr[r11]);
		vaesdeclast(xmm9, xmm10, xmm11);
		vaesdeclast(xmm9, xmm10, xmmword_ptr[r11]);
		vaesimc(xmm9, xmm10);
		vaesimc(xmm9, xmmword_ptr[r11]);
		vaeskeygenassist(xmm9, xmm10, 3);
		vaeskeygenassist(xmm9, xmmword_ptr[r11], 3);
		vandpd(xmm9, xmm10, xmm11);
		vandpd(xmm9, xmm10, xmmword_ptr[r11]);
		vandpd(ymm9, ymm10, ymm11);
		vandpd(ymm9, ymm10, ymmword_ptr[r11]);
		vandps(xmm9, xmm10, xmm11);
		vandps(xmm9, xmm10, xmmword_ptr[r11]);
		vandps(ymm9, ymm10, ymm11);
		vandps(ymm9, ymm10, ymmword_ptr[r11]);
		vandnpd(xmm9, xmm10, xmm11);
		vandnpd(xmm9, xmm10, xmmword_ptr[r11]);
		vandnpd(ymm9, ymm10, ymm11);
		vandnpd(ymm9, ymm10, ymmword_ptr[r11]);
		vandnps(xmm9, xmm10, xmm11);
		vandnps(xmm9, xmm10, xmmword_ptr[r11]);
		vandnps(ymm9, ymm10, ymm11);
		vandnps(ymm9, ymm10, ymmword_ptr[r11]);
#endif
	}
};

//----------------------------------------
// AVX B~
//----------------------------------------
extern "C" void masm_test_avx_b();
struct test_avx_b : jitasm::function<void, test_avx_b>
{
	void naked_main()
	{
		vblendpd(xmm1, xmm2, xmm2, 3);
		vblendpd(xmm1, xmm2, xmmword_ptr[edx], 3);
		vblendpd(ymm1, ymm2, ymm2, 3);
		vblendpd(ymm1, ymm2, ymmword_ptr[edx], 3);
		vblendps(xmm1, xmm2, xmm2, 3);
		vblendps(xmm1, xmm2, xmmword_ptr[edx], 3);
		vblendps(ymm1, ymm2, ymm2, 3);
		vblendps(ymm1, ymm2, ymmword_ptr[edx], 3);
		vblendvpd(xmm1, xmm2, xmm2, xmm3);
		vblendvpd(xmm1, xmm2, xmmword_ptr[edx], xmm3);
		vblendvpd(ymm1, ymm2, ymm2, ymm3);
		vblendvpd(ymm1, ymm2, ymmword_ptr[edx], ymm3);
		vblendvps(xmm1, xmm2, xmm2, xmm3);
		vblendvps(xmm1, xmm2, xmmword_ptr[edx], xmm3);
		vblendvps(ymm1, ymm2, ymm2, ymm3);
		vblendvps(ymm1, ymm2, ymmword_ptr[edx], ymm3);
		vbroadcastss(xmm1, dword_ptr[edx]);
		vbroadcastss(ymm1, dword_ptr[edx]);
		vbroadcastsd(ymm1, qword_ptr[edx]);
		vbroadcastf128(ymm1, xmmword_ptr[edx]);
		vcmppd(xmm1, xmm2, xmm2, 3);
		vcmppd(xmm1, xmm2, xmmword_ptr[edx], 3);
		vcmppd(ymm1, ymm2, ymm2, 3);
		vcmppd(ymm1, ymm2, ymmword_ptr[edx], 3);
		vcmpps(xmm1, xmm2, xmm2, 3);
		vcmpps(xmm1, xmm2, xmmword_ptr[edx], 3);
		vcmpps(ymm1, ymm2, ymm2, 3);
		vcmpps(ymm1, ymm2, ymmword_ptr[edx], 3);
		vcmpsd(xmm1, xmm2, xmm2, 3);
		vcmpsd(xmm1, xmm2, qword_ptr[edx], 3);
		vcmpss(xmm1, xmm2, xmm2, 3);
		vcmpss(xmm1, xmm2, dword_ptr[edx], 3);
		vcomisd(xmm1, xmm2);
		vcomisd(xmm1, qword_ptr[edx]);
		vcomiss(xmm1, xmm2);
		vcomiss(xmm1, dword_ptr[edx]);
		vcvtdq2pd(xmm1, xmm2);
		vcvtdq2pd(xmm1, qword_ptr[edx]);
		vcvtdq2pd(ymm1, xmm2);
		vcvtdq2pd(ymm1, xmmword_ptr[edx]);
		vcvtdq2ps(xmm1, xmm2);
		vcvtdq2ps(xmm1, xmmword_ptr[edx]);
		vcvtdq2ps(ymm1, ymm2);
		vcvtdq2ps(ymm1, ymmword_ptr[edx]);
		vcvtpd2dq(xmm1, xmm2);
		vcvtpd2dq(xmm1, xmmword_ptr[edx]);
		vcvtpd2dq(xmm1, ymm2);
		vcvtpd2dq(xmm1, ymmword_ptr[edx]);
		vcvtpd2ps(xmm1, xmm2);
		vcvtpd2ps(xmm1, xmmword_ptr[edx]);
		vcvtpd2ps(xmm1, ymm2);
		vcvtpd2ps(xmm1, ymmword_ptr[edx]);
		vcvtps2dq(xmm1, xmm2);
		vcvtps2dq(xmm1, xmmword_ptr[edx]);
		vcvtps2dq(ymm1, ymm2);
		vcvtps2dq(ymm1, ymmword_ptr[edx]);
		vcvtps2pd(xmm1, xmm2);
		vcvtps2pd(xmm1, qword_ptr[edx]);
		vcvtps2pd(ymm1, xmm2);
		vcvtps2pd(ymm1, xmmword_ptr[edx]);
		vcvtsd2si(esp, xmm2);
		vcvtsd2si(esp, qword_ptr[edx]);
#ifdef JITASM64
		vcvtsd2si(rsp, xmm2);
		vcvtsd2si(rsp, qword_ptr[edx]);
#endif
		vcvtsd2ss(xmm1, xmm2, xmm2);
		vcvtsd2ss(xmm1, xmm2, qword_ptr[edx]);
		vcvtsi2sd(xmm1, xmm2, ebx);
		vcvtsi2sd(xmm1, xmm2, dword_ptr[edx]);
#ifdef JITASM64
		vcvtsi2sd(xmm1, xmm2, rbx);
		vcvtsi2sd(xmm1, xmm2, qword_ptr[edx]);
#endif
		vcvtsi2ss(xmm1, xmm2, ebx);
		vcvtsi2ss(xmm1, xmm2, dword_ptr[edx]);
#ifdef JITASM64
		vcvtsi2ss(xmm1, xmm2, rbx);
		vcvtsi2ss(xmm1, xmm2, qword_ptr[edx]);
#endif
		vcvtss2sd(xmm1, xmm2, xmm2);
		vcvtss2sd(xmm1, xmm2, dword_ptr[edx]);
		vcvtss2si(ecx, xmm2);
		vcvtss2si(ecx, dword_ptr[edx]);
#ifdef JITASM64
		vcvtss2si(rcx, xmm2);
		vcvtss2si(rcx, dword_ptr[edx]);
#endif
		vcvttpd2dq(xmm1, xmm2);
		vcvttpd2dq(xmm1, xmmword_ptr[edx]);
		vcvttpd2dq(xmm1, ymm2);
		vcvttpd2dq(xmm1, ymmword_ptr[edx]);
		vcvttps2dq(xmm1, xmm2);
		vcvttps2dq(xmm1, xmmword_ptr[edx]);
		vcvttps2dq(ymm1, ymm2);
		vcvttps2dq(ymm1, ymmword_ptr[edx]);
		vcvttsd2si(ecx, xmm2);
		vcvttsd2si(ecx, qword_ptr[edx]);
#ifdef JITASM64
		vcvttsd2si(rcx, xmm2);
		vcvttsd2si(rcx, qword_ptr[edx]);
#endif
		vcvttss2si(ecx, xmm2);
		vcvttss2si(ecx, dword_ptr[edx]);
#ifdef JITASM64
		vcvttss2si(rcx, xmm2);
		vcvttss2si(rcx, dword_ptr[edx]);
#endif
	}
};

//----------------------------------------
// AVX D~
//----------------------------------------
extern "C" void masm_test_avx_d();
struct test_avx_d : jitasm::function<void, test_avx_d>
{
	void naked_main()
	{
		vdivpd(xmm1, xmm2, xmm3);
		vdivpd(xmm1, xmm2, xmmword_ptr[edx]);
		vdivpd(ymm1, ymm2, ymm3);
		vdivpd(ymm1, ymm2, ymmword_ptr[edx]);
		vdivps(xmm1, xmm2, xmm3);
		vdivps(xmm1, xmm2, xmmword_ptr[edx]);
		vdivps(ymm1, ymm2, ymm3);
		vdivps(ymm1, ymm2, ymmword_ptr[edx]);
		vdivsd(xmm1, xmm2, xmm3);
		vdivsd(xmm1, xmm2, qword_ptr[edx]);
		vdivss(xmm1, xmm2, xmm3);
		vdivss(xmm1, xmm2, dword_ptr[edx]);
		vdppd(xmm1, xmm2, xmm3, 5);
		vdppd(xmm1, xmm2, xmmword_ptr[edx], 5);
		vdpps(xmm1, xmm2, xmm3, 5);
		vdpps(xmm1, xmm2, xmmword_ptr[edx], 5);
		vdpps(ymm1, ymm2, ymm3, 5);
		vdpps(ymm1, ymm2, ymmword_ptr[edx], 5);
		vextractf128(xmm1, ymm2, 1);
		vextractf128(xmmword_ptr[edx], ymm2, 1);
		vextractps(eax, xmm2, 5);
		vextractps(dword_ptr[eax], xmm2, 5);
		vhaddpd(xmm1, xmm2, xmm3);
		vhaddpd(xmm1, xmm2, xmmword_ptr[edx]);
		vhaddpd(ymm1, ymm2, ymm3);
		vhaddpd(ymm1, ymm2, ymmword_ptr[edx]);
		vhaddps(xmm1, xmm2, xmm3);
		vhaddps(xmm1, xmm2, xmmword_ptr[edx]);
		vhaddps(ymm1, ymm2, ymm3);
		vhaddps(ymm1, ymm2, ymmword_ptr[edx]);
		vhsubpd(xmm1, xmm2, xmm3);
		vhsubpd(xmm1, xmm2, xmmword_ptr[edx]);
		vhsubpd(ymm1, ymm2, ymm3);
		vhsubpd(ymm1, ymm2, ymmword_ptr[edx]);
		vhsubps(xmm1, xmm2, xmm3);
		vhsubps(xmm1, xmm2, xmmword_ptr[edx]);
		vhsubps(ymm1, ymm2, ymm3);
		vhsubps(ymm1, ymm2, ymmword_ptr[edx]);
		vinsertf128(ymm1, ymm2, xmm3, 1);
		vinsertf128(ymm1, ymm2, xmmword_ptr[edx], 1);
		vinsertps(xmm1, xmm2, xmm3, 1);
		vinsertps(xmm1, xmm2, dword_ptr[edx], 1);
		vlddqu(xmm1, xmmword_ptr[edx]);
		vlddqu(ymm1, ymmword_ptr[edx]);
		vldmxcsr(dword_ptr[edx]);
		vmaskmovdqu(xmm1, xmm2, zdi);
		vmaskmovps(xmm1, xmm2, xmmword_ptr[edx]);
		vmaskmovps(ymm1, ymm2, ymmword_ptr[edx]);
		vmaskmovpd(xmm1, xmm2, xmmword_ptr[edx]);
		vmaskmovpd(ymm1, ymm2, ymmword_ptr[edx]);
		vmaskmovps(xmmword_ptr[edx], xmm2, xmm3);
		vmaskmovps(ymmword_ptr[edx], ymm2, ymm3);
		vmaskmovpd(xmmword_ptr[edx], xmm2, xmm3);
		vmaskmovpd(ymmword_ptr[edx], ymm2, ymm3);
		vmaxpd(xmm1, xmm2, xmm3);
		vmaxpd(xmm1, xmm2, xmmword_ptr[edx]);
		vmaxpd(ymm1, ymm2, ymm3);
		vmaxpd(ymm1, ymm2, ymmword_ptr[edx]);
		vmaxps(xmm1, xmm2, xmm3);
		vmaxps(xmm1, xmm2, xmmword_ptr[edx]);
		vmaxps(ymm1, ymm2, ymm3);
		vmaxps(ymm1, ymm2, ymmword_ptr[edx]);
		vmaxsd(xmm1, xmm2, xmm3);
		vmaxsd(xmm1, xmm2, qword_ptr[edx]);
		vmaxss(xmm1, xmm2, xmm3);
		vmaxss(xmm1, xmm2, dword_ptr[edx]);
		vminpd(xmm1, xmm2, xmm3);
		vminpd(xmm1, xmm2, xmmword_ptr[edx]);
		vminpd(ymm1, ymm2, ymm3);
		vminpd(ymm1, ymm2, ymmword_ptr[edx]);
		vminps(xmm1, xmm2, xmm3);
		vminps(xmm1, xmm2, xmmword_ptr[edx]);
		vminps(ymm1, ymm2, ymm3);
		vminps(ymm1, ymm2, ymmword_ptr[edx]);
		vminsd(xmm1, xmm2, xmm3);
		vminsd(xmm1, xmm2, qword_ptr[edx]);
		vminss(xmm1, xmm2, xmm3);
		vminss(xmm1, xmm2, dword_ptr[edx]);
		vmovapd(xmm1, xmm2);
		vmovapd(xmm1, xmmword_ptr[edx]);
		vmovapd(xmmword_ptr[edx], xmm2);
		vmovapd(ymm1, ymm2);
		vmovapd(ymm1, ymmword_ptr[edx]);
		vmovapd(ymmword_ptr[edx], ymm2);
		vmovaps(xmm1, xmm2);
		vmovaps(xmm1, xmmword_ptr[edx]);
		vmovaps(xmmword_ptr[edx], xmm2);
		vmovaps(ymm1, ymm2);
		vmovaps(ymm1, ymmword_ptr[edx]);
		vmovaps(ymmword_ptr[edx], ymm2);
		vmovd(xmm3, edx);
		vmovd(xmm3, dword_ptr[edx]);
		vmovd(eax, xmm4);
		vmovd(dword_ptr[eax], xmm4);
		vmovq(xmm3, xmm4);
		vmovq(xmm3, qword_ptr[edx]);
		vmovq(qword_ptr[eax], xmm4);
#ifdef JITASM64
		vmovq(xmm3, rdx);
		vmovq(rax, xmm4);
#endif
		vmovddup(xmm3, xmm4);
		vmovddup(xmm3, qword_ptr[edx]);
		vmovddup(ymm3, ymm4);
		vmovddup(ymm3, ymmword_ptr[edx]);
		vmovdqa(xmm3, xmm4);
		vmovdqa(xmm3, xmmword_ptr[edx]);
		vmovdqa(xmmword_ptr[eax], xmm4);
		vmovdqa(ymm3, ymm4);
		vmovdqa(ymm3, ymmword_ptr[edx]);
		vmovdqa(ymmword_ptr[eax], ymm4);
		vmovdqu(xmm3, xmm4);
		vmovdqu(xmm3, xmmword_ptr[edx]);
		vmovdqu(xmmword_ptr[eax], xmm4);
		vmovdqu(ymm3, ymm4);
		vmovdqu(ymm3, ymmword_ptr[edx]);
		vmovdqu(ymmword_ptr[eax], ymm4);
		vmovhlps(xmm3, xmm4, xmm5);
		vmovhpd(xmm3, xmm4, qword_ptr[edx]);
		vmovhpd(qword_ptr[eax], xmm4);
		vmovhps(xmm3, xmm4, qword_ptr[edx]);
		vmovhps(qword_ptr[eax], xmm4);
		vmovlhps(xmm3, xmm4, xmm5);
		vmovlpd(xmm3, xmm4, qword_ptr[edx]);
		vmovlpd(qword_ptr[eax], xmm4);
		vmovlps(xmm3, xmm4, qword_ptr[edx]);
		vmovlps(qword_ptr[eax], xmm4);
		vmovmskpd(eax, xmm5);
		vmovmskpd(eax, ymm5);
#ifdef JITASM64
		vmovmskpd(rax, xmm5);
		vmovmskpd(rax, ymm5);
#endif
		vmovmskps(eax, xmm5);
		vmovmskps(eax, ymm5);
#ifdef JITASM64
		vmovmskps(rax, xmm5);
		vmovmskps(rax, ymm5);
#endif
		vmovntdq(xmmword_ptr[eax], xmm5);
		vmovntdq(ymmword_ptr[eax], ymm5);
		vmovntdqa(xmm3, xmmword_ptr[edi]);
		vmovntpd(xmmword_ptr[eax], xmm5);
		vmovntpd(ymmword_ptr[eax], ymm5);
		vmovntps(xmmword_ptr[eax], xmm5);
		vmovntps(ymmword_ptr[eax], ymm5);
		vmovsd(xmm3, xmm5, xmm6);
		vmovsd(xmm3, qword_ptr[edi]);
		vmovsd(qword_ptr[eax], xmm5);
		vmovshdup(xmm3, xmm5);
		vmovshdup(xmm3, xmmword_ptr[edi]);
		vmovshdup(ymm3, ymm5);
		vmovshdup(ymm3, ymmword_ptr[edi]);
		vmovsldup(xmm3, xmm5);
		vmovsldup(xmm3, xmmword_ptr[edi]);
		vmovsldup(ymm3, ymm5);
		vmovsldup(ymm3, ymmword_ptr[edi]);
		vmovss(xmm3, xmm5, xmm6);
		vmovss(xmm3, dword_ptr[edi]);
		vmovss(dword_ptr[eax], xmm5);
		vmovupd(xmm3, xmm5);
		vmovupd(xmm3, xmmword_ptr[edi]);
		vmovupd(xmmword_ptr[eax], xmm3);
		vmovupd(ymm3, ymm5);
		vmovupd(ymm3, ymmword_ptr[edi]);
		vmovupd(ymmword_ptr[eax], ymm3);
		vmovups(xmm3, xmm5);
		vmovups(xmm3, xmmword_ptr[edi]);
		vmovups(xmmword_ptr[eax], xmm3);
		vmovups(ymm3, ymm5);
		vmovups(ymm3, ymmword_ptr[edi]);
		vmovups(ymmword_ptr[eax], ymm3);
		vmpsadbw(xmm3, xmm5, xmm6, 2);
		vmpsadbw(xmm3, xmm5, xmmword_ptr[edi], 2);
		vmulpd(xmm3, xmm5, xmm6);
		vmulpd(xmm3, xmm5, xmmword_ptr[edi]);
		vmulpd(ymm3, ymm5, ymm6);
		vmulpd(ymm3, ymm5, ymmword_ptr[edi]);
		vmulps(xmm3, xmm5, xmm6);
		vmulps(xmm3, xmm5, xmmword_ptr[edi]);
		vmulps(ymm3, ymm5, ymm6);
		vmulps(ymm3, ymm5, ymmword_ptr[edi]);
		vmulsd(xmm3, xmm5, xmm6);
		vmulsd(xmm3, xmm5, qword_ptr[edi]);
		vmulss(xmm3, xmm5, xmm6);
		vmulss(xmm3, xmm5, dword_ptr[edi]);
	}
};

//----------------------------------------
// AVX O~
//----------------------------------------
extern "C" void masm_test_avx_o();
struct test_avx_o : jitasm::function<void, test_avx_o>
{
	void naked_main()
	{
		vorpd(xmm1, xmm2, xmm3);
		vorpd(xmm1, xmm2, xmmword_ptr[edx]);
		vorpd(ymm1, ymm2, ymm3);
		vorpd(ymm1, ymm2, ymmword_ptr[edx]);
		vorps(xmm1, xmm2, xmm3);
		vorps(xmm1, xmm2, xmmword_ptr[edx]);
		vorps(ymm1, ymm2, ymm3);
		vorps(ymm1, ymm2, ymmword_ptr[edx]);
		vpabsb(xmm1, xmm2);
		vpabsb(xmm1, xmmword_ptr[edx]);
		vpabsw(xmm1, xmm2);
		vpabsw(xmm1, xmmword_ptr[edx]);
		vpabsd(xmm1, xmm2);
		vpabsd(xmm1, xmmword_ptr[edx]);
		vpacksswb(xmm1, xmm2, xmm3);
		vpacksswb(xmm1, xmm2, xmmword_ptr[edx]);
		vpackssdw(xmm1, xmm2, xmm3);
		vpackssdw(xmm1, xmm2, xmmword_ptr[edx]);
		vpackuswb(xmm1, xmm2, xmm3);
		vpackuswb(xmm1, xmm2, xmmword_ptr[edx]);
		vpackusdw(xmm1, xmm2, xmm3);
		vpackusdw(xmm1, xmm2, xmmword_ptr[edx]);
		vpaddb(xmm1, xmm2, xmm3);
		vpaddb(xmm1, xmm2, xmmword_ptr[edx]);
		vpaddw(xmm1, xmm2, xmm3);
		vpaddw(xmm1, xmm2, xmmword_ptr[edx]);
		vpaddd(xmm1, xmm2, xmm3);
		vpaddd(xmm1, xmm2, xmmword_ptr[edx]);
		vpaddq(xmm1, xmm2, xmm3);
		vpaddq(xmm1, xmm2, xmmword_ptr[edx]);
		vpaddsb(xmm1, xmm2, xmm3);
		vpaddsb(xmm1, xmm2, xmmword_ptr[edx]);
		vpaddsw(xmm1, xmm2, xmm3);
		vpaddsw(xmm1, xmm2, xmmword_ptr[edx]);
		vpaddusb(xmm1, xmm2, xmm3);
		vpaddusb(xmm1, xmm2, xmmword_ptr[edx]);
		vpaddusw(xmm1, xmm2, xmm3);
		vpaddusw(xmm1, xmm2, xmmword_ptr[edx]);
		vpalignr(xmm1, xmm2, xmm3, 1);
		vpalignr(xmm1, xmm2, xmmword_ptr[edx], 1);
		vpand(xmm1, xmm2, xmm3);
		vpand(xmm1, xmm2, xmmword_ptr[edx]);
		vpandn(xmm1, xmm2, xmm3);
		vpandn(xmm1, xmm2, xmmword_ptr[edx]);
		vpavgb(xmm1, xmm2, xmm3);
		vpavgb(xmm1, xmm2, xmmword_ptr[edx]);
		vpavgw(xmm1, xmm2, xmm3);
		vpavgw(xmm1, xmm2, xmmword_ptr[edx]);
		vpblendvb(xmm1, xmm2, xmmword_ptr[edx], xmm4);
		vpblendvb(xmm1, xmm2, xmm3, xmm4);
		vpblendw(xmm1, xmm2, xmmword_ptr[edx], 5);
		vpblendw(xmm1, xmm2, xmm3, 5);
		pclmulqdq(xmm1, xmmword_ptr[zdx], 1);
		pclmulqdq(xmm1, xmm2, 1);
		vpclmulqdq(xmm1, xmm2, xmmword_ptr[edx], 1);
		vpclmulqdq(xmm1, xmm2, xmm3, 1);
		vpcmpeqb(xmm0, xmm1, xmm2);
		vpcmpeqb(xmm0, xmm1, xmmword_ptr[esi]);
		vpcmpeqw(xmm0, xmm1, xmm2);
		vpcmpeqw(xmm0, xmm1, xmmword_ptr[esi]);
		vpcmpeqd(xmm0, xmm1, xmm2);
		vpcmpeqd(xmm0, xmm1, xmmword_ptr[esi]);
		vpcmpeqq(xmm0, xmm1, xmm2);
		vpcmpeqq(xmm0, xmm1, xmmword_ptr[esi]);
		vpcmpgtb(xmm0, xmm1, xmm2);
		vpcmpgtb(xmm0, xmm1, xmmword_ptr[esi]);
		vpcmpgtw(xmm0, xmm1, xmm2);
		vpcmpgtw(xmm0, xmm1, xmmword_ptr[esi]);
		vpcmpgtd(xmm0, xmm1, xmm2);
		vpcmpgtd(xmm0, xmm1, xmmword_ptr[esi]);
		vpcmpgtq(xmm0, xmm1, xmm2);
		vpcmpgtq(xmm0, xmm1, xmmword_ptr[esi]);
		vpcmpestri(zcx, xmm2, zax, xmm1, zdx, 0);
		vpcmpestri(zcx, xmm2, zax, xmmword_ptr[esi], zdx, 0);
		vpcmpestrm(xmm0, xmm2, zax, xmm1, zdx, 1);
		vpcmpestrm(xmm0, xmm2, zax, xmmword_ptr[esi], zdx, 1);
		vpcmpistri(zcx, xmm2, xmm1, 0);
		vpcmpistri(zcx, xmm2, xmmword_ptr[esi], 0);
		vpcmpistrm(xmm0, xmm2, xmm1, 1);
		vpcmpistrm(xmm0, xmm2, xmmword_ptr[esi], 1);
		vpermilpd(xmm1, xmm2, xmm3);
		vpermilpd(xmm1, xmm2, xmmword_ptr[zsi]);
		vpermilpd(ymm4, ymm5, ymm6);
		vpermilpd(ymm4, ymm5, ymmword_ptr[zsp]);
		vpermilpd(xmm1, xmm2, 1);
		vpermilpd(xmm1, xmmword_ptr[zsi], 2);
		vpermilpd(ymm4, ymm5, 3);
		vpermilpd(ymm4, ymmword_ptr[zsp], 4);
		vpermilps(xmm1, xmm2, xmm3);
		vpermilps(xmm1, xmm2, xmmword_ptr[esi]);
		vpermilps(ymm4, ymm5, ymm6);
		vpermilps(ymm4, ymm5, ymmword_ptr[zsp]);
		vpermilps(xmm1, xmm2, 3);
		vpermilps(xmm1, xmmword_ptr[esp], 2);
		vpermilps(ymm4, ymm5, 1);
		vpermilps(ymm4, ymmword_ptr[zsp], 1);
		vperm2f128(ymm4, ymm5, ymm6, 1);
		vperm2f128(ymm4, ymm5, ymmword_ptr[zsp], 2);
		vpextrb(ecx, xmm7, 13);
		vpextrb(byte_ptr[zsi], xmm7, 5);
		vpextrw(edx, xmm7, 6);
		vpextrw(word_ptr[zsp], xmm7, 4);
		vpextrd(eax, xmm7, 3);
		vpextrd(dword_ptr[esp], xmm7, 2);
#ifdef JITASM64
		vpextrb(r9, xmm8, 12);
		vpextrw(rax, xmm9, 7);
		vpextrd(r10, xmm3, 3);
		vpextrq(rcx, xmm10, 0);
		vpextrq(qword_ptr[r13], xmm2, 1);
#endif
		vphaddw(xmm7, xmm6, xmm5);
		vphaddw(xmm7, xmm6, xmmword_ptr[zsp]);
		vphaddd(xmm7, xmm6, xmm5);
		vphaddd(xmm7, xmm6, xmmword_ptr[zsp]);
		vphaddsw(xmm7, xmm6, xmm5);
		vphaddsw(xmm7, xmm6, xmmword_ptr[zsp]);
		vphminposuw(xmm7, xmm5);
		vphminposuw(xmm7, xmmword_ptr[zsp]);
		vphsubw(xmm7, xmm6, xmm5);
		vphsubw(xmm7, xmm6, xmmword_ptr[zsp]);
		vphsubd(xmm7, xmm6, xmm5);
		vphsubd(xmm7, xmm6, xmmword_ptr[zsp]);
		vphsubsw(xmm7, xmm6, xmm5);
		vphsubsw(xmm7, xmm6, xmmword_ptr[zsp]);
		vpinsrb(xmm2, xmm0, ebx, 15);
		vpinsrb(xmm2, xmm0, byte_ptr[zsi], 7);
		vpinsrw(xmm2, xmm0, ecx, 6);
		vpinsrw(xmm2, xmm0, word_ptr[zdi], 5);
		vpinsrd(xmm2, xmm1, eax, 3);
		vpinsrd(xmm2, xmm0, dword_ptr[esp], 2);
#ifdef JITASM64
		vpinsrb(xmm7, xmm0, r9, 13);
		vpinsrw(xmm9, xmm0, r10, 4);
		vpinsrd(xmm10, xmm0, r11, 1);
		vpinsrq(xmm11, xmm0, rcx, 1);
		vpinsrq(xmm12, xmm0, qword_ptr[r12], 0);
#endif
		vpmaddwd(xmm2, xmm1, xmm6);
		vpmaddwd(xmm2, xmm1, xmmword_ptr[esi]);
		vpmaddubsw(xmm2, xmm1, xmm5);
		vpmaddubsw(xmm2, xmm1, xmmword_ptr[zsi]);
		vpmaxsb(xmm6, xmm5, xmm4);
		vpmaxsb(xmm6, xmm5, xmmword_ptr[zsi]);
		vpmaxsw(xmm6, xmm5, xmm4);
		vpmaxsw(xmm6, xmm5, xmmword_ptr[zsi]);
		vpmaxsd(xmm6, xmm5, xmm4);
		vpmaxsd(xmm6, xmm5, xmmword_ptr[zsi]);
		vpmaxub(xmm6, xmm5, xmm4);
		vpmaxub(xmm6, xmm5, xmmword_ptr[zsi]);
		vpmaxuw(xmm6, xmm5, xmm4);
		vpmaxuw(xmm6, xmm5, xmmword_ptr[zsi]);
		vpmaxud(xmm6, xmm5, xmm4);
		vpmaxud(xmm6, xmm5, xmmword_ptr[zsi]);
		vpminsb(xmm6, xmm5, xmm4);
		vpminsb(xmm6, xmm5, xmmword_ptr[zsi]);
		vpminsw(xmm6, xmm5, xmm4);
		vpminsw(xmm6, xmm5, xmmword_ptr[zsi]);
		vpminsd(xmm6, xmm5, xmm4);
		vpminsd(xmm6, xmm5, xmmword_ptr[zsi]);
		vpminub(xmm6, xmm5, xmm4);
		vpminub(xmm6, xmm5, xmmword_ptr[zsi]);
		vpminuw(xmm6, xmm5, xmm4);
		vpminuw(xmm6, xmm5, xmmword_ptr[zsi]);
		vpminud(xmm6, xmm5, xmm4);
		vpminud(xmm6, xmm5, xmmword_ptr[zsi]);
		vpmovmskb(ecx, xmm5);
#ifdef JITASM64
		vpmovmskb(rax, xmm5);
#endif
		vpmovsxbw(xmm1, xmm2);
		vpmovsxbw(xmm1, qword_ptr[esp]);
		vpmovsxbd(xmm1, xmm2);
		vpmovsxbd(xmm1, dword_ptr[esp]);
		vpmovsxbq(xmm1, xmm2);
		vpmovsxbq(xmm1, word_ptr[esp]);
		vpmovsxwd(xmm1, xmm2);
		vpmovsxwd(xmm1, qword_ptr[esp]);
		vpmovsxwq(xmm1, xmm2);
		vpmovsxwq(xmm1, dword_ptr[esp]);
		vpmovsxdq(xmm1, xmm2);
		vpmovsxdq(xmm1, qword_ptr[esp]);
		vpmovzxbw(xmm1, xmm2);
		vpmovzxbw(xmm1, qword_ptr[esp]);
		vpmovzxbd(xmm1, xmm2);
		vpmovzxbd(xmm1, dword_ptr[esp]);
		vpmovzxbq(xmm1, xmm2);
		vpmovzxbq(xmm1, word_ptr[esp]);
		vpmovzxwd(xmm1, xmm2);
		vpmovzxwd(xmm1, qword_ptr[esp]);
		vpmovzxwq(xmm1, xmm2);
		vpmovzxwq(xmm1, dword_ptr[esp]);
		vpmovzxdq(xmm1, xmm2);
		vpmovzxdq(xmm1, qword_ptr[esp]);
		vpmulhuw(xmm2, xmm3, xmm4);
		vpmulhuw(xmm2, xmm3, xmmword_ptr[zsi]);
		vpmulhrsw(xmm2, xmm3, xmm4);
		vpmulhrsw(xmm2, xmm3, xmmword_ptr[zsi]);
		vpmulhw(xmm2, xmm3, xmm4);
		vpmulhw(xmm2, xmm3, xmmword_ptr[zsi]);
		vpmullw(xmm2, xmm3, xmm4);
		vpmullw(xmm2, xmm3, xmmword_ptr[zsi]);
		vpmulld(xmm2, xmm3, xmm4);
		vpmulld(xmm2, xmm3, xmmword_ptr[zsi]);
		vpmuludq(xmm2, xmm3, xmm4);
		vpmuludq(xmm2, xmm3, xmmword_ptr[zsi]);
		vpmuldq(xmm2, xmm3, xmm4);
		vpmuldq(xmm2, xmm3, xmmword_ptr[zsi]);
		vpor(xmm2, xmm3, xmm4);
		vpor(xmm2, xmm3, xmmword_ptr[zsi]);
		vpsadbw(xmm2, xmm3, xmm4);
		vpsadbw(xmm2, xmm3, xmmword_ptr[zsi]);
		vpshufb(xmm2, xmm3, xmm4);
		vpshufb(xmm2, xmm3, xmmword_ptr[zsi]);
		vpshufd(xmm2, xmm3, 1);
		vpshufd(xmm2, xmmword_ptr[zsi], 2);
		vpshufhw(xmm2, xmm3, 3);
		vpshufhw(xmm2, xmmword_ptr[zsi], 4);
		vpshuflw(xmm2, xmm3, 5);
		vpshuflw(xmm2, xmmword_ptr[zsi], 6);
		vpsignb(xmm5, xmm0, xmm1);
		vpsignb(xmm5, xmm0, xmmword_ptr[zsi]);
		vpsignw(xmm5, xmm0, xmm1);
		vpsignw(xmm5, xmm0, xmmword_ptr[zsi]);
		vpsignd(xmm5, xmm0, xmm1);
		vpsignd(xmm5, xmm0, xmmword_ptr[zsi]);
		vpsllw(xmm7, xmm5, xmm2);
		vpsllw(xmm7, xmm5, xmmword_ptr[zsi]);
		vpsllw(xmm7, xmm5, 1);
		vpslld(xmm7, xmm5, xmm2);
		vpslld(xmm7, xmm5, xmmword_ptr[zsi]);
		vpslld(xmm7, xmm5, 1);
		vpsllq(xmm7, xmm5, xmm2);
		vpsllq(xmm7, xmm5, xmmword_ptr[zsi]);
		vpsllq(xmm7, xmm5, 1);
		vpslldq(xmm7, xmm5, 1);
		vpsraw(xmm7, xmm5, xmm2);
		vpsraw(xmm7, xmm5, xmmword_ptr[zsi]);
		vpsraw(xmm7, xmm5, 1);
		vpsrad(xmm7, xmm5, xmm2);
		vpsrad(xmm7, xmm5, xmmword_ptr[zsi]);
		vpsrad(xmm7, xmm5, 1);
		vpsrlw(xmm7, xmm5, xmm2);
		vpsrlw(xmm7, xmm5, xmmword_ptr[zsi]);
		vpsrlw(xmm7, xmm5, 1);
		vpsrld(xmm7, xmm5, xmm2);
		vpsrld(xmm7, xmm5, xmmword_ptr[zsi]);
		vpsrld(xmm7, xmm5, 1);
		vpsrlq(xmm7, xmm5, xmm2);
		vpsrlq(xmm7, xmm5, xmmword_ptr[zsi]);
		vpsrlq(xmm7, xmm5, 1);
		vpsrldq(xmm7, xmm5, 1);
		vptest(xmm1, xmm0);
		vptest(xmm1, xmmword_ptr[zsi]);
		vptest(ymm1, ymm0);
		vptest(ymm1, ymmword_ptr[zsi]);
		vtestps(xmm1, xmm0);
		vtestps(xmm1, xmmword_ptr[zsi]);
		vtestps(ymm1, ymm0);
		vtestps(ymm1, ymmword_ptr[zsi]);
		vtestpd(xmm1, xmm0);
		vtestpd(xmm1, xmmword_ptr[zsi]);
		vtestpd(ymm1, ymm0);
		vtestpd(ymm1, ymmword_ptr[zsi]);
		vpsubb(xmm2, xmm3, xmm7);
		vpsubb(xmm2, xmm3, xmmword_ptr[zsi]);
		vpsubw(xmm2, xmm3, xmm7);
		vpsubw(xmm2, xmm3, xmmword_ptr[zsi]);
		vpsubd(xmm2, xmm3, xmm7);
		vpsubd(xmm2, xmm3, xmmword_ptr[zsi]);
		vpsubq(xmm2, xmm3, xmm7);
		vpsubq(xmm2, xmm3, xmmword_ptr[zsi]);
		vpsubsb(xmm2, xmm3, xmm7);
		vpsubsb(xmm2, xmm3, xmmword_ptr[zsi]);
		vpsubsw(xmm2, xmm3, xmm7);
		vpsubsw(xmm2, xmm3, xmmword_ptr[zsi]);
		vpsubusb(xmm2, xmm3, xmm7);
		vpsubusb(xmm2, xmm3, xmmword_ptr[zsi]);
		vpsubusw(xmm2, xmm3, xmm7);
		vpsubusw(xmm2, xmm3, xmmword_ptr[zsi]);
		vpunpckhbw(xmm1, xmm2, xmm3);
		vpunpckhbw(xmm1, xmm2, xmmword_ptr[zsi]);
		vpunpckhwd(xmm1, xmm2, xmm3);
		vpunpckhwd(xmm1, xmm2, xmmword_ptr[zsi]);
		vpunpckhdq(xmm1, xmm2, xmm3);
		vpunpckhdq(xmm1, xmm2, xmmword_ptr[zsi]);
		vpunpckhqdq(xmm1, xmm2, xmm3);
		vpunpckhqdq(xmm1, xmm2, xmmword_ptr[zsi]);
		vpunpcklbw(xmm1, xmm2, xmm3);
		vpunpcklbw(xmm1, xmm2, xmmword_ptr[zsi]);
		vpunpcklwd(xmm1, xmm2, xmm3);
		vpunpcklwd(xmm1, xmm2, xmmword_ptr[zsi]);
		vpunpckldq(xmm1, xmm2, xmm3);
		vpunpckldq(xmm1, xmm2, xmmword_ptr[zsi]);
		vpunpcklqdq(xmm1, xmm2, xmm3);
		vpunpcklqdq(xmm1, xmm2, xmmword_ptr[zsi]);
		vpxor(xmm1, xmm2, xmm3);
		vpxor(xmm1, xmm2, xmmword_ptr[zsi]);
	}
};

//----------------------------------------
// AVX R~
//----------------------------------------
extern "C" void masm_test_avx_r();
struct test_avx_r : jitasm::function<void, test_avx_r>
{
	void naked_main()
	{
		vrcpps(xmm5, xmm0);
		vrcpps(xmm5, xmmword_ptr[zsi]);
		vrcpps(ymm4, ymm0);
		vrcpps(ymm4, ymmword_ptr[zsi]);
		vrcpss(xmm5, xmm3, xmm0);
		vrcpss(xmm5, xmm3, dword_ptr[zsi]);
		vrsqrtps(xmm5, xmm0);
		vrsqrtps(xmm5, xmmword_ptr[zsi]);
		vrsqrtps(ymm4, ymm0);
		vrsqrtps(ymm4, ymmword_ptr[zsi]);
		vrsqrtss(xmm5, xmm3, xmm0);
		vrsqrtss(xmm5, xmm3, dword_ptr[zsi]);
		vroundpd(xmm1, xmm3, 1);
		vroundpd(xmm1, xmmword_ptr[zsi], 2);
		vroundpd(ymm1, ymm2, 1);
		vroundpd(ymm1, ymmword_ptr[zsi], 3);
		vroundps(xmm1, xmm3, 0);
		vroundps(xmm1, xmmword_ptr[zsi], 1);
		vroundps(ymm1, ymm2, 2);
		vroundps(ymm1, ymmword_ptr[zsi], 0);
		vroundsd(xmm1, xmm2, xmm3, 1);
		vroundsd(xmm1, xmm2, qword_ptr[zsi], 2);
		vroundss(xmm1, xmm2, xmm3, 3);
		vroundss(xmm1, xmm2, dword_ptr[zdx], 1);
		vshufpd(xmm1, xmm3, xmm4, 1);
		vshufpd(xmm1, xmm3, xmmword_ptr[esi], 2);
		vshufpd(ymm2, ymm0, ymm5, 3);
		vshufpd(ymm2, ymm0, ymmword_ptr[esi], 4);
		vshufps(xmm1, xmm3, xmm5, 5);
		vshufps(xmm1, xmm3, xmmword_ptr[esi], 6);
		vshufps(ymm2, ymm0, ymm6, 7);
		vshufps(ymm2, ymm0, ymmword_ptr[esi], 8);
		vsqrtpd(xmm7, xmm3);
		vsqrtpd(xmm7, xmmword_ptr[edx]);
		vsqrtpd(ymm7, ymm3);
		vsqrtpd(ymm7, ymmword_ptr[edx]);
		vsqrtps(xmm7, xmm3);
		vsqrtps(xmm7, xmmword_ptr[edx]);
		vsqrtps(ymm7, ymm3);
		vsqrtps(ymm7, ymmword_ptr[edx]);
		vsqrtsd(xmm7, xmm2, xmm4);
		vsqrtsd(xmm7, xmm2, qword_ptr[edx]);
		vsqrtss(xmm7, xmm2, xmm5);
		vsqrtss(xmm7, xmm2, dword_ptr[edx]);
		vstmxcsr(dword_ptr[esi]);
		vsubpd(xmm1, xmm2, xmm3);
		vsubpd(xmm1, xmm2, xmmword_ptr[edx]);
		vsubpd(ymm1, ymm2, ymm3);
		vsubpd(ymm1, ymm2, ymmword_ptr[edx]);
		vsubps(xmm1, xmm2, xmm3);
		vsubps(xmm1, xmm2, xmmword_ptr[edx]);
		vsubps(ymm1, ymm2, ymm3);
		vsubps(ymm1, ymm2, ymmword_ptr[edx]);
		vsubsd(xmm1, xmm2, xmm4);
		vsubsd(xmm1, xmm2, qword_ptr[edx]);
		vsubss(xmm1, xmm2, xmm5);
		vsubss(xmm1, xmm2, dword_ptr[edx]);
		vucomisd(xmm4, xmm6);
		vucomisd(xmm3, qword_ptr[ebp]);
		vucomiss(xmm0, xmm7);
		vucomiss(xmm1, dword_ptr[ebx]);
		vunpckhpd(xmm1, xmm2, xmm3);
		vunpckhpd(xmm1, xmm2, xmmword_ptr[edi]);
		vunpckhpd(ymm1, ymm2, ymm4);
		vunpckhpd(ymm1, ymm2, ymmword_ptr[esi]);
		vunpckhps(xmm1, xmm2, xmm3);
		vunpckhps(xmm1, xmm2, xmmword_ptr[edi]);
		vunpckhps(ymm1, ymm2, ymm4);
		vunpckhps(ymm1, ymm2, ymmword_ptr[esi]);
		vunpcklpd(xmm1, xmm2, xmm3);
		vunpcklpd(xmm1, xmm2, xmmword_ptr[edi]);
		vunpcklpd(ymm1, ymm2, ymm4);
		vunpcklpd(ymm1, ymm2, ymmword_ptr[esi]);
		vunpcklps(xmm1, xmm2, xmm3);
		vunpcklps(xmm1, xmm2, xmmword_ptr[edi]);
		vunpcklps(ymm1, ymm2, ymm4);
		vunpcklps(ymm1, ymm2, ymmword_ptr[esi]);
		vxorpd(xmm1, xmm2, xmm3);
		vxorpd(xmm1, xmm2, xmmword_ptr[edi]);
		vxorpd(ymm1, ymm2, ymm4);
		vxorpd(ymm1, ymm2, ymmword_ptr[esi]);
		vxorps(xmm1, xmm2, xmm3);
		vxorps(xmm1, xmm2, xmmword_ptr[edi]);
		vxorps(ymm1, ymm2, ymm4);
		vxorps(ymm1, ymm2, ymmword_ptr[esi]);
		vzeroall();
		vzeroupper();
	}
};

//----------------------------------------
// FMA
//----------------------------------------
extern "C" void nasm_test_fma();
struct test_fma : jitasm::function<void, test_fma>
{
	void naked_main()
	{
		vfmadd132pd(xmm1, xmm3, xmm5);
		vfmadd132pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmadd132pd(ymm1, ymm3, ymm5);
		vfmadd132pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmadd213pd(xmm1, xmm3, xmm5);
		vfmadd213pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmadd213pd(ymm1, ymm3, ymm5);
		vfmadd213pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmadd231pd(xmm1, xmm3, xmm5);
		vfmadd231pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmadd231pd(ymm1, ymm3, ymm5);
		vfmadd231pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmadd132ps(xmm1, xmm3, xmm5);
		vfmadd132ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmadd132ps(ymm1, ymm3, ymm5);
		vfmadd132ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmadd213ps(xmm1, xmm3, xmm5);
		vfmadd213ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmadd213ps(ymm1, ymm3, ymm5);
		vfmadd213ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmadd231ps(xmm1, xmm3, xmm5);
		vfmadd231ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmadd231ps(ymm1, ymm3, ymm5);
		vfmadd231ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmadd132sd(xmm1, xmm3, xmm5);
		vfmadd132sd(xmm1, xmm3, qword_ptr[edi]);
		vfmadd213sd(xmm1, xmm3, xmm5);
		vfmadd213sd(xmm1, xmm3, qword_ptr[edi]);
		vfmadd231sd(xmm1, xmm3, xmm5);
		vfmadd231sd(xmm1, xmm3, qword_ptr[edi]);
		vfmadd132ss(xmm1, xmm3, xmm5);
		vfmadd132ss(xmm1, xmm3, qword_ptr[edi]);
		vfmadd213ss(xmm1, xmm3, xmm5);
		vfmadd213ss(xmm1, xmm3, qword_ptr[edi]);
		vfmadd231ss(xmm1, xmm3, xmm5);
		vfmadd231ss(xmm1, xmm3, qword_ptr[edi]);
		vfmaddsub132pd(xmm1, xmm3, xmm5);
		vfmaddsub132pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmaddsub132pd(ymm1, ymm3, ymm5);
		vfmaddsub132pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmaddsub213pd(xmm1, xmm3, xmm5);
		vfmaddsub213pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmaddsub213pd(ymm1, ymm3, ymm5);
		vfmaddsub213pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmaddsub231pd(xmm1, xmm3, xmm5);
		vfmaddsub231pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmaddsub231pd(ymm1, ymm3, ymm5);
		vfmaddsub231pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmaddsub132ps(xmm1, xmm3, xmm5);
		vfmaddsub132ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmaddsub132ps(ymm1, ymm3, ymm5);
		vfmaddsub132ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmaddsub213ps(xmm1, xmm3, xmm5);
		vfmaddsub213ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmaddsub213ps(ymm1, ymm3, ymm5);
		vfmaddsub213ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmaddsub231ps(xmm1, xmm3, xmm5);
		vfmaddsub231ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmaddsub231ps(ymm1, ymm3, ymm5);
		vfmaddsub231ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsubadd132pd(xmm1, xmm3, xmm5);
		vfmsubadd132pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsubadd132pd(ymm1, ymm3, ymm5);
		vfmsubadd132pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsubadd213pd(xmm1, xmm3, xmm5);
		vfmsubadd213pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsubadd213pd(ymm1, ymm3, ymm5);
		vfmsubadd213pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsubadd231pd(xmm1, xmm3, xmm5);
		vfmsubadd231pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsubadd231pd(ymm1, ymm3, ymm5);
		vfmsubadd231pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsubadd132ps(xmm1, xmm3, xmm5);
		vfmsubadd132ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsubadd132ps(ymm1, ymm3, ymm5);
		vfmsubadd132ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsubadd213ps(xmm1, xmm3, xmm5);
		vfmsubadd213ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsubadd213ps(ymm1, ymm3, ymm5);
		vfmsubadd213ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsubadd231ps(xmm1, xmm3, xmm5);
		vfmsubadd231ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsubadd231ps(ymm1, ymm3, ymm5);
		vfmsubadd231ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsub132pd(xmm1, xmm3, xmm5);
		vfmsub132pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsub132pd(ymm1, ymm3, ymm5);
		vfmsub132pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsub213pd(xmm1, xmm3, xmm5);
		vfmsub213pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsub213pd(ymm1, ymm3, ymm5);
		vfmsub213pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsub231pd(xmm1, xmm3, xmm5);
		vfmsub231pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsub231pd(ymm1, ymm3, ymm5);
		vfmsub231pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsub132ps(xmm1, xmm3, xmm5);
		vfmsub132ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsub132ps(ymm1, ymm3, ymm5);
		vfmsub132ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsub213ps(xmm1, xmm3, xmm5);
		vfmsub213ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsub213ps(ymm1, ymm3, ymm5);
		vfmsub213ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsub231ps(xmm1, xmm3, xmm5);
		vfmsub231ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfmsub231ps(ymm1, ymm3, ymm5);
		vfmsub231ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfmsub132sd(xmm1, xmm3, xmm5);
		vfmsub132sd(xmm1, xmm3, qword_ptr[edi]);
		vfmsub213sd(xmm1, xmm3, xmm5);
		vfmsub213sd(xmm1, xmm3, qword_ptr[edi]);
		vfmsub231sd(xmm1, xmm3, xmm5);
		vfmsub231sd(xmm1, xmm3, qword_ptr[edi]);
		vfmsub132ss(xmm1, xmm3, xmm5);
		vfmsub132ss(xmm1, xmm3, qword_ptr[edi]);
		vfmsub213ss(xmm1, xmm3, xmm5);
		vfmsub213ss(xmm1, xmm3, qword_ptr[edi]);
		vfmsub231ss(xmm1, xmm3, xmm5);
		vfmsub231ss(xmm1, xmm3, qword_ptr[edi]);
		vfnmadd132pd(xmm1, xmm3, xmm5);
		vfnmadd132pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmadd132pd(ymm1, ymm3, ymm5);
		vfnmadd132pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmadd213pd(xmm1, xmm3, xmm5);
		vfnmadd213pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmadd213pd(ymm1, ymm3, ymm5);
		vfnmadd213pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmadd231pd(xmm1, xmm3, xmm5);
		vfnmadd231pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmadd231pd(ymm1, ymm3, ymm5);
		vfnmadd231pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmadd132ps(xmm1, xmm3, xmm5);
		vfnmadd132ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmadd132ps(ymm1, ymm3, ymm5);
		vfnmadd132ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmadd213ps(xmm1, xmm3, xmm5);
		vfnmadd213ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmadd213ps(ymm1, ymm3, ymm5);
		vfnmadd213ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmadd231ps(xmm1, xmm3, xmm5);
		vfnmadd231ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmadd231ps(ymm1, ymm3, ymm5);
		vfnmadd231ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmadd132sd(xmm1, xmm3, xmm5);
		vfnmadd132sd(xmm1, xmm3, qword_ptr[edi]);
		vfnmadd213sd(xmm1, xmm3, xmm5);
		vfnmadd213sd(xmm1, xmm3, qword_ptr[edi]);
		vfnmadd231sd(xmm1, xmm3, xmm5);
		vfnmadd231sd(xmm1, xmm3, qword_ptr[edi]);
		vfnmadd132ss(xmm1, xmm3, xmm5);
		vfnmadd132ss(xmm1, xmm3, qword_ptr[edi]);
		vfnmadd213ss(xmm1, xmm3, xmm5);
		vfnmadd213ss(xmm1, xmm3, qword_ptr[edi]);
		vfnmadd231ss(xmm1, xmm3, xmm5);
		vfnmadd231ss(xmm1, xmm3, qword_ptr[edi]);
		vfnmsub132pd(xmm1, xmm3, xmm5);
		vfnmsub132pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmsub132pd(ymm1, ymm3, ymm5);
		vfnmsub132pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmsub213pd(xmm1, xmm3, xmm5);
		vfnmsub213pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmsub213pd(ymm1, ymm3, ymm5);
		vfnmsub213pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmsub231pd(xmm1, xmm3, xmm5);
		vfnmsub231pd(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmsub231pd(ymm1, ymm3, ymm5);
		vfnmsub231pd(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmsub132ps(xmm1, xmm3, xmm5);
		vfnmsub132ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmsub132ps(ymm1, ymm3, ymm5);
		vfnmsub132ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmsub213ps(xmm1, xmm3, xmm5);
		vfnmsub213ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmsub213ps(ymm1, ymm3, ymm5);
		vfnmsub213ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmsub231ps(xmm1, xmm3, xmm5);
		vfnmsub231ps(xmm1, xmm3, xmmword_ptr[edi]);
		vfnmsub231ps(ymm1, ymm3, ymm5);
		vfnmsub231ps(ymm1, ymm3, ymmword_ptr[edi]);
		vfnmsub132sd(xmm1, xmm3, xmm5);
		vfnmsub132sd(xmm1, xmm3, qword_ptr[edi]);
		vfnmsub213sd(xmm1, xmm3, xmm5);
		vfnmsub213sd(xmm1, xmm3, qword_ptr[edi]);
		vfnmsub231sd(xmm1, xmm3, xmm5);
		vfnmsub231sd(xmm1, xmm3, qword_ptr[edi]);
		vfnmsub132ss(xmm1, xmm3, xmm5);
		vfnmsub132ss(xmm1, xmm3, qword_ptr[edi]);
		vfnmsub213ss(xmm1, xmm3, xmm5);
		vfnmsub213ss(xmm1, xmm3, qword_ptr[edi]);
		vfnmsub231ss(xmm1, xmm3, xmm5);
		vfnmsub231ss(xmm1, xmm3, qword_ptr[edi]);
	}
};

//----------------------------------------
// F16C
//----------------------------------------
extern "C" void nasm_test_f16c();
struct test_f16c : jitasm::function<void, test_f16c>
{
	void naked_main()
	{
#ifdef JITASM64
		rdfsbase(ecx);
		rdfsbase(rcx);
		rdgsbase(ecx);
		rdgsbase(rcx);
#endif
		rdrand(cx);
		rdrand(ecx);
#ifdef JITASM64
		rdrand(rcx);
#endif
#ifdef JITASM64
		wrfsbase(ecx);
		wrfsbase(rcx);
		wrgsbase(ecx);
		wrgsbase(rcx);
#endif
		vcvtph2ps(ymm1, xmm3);
		vcvtph2ps(ymm1, xmmword_ptr[edx]);
		vcvtph2ps(xmm1, xmm3);
		vcvtph2ps(xmm1, qword_ptr[edx]);
		vcvtps2ph(xmm1, ymm3, 5);
		vcvtps2ph(xmmword_ptr[edx], ymm3, 5);
		vcvtps2ph(xmm1, xmm3, 5);
		vcvtps2ph(qword_ptr[edx], xmm3, 5);
	}
};

//----------------------------------------
// XOP
//----------------------------------------
extern "C" void nasm_test_xop();
struct test_xop : jitasm::function<void, test_xop>
{
	void naked_main()
	{
		vfrczpd(xmm1, xmm3);
		vfrczpd(xmm1, xmmword_ptr[edx]);
		vfrczpd(ymm1, ymm3);
		vfrczpd(ymm1, ymmword_ptr[edx]);
		vfrczps(xmm1, xmm3);
		vfrczps(xmm1, xmmword_ptr[edx]);
		vfrczps(ymm1, ymm3);
		vfrczps(ymm1, ymmword_ptr[edx]);
		vfrczsd(xmm1, xmm3);
		vfrczsd(xmm1, qword_ptr[edx]);
		vfrczss(xmm1, xmm3);
		vfrczss(xmm1, dword_ptr[edx]);
		vpcmov(xmm1, xmm3, xmm5, xmm7);
		vpcmov(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpcmov(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vpcmov(ymm1, ymm3, ymm5, ymm7);
		vpcmov(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vpcmov(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vpcomb(xmm1, xmm3, xmm5, 2);
		vpcomb(xmm1, xmm3, xmmword_ptr[esp], 2);
		vpcomd(xmm1, xmm3, xmm5, 2);
		vpcomd(xmm1, xmm3, xmmword_ptr[esp], 2);
		vpcomq(xmm1, xmm3, xmm5, 2);
		vpcomq(xmm1, xmm3, xmmword_ptr[esp], 2);
		//vpcomub(xmm1, xmm3, xmm5, 2);
		//vpcomub(xmm1, xmm3, xmmword_ptr[esp], 2);
		//vpcomud(xmm1, xmm3, xmm5, 2);
		//vpcomud(xmm1, xmm3, xmmword_ptr[esp], 2);
		//vpcomuq(xmm1, xmm3, xmm5, 2);
		//vpcomuq(xmm1, xmm3, xmmword_ptr[esp], 2);
		//vpcomuw(xmm1, xmm3, xmm5, 2);
		//vpcomuw(xmm1, xmm3, xmmword_ptr[esp], 2);
		//vpcomw(xmm1, xmm3, xmm5, 2);
		//vpcomw(xmm1, xmm3, xmmword_ptr[esp], 2);
		//vpermil2pd(xmm1, xmm3, xmm5, xmm7);
		//vpermil2pd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		//vpermil2pd(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		//vpermil2pd(ymm1, ymm3, ymm5, ymm7);
		//vpermil2pd(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		//vpermil2pd(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		//vpermil2ps(xmm1, xmm3, xmm5, xmm7);
		//vpermil2ps(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		//vpermil2ps(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		//vpermil2ps(ymm1, ymm3, ymm5, ymm7);
		//vpermil2ps(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		//vpermil2ps(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vphaddbd(xmm1, xmm3);
		vphaddbd(xmm1, xmmword_ptr[edx]);
		vphaddbq(xmm1, xmm3);
		vphaddbq(xmm1, xmmword_ptr[edx]);
		vphaddbw(xmm1, xmm3);
		vphaddbw(xmm1, xmmword_ptr[edx]);
		vphadddq(xmm1, xmm3);
		vphadddq(xmm1, xmmword_ptr[edx]);
		vphaddubd(xmm1, xmm3);
		vphaddubd(xmm1, xmmword_ptr[edx]);
		vphaddubq(xmm1, xmm3);
		vphaddubq(xmm1, xmmword_ptr[edx]);
		vphaddubw(xmm1, xmm3);
		vphaddubw(xmm1, xmmword_ptr[edx]);
		//vphaddudq(xmm1, xmm3);
		//vphaddudq(xmm1, xmmword_ptr[edx]);
		vphadduwd(xmm1, xmm3);
		vphadduwd(xmm1, xmmword_ptr[edx]);
		vphadduwq(xmm1, xmm3);
		vphadduwq(xmm1, xmmword_ptr[edx]);
		vphaddwd(xmm1, xmm3);
		vphaddwd(xmm1, xmmword_ptr[edx]);
		vphaddwq(xmm1, xmm3);
		vphaddwq(xmm1, xmmword_ptr[edx]);
		vphsubbw(xmm1, xmm3);
		vphsubbw(xmm1, xmmword_ptr[edx]);
		//vphsubdq(xmm1, xmm3);
		//vphsubdq(xmm1, xmmword_ptr[edx]);
		vphsubwd(xmm1, xmm3);
		vphsubwd(xmm1, xmmword_ptr[edx]);
		vpmacsdd(xmm1, xmm3, xmm5, xmm7);
		vpmacsdd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacsdqh(xmm1, xmm3, xmm5, xmm7);
		vpmacsdqh(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacsdql(xmm1, xmm3, xmm5, xmm7);
		vpmacsdql(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacssdd(xmm1, xmm3, xmm5, xmm7);
		vpmacssdd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacssdqh(xmm1, xmm3, xmm5, xmm7);
		vpmacssdqh(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacssdql(xmm1, xmm3, xmm5, xmm7);
		vpmacssdql(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacsswd(xmm1, xmm3, xmm5, xmm7);
		vpmacsswd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacssww(xmm1, xmm3, xmm5, xmm7);
		vpmacssww(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacswd(xmm1, xmm3, xmm5, xmm7);
		vpmacswd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmacsww(xmm1, xmm3, xmm5, xmm7);
		vpmacsww(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmadcsswd(xmm1, xmm3, xmm5, xmm7);
		vpmadcsswd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpmadcswd(xmm1, xmm3, xmm5, xmm7);
		vpmadcswd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpperm(xmm1, xmm3, xmm5, xmm7);
		vpperm(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vpperm(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vprotb(xmm1, xmm3, xmm5);
		vprotb(xmm1, xmmword_ptr[edx], xmm5);
		vprotb(xmm1, xmm3, xmmword_ptr[esp]);
		vprotb(xmm1, xmm3, 2);
		vprotb(xmm1, xmmword_ptr[edx], 2);
		vprotd(xmm1, xmm3, xmm5);
		vprotd(xmm1, xmmword_ptr[edx], xmm5);
		vprotd(xmm1, xmm3, xmmword_ptr[esp]);
		vprotd(xmm1, xmm3, 2);
		vprotd(xmm1, xmmword_ptr[edx], 2);
		vprotq(xmm1, xmm3, xmm5);
		vprotq(xmm1, xmmword_ptr[edx], xmm5);
		vprotq(xmm1, xmm3, xmmword_ptr[esp]);
		vprotq(xmm1, xmm3, 2);
		vprotq(xmm1, xmmword_ptr[edx], 2);
		vprotw(xmm1, xmm3, xmm5);
		vprotw(xmm1, xmmword_ptr[edx], xmm5);
		vprotw(xmm1, xmm3, xmmword_ptr[esp]);
		vprotw(xmm1, xmm3, 2);
		vprotw(xmm1, xmmword_ptr[edx], 2);
		vpshab(xmm1, xmm3, xmm5);
		vpshab(xmm1, xmmword_ptr[edx], xmm5);
		vpshab(xmm1, xmm3, xmmword_ptr[esp]);
		vpshad(xmm1, xmm3, xmm5);
		vpshad(xmm1, xmmword_ptr[edx], xmm5);
		vpshad(xmm1, xmm3, xmmword_ptr[esp]);
		vpshaq(xmm1, xmm3, xmm5);
		vpshaq(xmm1, xmmword_ptr[edx], xmm5);
		vpshaq(xmm1, xmm3, xmmword_ptr[esp]);
		vpshaw(xmm1, xmm3, xmm5);
		vpshaw(xmm1, xmmword_ptr[edx], xmm5);
		vpshaw(xmm1, xmm3, xmmword_ptr[esp]);
		vpshlb(xmm1, xmm3, xmm5);
		vpshlb(xmm1, xmmword_ptr[edx], xmm5);
		vpshlb(xmm1, xmm3, xmmword_ptr[esp]);
		vpshld(xmm1, xmm3, xmm5);
		vpshld(xmm1, xmmword_ptr[edx], xmm5);
		vpshld(xmm1, xmm3, xmmword_ptr[esp]);
		vpshlq(xmm1, xmm3, xmm5);
		vpshlq(xmm1, xmmword_ptr[edx], xmm5);
		vpshlq(xmm1, xmm3, xmmword_ptr[esp]);
		vpshlw(xmm1, xmm3, xmm5);
		vpshlw(xmm1, xmmword_ptr[edx], xmm5);
		vpshlw(xmm1, xmm3, xmmword_ptr[esp]);
	}
};

//----------------------------------------
// FMA4
//----------------------------------------
extern "C" void nasm_test_fma4();
struct test_fma4 : jitasm::function<void, test_fma4>
{
	void naked_main()
	{
		vfmaddpd(xmm1, xmm3, xmm5, xmm7);
		vfmaddpd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfmaddpd(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfmaddpd(ymm1, ymm3, ymm5, ymm7);
		vfmaddpd(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfmaddpd(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfmaddps(xmm1, xmm3, xmm5, xmm7);
		vfmaddps(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfmaddps(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfmaddps(ymm1, ymm3, ymm5, ymm7);
		vfmaddps(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfmaddps(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfmaddsd(xmm1, xmm3, xmm5, xmm7);
		vfmaddsd(xmm1, xmm3, qword_ptr[esp], xmm7);
		vfmaddsd(xmm1, xmm3, xmm5, qword_ptr[esi]);
		vfmaddss(xmm1, xmm3, xmm5, xmm7);
		vfmaddss(xmm1, xmm3, dword_ptr[esp], xmm7);
		vfmaddss(xmm1, xmm3, xmm5, dword_ptr[esi]);
		vfmaddsubpd(xmm1, xmm3, xmm5, xmm7);
		vfmaddsubpd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfmaddsubpd(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfmaddsubpd(ymm1, ymm3, ymm5, ymm7);
		vfmaddsubpd(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfmaddsubpd(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfmaddsubps(xmm1, xmm3, xmm5, xmm7);
		vfmaddsubps(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfmaddsubps(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfmaddsubps(ymm1, ymm3, ymm5, ymm7);
		vfmaddsubps(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfmaddsubps(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfmsubaddpd(xmm1, xmm3, xmm5, xmm7);
		vfmsubaddpd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfmsubaddpd(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfmsubaddpd(ymm1, ymm3, ymm5, ymm7);
		vfmsubaddpd(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfmsubaddpd(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfmsubaddps(xmm1, xmm3, xmm5, xmm7);
		vfmsubaddps(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfmsubaddps(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfmsubaddps(ymm1, ymm3, ymm5, ymm7);
		vfmsubaddps(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfmsubaddps(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfmsubpd(xmm1, xmm3, xmm5, xmm7);
		vfmsubpd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfmsubpd(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfmsubpd(ymm1, ymm3, ymm5, ymm7);
		vfmsubpd(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfmsubpd(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfmsubps(xmm1, xmm3, xmm5, xmm7);
		vfmsubps(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfmsubps(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfmsubps(ymm1, ymm3, ymm5, ymm7);
		vfmsubps(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfmsubps(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfmsubsd(xmm1, xmm3, xmm5, xmm7);
		vfmsubsd(xmm1, xmm3, qword_ptr[esp], xmm7);
		vfmsubsd(xmm1, xmm3, xmm5, qword_ptr[esi]);
		vfmsubss(xmm1, xmm3, xmm5, xmm7);
		vfmsubss(xmm1, xmm3, dword_ptr[esp], xmm7);
		vfmsubss(xmm1, xmm3, xmm5, dword_ptr[esi]);
		vfnmaddpd(xmm1, xmm3, xmm5, xmm7);
		vfnmaddpd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfnmaddpd(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfnmaddpd(ymm1, ymm3, ymm5, ymm7);
		vfnmaddpd(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfnmaddpd(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfnmaddps(xmm1, xmm3, xmm5, xmm7);
		vfnmaddps(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfnmaddps(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfnmaddps(ymm1, ymm3, ymm5, ymm7);
		vfnmaddps(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfnmaddps(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfnmaddsd(xmm1, xmm3, xmm5, xmm7);
		vfnmaddsd(xmm1, xmm3, qword_ptr[esp], xmm7);
		vfnmaddsd(xmm1, xmm3, xmm5, qword_ptr[esi]);
		vfnmaddss(xmm1, xmm3, xmm5, xmm7);
		vfnmaddss(xmm1, xmm3, dword_ptr[esp], xmm7);
		vfnmaddss(xmm1, xmm3, xmm5, dword_ptr[esi]);
		vfnmsubpd(xmm1, xmm3, xmm5, xmm7);
		vfnmsubpd(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfnmsubpd(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfnmsubpd(ymm1, ymm3, ymm5, ymm7);
		vfnmsubpd(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfnmsubpd(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfnmsubps(xmm1, xmm3, xmm5, xmm7);
		vfnmsubps(xmm1, xmm3, xmmword_ptr[esp], xmm7);
		vfnmsubps(xmm1, xmm3, xmm5, xmmword_ptr[esi]);
		vfnmsubps(ymm1, ymm3, ymm5, ymm7);
		vfnmsubps(ymm1, ymm3, ymmword_ptr[esp], ymm7);
		vfnmsubps(ymm1, ymm3, ymm5, ymmword_ptr[esi]);
		vfnmsubsd(xmm1, xmm3, xmm5, xmm7);
		vfnmsubsd(xmm1, xmm3, qword_ptr[esp], xmm7);
		vfnmsubsd(xmm1, xmm3, xmm5, qword_ptr[esi]);
		vfnmsubss(xmm1, xmm3, xmm5, xmm7);
		vfnmsubss(xmm1, xmm3, dword_ptr[esp], xmm7);
		vfnmsubss(xmm1, xmm3, xmm5, dword_ptr[esi]);
	}
};

//----------------------------------------
// BMI
//----------------------------------------
extern "C" void nasm_test_bmi();
struct test_bmi : jitasm::function<void, test_bmi>
{
	void naked_main()
	{
		andn(edi, ecx, eax);
		andn(edi, ecx, dword_ptr[eax]);
#ifdef JITASM64
		andn(rdi, rcx, rax);
		andn(rdi, rcx, qword_ptr[rax]);
#endif
		bextr(edi, ecx, eax);
		bextr(edi, dword_ptr[ecx], eax);
#ifdef JITASM64
		bextr(rdi, rcx, rax);
		bextr(rdi, qword_ptr[rcx], rax);
#endif
		blsi(edi, ecx);
		blsi(edi, dword_ptr[ecx]);
#ifdef JITASM64
		blsi(rdi, rcx);
		blsi(rdi, qword_ptr[rcx]);
#endif
		blsmsk(edi, ecx);
		blsmsk(edi, dword_ptr[ecx]);
#ifdef JITASM64
		blsmsk(rdi, rcx);
		blsmsk(rdi, qword_ptr[rcx]);
#endif
		blsr(edi, ecx);
		blsr(edi, dword_ptr[ecx]);
#ifdef JITASM64
		blsr(rdi, rcx);
		blsr(rdi, qword_ptr[rcx]);
#endif
		bzhi(edi, ecx, eax);
		bzhi(edi, dword_ptr[ecx], eax);
#ifdef JITASM64
		bzhi(rdi, rcx, rax);
		bzhi(rdi, qword_ptr[rcx], rax);
#endif
		//lzcnt(di, cx);
		//lzcnt(di, word_ptr[ecx]);
		lzcnt(zdi, zcx);
		lzcnt(zdi, ptr[zcx]);
		mulx(edi, ecx, edx, eax);
		mulx(edi, ecx, edx, dword_ptr[eax]);
#ifdef JITASM64
		mulx(rdi, rcx, rdx, rax);
		mulx(rdi, rcx, rdx, qword_ptr[rax]);
#endif
		pdep(edi, ecx, eax);
		pdep(edi, ecx, dword_ptr[eax]);
#ifdef JITASM64
		pdep(rdi, rcx, rax);
		pdep(rdi, rcx, qword_ptr[rax]);
#endif
		pext(edi, ecx, eax);
		pext(edi, ecx, dword_ptr[eax]);
#ifdef JITASM64
		pext(rdi, rcx, rax);
		pext(rdi, rcx, qword_ptr[rax]);
#endif
		rorx(edi, ecx, 1);
		rorx(edi, dword_ptr[ecx], 1);
#ifdef JITASM64
		rorx(rdi, rcx, 1);
		rorx(rdi, qword_ptr[rcx], 1);
#endif
		sarx(edi, ecx, eax);
		sarx(edi, dword_ptr[ecx], eax);
#ifdef JITASM64
		sarx(rdi, rcx, rax);
		sarx(rdi, qword_ptr[rcx], rax);
#endif
		shlx(edi, ecx, eax);
		shlx(edi, dword_ptr[ecx], eax);
#ifdef JITASM64
		shlx(rdi, rcx, rax);
		shlx(rdi, qword_ptr[rcx], rax);
#endif
		shrx(edi, ecx, eax);
		shrx(edi, dword_ptr[ecx], eax);
#ifdef JITASM64
		shrx(rdi, rcx, rax);
		shrx(rdi, qword_ptr[rcx], rax);
#endif
		//tzcnt(di, cx);
		//tzcnt(di, word_ptr[ecx]);
		tzcnt(zdi, zcx);
		tzcnt(zdi, ptr[zcx]);
#ifndef JITASM64
		invpcid(edi, xmmword_ptr[ecx]);
#else
		invpcid(rdi, xmmword_ptr[rcx]);
#endif
	}
};

//----------------------------------------
// AVX2
//----------------------------------------
extern "C" void masm_test_avx2();
struct test_avx2 : jitasm::function<void, test_avx2>
{
	void naked_main()
	{
		vbroadcastss(xmm1, xmm2);
		vbroadcastss(ymm7, xmm2);
		vbroadcastsd(ymm7, xmm2);
		vbroadcasti128(ymm7, xmmword_ptr[ecx]);
		vextracti128(xmm2, ymm4, 1);
		vextracti128(xmmword_ptr[edi], ymm3, 0);
		vinserti128(ymm3, ymm2, xmm1, 1);
		vinserti128(ymm3, ymm2, xmmword_ptr[esi], 0);
		vmovntdqa(ymm5, ymmword_ptr[esi]);
		vmpsadbw(ymm6, ymm4, ymm3, 1);
		vmpsadbw(ymm6, ymm4, ymmword_ptr[esi], 2);
		vpabsb(ymm6, ymm5);
		vpabsb(ymm6, ymmword_ptr[ecx]);
		vpabsw(ymm6, ymm5);
		vpabsw(ymm6, ymmword_ptr[ecx]);
		vpabsd(ymm6, ymm5);
		vpabsd(ymm6, ymmword_ptr[ecx]);
		vpacksswb(ymm6, ymm4, ymm3);
		vpacksswb(ymm6, ymm4, ymmword_ptr[esi]);
		vpackssdw(ymm6, ymm4, ymm3);
		vpackssdw(ymm6, ymm4, ymmword_ptr[esi]);
		vpackuswb(ymm6, ymm4, ymm3);
		vpackuswb(ymm6, ymm4, ymmword_ptr[esi]);
		vpackusdw(ymm6, ymm4, ymm3);
		vpackusdw(ymm6, ymm4, ymmword_ptr[esi]);
		vpaddb(ymm6, ymm4, ymm3);
		vpaddb(ymm6, ymm4, ymmword_ptr[esi]);
		vpaddw(ymm6, ymm4, ymm3);
		vpaddw(ymm6, ymm4, ymmword_ptr[esi]);
		vpaddd(ymm6, ymm4, ymm3);
		vpaddd(ymm6, ymm4, ymmword_ptr[esi]);
		vpaddq(ymm6, ymm4, ymm3);
		vpaddq(ymm6, ymm4, ymmword_ptr[esi]);
		vpaddsb(ymm6, ymm4, ymm3);
		vpaddsb(ymm6, ymm4, ymmword_ptr[esi]);
		vpaddsw(ymm6, ymm4, ymm3);
		vpaddsw(ymm6, ymm4, ymmword_ptr[esi]);
		vpaddusb(ymm6, ymm4, ymm3);
		vpaddusb(ymm6, ymm4, ymmword_ptr[esi]);
		vpaddusw(ymm6, ymm4, ymm3);
		vpaddusw(ymm6, ymm4, ymmword_ptr[esi]);
		vpalignr(ymm6, ymm4, ymm3, 2);
		vpalignr(ymm6, ymm4, ymmword_ptr[esi], 3);
		vpand(ymm6, ymm4, ymm3);
		vpand(ymm6, ymm4, ymmword_ptr[esi]);
		vpandn(ymm6, ymm4, ymm3);
		vpandn(ymm6, ymm4, ymmword_ptr[esi]);
		vpavgb(ymm6, ymm4, ymm3);
		vpavgb(ymm6, ymm4, ymmword_ptr[esi]);
		vpavgw(ymm6, ymm4, ymm3);
		vpavgw(ymm6, ymm4, ymmword_ptr[esi]);
		vpblendvb(ymm6, ymm4, ymm3, ymm2);
		vpblendvb(ymm6, ymm4, ymmword_ptr[esi], ymm2);
		vpblendw(ymm6, ymm4, ymm3, 0x0F);
		vpblendw(ymm6, ymm4, ymmword_ptr[esi], 0xF0);
		vpblendd(xmm3, xmm2, xmm1, 0x0A);
		vpblendd(xmm3, xmm2, xmmword_ptr[eax], 0x03);
		vpblendd(ymm6, ymm4, ymm3, 0x22);
		vpblendd(ymm6, ymm4, ymmword_ptr[esi], 0x33);
		vpbroadcastb(xmm1, xmm2);
		vpbroadcastb(xmm1, byte_ptr[esi]);
		vpbroadcastb(ymm7, xmm2);
		vpbroadcastb(ymm7, byte_ptr[edi]);
		vpbroadcastw(xmm1, xmm2);
		vpbroadcastw(xmm1, word_ptr[eax]);
		vpbroadcastw(ymm7, xmm2);
		vpbroadcastw(ymm7, word_ptr[esi]);
		vpbroadcastd(xmm1, xmm2);
		vpbroadcastd(xmm1, dword_ptr[edx]);
		vpbroadcastd(ymm7, xmm2);
		vpbroadcastd(ymm7, dword_ptr[eax]);
		vpbroadcastq(xmm1, xmm2);
		vpbroadcastq(xmm1, qword_ptr[esi]);
		vpbroadcastq(ymm7, xmm2);
		vpbroadcastq(ymm7, qword_ptr[esi]);
		vpcmpeqb(ymm0, ymm1, ymm2);
		vpcmpeqb(ymm0, ymm1, ymmword_ptr[ecx]);
		vpcmpeqw(ymm0, ymm1, ymm2);
		vpcmpeqw(ymm0, ymm1, ymmword_ptr[ecx]);
		vpcmpeqd(ymm0, ymm1, ymm2);
		vpcmpeqd(ymm0, ymm1, ymmword_ptr[ecx]);
		vpcmpeqq(ymm0, ymm1, ymm2);
		vpcmpeqq(ymm0, ymm1, ymmword_ptr[ecx]);
		vpcmpgtb(ymm0, ymm1, ymm2);
		vpcmpgtb(ymm0, ymm1, ymmword_ptr[ecx]);
		vpcmpgtw(ymm0, ymm1, ymm2);
		vpcmpgtw(ymm0, ymm1, ymmword_ptr[ecx]);
		vpcmpgtd(ymm0, ymm1, ymm2);
		vpcmpgtd(ymm0, ymm1, ymmword_ptr[ecx]);
		vpcmpgtq(ymm0, ymm1, ymm2);
		vpcmpgtq(ymm0, ymm1, ymmword_ptr[ecx]);
		vpermd(ymm0, ymm5, ymm3);
		vpermd(ymm0, ymm5, ymmword_ptr[esi]);
		vpermq(ymm0, ymm3, 5);
		vpermq(ymm0, ymmword_ptr[esi], 6);
		vpermps(ymm0, ymm5, ymm3);
		vpermps(ymm0, ymm5, ymmword_ptr[esi]);
		vpermpd(ymm0, ymm3, 9);
		vpermpd(ymm0, ymmword_ptr[esi], 4);
		vperm2i128(ymm0, ymm1, ymm3, 2);
		vperm2i128(ymm0, ymm1, ymmword_ptr[esi], 1);
		vphaddw(ymm5, ymm6, ymm4);
		vphaddw(ymm5, ymm6, ymmword_ptr[eax]);
		vphaddd(ymm5, ymm6, ymm4);
		vphaddd(ymm5, ymm6, ymmword_ptr[eax]);
		vphaddsw(ymm5, ymm6, ymm4);
		vphaddsw(ymm5, ymm6, ymmword_ptr[eax]);
		vphsubw(ymm5, ymm6, ymm4);
		vphsubw(ymm5, ymm6, ymmword_ptr[eax]);
		vphsubd(ymm5, ymm6, ymm4);
		vphsubd(ymm5, ymm6, ymmword_ptr[eax]);
		vphsubsw(ymm5, ymm6, ymm4);
		vphsubsw(ymm5, ymm6, ymmword_ptr[eax]);
		vpmaddwd(ymm5, ymm6, ymm4);
		vpmaddwd(ymm5, ymm6, ymmword_ptr[eax]);
		vpmaddubsw(ymm5, ymm6, ymm4);
		vpmaddubsw(ymm5, ymm6, ymmword_ptr[eax]);
		vpmaskmovd(xmm1, xmm0, xmmword_ptr[esi]);
		vpmaskmovd(ymm2, ymm7, ymmword_ptr[esi]);
		vpmaskmovq(xmm3, xmm0, xmmword_ptr[ecx]);
		vpmaskmovq(ymm4, ymm7, ymmword_ptr[eax]);
		vpmaskmovd(xmmword_ptr[edi], xmm0, xmm1);
		vpmaskmovd(ymmword_ptr[eax], ymm7, ymm2);
		vpmaskmovq(xmmword_ptr[esp], xmm0, xmm3);
		vpmaskmovq(ymmword_ptr[ecx], ymm7, ymm4);
		vpmaxsb(ymm1, ymm2, ymm3);
		vpmaxsb(ymm1, ymm2, ymmword_ptr[esi]);
		vpmaxsw(ymm1, ymm2, ymm3);
		vpmaxsw(ymm1, ymm2, ymmword_ptr[esi]);
		vpmaxsd(ymm1, ymm2, ymm3);
		vpmaxsd(ymm1, ymm2, ymmword_ptr[esi]);
		vpmaxub(ymm1, ymm2, ymm3);
		vpmaxub(ymm1, ymm2, ymmword_ptr[esi]);
		vpmaxuw(ymm1, ymm2, ymm3);
		vpmaxuw(ymm1, ymm2, ymmword_ptr[esi]);
		vpmaxud(ymm1, ymm2, ymm3);
		vpmaxud(ymm1, ymm2, ymmword_ptr[esi]);
		vpminsb(ymm1, ymm2, ymm3);
		vpminsb(ymm1, ymm2, ymmword_ptr[esi]);
		vpminsw(ymm1, ymm2, ymm3);
		vpminsw(ymm1, ymm2, ymmword_ptr[esi]);
		vpminsd(ymm1, ymm2, ymm3);
		vpminsd(ymm1, ymm2, ymmword_ptr[esi]);
		vpminub(ymm1, ymm2, ymm3);
		vpminub(ymm1, ymm2, ymmword_ptr[esi]);
		vpminuw(ymm1, ymm2, ymm3);
		vpminuw(ymm1, ymm2, ymmword_ptr[esi]);
		vpminud(ymm1, ymm2, ymm3);
		vpminud(ymm1, ymm2, ymmword_ptr[esi]);
		vpmovmskb(eax, ymm1);
#ifdef JITASM64
		vpmovmskb(rax, ymm2);
#endif
		vpmovsxbw(ymm7, xmm6);
		vpmovsxbw(ymm7, qword_ptr[esp]);
		vpmovsxbd(ymm7, xmm6);
		vpmovsxbd(ymm7, dword_ptr[ecx]);
		vpmovsxbq(ymm7, xmm6);
		vpmovsxbq(ymm7, word_ptr[esi]);
		vpmovsxwd(ymm7, xmm6);
		vpmovsxwd(ymm7, qword_ptr[esp]);
		vpmovsxwq(ymm7, xmm6);
		vpmovsxwq(ymm7, dword_ptr[ecx]);
		vpmovsxdq(ymm7, xmm6);
		vpmovsxdq(ymm7, qword_ptr[esp]);
		vpmovzxbw(ymm7, xmm6);
		vpmovzxbw(ymm7, qword_ptr[esp]);
		vpmovzxbd(ymm7, xmm6);
		vpmovzxbd(ymm7, dword_ptr[ecx]);
		vpmovzxbq(ymm7, xmm6);
		vpmovzxbq(ymm7, word_ptr[esi]);
		vpmovzxwd(ymm7, xmm6);
		vpmovzxwd(ymm7, qword_ptr[esp]);
		vpmovzxwq(ymm7, xmm6);
		vpmovzxwq(ymm7, dword_ptr[ecx]);
		vpmovzxdq(ymm7, xmm6);
		vpmovzxdq(ymm7, qword_ptr[esp]);
		vpmulhuw(ymm1, ymm2, ymm3);
		vpmulhuw(ymm1, ymm2, ymmword_ptr[edi]);
		vpmulhrsw(ymm1, ymm2, ymm3);
		vpmulhrsw(ymm1, ymm2, ymmword_ptr[edi]);
		vpmulhw(ymm1, ymm2, ymm3);
		vpmulhw(ymm1, ymm2, ymmword_ptr[edi]);
		vpmullw(ymm1, ymm2, ymm3);
		vpmullw(ymm1, ymm2, ymmword_ptr[edi]);
		vpmulld(ymm1, ymm2, ymm3);
		vpmulld(ymm1, ymm2, ymmword_ptr[edi]);
		vpmuludq(ymm1, ymm2, ymm3);
		vpmuludq(ymm1, ymm2, ymmword_ptr[edi]);
		vpmuldq(ymm1, ymm2, ymm3);
		vpmuldq(ymm1, ymm2, ymmword_ptr[edi]);
		vpor(ymm3, ymm4, ymm5);
		vpor(ymm3, ymm4, ymmword_ptr[eax]);
		vpsadbw(ymm3, ymm4, ymm5);
		vpsadbw(ymm3, ymm4, ymmword_ptr[eax]);
		vpshufb(ymm3, ymm6, ymm7);
		vpshufb(ymm3, ymm6, ymmword_ptr[ebx]);
		vpshufd(ymm3, ymm6, 3);
		vpshufd(ymm3, ymmword_ptr[ecx], 4);
		vpshufhw(ymm3, ymm6, 5);
		vpshufhw(ymm3, ymmword_ptr[ecx], 6);
		vpshuflw(ymm3, ymm6, 7);
		vpshuflw(ymm3, ymmword_ptr[ecx], 8);
		vpsignb(ymm3, ymm4, ymm5);
		vpsignb(ymm3, ymm4, ymmword_ptr[eax]);
		vpsignw(ymm3, ymm4, ymm5);
		vpsignw(ymm3, ymm4, ymmword_ptr[eax]);
		vpsignd(ymm3, ymm4, ymm5);
		vpsignd(ymm3, ymm4, ymmword_ptr[eax]);
		vpsllw(ymm3, ymm6, xmm1);
		vpsllw(ymm3, ymm6, xmmword_ptr[esi]);
		vpsllw(ymm3, ymm6, 9);
		vpslld(ymm3, ymm6, xmm1);
		vpslld(ymm3, ymm6, xmmword_ptr[esi]);
		vpslld(ymm3, ymm6, 10);
		vpsllq(ymm3, ymm6, xmm1);
		vpsllq(ymm3, ymm6, xmmword_ptr[esi]);
		vpsllq(ymm3, ymm6, 11);
		vpslldq(ymm3, ymm6, 12);
		vpsllvd(xmm0, xmm2, xmm1);
		vpsllvd(xmm0, xmm1, xmmword_ptr[ecx]);
		vpsllvd(ymm3, ymm6, ymm0);
		vpsllvd(ymm3, ymm0, ymmword_ptr[ecx]);
		vpsllvq(xmm0, xmm2, xmm1);
		vpsllvq(xmm0, xmm1, xmmword_ptr[ecx]);
		vpsllvq(ymm3, ymm6, ymm0);
		vpsllvq(ymm3, ymm0, ymmword_ptr[ecx]);
		vpsraw(ymm3, ymm6, xmm1);
		vpsraw(ymm3, ymm6, xmmword_ptr[esi]);
		vpsraw(ymm3, ymm6, 1);
		vpsrad(ymm3, ymm6, xmm1);
		vpsrad(ymm3, ymm6, xmmword_ptr[esi]);
		vpsrad(ymm3, ymm6, 2);
		vpsravd(xmm0, xmm2, xmm1);
		vpsravd(xmm0, xmm1, xmmword_ptr[ecx]);
		vpsravd(ymm3, ymm6, ymm0);
		vpsravd(ymm3, ymm0, ymmword_ptr[ecx]);
		vpsrlw(ymm3, ymm6, xmm1);
		vpsrlw(ymm3, ymm6, xmmword_ptr[esi]);
		vpsrlw(ymm3, ymm6, 3);
		vpsrld(ymm3, ymm6, xmm1);
		vpsrld(ymm3, ymm6, xmmword_ptr[esi]);
		vpsrld(ymm3, ymm6, 4);
		vpsrlq(ymm3, ymm6, xmm1);
		vpsrlq(ymm3, ymm6, xmmword_ptr[esi]);
		vpsrlq(ymm3, ymm6, 5);
		vpsrldq(ymm3, ymm6, 6);
		vpsrlvd(xmm0, xmm2, xmm1);
		vpsrlvd(xmm0, xmm1, xmmword_ptr[ecx]);
		vpsrlvd(ymm3, ymm6, ymm0);
		vpsrlvd(ymm3, ymm0, ymmword_ptr[ecx]);
		vpsrlvq(xmm0, xmm2, xmm1);
		vpsrlvq(xmm0, xmm1, xmmword_ptr[ecx]);
		vpsrlvq(ymm3, ymm6, ymm0);
		vpsrlvq(ymm3, ymm0, ymmword_ptr[ecx]);
		vpsubb(ymm1, ymm5, ymm6);
		vpsubb(ymm1, ymm5, ymmword_ptr[eax]);
		vpsubw(ymm1, ymm5, ymm6);
		vpsubw(ymm1, ymm5, ymmword_ptr[eax]);
		vpsubd(ymm1, ymm5, ymm6);
		vpsubd(ymm1, ymm5, ymmword_ptr[eax]);
		vpsubq(ymm1, ymm5, ymm6);
		vpsubq(ymm1, ymm5, ymmword_ptr[eax]);
		vpsubsb(ymm1, ymm5, ymm6);
		vpsubsb(ymm1, ymm5, ymmword_ptr[eax]);
		vpsubsw(ymm1, ymm5, ymm6);
		vpsubsw(ymm1, ymm5, ymmword_ptr[eax]);
		vpsubusb(ymm1, ymm5, ymm6);
		vpsubusb(ymm1, ymm5, ymmword_ptr[eax]);
		vpsubusw(ymm1, ymm5, ymm6);
		vpsubusw(ymm1, ymm5, ymmword_ptr[eax]);
		vpunpckhbw(ymm1, ymm5, ymm6);
		vpunpckhbw(ymm1, ymm5, ymmword_ptr[eax]);
		vpunpckhwd(ymm1, ymm5, ymm6);
		vpunpckhwd(ymm1, ymm5, ymmword_ptr[eax]);
		vpunpckhdq(ymm1, ymm5, ymm6);
		vpunpckhdq(ymm1, ymm5, ymmword_ptr[eax]);
		vpunpckhqdq(ymm1, ymm5, ymm6);
		vpunpckhqdq(ymm1, ymm5, ymmword_ptr[eax]);
		vpunpcklbw(ymm1, ymm5, ymm6);
		vpunpcklbw(ymm1, ymm5, ymmword_ptr[eax]);
		vpunpcklwd(ymm1, ymm5, ymm6);
		vpunpcklwd(ymm1, ymm5, ymmword_ptr[eax]);
		vpunpckldq(ymm1, ymm5, ymm6);
		vpunpckldq(ymm1, ymm5, ymmword_ptr[eax]);
		vpunpcklqdq(ymm1, ymm5, ymm6);
		vpunpcklqdq(ymm1, ymm5, ymmword_ptr[eax]);
		vpxor(ymm1, ymm5, ymm6);
		vpxor(ymm1, ymm5, ymmword_ptr[eax]);

	}
};

extern "C" void nasm_test_avx2_gather();
struct test_avx2_gather : jitasm::function<void, test_avx2_gather>
{
	void naked_main()
	{
		vgatherdps(xmm2, dword_ptr[ebp + xmm5 * 2 + 1], xmm3);
		vgatherdps(ymm5, dword_ptr[ebp + ymm5 * 2 + 1], ymm4);
		vgatherqps(xmm2, dword_ptr[ebp + xmm6 * 2 + 1], xmm3);
		vgatherqps(xmm2, dword_ptr[ebp + ymm6 * 2 + 1], xmm3);
		vgatherdpd(xmm2, qword_ptr[ebp + xmm5 * 2 + 1], xmm3);
		vgatherdpd(ymm5, qword_ptr[ebp + xmm5 * 2 + 1], ymm4);
		vgatherqpd(xmm2, qword_ptr[ebp + xmm6 * 2 + 1], xmm3);
		vgatherqpd(ymm5, qword_ptr[ebp + ymm6 * 2 + 1], ymm4);
		vpgatherdd(xmm2, dword_ptr[ebp + xmm5 * 2 + 1], xmm3);
		vpgatherdd(ymm5, dword_ptr[ebp + ymm5 * 2 + 1], ymm4);
		vpgatherqd(xmm2, dword_ptr[ebp + xmm6 * 2 + 1], xmm3);
		vpgatherqd(xmm2, dword_ptr[ebp + ymm6 * 2 + 1], xmm3);
		vpgatherdq(xmm2, qword_ptr[ebp + xmm5 * 2 + 1], xmm3);
		vpgatherdq(ymm5, qword_ptr[ebp + xmm5 * 2 + 1], ymm4);
		vpgatherqq(xmm2, qword_ptr[ebp + xmm6 * 2 + 1], xmm3);
		vpgatherqq(ymm5, qword_ptr[ebp + ymm6 * 2 + 1], ymm4);
	}
};

void test_backend()
{
	TEST_M(test_sal);
	TEST_M(test_sar);
	TEST_M(test_shl);
	TEST_M(test_shr);
	TEST_M(test_rcl);
	TEST_M(test_rcr);
	TEST_M(test_rol);
	TEST_M(test_ror);
	TEST_M(test_inc_dec);
	TEST_M(test_push_pop);
	TEST_M(test_add);
	TEST_M(test_or);
	TEST_M(test_adc);
	TEST_M(test_sbb);
	TEST_M(test_and);
	TEST_M(test_sub);
	TEST_M(test_xor);
	TEST_M(test_cmp);
	TEST_M(test_xchg);
	TEST_M(test_test);
	TEST_M(test_mov);
	TEST_N(test_mov_disp);
	TEST_M(test_lea);
	TEST_M(test_fld);
	TEST_M(test_jmp);
	TEST_M(test_movs);
	TEST_M(test_neg_not);
	TEST_M(test_div_idiv_mul);
	TEST_M(test_imul);
	TEST_M(test_fst);
	TEST_M(test_setcc);
	TEST_M(test_cmovcc);
	TEST_M(test_gpi_b);
	TEST_M(test_gpi_e);
	TEST_M(test_fpu);
	TEST_M(test_mmx);
	TEST_M(test_mmx2);
	TEST_M(test_sse);
	TEST_M(test_sse2_a);
	TEST_M(test_sse2_d);
	TEST_M(test_sse2_p);
	TEST_M(test_sse2_s);
	TEST_M(test_movd_movq);
	TEST_M(test_movsd_movss);
	TEST_M(test_sse3);
	TEST_M(test_ssse3);
	TEST_M(test_sse4_1);
	TEST_M(test_sse4_2);
	TEST_M(test_avx_a);
	TEST_M(test_avx_a);
	TEST_M(test_avx_b);
	TEST_M(test_avx_d);
	TEST_M(test_avx_o);
	TEST_M(test_avx_r);
	TEST_N(test_fma);
	TEST_N(test_f16c);
	TEST_N(test_xop);
	TEST_N(test_fma4);
	TEST_N(test_bmi);
	TEST_M(test_avx2);
	TEST_N(test_avx2_gather);
}
