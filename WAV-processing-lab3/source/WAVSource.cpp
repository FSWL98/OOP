#include "stdafx.h"
#include "WAV.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>
#include <math.h>

void WAV::open(const std::string& filename) throw (IOException)
{
	this->filename = filename;
	this->header.read(filename);
	this->extractChannelsData(filename);
}

void WAV::mono()
{
	int channelsAmount = this->getChannelsAmount();

	if (channelsAmount != 2) 
		std::cout << "BAD PARAMS" << std::endl;

	int samplesPerChannel = (int)this->channelsData[0].size();

	for (size_t i = 0; i < channelsAmount; i++) 
	{
		if (this->channelsData[i].size() != (size_t)samplesPerChannel) 
			std::cout << "BAD PARAMS" << std::endl;
	}

	std::vector<short> mono;
	mono.resize(samplesPerChannel);

	for (size_t i = 0; i < samplesPerChannel; i++) 
	{
		mono[i] = (this->channelsData[0][i] + this->channelsData[1][i]) / (short)2;
	}

	this->channelsData.resize(1);

	this->channelsData[0] = mono;
}

void WAV::reverb(double delay, float decay) {

	int channelsAmount = this->getChannelsAmount();
	int sampleRate = this->getSampleRate();

	if (channelsAmount < 1) {
		std::cout << "BAD PARAMS" << std::endl;
	}

	int samplesPerChannel = (int)this->channelsData[0].size();

	// Verify that all channels have the same number of samples.
	for (size_t ch = 0; ch < channelsAmount; ch++) {
		if (this->channelsData[ch].size() != (size_t)samplesPerChannel) {
			std::cout << "BAD PARAMS" << std::endl;
		}
	}

	int samplesDelay = (int)(delay * sampleRate);


	for (size_t ch = 0; ch < channelsAmount; ch++) {
		std::vector<float> tmp;
		tmp.resize(this->channelsData[ch].size());

		// Convert signal from short to float
		for (size_t i = 0; i < samplesPerChannel; i++) {
			tmp[i] = this->channelsData[ch][i];
		}

		// Add a reverb
		for (size_t i = 0; i < samplesPerChannel - samplesDelay; i++) {
			tmp[i + samplesDelay] += decay * tmp[i];
		}

		// Find maximum signal's magnitude
		float maxMagnitude = 0.0f;
		for (size_t i = 0; i < samplesPerChannel - samplesDelay; i++) {
			if (std::abs(tmp[i]) > maxMagnitude) {
				maxMagnitude = std::abs(tmp[i]);
			}
		}

		// Signed short can keep values from -32768 to +32767,
		// After reverb, usually there are values large 32000.
		// So we must scale all values back to [-32768 ... 32768]
		float normalCoeff = 30000.0f / maxMagnitude;

		// Scale back and transform floats to shorts.
		for (size_t i = 0; i < samplesPerChannel; i++) {
			this->channelsData[ch][i] = (short)(normalCoeff * tmp[i]);
		}
	}

}

void WAV::printInfo() const
{
	this->header.print();
}

int WAV::getSampleRate() const
{
	return this->header.data->sampleRate;
}

int WAV::getChannelsAmount() const
{
	return (int)this->channelsData.size();
}

bool WAV::isStereo() const
{
	return this->channelsData.size() == 2;
}

void WAV::save()
{
	this->saveToFile(this->filename);
}

void WAV::saveToFile(const std::string &filename) {

	int channelsAmount = this->getChannelsAmount();

	if (channelsAmount < 1) {
		std::cout << "BAD PARAMS" << std::endl;
	}

	int samplesPerChannel = (int)this->channelsData[0].size();

	// Verify that all channels have the same number of samples.
	for (size_t ch = 0; ch < channelsAmount; ch++) {
		if (this->channelsData[ch].size() != (size_t)samplesPerChannel) {
			std::cout << "BAD PARAMS" << std::endl;
		}
	}

	this->header.fill(channelsAmount, this->getSampleRate(), samplesPerChannel);


	std::vector<short> allChannels;
	allChannels.resize(channelsAmount * samplesPerChannel);

	for (int ch = 0; ch < channelsAmount; ch++) {
		const std::vector<short>& channelData = this->channelsData[ch];
		for (size_t i = 0; i < samplesPerChannel; i++) {
			allChannels[channelsAmount * i + ch] = channelData[i];
		}
	}

	std::ofstream output(filename, std::ofstream::binary);
	output.write((char *)this->header.data, sizeof(this->header.data));
	output.write((char *)allChannels.data(), sizeof(short) * allChannels.size());

}

void WAV::extractChannelsData(const std::string& filename) throw(IOException) {

	std::ifstream input(filename, std::ifstream::binary);

	if (!input.good()) {
		throw IOException(filename);
	}

	input.seekg(44);

	int numChannels = this->header.data->numChannels;
	int samplesPerChannel = (this->header.data->subchunk2Size / sizeof(short)) / numChannels;

	// 1. Reading all PCM data from file to a single vector.
	std::vector<short> allChannels;

	allChannels.resize(numChannels * samplesPerChannel);

	input.read((char*)&allChannels[0], this->header.data->subchunk2Size);

	// 2. Put all channels to its own vector.
	this->channelsData.resize(numChannels);
	for (auto &ch : this->channelsData) {
		ch.resize(samplesPerChannel);
	}

	for (int ch = 0; ch < numChannels; ch++) {
		std::vector<short>& channelData = this->channelsData[ch];
		for (size_t i = 0; i < samplesPerChannel; i++) {
			channelData[i] = allChannels[numChannels * i + ch];
		}
	}

}