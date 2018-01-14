//
// Created by whg on 09/01/18.
//

#include "Image.hpp"

#include "cinder/app/App.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"

namespace dsi {

using namespace ci;

ImageRef Image::create( const ci::fs::path &path ) {

	auto output = std::make_shared<Image>();
	output->mChannel = Channel::create( loadImage( loadFile( path ) ) );

	return output;
}


const uint8_t *Image::getData() const {
	return mChannel->getData();
}

void Image::setData( const uint8_t *data, size_t n ) {
	auto N = std::min( static_cast<size_t>( this->size() ), n );
	std::copy( data, data + N, mChannel->getData() );
}

int32_t Image::size() const {
	return mChannel->getWidth() * mChannel->getHeight();
}

void Image::draw() {
	if ( !mTexture ) {
		mTexture = gl::Texture::create( *mChannel );
	}

	gl::draw( mTexture );
}


};