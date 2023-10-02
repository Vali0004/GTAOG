#pragma once
#include "pch/pch.h"
#include "defines.h"
#include "templates.h"

class string {
public:
	string();
	string(ccp str);
	string(const string& other);
	string(size_t size);
	string(size_t size, char initValue);
	~string();

	size_t size() const {
		return size_;
	}
	ccp str() const {
		return data_;
	}
	buf_t data() const {
		return data_;
	}
	bool empty() const {
		return size_;
	}
	void clear() {
		delete[] data_;
		size_ = 0;
	}
	buf_t begin() {
		return &data_[0];
	}
	buf_t end() {
		return &data_[size()];
	}
	string substr(size_t startIdx, size_t endIdx = -1) {
		if (endIdx == -1) {
			return &begin()[startIdx];
		}
		size_t len = endIdx - startIdx;
		buf_t dest = new char[len];
		strncpy(dest, (begin() + startIdx), len);
		delete dest;
		return dest;
	}
	void insert(size_t pos, ccp str);
	void insert(size_t pos, char c);
	template <size_t s>
	void append(const char(&str)[s]) {
		strncat(data_, str, s);
	}
	void append(string str);
	void append(char c);
	string& operator+(s32 value);
	string& operator+(db value);
	string& operator+(fp value);
	string& operator+(const string& other);
	string& operator=(const string& other);
	string& operator=(const char* other);
	bool operator==(const string& other) {
		return data() == other.data();
	}
	bool operator==(const char* str) {
		return data() == str;
	}
	char operator[](size_t index) {
		return begin()[index];
	}
	size_t find_last_of(buf_t const str) {
		size_t strLen{ strlen(str) };
		for (size_t i{ size_ - 1 }; i; --i) {
			for (size_t j{}; j != strLen; ++j) {
				if (data_[i] == str[j]) {
					return i;
				}
			}
		}
		return -1;
	}
	size_t find_last_of(char const c) {
		for (size_t i{ size_ - 1 }; i; --i) {
			if (data_[i] == c) {
				return i;
			}
		}
		return -1;
	}
	size_t find_first_of(buf_t const str) {
		size_t strLen{ strlen(str) };
		for (size_t i{}; i != (size_ - 1); ++i) {
			for (size_t j{}; j != strLen; ++j) {
				if (data_[i] == str[j]) {
					return i;
				}
			}
		}
		return -1;
	}
	size_t find_first_of(char const c) {
		for (size_t i{}; i != (size_ - 1); ++i) {
			if (data_[i] == c) {
				return i;
			}
		}
		return -1;
	}
private:
	buf_t data_{};
	size_t size_{};
};