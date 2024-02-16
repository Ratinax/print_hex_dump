#include <iostream>
#include <cstdio>
#include <ctype.h>

int real_size(const std::string & str)
{
	int i = 0;
	while (i < str.size() && !(str[i] == ' ' && str[i + 1] == ' '))
		i++;
	return (i);
}

std::string hexdump_to_text(const std::string & buffer)
{
	std::string res = "";
	char c;
	int ind = 8;
	// std::cout << "Real Size : " << real_size(buffer) << std::endl;
	for (int i = 8; i < real_size(buffer); i += 5)
	{
		c = static_cast<char>(std::stoi(buffer.substr(i + 2, 2), nullptr, 16));
		if (isascii(c) && c != '\n')
			res += c;
		else
			res += '.';
		c = static_cast<char>(std::stoi(buffer.substr(i, 2), nullptr, 16));
		if (isascii(c) && c != '\n')
			res += c;
		else
			res += '.';
		ind = i;
	}
	// while (ind < buffer.size() - 6)
	// {
	// 	ind += 5;
	// 	res += "..";
	// }
	return (res);
}

void hexDump(const std::string& filePath) {
	std::string command = "hexdump " + filePath;
	FILE* pipe = popen(command.c_str(), "r");

	if (!pipe) {
		std::cerr << "Error while trying to execute hexdump" << std::endl;
		return;
	}

	char buffer[128];
	while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
		std::string str = buffer;
		hexdump_to_text(str);
		std::cout << str.substr(0, str.size() - 1) << " " << hexdump_to_text(str) << str[str.size() - 1];
	}

	pclose(pipe);
}

int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cout << "Usage: ./prog file_path" << std::endl;
		return (1);
	}
	hexDump(argv[1]);

	return 0;
}
