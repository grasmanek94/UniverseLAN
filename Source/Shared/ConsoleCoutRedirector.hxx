#pragma once

#include <iostream>
#include <memory>
#include <sstream>

namespace universelan::console {
	template < typename C, typename T = std::char_traits<C> >
	struct basic_teebuf : public std::basic_streambuf<C, T>
	{
		using streambuf_type = std::basic_streambuf<C, T>;
		using int_type = typename T::int_type;

		basic_teebuf(streambuf_type* buff_a, streambuf_type* buff_b)
			: first(buff_a), second(buff_b) {}

	protected:
		virtual int_type overflow(int_type c) override
		{
			const int_type eof = T::eof();
			if (T::eq_int_type(c, eof)) return T::not_eof(c);
			else
			{
				const auto ch = T::to_char_type(c);
				return T::eq_int_type(first->sputc(ch), eof) ||
					T::eq_int_type(second->sputc(ch), eof) ? eof : c;
			}
		}

		virtual int sync() override { return !first->pubsync() && !second->pubsync() ? 0 : -1; }

	private:
		streambuf_type* first;
		streambuf_type* second;
	};

	using teebuf = basic_teebuf<char>;

	class Redirector {
	private:
		std::stringbuf sbuf;
		std::streambuf* oldbuf;
		std::shared_ptr<teebuf> tbuf;

		Redirector();
		~Redirector();

	public:
		void capture_tee();
		void capture();
		void release();

		static Redirector* get();
	};
}
