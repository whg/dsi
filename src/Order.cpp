//
// Created by whg on 09/01/18.
//

#include "Order.hpp"
#include "cinder/Channel.h"

namespace dsi {


Order::Order( size_t w, size_t h ):
mWidth( w ), mHeight( h ),
mTable( w * h )
{
	fill();
}

void Order::fill() {
	for ( size_t i = 0; i < mTable.size(); i++ ) {
		mTable[i] = i;
	}
	std::cout << "normal" << std::endl;
}

ci::gl::TextureRef Order::getTexture( size_t sampleRate ) {
	ci::Channel32f channel( mWidth, mHeight );
	auto *data = channel.getData();
	auto sampleRatef = static_cast<float>( sampleRate );
	for ( size_t i = 0; i < mTable.size(); i++ ) {
		data[mTable[i]] = i / sampleRatef;
	}
	return ci::gl::Texture::create( channel, ci::gl::Texture::Format().dataType( GL_FLOAT ).internalFormat( GL_R32F ) );
}


void ColumnMajorOrder::fill() {
	size_t i = 0, index = 0;
	for ( size_t x = 0; x < mWidth; x++ ) {
		for ( size_t y = 0; y < mHeight; y++, i++ ) {
			index = y * mWidth + x;
			mTable[i] = index;
		}
	}
	std::cout << "column" << std::endl;
}

void RandomOrder::fill() {

	Order::fill();

	size_t a, b, temp;
	for ( size_t i = 0; i < mTable.size(); i++ ) {
		a = static_cast<size_t>( mRand.nextInt( mTable.size() ) );
		b = static_cast<size_t>( mRand.nextInt( mTable.size() ) );
		temp = mTable[a];
		mTable[a] = mTable[b];
		mTable[b] = temp;
	}

	std::cout << "random" << std::endl;
}

void SpiralInOrder::fill() {
	int x = 0, y = 0, i = 0;
	int w = static_cast<int>( mWidth ), h = static_cast<int>( mHeight );

	for ( x = 0; x < w; x++ ) {
		mTable[i++] = x + y * mWidth;
	}
	x--;
	for ( y = 1; y < h; y++ ) {
		mTable[i++] = x + y * mWidth;
	}
	y--;
	x--;
	for ( ; x >= 0; x-- ) {
		mTable[i++] = x + y * mWidth;
	}
	x++;
	y--;
	for ( ; y >= 1; y--) {
		mTable[i++] = x + y * mWidth;
	}
	y++;
	x++;

	w--;
	h-= 2;

	while ( w > 0 && h > 0 ) {
		for ( size_t n = 1; n < w; n++, x++ ) {
			mTable[i++] = x + y * mWidth;
		}
		x--;
		y++;
		--w;
		for ( size_t n = 1; n < h; n++, y++ ) {
			mTable[i++] = x + y * mWidth;
		}
		y--;
		x--;
		--h;
		for ( size_t n = 1; n < w; n++, x-- ) {
			mTable[i++] = x + y * mWidth;
		}
		x++;
		y--;
		--w;
		for ( size_t n = 1; n < h; n++, y--) {
			mTable[i++] = x + y * mWidth;
		}
		y++;
		x++;
		--h;
	}


}

void SpiralOutOrder::fill() {
	SpiralInOrder::fill();
	std::reverse( std::begin( mTable ), std::end( mTable ) );
}

void ZigZagOrder::fill() {

	size_t i = 0;
	int x = 1, y = 0;

	mTable[i++] = 0;

	while ( i < mTable.size() ) {
		do {
			mTable[i++] = x + y * mWidth;
			--x;
			++y;
		} while ( x >= 0 && y < mHeight && i < mTable.size() );


		if ( y >= mHeight ) {
			y = static_cast<int>( mHeight - 1 );
			x+= 2;
		} else if ( x < 0 ) {
			x = 0;
		}

		do {
			mTable[i++] = x + y * mWidth;
			++x;
			--y;
		} while ( x < mWidth && y >= 0 && i < mTable.size() );

		if ( y < 0 ) {
			y = 0;
		} else if ( x >= mWidth ) {
			x = static_cast<int>( mWidth - 1 );
			y+= 2;
		}

	}
}


}