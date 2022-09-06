#include "stdio.h"
#include "jitasm.h"

struct Fibonacci : jitasm::function<unsigned int, Fibonacci, unsigned int>
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

int main()
{
	Fibonacci fibonacci;
	for (int n = 0; n < 10; n++) {
		printf("%d, ", fibonacci(n));
	}
	return 0;
}
