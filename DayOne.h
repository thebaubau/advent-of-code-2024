#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class DayOne {
private:
	std::string word;
	std::ifstream stream;
	std::vector<int> first, second;

	unsigned int total{ 0 };
	unsigned int totalTwo{ 0 };
	unsigned int totalTwoTwo{ 0 };
	int count{ 0 };

public:
	DayOne() {
		stream.open("pairs.txt");

		while (stream >> word) {
			int num{ stoi(word) };

			if (count % 2 == 0)
				first.push_back(num);
			else
				second.push_back(num);

			count++;
		}

		std::sort(first.begin(), first.end());
		std::sort(second.begin(), second.end());

	};

	void FirstPuzzle() {
		for (int i{ 0 }; i < first.size(); i++) {
			total += abs(first[i] - second[i]);
		}

		std::cout << total << std::endl;
	}

	void SecondPuzzle() {
		// Second puzzle - less efficient
		std::for_each(first.begin(), first.end(), [&](auto elem) {
			totalTwo += elem * std::count(second.begin(), second.end(), elem);
		});

		std::cout << totalTwo << std::endl;

		// Efficient
		std::unordered_map<int, int> counts;

		for (int num : second) {
			counts[num]++;
		}

		for (int num : first) {
			totalTwoTwo += num * counts[num];
		}

		std::cout << totalTwoTwo << std::endl;
	}
};