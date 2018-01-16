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
	output->mTexture = nullptr;
	return output;
}

ImageRef Image::create( size_t w, size_t h ) {
	auto output = std::make_shared<Image>();
	output->mChannel = Channel::create( w, h );
	output->mTexture = nullptr;
	return output;
}

const uint8_t *Image::getData() const {
	return mChannel->getData();
}

void Image::setData( const uint8_t *data, size_t n ) {
	auto N = std::min( static_cast<size_t>( this->size() ), n );
	std::copy( data, data + N, mChannel->getData() );
	this->mTexture = nullptr;
}

int32_t Image::size() const {
	return mChannel->getWidth() * mChannel->getHeight();
}

gl::TextureRef Image::getTexture() {
	if ( !mTexture ) {
		mTexture = gl::Texture::create( *mChannel );
		mTexture->setMagFilter( GL_NEAREST );
	}
	return mTexture;
}


};