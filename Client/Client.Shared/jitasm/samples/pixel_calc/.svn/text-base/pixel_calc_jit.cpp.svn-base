// Copyright (c) 2009, Hikaru Inoue, Akihiro Yamasaki,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
//      copyright notice, this list of conditions and the following
//      disclaimer in the documentation and/or other materials provided
//      with the distribution.
//    * The names of the contributors may not be used to endorse or promote
//      products derived from this software without specific prior written
//      permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <string>
#include <vector>
#include <boost/bind.hpp>
#include <boost/spirit.hpp>
#include "jitasm.h"


class RenderExpr : public jitasm::function<void, RenderExpr, void *, size_t, void *, size_t, void *, size_t, int, int>
{
private:
	struct Calculator : public boost::spirit::grammar<Calculator>
	{
		RenderExpr& renderExpr_;
		Calculator(RenderExpr& renderExpr) : renderExpr_(renderExpr) {}

		template <typename ScannerT>
		struct definition
		{
			definition(Calculator const& self)
			{
				using namespace boost;
				using namespace boost::spirit;
				expression
					=	term
						>> *(   (L'+' >> term)[boost::bind(&do_add, ref(self.renderExpr_), _1, _2)]
							|	(L'-' >> term)[boost::bind(&do_sub, ref(self.renderExpr_), _1, _2)]
							);

				term
					=   factor
						>> *(   (L'*' >> factor)[boost::bind(&do_mul, ref(self.renderExpr_), _1, _2)]
							|   (L'/' >> factor)[boost::bind(&do_div, ref(self.renderExpr_), _1, _2)]
							);

				factor
					=   real_p[boost::bind(&do_real, ref(self.renderExpr_), _1)]
					|	chseq_p(L"src1")[boost::bind(&do_src1, ref(self.renderExpr_), _1, _2)]
					|	chseq_p(L"src2")[boost::bind(&do_src2, ref(self.renderExpr_), _1, _2)]
					|   L'(' >> expression >> L')'
					|   (L'-' >> factor)[boost::bind(&do_neg, ref(self.renderExpr_), _1, _2)]
					|   (L'+' >> factor);
			}

			boost::spirit::rule<ScannerT> expression, term, factor;

			boost::spirit::rule<ScannerT> const& start() const { return expression; }
		};
	};

	void do_add(const wchar_t *, const wchar_t *)
	{
		XmmReg reg1 = variableStack_.back();
		variableStack_.pop_back();
		XmmReg reg2 = variableStack_.back();
		addps(reg2, reg1);
	}

	void do_sub(const wchar_t *, const wchar_t *)
	{
		XmmReg reg1 = variableStack_.back();
		variableStack_.pop_back();
		XmmReg reg2 = variableStack_.back();
		subps(reg2, reg1);
	}

	void do_mul(const wchar_t *, const wchar_t *)
	{
		XmmReg reg1 = variableStack_.back();
		variableStack_.pop_back();
		XmmReg reg2 = variableStack_.back();
		mulps(reg2, reg1);
	}

	void do_div(const wchar_t *, const wchar_t *)
	{
		XmmReg reg1 = variableStack_.back();
		variableStack_.pop_back();
		XmmReg reg2 = variableStack_.back();
		divps(reg2, reg1);
	}

	void do_real(double val)
	{
		float fval = static_cast<float>(val);
		mov(eax, *(unsigned int*)&fval);
		XmmReg var;
		movd(var, eax);
		shufps(var, var, 0);
		variableStack_.push_back(var);
	}

	void do_src(int i)
	{
		__declspec(align(16)) const static float factor8bpp[4] = {1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f, 1.0f/255.0f};
		XmmReg src;
		movd(src, dword_ptr[i == 0 ? zsi : zbx]);
		punpcklbw(src, zero_);
		punpcklwd(src, zero_);
		cvtdq2ps(src, src);
		mov(zax, (uintptr_t)factor8bpp);
		mulps(src, xmmword_ptr[zax]);
		variableStack_.push_back(src);
	}

	void do_src1(const wchar_t *, const wchar_t *)
	{
		do_src(0);
	}

	void do_src2(const wchar_t *, const wchar_t *)
	{
		do_src(1);
	}

	void do_neg(const wchar_t *, const wchar_t *)
	{
		XmmReg var = variableStack_.back();
		XmmReg tmp;
		xorps(tmp, tmp);
		subps(tmp, var);
		movaps(var, tmp);
	}

public:
	RenderExpr(wchar_t *expr) : expr_(expr) {}

	void main(Addr dst, Addr dstSkip, Addr src1, Addr src1Skip, Addr src2, Addr src2Skip, Addr width, Addr height)
	{
		mov(zsi, ptr[src1]);
		mov(zbx, ptr[src2]);
		mov(zdi, ptr[dst]);
		xorps(zero_, zero_);

		L("LoopY");
		{
			mov(ecx, dword_ptr[width]);

			L("LoopX");
			{
				Calculator calc(*this);
				boost::spirit::parse_info<const wchar_t *> info = boost::spirit::parse(expr_, calc, boost::spirit::space_p);
				if (!info.full)
					throw info;

				__declspec(align(16)) const static float factor8bpp[4] = {255.0f, 255.0f, 255.0f, 255.0f};
				mov(zax, (uintptr_t)factor8bpp);
				XmmReg dstReg = variableStack_.back();
				mulps(dstReg, xmmword_ptr[zax]);
				cvtps2dq(dstReg, dstReg);
				packssdw(dstReg, dstReg);
				packuswb(dstReg, dstReg);
				movd(eax, dstReg);
				movnti(dword_ptr[zdi], eax);

				add(zsi, 4);
				add(zbx, 4);
				add(zdi, 4);
				dec(ecx);
				jnz("LoopX");
			}

			add(zsi, ptr[src1Skip]);
			add(zbx, ptr[src2Skip]);
			add(zdi, ptr[dstSkip]);
			dec(dword_ptr[height]);
			jnz("LoopY");
		}
	}

private:
	wchar_t *expr_;
	std::vector<XmmReg> variableStack_;
	XmmReg zero_;
};

bool RenderJIT(wchar_t *expr, void *dst, size_t dstStride, void *src1, size_t src1Stride, void *src2, size_t src2Stride, int width, int height)
{
	try {
		RenderExpr renderExpr(expr);
		renderExpr(dst, dstStride - width * 4, src1, src1Stride - width * 4, src2, src2Stride - width * 4, width, height);

		//FILE *file = fopen("render.dmp", "wb");
		//fwrite(renderExpr.GetCode(), 1, renderExpr.GetCodeSize(), file);
		//fclose(file);

		return true;
	}
	catch (...) {
		return false;
	}
}
