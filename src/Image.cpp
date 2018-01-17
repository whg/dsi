//
// Created by whg on 09/01/18.
//

#include "Image.hpp"

#include "cinder/app/App.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/gl.h"

namespace dsi {

using namespace ci;


Image::Image( const ci::fs::path &path ):
		Surface( loadImage( loadFile( path ) ) ) {
}

Image::Image( int32_t w, int32_t h ):
		Surface( w, h, false, SurfaceChannelOrder::RGB ){
}

ImageRef Image::create( const ci::fs::path &path ) {


	ImageRef output = std::make_shared<Image>( path );
	output->mTexture = nullptr;

	auto r = output->getChannelBlue().getData();
	for ( int i = 0; i < 10; i++ ) std::cout << int(r[i]) << " ";
	std::cout << std::endl;

	auto d = output->getData();
	for ( int i = 0; i < 10; i+= 3 ) std::cout << int(r[i]) << " " << int(r[i+1]) << " " << int(r[i+2]) << " ";
	std::cout << std::endl;

	return output;
}

ImageRef Image::create( int32_t w, int32_t h ) {
	ImageRef output = std::make_shared<Image>( w, h );
	output->mTexture = nullptr;
	return output;
}

//const uint8_t* Image::getData() const {
//	return mSurface->getData();
//}

//void Image::setData( const uint8_t *data, size_t n ) {
//	auto N = std::min( static_cast<size_t>( this->size() ), n );
//	std::copy( data, data + N, mSurface->getData() );
//	this->mTexture = nullptr;
//}

int32_t Image::size() const {
	return getWidth() * getHeight();
}

gl::TextureRef Image::getTexture() {
	if ( !mTexture ) {
		mTexture = gl::Texture::create( *this );
		mTexture->setMagFilter( GL_NEAREST );
	}
	return mTexture;
}


};