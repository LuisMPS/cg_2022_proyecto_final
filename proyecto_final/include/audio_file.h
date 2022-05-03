#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <type_traits>

bool is_big_endian(void)
{
	union {
		uint32_t i;
		char c[4];
	} bint = { 0x01020304 };

	return bint.c[0] == 1;
}

std::int32_t convert_to_int(char* buffer, std::size_t len)
{
	std::int32_t a = 0;
	if (!is_big_endian())
		std::memcpy(&a, buffer, len);
	else
		for (std::size_t i = 0; i < len; ++i)
			reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
	return a;
}

class AudioFile {

	public:
		std::uint8_t channels;
		std::int32_t sampleRate;
		std::uint8_t bitsPerSample;
		std::uint32_t size;
		AudioFile() {

		}
		~AudioFile() {

		}
		char* load(const std::string& filename) {
			std::ifstream in(filename, std::ios::binary);
			if (!in.is_open()) {
				std::cerr << "ERROR: Could not open \"" << filename << "\"" << std::endl;
				return NULL;
			}
			if (!load_wav_file_header(in)) {
				std::cerr << "ERROR: Could not load wav header of \"" << filename << "\"" << std::endl;
				return NULL;
			}
			char* data = new char[size];
			in.read(data, size);
			return data;
		}
	private:
		bool load_wav_file_header(std::ifstream& file) {
			char buffer[4];
			if (!file.is_open())
				return false;

			// the RIFF
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read RIFF" << std::endl;
				return false;
			}
			if (std::strncmp(buffer, "RIFF", 4) != 0)
			{
				std::cerr << "ERROR: file is not a valid WAVE file (header doesn't begin with RIFF)" << std::endl;
				return false;
			}

			// the size of the file
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read size of file" << std::endl;
				return false;
			}

			// the WAVE
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read WAVE" << std::endl;
				return false;
			}
			if (std::strncmp(buffer, "WAVE", 4) != 0)
			{
				std::cerr << "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)" << std::endl;
				return false;
			}

			// "fmt/0"
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read fmt/0" << std::endl;
				return false;
			}

			// this is always 16, the size of the fmt data chunk
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read the 16" << std::endl;
				return false;
			}

			// PCM should be 1?
			if (!file.read(buffer, 2))
			{
				std::cerr << "ERROR: could not read PCM" << std::endl;
				return false;
			}

			// the number of channels
			if (!file.read(buffer, 2))
			{
				std::cerr << "ERROR: could not read number of channels" << std::endl;
				return false;
			}
			channels = convert_to_int(buffer, 2);

			// sample rate
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read sample rate" << std::endl;
				return false;
			}
			sampleRate = convert_to_int(buffer, 4);

			// (sampleRate * bitsPerSample * channels) / 8
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8" << std::endl;
				return false;
			}

			// ?? dafaq
			if (!file.read(buffer, 2))
			{
				std::cerr << "ERROR: could not read dafaq" << std::endl;
				return false;
			}

			// bitsPerSample
			if (!file.read(buffer, 2))
			{
				std::cerr << "ERROR: could not read bits per sample" << std::endl;
				return false;
			}
			bitsPerSample = convert_to_int(buffer, 2);

			// data chunk header "data"
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read data chunk header" << std::endl;
				return false;
			}
			if (std::strncmp(buffer, "data", 4) != 0)
			{
				std::cerr << "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)" << std::endl;
				return false;
			}

			// size of data
			if (!file.read(buffer, 4))
			{
				std::cerr << "ERROR: could not read data size" << std::endl;
				return false;
			}
			size = convert_to_int(buffer, 4);

			/* cannot be at the end of file */
			if (file.eof())
			{
				std::cerr << "ERROR: reached EOF on the file" << std::endl;
				return false;
			}
			if (file.fail())
			{
				std::cerr << "ERROR: fail state set on the file" << std::endl;
				return false;
			}

			return true;
		}
};

