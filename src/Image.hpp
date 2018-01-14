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

class Image {
public:
	static ImageRef create( const ci::fs::path &path );

	void draw();

	const uint8_t* getData() const;
	void setData( const uint8_t *data, size_t n );

	int32_t size() const;

protected:
	ci::ChannelRef mChannel;
	ci::gl::TextureRef mTexture;
};

}

