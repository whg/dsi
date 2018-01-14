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

	const ci::audio::BufferRef getBuffer() const { return mBuffer; }

	const float* getData() const;
	void setData( const float *data, size_t n );

	size_t size() const;

protected:
	ci::audio::BufferRef mBuffer;
};


}

