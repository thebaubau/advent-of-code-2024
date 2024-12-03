#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>

class DayTwo {
private:
	std::string line;
	std::string num;
	std::ifstream stream;
	int count{ 0 };

public:
	DayTwo() {
		stream.open("DayTwo.txt");

		while (getline(stream, line)) {
			std::istringstream iss(line);
			std::vector<int> data;

			std::cout << line << std::endl;

			while (getline(iss, num, ' ')) {
				data.push_back(stoi(num));
			}

			if (Safe(data)) {
				count++;
			}
		}

		std::cout << count << std::endl;
	};

	bool Safe(std::vector<int>& numbers) {
		int prevResult{ 0 };

		for (int i{ 0 }; i < numbers.size() - 1; i++) {
			int result = numbers[i] - numbers[i + 1];

			if ((prevResult * result) < 0) {
				std::cout << "Value fluctuated." << std::endl;
				return false;
			}

			prevResult = result;

			std::cout << result << " ";

			result = abs(result);

			if (result > 3 || result < 1) {
				std::cout << "Value not in range." << std::endl;
				return false;
			}
		}
		std::cout << std::endl;
		return true;
	}
};