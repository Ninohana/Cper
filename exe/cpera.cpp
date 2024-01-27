#include "splayer.hpp"
#include "keymap.hpp"
#include "lib/cxxopts/cxxopts.hpp"

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

void play(const std::string& content) {
	Splayer splayer;
	std::stringstream ss(content);
	std::vector<std::string> pitches;
	char ch;
	while (ss >> ch)
	{
		switch (ch)
		{
		case ' ':
		case '\n':
			continue;// ignore it
		case '\\':
		{
			std::string command;
			std::string parameter;
			while (ss >> ch)
			{
				if (ch == '{')
					break;
				else command.append(1, ch);
			}
			while (ss >> ch)
			{
				if (ch == '}')
					break;
				else parameter.append(1, ch);
			}
			
			if (splayer.commands.find(command) != splayer.commands.end())
			{
				// splay.*(splay.commands[command])(parameter);// why cant do that?
				void(Splayer:: * pCommand)(const std::string&) = splayer.commands[command];
				(splayer.*pCommand)(parameter);
			}
			else std::cerr << "无效的命令：" << command << std::endl;
			
			break;
		}
		case '_':
			std::cout << "休止" << std::endl;
			splayer.rest();
			continue;
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'A':
		case 'B':
		{
			std::string pitch;
			pitch.append(1, ch);

			ss >> ch;
			pitch.append(1, ch);
			if (!std::isdigit(ch) || ch == '0')
			{
				std::cerr << "无法解析的字符：" << pitch.c_str() << std::endl;
				continue;
			}

			if (ss.peek() == '#')
			{
				ss.ignore();
				pitch.append(1, '#');
			}

			pitches.push_back(pitch);

			while (ss.peek() == ' ' || ss.peek() == '\n')
				ss.ignore();

			if (ss.peek() == '+')
			{
				ss.ignore();
				continue;
			}

			splayer.knock(pitches);

			pitches.clear();
			std::cout << std::endl;
			continue;
		}
		default:
			std::cerr << "无法解析的字符：" << ch << std::endl;
			break;
		}

	}

}

int main(int argc, char* argv[])
{
	try
	{
		cxxopts::Options options("Cper", "Keyboard also can play.");

		options.add_options()
			("m,map", "key map file name", cxxopts::value<std::string>()->default_value("config/AutoPiano.ckm"))
			("t,text", "text file(s) name", cxxopts::value<std::vector<std::string>>())
			;

		auto result = options.parse(argc, argv);
	
		if (result.count("help"))
		{
			std::cout << options.help() << std::endl;
			return EXIT_SUCCESS;
		}

		std::string map = result["map"].as<std::string>();
		getKeyMap(map);

		std::vector<std::string> files = result["text"].as<std::vector<std::string>>();
		std::vector<std::thread> threads;
		for (const auto& f : files)
		{
			std::ifstream file(f);
			if (!file.good())
			{
				std::cerr << "打开文件失败：" << f << std::endl;
				return EXIT_FAILURE;
			}
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			file.close();

			threads.push_back(std::thread(play, content));
		}
		for (auto& t : threads)
			t.join();
		
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

	return EXIT_SUCCESS;
	// write();
	//Score score = read("rain.cps");
	/*
	// std::cout << "STIGMA: " << std::hex << static_cast<int>(score.header.stigma) << std::endl;
	// std::cout << "VERSION: " << static_cast<int>(score.header.version) << std::endl;
	std::cout << score.header.title << std::endl;
	std::cout << "谱作者: " << score.header.author << std::endl;
	std::cout << "曲作者: " << score.header.composer << std::endl;
	std::cout << "SPEED: " << score.track.speed << std::endl;
	//std::cout << "MEASURETIME: " << track.measureTime << std::endl;
	//std::cout << "MODE: " << track.mode << std::endl;
	std::cout << "NOTESIZE: " << score.track.noteSize << std::endl;
	*/
}
/*
const char VERSION = '1';
const char END[3] = { 0xBE, 0xDE, 0xAD };

struct Header
{
	byte stigma;
	byte version;
	std::string title;
	std::string author;
	std::string composer;

	friend std::ostream& operator <<(std::ostream& out, const Header& header)
	{
		out << header.stigma;
		out << header.version;
		out << header.title << '\0';
		out << header.author << '\0';
		out << header.composer << '\0';

		return out;
	}

	friend std::istream& operator >>(std::istream& in, Header& header)
	{
		in >> header.stigma >> header.version;
		char c;
		while (in >> c)
		{
			if (c == '\0')
				break;
			
			header.title.push_back(c);
		}
		while (in >> c)
		{
			if (c == '\0')
				break;
			
			header.author.push_back(c);
		}
		while (in >> c)
		{
			if (c == '\0')
				break;
			
			header.composer.push_back(c);
		}

		return in;
	}
};

struct Note
{
	char duration[3];
	std::vector<char> pitches;

	friend std::ostream& operator <<(std::ostream& out, const Note& note)
	{
		out.write(note.duration, 3);
		for (auto& pitch : note.pitches)
		{
			out << pitch;
		}
		out << '\0';

		return out;
	}

	friend std::istream& operator >>(std::istream& in, Note& note)
	{
		in.read(note.duration, 3);
		char pitch;
		while (in >> pitch)
		{
			if (pitch == '\0')
				break;

			note.pitches.push_back(pitch);
		}

		return in;
	}
};

#pragma pack(1)
struct Track
{
	unsigned short speed;
	std::string measureTime;
	std::string mode;
	unsigned short noteSize;
	std::vector<Note> notes;
	// Note notes[65535];

	friend std::ostream& operator <<(std::ostream& out, const Track& track)
	{
		out.put(track.speed & 0xFF);
		out.put(track.speed >> 8);
		out << track.measureTime << '\0';
		out << track.mode << '\0';
		out.put(track.noteSize & 0xFF);
		out.put(track.noteSize >> 8);
		for (size_t i = 0;i < track.noteSize;i++)
		{
			out << track.notes.at(i);
		}

		return out;
	}

	friend std::istream& operator >>(std::istream& in, Track& track)
	{
		track.speed = in.get() | in.get() << 8;
		char measureTime[4];
		in.read(measureTime, 4);
		track.measureTime = measureTime;
		char mode[3];
		in.read(mode, 3);
		track.mode = mode;
		track.noteSize = in.get() | in.get() << 8;
		for (size_t i = 0;i < track.noteSize;i++)
		{
			Note note;
			track.notes.push_back(note);
			in >> track.notes.at(i);
		}

		return in;
	}
};
#pragma pack()

struct Score
{
	Header header;
	Track track;
};

void write()
{
	Header header;
	header.stigma = 0x89;
	header.version = 1;
	header.title = "rain";
	header.author = "Snowiest";
	header.composer = "Ninohana";

	std::ofstream file("rain.cps", std::ios::binary);
	if (!file)
	{
		std::cerr << "Failed to open file." << std::endl;
		return;
	}

	//file.write(reinterpret_cast<const char*>(&header), sizeof(Header));
	file << header;

	Track track;
	track.speed = 190;
	track.measureTime = "4/4";
	track.mode = "Bb";
	track.noteSize = 1;

	Note note;
	note.duration[0] = '1';
	note.duration[1] = '/';
	note.duration[2] = '8';
	note.pitches.push_back(PITCH_G5S);
	note.pitches.push_back(PITCH_F5S);
	track.notes.push_back(note);
	
	file << track;

	file.write(END, 3);

	file.close();
}

Score read(std::string path)
{
	Score score;

	std::ifstream cps(path);
	if (!cps)
	{
		std::cerr << "打开文件失败" << std::endl;
		return score;
	}

	Header header;
	Track track;

	cps >> header;
	cps >> track;
	cps.close();
	
	score.header = header;
	score.track = track;

	return score;
}
*/