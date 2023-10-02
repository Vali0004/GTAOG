#include "pointers.h"
#define SCAN(p, n, a, ...) p = memory::scanner(n, a).get()__VA_ARGS__.as<decltype(p)>();

namespace pointers {
	u64 patch1, patch2, statPatch1, statPatch2;
	void scan() {
		SCAN(patch1, "P1", "38 80 ? ? 38 A0 ? ? 48 03 ? ? 3C 60 ? ? 3C 80");
		SCAN(patch2, "P2", "38 C0 ? ? 31 08 ? ? 38 E0 ? ? 4B");
		SCAN(statPatch1, "SP1", "7C 08 ? ? 48 23 ? ? F8 21 ? ? F8 01 ? ? 60 7E 00 00 60 9F 00 00 80 9E 00 1C");
		SCAN(statPatch2, "SP2", "62 E9 00 00 30 A5 ? ? 63 A3 00 00 63 64 00 00");
	}
	void applyPatches() {
		memory::findAndReplaceString("https://", "http://");
		memory::findAndReplaceString("ros.rockstargames.com", "ros.gtao.gg");
		// Core patches
		*(uint8_t*)(patch1 + 3) = 0x00; // Change 01 to 00 (38 80 00 01)
		*(uint16_t*)(patch2 + 2) = 0x03; // Change 08 to 03 (38 C0 08 A3)
		// Stat patches (ig)
		*(uint32_t*)statPatch1 = 0x38600001;
		*(uint32_t*)(statPatch1 + 4) = 0x4E800020;
		*(uint32_t*)statPatch2 = 0x39200001;
		*(uint32_t*)(statPatch2 + 0x10) = 0x38C0001B;
	}
}