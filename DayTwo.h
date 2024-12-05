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
	int countPuzzleOne{ 0 };
	int countPuzzleTwo{ 0 };

public:
	DayTwo() {
		stream.open("DayTwo.txt");

		while (getline(stream, line)) {
			std::istringstream iss(line);
			std::vector<int> data;

			while (getline(iss, num, ' ')) {
				int currentNum = stoi(num);
				data.push_back(currentNum);
			}

			if (Safe(data)) {
				countPuzzleOne++;
			}

			if (SafeTwo(data)) {
				countPuzzleTwo++;
			}
		}

		std::cout << countPuzzleOne << std::endl;
		std::cout << countPuzzleTwo << std::endl;
	};

	bool Safe(std::vector<int>& numbers) {
		int prevResult{ 0 };

		for (int i{ 0 }; i < numbers.size() - 1; i++) {
			int result = numbers[i] - numbers[i + 1];

			if (DifferenceInvalid(prevResult, result)) return false;
			if (PairNotInRange(numbers[i], numbers[i + 1])) return false;

			prevResult = result;
		}
		return true;
	}

	bool SafeTwo(std::vector<int>& numbers) {
		std::vector<int> numbersCopy = numbers;

		if (Safe(numbers)) return true;

		for (int i{ 0 }; i < numbersCopy.size(); i++) {
			std::vector<int> numbersCopy = numbers;
			numbersCopy.erase(numbersCopy.begin() + i);

			if (Safe(numbersCopy)) return true;
		}

		return false;
	}

	bool PairNotInRange(int& numOne, int& numTwo) {
		int difference = abs(numOne - numTwo);

		return (difference > 3 || difference < 1);
	}

	bool DifferenceInvalid(int& diffOne, int& diffTwo) {
		return (diffOne * diffTwo) < 0;
	}
};