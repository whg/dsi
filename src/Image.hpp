//
// Created by whg on 09/01/18.
//

#pragma once

#include <memory>

#include "cinder/Cinder.h"
#include "cinder/Filesystem.h"
#include "cinder/Surface.h"
#include "cinder/Channel.h"
#include "cinder/gl/Texture.h"

#include "Audio.hpp"

namespace dsi {

using ImageRef = std::shared_ptr<class Image>;

class Image : public ci::Surface {
public:
	Image() = default;
	Image( const ci::fs::path &path );
	Image( int32_t w, int32_t h );

	static ImageRef create( const ci::fs::path &path );
	static ImageRef create( int32_t w, int32_t h );

	ci::gl::TextureRef getTexture();

//	int32_t getWidth() const { return mSurface->getWidth(); }
//	int32_t getHeight() const { return mSurface->getHeight(); }

//	ci::ivec2 getSize() const { return mSurface->getSize(); }

//	const uint8_t* getData() const;
//	void setData( const uint8_t *data, size_t n );

	int32_t size() const;

protected:
	ci::gl::TextureRef mTexture;
};

}

