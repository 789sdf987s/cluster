#pragma once
#include <cstdio>
#include <cinttypes>
#include <iostream>
#include <string>

class c_hasher {
public:
	static constexpr std::uint32_t basis = 0x811C9DC5;
	static constexpr std::uint32_t prime = 0x1000193;

	constexpr std::uint32_t hash_const(const char* string, const std::uint32_t value = basis) noexcept {
		return !*string ? value : hash_const(&string[1], (value ^ std::uint32_t(string[0])) * prime);
	}

	inline const std::uint32_t hash(const std::string& string) {
		std::uint32_t hashed = basis;

		for (std::size_t i = 0U; i < string.length(); ++i) {
			hashed ^= string[i];
			hashed *= prime;
		}

		return hashed;
	}
};

extern c_hasher g_hasher;