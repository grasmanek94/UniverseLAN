#include "stdio.h"
#include "jitasm.h"

// int add1(int arg1)
// {
//   return arg1 + 1;
// }
struct add1 : jitasm::function<int, add1, int>
{
	Result main(Addr a)
	{
		mov(ecx, dword_ptr[a]);
		add(ecx, 1);
		return ecx;
	}
};

int main()
{
	// Make function instance
	add1 f;

	// Runtime code genaration and run
	int result = f(99);

	printf("Result : %d\n", result);

	return 0;
}
