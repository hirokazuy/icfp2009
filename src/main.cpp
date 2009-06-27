//------------------------------------------------------------------------------
// main インプリメント
// Last Modified: 2009/06/27 10:52:57
//------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>

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

	int size() {
		return counter_;
	}

	int isEof() {
		return stream_.eof();
	}

private:
	std::istream& stream_;
	int counter_;
};

class ObfVM
{
public:
	ObfVM() {}
	~ObfVM() {}

	int load(std::istream& stream) {
		ObfReader reader(stream);
		while (true) {
			ObfFrame frame = reader.getNextFrame();
			if (reader.isEof()) break;

			addFrame(frame);
			std::cout << frame.instruction << ", " << frame.data << std::endl;
		}
		return reader.size();
	}

	void addFrame(const ObfFrame& frame) {
		operators_.push_back(frame.instruction);
		memory_.push_back(frame.data);
	}

private:
	std::vector<double> memory_;
	std::vector<unsigned int> operators_;
};

void printUsage() {
	std::cout << "usage: simulator obf" << std::endl;
}

void loadFromFile(ObfVM& vm, char *filename) {
	std::fstream stream(filename, std::fstream::in | std::fstream::binary);
	vm.load(stream);
	stream.close();
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printUsage();
		return 0;
	}

	ObfVM vm;
	loadFromFile(vm, argv[1]);

	return 0;
}
