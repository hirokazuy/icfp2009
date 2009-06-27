//------------------------------------------------------------------------------
// main インプリメント
// Last Modified: 2009/06/27 10:52:57
//------------------------------------------------------------------------------
#include <iostream>
#include <fstream>

struct ObfFrame
{
	unsigned int instruction;
	double data;
};

class ObfReader
{
public:
	ObfReader(std::istream& stream) : stream_(stream), counter_(0) {
	}
	~ObfReader() {}

	ObfFrame getNextFrame() {
		ObfFrame frame;
		if (counter_ & 1) {
			// odd
			frame.instruction = read<unsigned int>();
			frame.data = read<double>();
		} else {
			// even
			frame.data = read<double>();
			frame.instruction = read<unsigned int>();
		}
		++counter_;
		return frame;
	}

	template<typename T>
	T read() {
		T val;
		stream_.read(reinterpret_cast<char*>(&val), sizeof(T));
		return val;
	}

	double readDouble() {
		return read<double>();
	}

	int readInt() {
		return read<unsigned int>();
	}

	int isEof() {
		return stream_.eof();
	}

private:
	std::istream& stream_;
	int counter_;
};

void printUsage() {
	std::cout << "usage: simulator obf" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printUsage();
		return 0;
	}

	std::fstream stream(argv[1], std::fstream::in | std::fstream::binary);
	ObfReader reader(stream);
	while (true) {
		ObfFrame frame = reader.getNextFrame();
		if (reader.isEof()) break;

		std::cout << frame.instruction << ", " << frame.data << std::endl;
	}
	stream.close();

	return 0;
}
