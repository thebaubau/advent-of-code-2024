#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include <regex>


class DayThree {
private:
	std::ifstream stream;
	std::string content;

	int mul(int x, int y) { return x * y; }
public:
	DayThree() {
		stream.open("DayThree.txt");
		std::stringstream ss;

		ss << stream.rdbuf();
		stream.close();

		content = ss.str();

		std::regex pattern(R"(mul\((\d+),(\d+)\))");

		PuzzleOne(pattern);
		PuzzleTwo();
	}

	void PuzzleOne(std::regex& pattern) {
		int total{ 0 };
		std::string::const_iterator searchStart(content.cbegin());
		std::smatch match;

		while (std::regex_search(searchStart, content.cend(), match, pattern)) {
			total += mul(stoi(match[1]), stoi(match[2]));

			searchStart = match.suffix().first;
		}

		std::cout << total << std::endl;
	}

	void PuzzleTwo() {
		int total{ 0 };
		bool skip{ false };
		std::regex patterns(R"((do\(\))|(don't\(\))|mul\((\d+),(\d+)\))");

		auto begin = std::sregex_iterator(content.begin(), content.end(), patterns);
		auto end = std::sregex_iterator();

		for (auto it = begin; it != end; ++it) {
			std::smatch match = *it;
			std::string matchedString = match.str();

			if (std::regex_match(matchedString, std::regex(R"(mul\((\d+),(\d+)\))")) && !skip)
				total += mul(stoi(match[3]), stoi(match[4]));

			else if (std::regex_match(matchedString, std::regex(R"(don\'t\(\))")))	skip = true;

			else if (std::regex_match(matchedString, std::regex(R"(do\(\))"))) skip = false;
		}

		std::cout << total << std::endl;
	}

	~DayThree() = default;
};