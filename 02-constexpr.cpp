#include <iostream>

namespace
{
	constexpr size_t bin_id(size_t x)
	{
		size_t y = 1;
		for(size_t i = 0; i < 8 * sizeof(size_t); ++i)
		{
			if (y >= x) return i;
			y *= 2;
		}
		return 8 * sizeof(size_t);
	}	

	static_assert(bin_id(0) == 0, "");
	static_assert(bin_id(1) == 0, "");
	static_assert(bin_id(2) == 1, "");
	static_assert(bin_id(4) == 2, "");
	static_assert(bin_id(7) == 3, "");
	static_assert(bin_id(8) == 3, "");
	static_assert(bin_id(9) == 4, "");
	static_assert(bin_id(1023) == 10, "");
	static_assert(bin_id(1024) == 10, "");
	static_assert(bin_id(1025) == 11, "");
	static_assert(bin_id(1024 * 1024 - 33) == 20, "");
	static_assert(bin_id(1024 * 1024) == 20, "");
	static_assert(bin_id(1024 * 1024 + 33) == 21, "");
	static_assert(bin_id(1024 * 1024 * 1024 - 127) == 30, "");
	static_assert(bin_id(1024 * 1024 * 1024) == 30, "");
	static_assert(bin_id(1024 * 1024 * 1024 + 127) == 31, "");
}

int main()
{
	size_t n;
	while (std::cin >> n)
		std::cout << bin_id(n) << std::endl;
	return 0;
}