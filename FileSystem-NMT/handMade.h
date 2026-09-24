#pragma once
#include <random>
#include <type_traits>
#include <iostream>

namespace hm {

	template <typename T>
	T CinFail(T content) {
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//std::cout << "ERROR: cin overflow, changing the value to numeric_limits<T>::max()";
			return std::numeric_limits<T>::max();
		}
		return content;
	}

	template <typename T>//for enum use : static_cast<enumName>(hm::RandomNumber<enumType>(min, max));
	std::enable_if_t<std::is_floating_point_v<T>, T> RandomGenerator(T min, T max) {
		if (min > max)
			std::swap(min, max);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<T> dist(min, max);
		return dist(gen);
	}

	template <typename T>//for enum use : static_cast<enumName>(hm::RandomNumber<enumType>(min, max));
	std::enable_if_t<std::is_integral_v<T>, T> RandomGenerator(T min, T max) {
		if (min > max)
			std::swap(min, max);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<T> dist(min, max);
		return dist(gen);
	}
}