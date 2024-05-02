#include "ConsoleCoutRedirector.hxx"

#include <iostream>
#include <memory>
#include <sstream>

namespace universelan::console {

	Redirector::Redirector() :
		sbuf{ std::ios_base::out },
		oldbuf{ nullptr },
		tbuf{ nullptr }
	{}

	void Redirector::capture_tee() {
		if (oldbuf) {
			return;
		}
		// set up a tee to also send output of stdout to a string buffer
		oldbuf = std::cout.rdbuf();
		tbuf = std::make_shared<teebuf>(oldbuf, std::addressof(sbuf));
		std::cout.rdbuf(tbuf.get());
	}

	void Redirector::capture() {
		if (oldbuf) {
			return;
		}
		// set up to send output of stdout to a string buffer
		oldbuf = std::cout.rdbuf();
		std::cout.rdbuf(std::addressof(sbuf));
	}

	void Redirector::release() {
		if (!oldbuf) {
			return;
		}

		// restore old behaviour of cout
		std::cout.rdbuf(oldbuf);
		std::cout << sbuf.str();

		oldbuf = nullptr;
	}

	Redirector::~Redirector() {
		release();
	}

	Redirector* Redirector::get() {
		static Redirector* instance = new Redirector();
		return instance;
	}
}
