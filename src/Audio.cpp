//
// Created by whg on 09/01/18.
//

#include "Audio.hpp"

#include "cinder/app/App.h"
#include "cinder/audio/Source.h"

namespace dsi {

using namespace ci;

AudioRef Audio::create( const ci::fs::path &path ) {

	auto output = std::make_shared<Audio>();

	auto sourceFile = audio::load( loadFile( path ) );
	output->mBuffer = sourceFile->loadBuffer();

	return output;
}

const float* Audio::getData() const {
	return mBuffer->getData();
}

void Audio::setData( const float *data, size_t n ) {

	if ( !mBuffer || this->size() < n ) {
		std::cout << "making buffer";
		mBuffer = std::make_shared<audio::BufferT<float>>( n, 1 );
	}

	auto N = std::min( n, this->size() );
	std::copy( data, data + N, mBuffer->getData() );
}

size_t Audio::size() const {
	return mBuffer->getNumChannels() * mBuffer->getNumFrames();
}


}