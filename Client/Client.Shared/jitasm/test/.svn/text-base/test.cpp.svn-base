// Workaround for issue #8
#if defined(__APPLE__) && defined(__MACH__)		// Mac OS X
#define JITASM_MMINTRIN 0
#endif

#include <assert.h>
#include "jitasm.h"
#include "test.h"

int g_test_succeeded = 0;
int g_test_failed = 0;
int g_assemble_time = 0;	// us


struct test_mmx_sse2 : jitasm::function<void, test_mmx_sse2>
{
	void main()
	{
#ifdef JITASM64
		movdqa(xmm0, xmm1);
		movdqa(xmm8, xmm1);
		movdqa(xmm0, xmm9);
		movdqa(xmm0, xmmword_ptr[ecx]);
		movdqa(xmm0, xmmword_ptr[rcx]);
		movdqa(xmm8, xmmword_ptr[ecx]);
		movdqa(xmm8, xmmword_ptr[rcx]);
		movdqa(xmmword_ptr[eax], xmm1);
		movdqa(xmmword_ptr[rax], xmm1);
		movdqa(xmmword_ptr[eax], xmm9);
		movdqa(xmmword_ptr[rax], xmm9);

		movdqu(xmm0, xmm1);
		movdqu(xmm8, xmm1);
		movdqu(xmm0, xmm9);
		movdqu(xmm0, xmmword_ptr[ecx]);
		movdqu(xmm0, xmmword_ptr[rcx]);
		movdqu(xmm8, xmmword_ptr[ecx]);
		movdqu(xmm8, xmmword_ptr[rcx]);
		movdqu(xmmword_ptr[eax], xmm1);
		movdqu(xmmword_ptr[rax], xmm1);
		movdqu(xmmword_ptr[eax], xmm9);
		movdqu(xmmword_ptr[rax], xmm9);

		pxor(xmm0, xmm1);
		pxor(xmm8, xmm1);
		pxor(xmm0, xmm9);
		pxor(xmm0, xmmword_ptr[ecx]);
		pxor(xmm0, xmmword_ptr[rcx]);
		pxor(xmm8, xmmword_ptr[ecx]);
		pxor(xmm8, xmmword_ptr[rcx]);
#else
		movdqa(xmm0, xmm1);
		movdqa(xmm0, xmmword_ptr[ecx]);
		movdqa(xmmword_ptr[eax], xmm1);

		movdqu(xmm0, xmm1);
		movdqu(xmm0, xmmword_ptr[ecx]);
		movdqu(xmmword_ptr[eax], xmm1);

		pabsb(mm0, mm1);
		pabsb(mm0, mmword_ptr[ecx]);
		pabsb(xmm0, xmm1);
		pabsb(xmm0, xmmword_ptr[ecx]);
		pabsw(mm0, mm1);
		pabsw(mm0, mmword_ptr[ecx]);
		pabsw(xmm0, xmm1);
		pabsw(xmm0, xmmword_ptr[ecx]);
		pabsd(mm0, mm1);
		pabsd(mm0, mmword_ptr[ecx]);
		pabsd(xmm0, xmm1);
		pabsd(xmm0, xmmword_ptr[ecx]);

		packsswb(mm0, mm1);
		packsswb(mm0, mmword_ptr[ecx]);
		packsswb(xmm0, xmm1);
		packsswb(xmm0, xmmword_ptr[ecx]);
		packssdw(mm0, mm1);
		packssdw(mm0, mmword_ptr[ecx]);
		packssdw(xmm0, xmm1);
		packssdw(xmm0, xmmword_ptr[ecx]);
		packuswb(mm0, mm1);
		packuswb(mm0, mmword_ptr[ecx]);
		packuswb(xmm0, xmm1);
		packuswb(xmm0, xmmword_ptr[ecx]);
		packusdw(xmm0, xmm1);
		packusdw(xmm0, xmmword_ptr[ecx]);

		paddb(mm0, mm1);
		paddb(mm0, mmword_ptr[ecx]);
		paddb(xmm0, xmm1);
		paddb(xmm0, xmmword_ptr[ecx]);
		paddw(mm0, mm1);
		paddw(mm0, mmword_ptr[ecx]);
		paddw(xmm0, xmm1);
		paddw(xmm0, xmmword_ptr[ecx]);
		paddd(mm0, mm1);
		paddd(mm0, mmword_ptr[ecx]);
		paddd(xmm0, xmm1);
		paddd(xmm0, xmmword_ptr[ecx]);

		pxor(mm0, mm1);
		pxor(mm0, mmword_ptr[ecx]);
		pxor(xmm0, xmm1);
		pxor(xmm0, xmmword_ptr[ecx]);
#endif
	}
};

//----------------------------------------
// Call graph
//----------------------------------------
extern "C" void masm_test_cfg1();
struct test_cfg1 : jitasm::function_cdecl<void, test_cfg1>
{
	void naked_main()
	{
		jitasm::Reg32 a;
		L("0");
		mov(a, 2);
		mov(edx, 1);
		cmp(a, 0);
		jle("1");
		dec(edx);
		L("1");
		dec(a);
		jne("0");
	}
};

//----------------------------------------
// Register allocation
//----------------------------------------
extern "C" void masm_test_register_allocation1();
struct test_register_allocation1 : jitasm::function_cdecl<void, test_register_allocation1>
{
	void main()
	{
		jitasm::Reg32 v1, v2, v3, v4, v5, v6, v7, v8;
		mov(v8, 2);
		mov(v7, 1);
		xor(v6, v6);
		xor(v5, v5);
		xor(v4, v4);
		xor(v3, v3);
		xor(v2, v2);
		xor(v1, v1);

		jitasm::Reg32 a;
		mov(a, 10);
		{
			L("LoopHeadA");

			cmp(v1, 5);
			jg("L1");

			jitasm::Reg32 i;
			mov(i, 10);
			jmp("LoopB");
			{
				L("LoopB");
				inc(v1);
				add(v2, v1);
				add(v3, v2);
				add(v4, v3);
				add(v5, v4);
				dec(i);
				jnz("LoopB");
			}
			dec(a);
			jnz("L1");
			jmp("LoopEndA");

			L("L1");
			dec(v1);
			add(v6, v5);
			add(v7, v6);
			add(v8, v7);
			dec(a);
			jnz("LoopHeadA");

			L("LoopEndA");
		}
	}
};

//----------------------------------------
// Reassign physical register by register allocator
//----------------------------------------
extern "C" void masm_test_regalloc_reassign_physical_reg();
struct test_regalloc_reassign_physical_reg : jitasm::function<void, test_regalloc_reassign_physical_reg>
{
	void naked_main()
	{
		maskmovdqu(xmm0, xmm1, zdi);
		maskmovdqu(xmm0, xmm1, zsi);
	}
};

//----------------------------------------
// VSIB register allocation
//----------------------------------------
extern "C" void nasm_test_regalloc_vsib();
struct test_regalloc_vsib : jitasm::function<void, test_regalloc_vsib>
{
	void naked_main()
	{
		jitasm::XmmReg xmm_index;
		vpxor(xmm_index, xmm_index, xmm_index);
		vgatherdps(xmm0, dword_ptr[ebp + xmm_index * 2 + 1], xmm2);
		vgatherqps(xmm0, dword_ptr[ebp + xmm_index * 2 + 1], xmm2);

		jitasm::YmmReg ymm_index;
		vxorps(ymm_index, ymm_index, ymm_index);
		vgatherdps(ymm1, dword_ptr[ebp + ymm_index * 2 + 1], ymm0);
		vgatherqps(xmm1, dword_ptr[ebp + ymm_index * 2 + 1], xmm0);
	}
};

//----------------------------------------
// function_cdecl<char>
//----------------------------------------
struct test_function_return_char : jitasm::function_cdecl<char, test_function_return_char, char>
{
	Result main(Reg8 a1)
	{
		return a1;
	}
};

//----------------------------------------
// function_cdecl<short>
//----------------------------------------
struct test_function_return_short : jitasm::function_cdecl<short, test_function_return_short, short>
{
	Result main(Reg16 a1)
	{
		return a1;
	}
};

//----------------------------------------
// function_cdecl<int> (return immediate)
//----------------------------------------
struct test_function_return_int_imm : jitasm::function_cdecl<int, test_function_return_int_imm>
{
	Result main()
	{
		return 0x4AC396D7;	// mov eax, 0x4AC396D7
	}
};

//----------------------------------------
// function_cdecl<int> (return eax)
//----------------------------------------
struct test_function_return_int_zero : jitasm::function_cdecl<int, test_function_return_int_zero>
{
	Result main()
	{
		xor(eax, eax);
		return eax;	// no instruction. (because mov eax, eax)
	}
};

//----------------------------------------
// function_cdecl<float> (return immediate)
//----------------------------------------
struct test_function_return_float_imm : jitasm::function_cdecl<float, test_function_return_float_imm>
{
	Result main()
	{
		return 11.0f;
	}
};

//----------------------------------------
// function_cdecl<float> (return xmm)
//----------------------------------------
#if JITASM_XMMINTRIN
struct test_function_return_float_xmm : jitasm::function_cdecl<float, test_function_return_float_xmm, float>
{
	Result main(Addr a1)
	{
		movss(xmm7, dword_ptr[a1]);
		return xmm7;
	}
};
#endif

//----------------------------------------
// function_cdecl<float, float> (return ptr)
//----------------------------------------
struct test_function_return_float_ptr : jitasm::function_cdecl<float, test_function_return_float_ptr, float>
{
	Result main(Addr a1)
	{
		return result_ptr[a1];
	}
};

//----------------------------------------
// function_cdecl<float, float> (return st(0))
//----------------------------------------
struct test_function_return_float_st0 : jitasm::function_cdecl<float, test_function_return_float_st0, float>
{
	Result main(Addr a1)
	{
		fld(real4_ptr[a1]);
		return st0;
	}
};

//----------------------------------------
// function_cdecl<double> (return immediate)
//----------------------------------------
struct test_function_return_double_imm : jitasm::function_cdecl<double, test_function_return_double_imm>
{
	Result main()
	{
		return 11.0;
	}
};

//----------------------------------------
// function_cdecl<double> (return xmm)
//----------------------------------------
#if JITASM_EMMINTRIN
struct test_function_return_double_xmm : jitasm::function_cdecl<double, test_function_return_double_xmm, double>
{
	Result main(Addr a1)
	{
		movsd(xmm7, qword_ptr[a1]);
		return xmm7;
	}
};
#endif

//----------------------------------------
// function_cdecl<double, double> (return ptr)
//----------------------------------------
struct test_function_return_double_ptr : jitasm::function_cdecl<double, test_function_return_double_ptr, double>
{
	Result main(Addr a1)
	{
		return result_ptr[a1];
	}
};

//----------------------------------------
// function_cdecl<double, double> (return st(0))
//----------------------------------------
struct test_function_return_double_st0 : jitasm::function_cdecl<double, test_function_return_double_st0, double>
{
	Result main(Addr a1)
	{
		fld(real8_ptr[a1]);
		return st0;
	}
};

#if JITASM_MMINTRIN
//----------------------------------------
// function_cdecl<__m64, int> (return mm1)
//----------------------------------------
struct test_function_return_m64_mm1 : jitasm::function_cdecl<__m64, test_function_return_m64_mm1, int>
{
	Result main(Addr a1)
	{
		movd(mm1, dword_ptr[a1]);
		punpckldq(mm1, mm1);
		paddd(mm1, mm1);
		return mm1;
	}
};

//----------------------------------------
// function_cdecl<__m64> (return ptr)
//----------------------------------------
struct test_function_return_m64_ptr : jitasm::function_cdecl<__m64, test_function_return_m64_ptr, __m64>
{
	Result main(Addr a1)
	{
		return result_ptr[a1];
	}
};
#endif	// JITASM_MMINTRIN

#if JITASM_XMMINTRIN
//----------------------------------------
// function_cdecl<__m128> (return xmm1)
//----------------------------------------
struct test_function_return_m128_zero : jitasm::function_cdecl<__m128, test_function_return_m128_zero>
{
	Result main()
	{
		xorps(xmm1, xmm1);
		return xmm1;
	}
};

//----------------------------------------
// function_cdecl<__m128> (return ptr)
//----------------------------------------
struct test_function_return_m128_ptr : jitasm::function_cdecl<__m128, test_function_return_m128_ptr, __m128>
{
	Result main(Addr a1)
	{
		return xmmword_ptr[a1];
	}
};
#endif

#if JITASM_EMMINTRIN
//----------------------------------------
// function_cdecl<__m128d> (return xmm1)
//----------------------------------------
struct test_function_return_m128d_zero : jitasm::function_cdecl<__m128d, test_function_return_m128d_zero>
{
	Result main()
	{
		xorpd(xmm1, xmm1);
		return xmm1;
	}
};

//----------------------------------------
// function_cdecl<__m128d> (return ptr)
//----------------------------------------
struct test_function_return_m128d_ptr : jitasm::function_cdecl<__m128d, test_function_return_m128d_ptr, __m128d>
{
	Result main(Addr a1)
	{
		return xmmword_ptr[a1];
	}
};

//----------------------------------------
// function_cdecl<__m128i> (return xmm1)
//----------------------------------------
struct test_function_return_m128i_zero : jitasm::function_cdecl<__m128i, test_function_return_m128i_zero>
{
	Result main()
	{
		pxor(xmm1, xmm1);
		return xmm1;
	}
};

//----------------------------------------
// function_cdecl<__m128i> (return ptr)
//----------------------------------------
struct test_function_return_m128i_ptr : jitasm::function_cdecl<__m128i, test_function_return_m128i_ptr, __m128i>
{
	Result main(Addr a1)
	{
		return xmmword_ptr[a1];
	}
};
#endif

void test_register_allocation()
{
	TEST_M(test_cfg1)
	TEST_M(test_register_allocation1)
	TEST_M(test_regalloc_reassign_physical_reg);
	TEST_N(test_regalloc_vsib);
}

void test_calling_convention()
{
	TEST_EQUAL((int)test_function_return_char()(0x78), (int)0x78);
	TEST_EQUAL(test_function_return_short()(0x7A52), (short)0x7A52);

	test_function_return_int_imm test_function_return_int_imm_obj;
	TEST_EQUAL(test_function_return_int_imm_obj(), (int)0x4AC396D7);

	test_function_return_int_zero test_function_return_int_zero_obj;
	TEST_EQUAL(test_function_return_int_zero_obj(), 0);

	test_function_return_float_imm test_function_return_float_imm_obj;
	TEST_EQUAL(test_function_return_float_imm_obj(), 11.0f);
#if JITASM_XMMINTRIN
	TEST_EQUAL(test_function_return_float_xmm()(2.0f), 2.0f);
#endif
	TEST_EQUAL(test_function_return_float_ptr()(3.0f), 3.0f);
	TEST_EQUAL(test_function_return_float_st0()(4.0f), 4.0f);
	test_function_return_double_imm test_function_return_double_imm_obj;
	TEST_EQUAL(test_function_return_double_imm_obj(), 11.0);
#if JITASM_EMMINTRIN
	TEST_EQUAL(test_function_return_double_xmm()(5.0), 5.0);
#endif
	TEST_EQUAL(test_function_return_double_ptr()(6.0), 6.0);
	TEST_EQUAL(test_function_return_double_st0()(7.0), 7.0);
#if JITASM_MMINTRIN && !defined(_WIN64)
	TEST_EQUAL(_mm_movemask_pi8(_mm_cmpeq_pi32(test_function_return_m64_mm1()(2), _mm_set_pi32(4, 4))), 0xFF);
	TEST_EQUAL(_mm_movemask_pi8(_mm_cmpeq_pi32(test_function_return_m64_ptr()(_mm_set_pi32(0x12345678, 0xFEDCBA98)), _mm_set_pi32(0x12345678, 0xFEDCBA98))), 0xFF);
	_mm_empty();
#endif

#if JITASM_XMMINTRIN
	test_function_return_m128_zero test_function_return_m128_zero_obj;
	TEST_EQUAL(_mm_movemask_ps(_mm_cmpeq_ps(test_function_return_m128_zero_obj(), _mm_setzero_ps())), 0x0F);
	TEST_EQUAL(_mm_movemask_ps(_mm_cmpeq_ps(test_function_return_m128_ptr()(_mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f)), _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f))), 0x0F);
#endif

#if JITASM_EMMINTRIN
	test_function_return_m128d_zero test_function_return_m128d_zero_obj;
	TEST_EQUAL(_mm_movemask_pd(_mm_cmpeq_pd(test_function_return_m128d_zero_obj(), _mm_setzero_pd())), 0x03);
	TEST_EQUAL(_mm_movemask_pd(_mm_cmpeq_pd(test_function_return_m128d_ptr()(_mm_set_pd(1.0f, 2.0f)), _mm_set_pd(1.0f, 2.0f))), 0x03);

	test_function_return_m128i_zero test_function_return_m128i_zero_obj;
	TEST_EQUAL(_mm_movemask_epi8(_mm_cmpeq_epi32(test_function_return_m128i_zero_obj(), _mm_setzero_si128())), 0xFFFF);
	TEST_EQUAL(_mm_movemask_epi8(_mm_cmpeq_epi32(test_function_return_m128i_ptr()(_mm_set_epi32(1, 2, 3, 4)), _mm_set_epi32(1, 2, 3, 4))), 0xFFFF);
#endif
}

struct test_cfg : jitasm::function_cdecl<void, test_cfg>
{
	void main()
	{
		jitasm::Reg32 i;
		mov(i, 10);
		While(i != 0);
			If(ecx == 1 || ecx == 2);
				mov(ecx, i);
			ElseIf(edx == 0);
				mov(edx, 1);
			Else();
				jmp("Exit");
			EndIf();
			dec(i);
		EndW();

		L("Exit");
	}
};

#if JITASM_MMINTRIN
struct test_m64_args3 : jitasm::function_cdecl<__m64, test_m64_args3, __m64, __m64, __m64>
{
	Result main(MmxReg v1, Addr v2, MmxReg v3)
	{
		MmxReg res;
		movq(res, v1);
		paddd(res, qword_ptr[v2]);
		paddd(res, v3);
		return res;
	}
};
#endif

#if JITASM_XMMINTRIN
struct test_m128_args3 : jitasm::function_cdecl<__m128, test_m128_args3, __m128, __m128, __m128>
{
	Result main(XmmReg v1, Addr v2, XmmReg v3)
	{
		XmmReg res;
		movaps(res, v1);
		addps(res, xmmword_ptr[v2]);
		addps(res, v3);
		return res;
	}
};
#endif

#if !defined(_WIN32)
#if JITASM_MMINTRIN
struct test_m64_args5 : jitasm::function_cdecl<__m64, test_m64_args5, __m64, __m64, __m64, __m64, __m64>
{
	Result main(MmxReg v1, Addr v2, MmxReg v3, MmxReg v4, Addr v5)
	{
		MmxReg res;
		movq(res, v1);
		paddd(res, qword_ptr[v2]);
		paddd(res, v3);
		paddd(res, v4);
		paddd(res, qword_ptr[v5]);
		return res;
	}
};
#endif

#if JITASM_XMMINTRIN
struct test_m128_args5 : jitasm::function_cdecl<__m128, test_m128_args5, __m128, __m128, __m128, __m128, __m128>
{
	Result main(XmmReg v1, Addr v2, XmmReg v3, XmmReg v4, Addr v5)
	{
		XmmReg res;
		movaps(res, v1);
		addps(res, xmmword_ptr[v2]);
		addps(res, v3);
		addps(res, v4);
		addps(res, xmmword_ptr[v5]);
		return res;
	}
};
#endif
#endif

#if JITASM_MMINTRIN && JITASM_XMMINTRIN && JITASM_EMMINTRIN
struct test_mix_args : jitasm::function_cdecl<__m128, test_mix_args, int, __m64, __m128i, __m64, __m128>
{
	Result main(Reg32 n, MmxReg v1, XmmReg v2, MmxReg v3, XmmReg v4)
	{
		XmmReg res;
		xorps(res, res);
		If(n == 0);
			cvtpi2ps(res, v1);
		ElseIf(n == 1);
			cvtdq2ps(res, v2);
		ElseIf(n == 2);
			cvtpi2ps(res, v3);
		ElseIf(n == 3);
			movaps(res, v4);
		EndIf();
		return res;
	}
};
#endif

struct test_ipow1 : jitasm::function_cdecl<int, test_ipow1, int, int>
{
	Result main(Reg32 a, Reg32 b)
	{
		Reg32 i;
		Reg32 c;
		mov(c, 1);
		xor(i, i);
		While(i < b);
			imul(c, a);
			inc(i);
		EndW();
		return c;
	}
};

struct test_ipow2 : jitasm::function_cdecl<int, test_ipow2, int, int>
{
	Result main(Addr a, Reg32 b)
	{
		Reg32 i;
		Reg32 c;
		mov(c, 1);
		xor(i, i);
		While(i < b);
			imul(c, dword_ptr[a]);
			inc(i);
		EndW();
		return c;
	}
};

struct test_fibonacci : jitasm::function_cdecl<unsigned int, test_fibonacci, unsigned int>
{
	Result main(Reg32 n)
	{
		Reg32 r;
		If(n == 0);
			mov(r, 0);
		ElseIf(n == 1 || n == 2);
			mov(r, 1);
		Else();
			Reg32 a;
			Reg32 b;
			Reg32 i;
			mov(a, 1);
			mov(b, 1);
			mov(i, 2);
			While(i < n);
				mov(r, a);
				add(r, b);
				mov(b, a);
				mov(a, r);
				inc(i);
			EndW();
		EndIf();
		return r;
	}
};

void test_execute()
{
	// MMX test
#if JITASM_MMINTRIN && !defined(_WIN64)	// VC does not support MMX intrinsics on x64.
	{
		__m64 v1 = _mm_set_pi32(1, 2);
		__m64 v2 = _mm_set_pi32(3, 4);
		__m64 v3 = _mm_set_pi32(7, 8);
		TEST_EQUAL(_mm_movemask_pi8(_mm_cmpeq_pi32(test_m64_args3()(v1, v2, v3), _mm_set_pi32(11, 14))), 0xFF);
		_mm_empty();
	}

#if defined(_WIN32) && JITASM_XMMINTRIN && JITASM_EMMINTRIN		// VC doest not support following parameter passing.
	{
		__m64 v1 = _mm_set_pi32(1, 2);
		__m128i v2 = _mm_set_epi32(3, 4, 5, 6);
		__m64 v3 = _mm_set_pi32(7, 8);
		__m128 v4 = _mm_set_ps(9.0f, 10.0f, 11.0f, 12.0f);
		TEST_EQUAL(_mm_movemask_ps(_mm_cmpeq_ps(test_mix_args()(0, v1, v2, v3, v4), _mm_set_ps(0.0f, 0.0f, 1.0f, 2.0f))), 0x0F);
		_mm_empty();
	}
#endif	// defined(_WIN32)
#endif	// JITASM_MMINTRIN && !defined(_WIN64)

#if JITASM_XMMINTRIN
	{
		__m128 v1 = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
		__m128 v2 = _mm_set_ps(5.0f, 6.0f, 7.0f, 8.0f);
		__m128 v3 = _mm_set_ps(9.0f, 10.0f, 11.0f, 12.0f);
		TEST_EQUAL(_mm_movemask_ps(_mm_cmpeq_ps(test_m128_args3()(v1, v2, v3), _mm_set_ps(15.0f, 18.0f, 21.0f, 24.0f))), 0x0F)
	}
#endif

	TEST_EQUAL(test_ipow1()(2, 0), 1);
	TEST_EQUAL(test_ipow1()(2, 3), 8);
	TEST_EQUAL(test_ipow2()(2, 0), 1);
	TEST_EQUAL(test_ipow2()(2, 3), 8);
	TEST_EQUAL(test_fibonacci()(0), 0U);
	TEST_EQUAL(test_fibonacci()(10), 55U);
	TEST_EQUAL(test_fibonacci()(47), 2971215073U);
}

void test_backend();

int main()
{
	test_backend();
	test_register_allocation();
	test_calling_convention();
	test_execute();

	printf("TEST RESULT - %d passed, %d failed\n", g_test_succeeded, g_test_failed);
	printf("Assemble time - %d us\n", g_assemble_time);
}
