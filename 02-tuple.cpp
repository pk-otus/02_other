#include <string>
#include <tuple>
#include <cassert>

#define TEST_CUSTOM_TUPLE	1
#define TEST_CUSTOM_TIE		2

namespace
{
	auto getPerson() {
		const std::string name = "Petia";
		const std::string secondName = "Ivanoff";
		const std::size_t age = 23;
		const std::string department = "Sale";
		return std::make_tuple(
			name, secondName, age, department
		);
	}


	template < std::size_t... Ns, typename... Ts >
	auto tail_impl(std::index_sequence<Ns...>, std::tuple<Ts...> t)
	{
		return  std::make_tuple(std::get<Ns + 1u>(t)...);
	}

	template < typename... Ts >
	auto tail(std::tuple<Ts...> t)
	{
		return  tail_impl(std::make_index_sequence<sizeof...(Ts) - 1u>(), t);
	}


	template<typename T, typename... Args> class custom_tuple
	{
	public:
		custom_tuple(T& param, Args&... args) : data(param), inner(args...) {}

		custom_tuple<T, Args...>& operator=(std::tuple<T, Args...> i)
		{
			data = std::get<0>(i);
			inner = tail(i);
			return *this;
		}

	private:
		T & data;
		custom_tuple<Args...> inner;
	};

	template <typename T> class custom_tuple<T>
	{
	public:
		custom_tuple(T& param) : data(param) {}

		custom_tuple<T>& operator=(std::tuple<T> ts)
		{
			data = std::get<0>(ts);
			return *this;
		}
	private:
		T & data;
	};

	template<typename... Args>
	std::tuple<Args&...> custom_tie(Args&... args)
	{
		return std::tuple<Args&...>(args...);
	}
}

int main_tuple(int argc, char * argv[]) {
	std::string name, secondName, department;
	std::size_t age;

#define TEST TEST_CUSTOM_TIE

#if TEST == TEST_CUSTOM_TUPLE
	custom_tuple<std::string, std::string, std::size_t, std::string>(name, secondName, age, department) = getPerson();
#elif TEST == TEST_CUSTOM_TIE
	custom_tie(name, secondName, age, department) = getPerson();
#endif

	assert(name == "Petia");
	assert(secondName == "Ivanoff");
	assert(age == 23);
	assert(department == "Sale");
	return 0;
}
