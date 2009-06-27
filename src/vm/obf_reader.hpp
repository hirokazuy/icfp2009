// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#ifndef __VM_OBF_READER_HPP__
#define __VM_OBF_READER_HPP__

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

#endif // __VM_OBF_READER_HPP__
