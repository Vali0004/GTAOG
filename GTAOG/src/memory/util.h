#pragma once
#include "memory/memory.h"
#include "memory/module.h"

namespace memory {
	namespace util {
		extern optional<u8> charToHex(char const c);
		extern vectorr<optional<u8>> toBytes(string str);
		extern bool memoryCmp(u8* addr, optional<u8>* sig, st size);
		extern u64 findPattern(vectorr<optional<u8>> bytes, moduleHandle handle = {});
	}
	global bool findInSection(size_t i, ccp value) {
		size_t valueSize{ strlen(value) + 1 };
		u8* data{ reinterpret_cast<u8*>(i) };
		for (size_t i{}; i != valueSize; ++i) {
			if (data[i] != value[i]) {
				return false;
			}
		}
		return true;
	}
	global void findAndReplaceString(ccp value, ccp replacement) {
		moduleHandle handle{};
		for (size_t i{ handle.m_begin.as<size_t>() }; i != handle.m_end.as<size_t>(); ++i) {
			if (findInSection(i, value)) {
				strncpy(reinterpret_cast<char*>(i), replacement, strlen(value) + 1);
			}
		}
	}
}