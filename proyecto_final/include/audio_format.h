#pragma once

#include <AL/al.h>
#include <iostream>

ALenum get_audio_format(std::uint8_t channels, std::uint8_t bitsPerSample) {
	if (channels == 1 && bitsPerSample == 8) {
		std::cout << "mono8" << std::endl;
		return AL_FORMAT_MONO8;
	}
	else if (channels == 1 && bitsPerSample == 16) {
		std::cout << "mono16" << std::endl;
		return AL_FORMAT_MONO16;
	}
	else if (channels == 2 && bitsPerSample == 8) {
		std::cout << "stereo8" << std::endl;
		return AL_FORMAT_STEREO8;
	}
	else if (channels == 2 && bitsPerSample == 16) {
		std::cout << "stereo16" << std::endl;
		return AL_FORMAT_STEREO16;
	}
	else {
		std::cerr
			<< "ERROR: unrecognised wave format: "
			<< channels << " channels, "
			<< bitsPerSample << " bps" << std::endl;
		return NULL;
	}
}