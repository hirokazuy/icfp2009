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
	ObfReader(std::istream& stream) : stream_(stream), counter_(0) {}
	~ObfReader() {}

	ObfFrame getNextFrame() {
		ObfFrame frame;
		if (counter_ & 1) {
			// odd
			stream_ >> frame.instruction;
			stream_ >> frame.data;
		} else {
			// even
			stream_ >> frame.data;
			stream_ >> frame.instruction;
		}
		++counter_;
		return frame;
	}

	int isEof() {
		return stream_.eof();
	}

private:
	std::istream stream_;
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

	std::fstream stream(argv[1]);
	ObfReader reader(stream);
	while (reader.isEof()) {
		ObfFrame frame = reader.getNextFrame();
		std::cout << frame.instruction << ", " << frame.data << std::endl;
	}

	return 0;
}
