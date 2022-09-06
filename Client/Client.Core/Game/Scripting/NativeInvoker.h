#pragma once

class scrNativeCallContext
{
protected:
	void *m_pReturn;
	uint32_t m_nArgCount;
	void *m_pArgs;
	uint32_t m_nDataCount;

public:
	template<typename T>
	inline T GetArgument(int idx)
	{
		intptr_t *arguments = (intptr_t *)m_pArgs;
		return *(T *)&arguments[idx];
	}

	template<typename T>
	inline void SetResult(int idx, T value)
	{
		intptr_t *returnValues = (intptr_t *)m_pReturn;
		*(T *)&returnValues[idx] = value;
	}

	inline int GetArgumentCount()
	{
		return m_nArgCount;
	}

	template<typename T>
	inline T GetResult(int idx)
	{
		intptr_t *returnValues = (intptr_t *)m_pReturn;
		return *(T *)&returnValues[idx];
	}
};

class NativeContext : public scrNativeCallContext
{
private:
	// Configuration
	enum {
		MaxNativeParams = 32,
		ArgSize = 8,
	};

	// Anything temporary that we need
	uint8_t m_TempStack[MaxNativeParams * ArgSize];

public:
	inline NativeContext()
	{
		m_pArgs = &m_TempStack;
		m_pReturn = &m_TempStack;		// It's okay to point both args and return at
		// the same pointer. The game should handle this.
		m_nArgCount = 0;
		m_nDataCount = 0;
	}

	template <typename T>
	inline void Push(T value)
	{
		if(sizeof(T) > ArgSize) { throw "Argument has an invalid size"; }
		else if(sizeof(T) < ArgSize)
		{
			// Ensure we don't have any stray data
			*reinterpret_cast<uintptr_t *>(m_TempStack + ArgSize * m_nArgCount) = 0;
		}

		*reinterpret_cast<T *>(m_TempStack + ArgSize * m_nArgCount) = value;
		m_nArgCount++;
	}

	inline void Reverse()
	{
		uintptr_t tempValues[MaxNativeParams];
		uintptr_t *args = (uintptr_t *)m_pArgs;

		for(uint32_t i = 0; i < m_nArgCount; i++)
		{
			int target = m_nArgCount - i - 1;
			tempValues[target] = args[i];
		}

		memcpy(m_TempStack, tempValues, sizeof(m_TempStack));
	}

	template <typename T>
	inline T GetResult()
	{
		return *reinterpret_cast<T *>(m_TempStack);
	}
};

/*

struct pass
{
	template<typename ...T> pass(T...) {}
};

class NativeInvoke
{
private:
	static void Invoke(NativeContext *cxt, uint64_t hash)
	{
		auto fn = ScriptEngine::GetNativeHandler(hash);

		if(fn != 0)
		{
			fn(cxt);
		}
	}

public:
	template<uint64_t Hash, typename R, typename... Args>
	static inline R Invoke(Args... args)
	{
		NativeContext cxt;

		pass{([&] ()
		{
			cxt.Push(args);
		}(), 1)...};

		// reverse the order of the list since the pass method pushes in reverse
		cxt.Reverse();

		Invoke(&cxt, Hash);

		return cxt.GetResult<R>();
	}
};

*/

class NativeInvoke
{
private:
	template <typename T>
	static inline void Push(NativeContext *ctx, T val)
	{
		uint64_t val64 = 0;

		if(sizeof(T) > sizeof(uint64_t))
		{
			throw "error, value size > 64 bit";
		}

		*reinterpret_cast<T *>(&val64) = val; // &val + sizeof(dw) - sizeof(val)
		ctx->Push(val64);
	}

	static void Invoke(NativeContext *cxt, uint64_t hash)
	{
		auto fn = ScriptEngine::GetNativeHandler(hash);

		if(fn != 0)
		{
			fn(cxt);
		}
	}

public:
	template <typename R>
	static inline R Invoke(uint64_t hash)
	{
		NativeContext cxt;
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1>
	static inline R Invoke(uint64_t hash, T1 P1)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Push(&cxt, P18);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Push(&cxt, P18);
		Push(&cxt, P19);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Push(&cxt, P18);
		Push(&cxt, P19);
		Push(&cxt, P20);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Push(&cxt, P18);
		Push(&cxt, P19);
		Push(&cxt, P20);
		Push(&cxt, P21);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Push(&cxt, P18);
		Push(&cxt, P19);
		Push(&cxt, P20);
		Push(&cxt, P21);
		Push(&cxt, P22);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Push(&cxt, P18);
		Push(&cxt, P19);
		Push(&cxt, P20);
		Push(&cxt, P21);
		Push(&cxt, P22);
		Push(&cxt, P23);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Push(&cxt, P18);
		Push(&cxt, P19);
		Push(&cxt, P20);
		Push(&cxt, P21);
		Push(&cxt, P22);
		Push(&cxt, P23);
		Push(&cxt, P24);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}

	template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
	static inline R Invoke(uint64_t hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25)
	{
		NativeContext cxt;
		Push(&cxt, P1);
		Push(&cxt, P2);
		Push(&cxt, P3);
		Push(&cxt, P4);
		Push(&cxt, P5);
		Push(&cxt, P6);
		Push(&cxt, P7);
		Push(&cxt, P8);
		Push(&cxt, P9);
		Push(&cxt, P10);
		Push(&cxt, P11);
		Push(&cxt, P12);
		Push(&cxt, P13);
		Push(&cxt, P14);
		Push(&cxt, P15);
		Push(&cxt, P16);
		Push(&cxt, P17);
		Push(&cxt, P18);
		Push(&cxt, P19);
		Push(&cxt, P20);
		Push(&cxt, P21);
		Push(&cxt, P22);
		Push(&cxt, P23);
		Push(&cxt, P24);
		Push(&cxt, P25);
		Invoke(&cxt, hash);
		return cxt.GetResult<R>();
	}
};
