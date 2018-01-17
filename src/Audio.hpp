//
// Created by whg on 09/01/18.
//

#pragma once

#include <memory>

#include "cinder/Filesystem.h"
#include "cinder/audio/Buffer.h"

namespace dsi {

using AudioRef = std::shared_ptr<class Audio>;

class Audio {
public:

	static AudioRef create( const ci::fs::path &path );
	static AudioRef create( size_t numFrames );

	const ci::audio::BufferRef getBuffer() const { return mBuffer; }

	const float* getData() const;
	void setData( const float *data, size_t n );

	float* getLeftChannel() const { return mBuffer->getChannel( 0 ); }
	float* getRightChannel() const { return mBuffer->getChannel( 1 ); }

	size_t size() const;
	size_t getNumChannels() const;

protected:
	ci::audio::BufferRef mBuffer;
};


}

