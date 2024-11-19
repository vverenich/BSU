#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <tchar.h>
#include <float.h>



double sqrt_x_RTL(double x) {
	// C-version by RTL
	return 1 / sqrt(1.0 + x);
}


double sqrt_x_FPU(double x) {
	// Asm version by FPU
	__asm {
		fld1;//st=1
		fld1;//st=1, st(1)=1
		fadd x;//st=1+x, st(1)=1
		fsqrt; //st = sqrt(1+x), st(1)=1
		fdiv;// st(0) = st(1) / st(0)
	}
}
const double d1pow10[DBL_DIG - 2 + 1] = {
 0.001, // 1/(10^3)
 0.0001, // 1/(10^4)
 0.00001, // 1/(10^5)
 0.000001, // 1/(10^6)
 0.0000001, // 1/(10^7)
 0.00000001, // 1/(10^8)
 0.000000001, // 1/(10^9)
 0.0000000001, // 1/(10^10)
 0.00000000001, // 1/(10^11)
 0.000000000001, // 1/(10^12)
 0.0000000000001, // 1/(10^13)
 0.00000000000001, // 1/(10^14)
 0.000000000000001, // 1/(10^15)
 0.0000000000000001, // 1/(10^16)
};
double sqrt_x_assembler(double x, int n) {
	double x1 = 1;
	double x0 = -x;
	// Asm version by Taylor
	// st(3) result
// st(2) x
// st(1) step
// st(0) eps
	__asm {;// result = 0
	mov eax, -1
		fldz
		;// load x
	fld x0
		;// step = x
	fld x1
		;// eps = 1 / 10^(n + 1)
	mov ebx, n
		dec ebx
		dec ebx
		fld qword ptr d1pow10[ebx * 8]
		;// n = 1, ebx == n
	mov ebx, 1
		mov n, ebx
		;// while( fabs( step ) >= eps ) {
	fld st(1);
next:
	fabs;// st= abs(step)
	fcomip st, st(1);
	jna finish;
	;// result += step;
	fld st(1)
		;// st= step, st1= eps, st2= step, st3= x, st4= result
	fadd st(4), st
		;
	fimul n;// st= step * n,
	fmul st, st(3);// st = (( step * n ) * x ), ...
	inc ebx;// n++
	mov n, ebx
		fidiv n;// st =((step * n)* x)/(n + 1)
	inc ebx;// n++
	mov n, ebx
		fst st(2);// step = st
	;// }
	jmp next
		finish :
	;// return result * (-1);
	fstp st;// clear stack
	fstp st;// clear stack
	fstp st;// clear stack
	}
}

int _tmain(int argc, _TCHAR* argv[]) {
	// Counts f(x,k)=log(1 - x)
	// Command line arguments:
	// [1]: x, [-1,1)
	// [2]: k, k > 1
	double x;
	int k;
	TCHAR fmt[80];
	if (argc != 3) {
		_ftprintf(stderr, _T("Syntax: %s x k"),
			_tcsrchr(argv[0], _T('\\')) + 1);
		return 1;
	}
	x = _tcstod(argv[1], (_TCHAR**)NULL);
	if (x >= 1 || x <= -1) {
		_ftprintf(stderr,
			_T("Argument x must be in range ]-1, 1[\n"));
		return 1;
	}
	k = _ttoi(argv[2]);
	if (k <= 1 || k > DBL_DIG) {
		_ftprintf(stderr,
			_T("Argument k must be in range ]1, %d]\n"), DBL_DIG);
		return 1;
	}
	_tprintf(_T("Started with arguments: %f %d\n"), x, k);
	_stprintf(fmt, _T("C version by RTL:\t %%.%df\n"), k);
	_tprintf(fmt, sqrt_x_RTL(x));
	_stprintf(fmt, _T("Asm version by FPU:\t %%.%df\n"), k);
	_tprintf(fmt, sqrt_x_FPU(x));
	_stprintf(fmt, _T("Asm version by Taylor:\t %%.%df\n"), k);
	_tprintf(fmt, sqrt_x_assembler(x, k));
	return 0;
}