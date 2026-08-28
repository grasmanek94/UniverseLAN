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
		// REVIEW: std::cout's process-wide stream buffer is replaced without
		// synchronization; concurrent capture/release or output can race. Restrict
		// this utility to an externally synchronized, single-threaded scope.
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

		// REVIEW: sbuf is never cleared, so a second capture/release replays all
		// earlier captured output. Reset the string buffer after releasing.
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
