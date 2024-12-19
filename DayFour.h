#pragma once

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>


class DayFour {
private:
	std::ifstream stream;
	std::string content;

	std::string line;
	std::vector<std::string> grid;

	std::string xmas{ "XMAS" };
	std::string samx{ "SAMX" };
	int count{ 0 };

	int countSecond{ 0 };


public:
	DayFour() {
		stream.open("DayFour.txt");

		while (getline(stream, line)) {
			grid.push_back(line);
		}

		RotateTextCW(grid, "DayFourCC.txt");
		RotateTextCCW(grid, "DayFourCCW.txt");
		ColumnsAsRows(grid, "DayFourColsAsRows.txt");

		count += CountXmas("DayFour.txt", xmas);
		count += CountXmas("DayFour.txt", samx);
		count += CountXmas("DayFourCC.txt", xmas);
		count += CountXmas("DayFourCC.txt", samx);
		count += CountXmas("DayFourCCW.txt", xmas);
		count += CountXmas("DayFourCCW.txt", samx);
		count += CountXmas("DayFourColsAsRows.txt", xmas);
		count += CountXmas("DayFourColsAsRows.txt", samx);

		std::cout << count << std::endl;

		std::stringstream ss;

		ss << stream.rdbuf();
		stream.close();

		content = ss.str();

		std::regex patternXMAS(R"(M\.S\n\.A\.\nM\.S)");
		std::regex patternSAMX(R"(S\.S\n\.A\.\nM\.M)");

		std::string::const_iterator searchStart(content.cbegin());
		//std::smatch match;

		// Use regex to find all matches
		auto matches_begin = std::sregex_iterator(content.begin(), content.end(), patternXMAS);
		auto matches_end = std::sregex_iterator();

		// Iterate over all matches
		for (auto it = matches_begin; it != matches_end; ++it) {
			std::smatch match = *it;
			size_t pos = match.position();

			// Output match and its position
			std::cout << "Match found at position: " << pos << std::endl;
			std::cout << "Matched region:\n" << match.str() << std::endl;
		}
	};

	~DayFour() = default;

	void RotateTextCW(const std::vector<std::string>& grid, std::string fileName) {
		int rows = grid.size();
		int cols = grid[0].size();

		std::ofstream outFile(fileName);
		std::vector<std::string> result(rows + cols - 1);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result[i + j] += grid[i][j];
			}
		}

		for (const auto& line : result) {
			outFile << line << "\n";
		}

		outFile.close();
	}

	void RotateTextCCW(const std::vector<std::string>& grid, std::string fileName) {
		int rows = grid.size();
		int cols = grid[0].size();
		int offset = cols - 1;

		std::ofstream outFile(fileName);
		std::vector<std::string> result(rows + cols - 1);

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result[j - i + offset] += grid[i][j];
			}
		}

		for (const auto& line : result) {
			outFile << line << '\n';
		}

		outFile.close();
	}

	void ColumnsAsRows(const std::vector<std::string>& grid, std::string fileName) {
		int rows = grid.size();
		int cols = grid[0].size();

		std::ofstream outFile(fileName);
		std::vector<std::string> transposed(cols, std::string(rows, ' '));

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				transposed[j][i] = grid[i][j];
			}
		}

		for (const auto& line : transposed) {
			outFile << line << '\n';
		}

		outFile.close();
	}

	int CountXmas(std::string fileName, std::string searchWord) {
		int count{ 0 };
		std::ifstream s;
		std::stringstream buffer;
		std::string content;

		s.open(fileName);

		buffer << s.rdbuf();
		content = buffer.str();

		for (size_t offset = content.find(searchWord); offset != std::string::npos; offset = content.find(searchWord, offset + searchWord.length())) {
			++count;
		}

		s.close();

		return count;
	}
};
