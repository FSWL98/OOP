#include "stdafx.h"
#include "WAVHeader.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>

void WAVHeader::read(const std::string& filename) throw(IOException)
{
	this->setToZero();
	int headerDataSize = sizeof(HeaderInfo);
	std::ifstream fin(filename, std::ifstream::binary);
	if (!fin.good())
		throw IOException(filename);
	fin.read((char*)this->data, headerDataSize);
	fin.seekg(0, fin.end);
	size_t length = fin.tellg();
	this->check(length);
}

void WAVHeader::setToZero()
{
	memset(this->data, 0, sizeof(HeaderInfo));
}

void WAVHeader::print() const
{
	std::cout << "ChunkID: " << this->data->chunkId << std::endl;
	std::cout << "ChunkSize: " << this->data->chunkSize << std::endl;
	std::cout << "Format: " << this->data->format << std::endl;
	std::cout << "Subchunk1ID: " << this->data->subchunk1Id << std::endl;
	std::cout << "Subchunk1Size: " << this->data->subchunk1Size << std::endl;
	std::cout << "AudioFormat: " << this->data->audioFormat << std::endl;
	std::cout << "NumChannels: " << this->data->numChannels << std::endl;
	std::cout << "SampleRate: " << this->data->sampleRate << std::endl;
	std::cout << "ByteRate: " << this->data->byteRate << std::endl;
	std::cout << "BlockAlign: " << this->data->blockAlign << std::endl;
	std::cout << "BitsPerSample: " << this->data->bitsPerSample << std::endl;
	std::cout << "Subchunk2ID: " << this->data->subchunk2Id << std::endl;
	std::cout << "Subchunk2Size: " << this->data->subchunk2Size << std::endl;
}

void WAVHeader::fill(int channelsAmount, int sampleRate, int samplesPerChannel) throw (HeaderFormatException)
{
	if (channelsAmount < 1) 
		throw HeaderFormatException("Wrong input");

	this->data->chunkId[0] = 0x52;
	this->data->chunkId[1] = 0x49;
	this->data->chunkId[2] = 0x46;
	this->data->chunkId[3] = 0x46;

	this->data->format[0] = 0x57;
	this->data->format[1] = 0x41;
	this->data->format[2] = 0x56;
	this->data->format[3] = 0x45;

	this->data->subchunk1Id[0] = 0x66;
	this->data->subchunk1Id[1] = 0x6d;
	this->data->subchunk1Id[2] = 0x74;
	this->data->subchunk1Id[3] = 0x20;

	this->data->subchunk2Id[0] = 0x64;
	this->data->subchunk2Id[1] = 0x61;
	this->data->subchunk2Id[2] = 0x74;
	this->data->subchunk2Id[3] = 0x61;

	this->data->audioFormat = 1;
	this->data->subchunk1Size = 16;
	this->data->bitsPerSample = 16;


	int fileSize = 44 + channelsAmount * 2 * samplesPerChannel;

	this->data->sampleRate = sampleRate;
	this->data->numChannels = channelsAmount;

	this->data->chunkSize = fileSize - 8;
	this->data->subchunk2Size = fileSize - 44;

	this->data->byteRate = this->data->sampleRate * this->data->numChannels * this->data->bitsPerSample / 8;
	this->data->blockAlign = this->data->numChannels * this->data->bitsPerSample / 8;
}

void WAVHeader::check(size_t fileSize) const throw (HeaderFormatException)
{
	if (this->data->chunkId[0] != 0x52 ||
		this->data->chunkId[1] != 0x49 ||
		this->data->chunkId[2] != 0x46 ||
		this->data->chunkId[3] != 0x46)
			throw HeaderFormatException("Header RIFF erorr");

	else if (this->data->chunkSize != fileSize - 8) 
		throw HeaderFormatException("Chunk size error");

	else if (this->data->format[0] != 0x57 ||
			this->data->format[1] != 0x41 ||
			this->data->format[2] != 0x56 ||
			this->data->format[3] != 0x45)
				throw HeaderFormatException("Header WAVE erorr");

	else if (this->data->subchunk1Id[0] != 0x66 ||
			this->data->subchunk1Id[1] != 0x6d ||
			this->data->subchunk1Id[2] != 0x74 ||
			this->data->subchunk1Id[3] != 0x20)
				throw HeaderFormatException("Header FMT Error");

	else if (this->data->audioFormat != 1) 
		throw HeaderFormatException("Header is not PCM");

	else if (this->data->subchunk1Size != 16)
		throw HeaderFormatException("Wrong SubChunk1 size");

	else if (this->data->byteRate !=
			this->data->sampleRate * this->data->numChannels * this->data->bitsPerSample / 8) 
				throw HeaderFormatException("Wrong ByteRate");

	else if (this->data->blockAlign != this->data->numChannels * this->data->bitsPerSample / 8) 
		throw HeaderFormatException("Wrong block align");

	else if (this->data->subchunk2Id[0] != 0x64 ||
			this->data->subchunk2Id[1] != 0x61 ||
			this->data->subchunk2Id[2] != 0x74 ||
			this->data->subchunk2Id[3] != 0x61)
				throw HeaderFormatException("Header FMT Error");

	else if (this->data->subchunk2Size != fileSize - 44) 
		throw HeaderFormatException("Wrong SubChunk2 size");

	else if (this->data->bitsPerSample != 16) 
		throw HeaderFormatException("Unsupported Format");
}