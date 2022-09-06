/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */

#pragma once

#include "Hooking.h"

#include <sstream>

namespace hook {
/*class pattern_match {
 private:
  void* m_pointer;

 public:
  inline pattern_match(void* pointer) { m_pointer = pointer; }

  template <typename T>
  T get(int offset) {
    char* ptr = reinterpret_cast<char*>(m_pointer);
    return reinterpret_cast<T>(ptr + offset);
  }

  template <typename T>
  T extract(int offset) {
    char* address = get<char*>(offset);
    return reinterpret_cast<T>(address + *(int32_t*)address + 4);
  }

  template <typename T>
  T* get() {
    return get<T>(0);
  }
};*/

	class pattern_match {
	private:

		void * m_pointer;

	public:

		inline pattern_match( void * pointer ) {

			m_pointer = pointer;
		}

		template<typename T>
		T * get( int offset ) {

			if ( m_pointer == nullptr ) {
				return nullptr;
			}

			char * ptr = reinterpret_cast<char*>( m_pointer );
			return reinterpret_cast<T*>( ptr + offset );
		}

		template<typename T>
		T * get() {

			return get<T>( 0 );
		}
	};

class pattern {
 private:
  std::string m_bytes;
  std::string m_mask;
  std::string orginal_pattern_;

  uint64_t m_hash;

  size_t m_size;

  std::vector<pattern_match> m_matches;

  bool m_matched;

 private:
  void Initialize(const char* pattern, size_t length);

  bool ConsiderMatch(uintptr_t offset);

  void EnsureMatches(int maxCount);

 public:
  template <size_t Len>
  pattern(const char (&pattern)[Len]) {
    orginal_pattern_ = pattern;
    Initialize(pattern, Len);
  }

  inline pattern& count(int expected) {
    if (!m_matched) {
      EnsureMatches(expected);
    }

    if (m_matches.size() != expected) {
      std::stringstream message;
      message << "pattern: " << orginal_pattern_ << std::endl
              << "found: " << m_matches.size() << " expected: " << expected;
      MessageBoxA(NULL, message.str().c_str(), "Hook: MatchesCountCheckError",
                  MB_OK | MB_ICONEXCLAMATION);
      abort();
    };

    return *this;
  }

  inline size_t size() {
    if (!m_matched) {
      EnsureMatches(INT_MAX);
    }

    return m_matches.size();
  }

  inline pattern_match& get(int index) {
    if (!m_matched) {
      EnsureMatches(INT_MAX);
    }

    return m_matches[index];
  }

 public:
  // define a hint
  static void hint(uint64_t hash, uintptr_t address);
};
class executable_meta {
 private:
  uintptr_t m_begin;
  uintptr_t m_end;

 public:
  executable_meta() : m_begin(0), m_end(0) {}

  void EnsureInit() {
	if ( m_begin ) {
		return;
	}

	HMODULE gtaModule = GetModuleHandle( NULL );

	m_begin = reinterpret_cast<uintptr_t>( gtaModule );
	const IMAGE_DOS_HEADER * dosHeader = reinterpret_cast<const IMAGE_DOS_HEADER*>( gtaModule );
	const IMAGE_NT_HEADERS * ntHeader = reinterpret_cast<const IMAGE_NT_HEADERS64*>( reinterpret_cast<const uint8_t*>(dosHeader)+dosHeader->e_lfanew );
	m_end = m_begin + ntHeader->OptionalHeader.SizeOfCode;
  }

  inline uintptr_t begin() { return m_begin; }
  inline uintptr_t end() { return m_end; }
};
}

void Citizen_PatternSaveHint(uint64_t hash, uintptr_t hint);
