#pragma once
#include <cstdio>
#include <string>
#include "exceptions.h"

class WAVHeader
{
public:
	void read(const std::string& filename) throw (IOException);
	void setToZero();
	void print() const;
	void fill(int channelsAmount, int sampleRate, int samplesPerChannel) throw (HeaderFormatException);
	void check(size_t fileSize) const throw (HeaderFormatException);
	struct HeaderInfo
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subchunk1Id[4];
		unsigned long subchunk1Size;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long byteRate;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char subchunk2Id[4];
		unsigned long subchunk2Size;
	};
	HeaderInfo* data = new HeaderInfo;
};