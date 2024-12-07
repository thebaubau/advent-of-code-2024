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

	typedef int (*FnPtr)(int, int);

public:
	DayThree() {


		stream.open("DayThree.txt");
		std::stringstream ss;

		ss << stream.rdbuf();
		stream.close();

		content = ss.str();

		std::regex pattern(R"(mul\((\d+),(\d+)\))");
		std::regex dos(R"(do\(\))");
		std::regex donts(R"(don\'t\(\))");


		PuzzleOne(pattern);
		PuzzleTwo(pattern, dos, donts);
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

	void PuzzleTwo(std::regex& pattern, std::regex& dos, std::regex& donts) {
		int total{ 0 };
		bool skip{ false };
		std::string::const_iterator searchStart(content.cbegin());
		std::vector<std::smatch> matches;
		std::smatch match;

		while (std::regex_search(searchStart, content.cend(), match, pattern)) {
			matches.emplace_back(match);
			searchStart = match.suffix().first;
		}

		searchStart = content.cbegin();
		while (std::regex_search(searchStart, content.cend(), match, donts)) {
			matches.emplace_back(match);
			searchStart = match.suffix().first;
		}

		searchStart = content.cbegin();
		while (std::regex_search(searchStart, content.cend(), match, dos)) {
			matches.emplace_back(match);
			searchStart = match.suffix().first;
		}

		auto firstMatch = *std::min_element(matches.begin(), matches.end(),
			[](const auto& a, const auto& b) {
			return a.position() < b.position();
		});

		std::cout << total << std::endl;
	}


	~DayThree() = default;
};