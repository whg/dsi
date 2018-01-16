//
// Created by whg on 09/01/18.
//

#pragma once

#include <vector>
#include <memory>
#include <cinder/Rand.h>
#include "cinder/gl/gl.h"

namespace dsi {

using lookup_table_t = std::vector<size_t>;

using OrderRef = std::shared_ptr<class Order>;

class Order {
public:
	Order() = default;
	Order( size_t w, size_t h );

	const lookup_table_t getTable() const { return mTable; }

	ci::gl::TextureRef getTexture( size_t sampleRate );

	size_t getWidth() const { return mWidth; }
	size_t getHeight() const { return mHeight; }

	virtual void fill();

protected:
	size_t mWidth, mHeight;
	lookup_table_t mTable;

};

class ColumnMajorOrder : public Order {
public:
	ColumnMajorOrder( size_t w, size_t h ): Order( w, h ) { fill(); }

	virtual void fill() override;
};

class RandomOrder : virtual public Order {
public:
	RandomOrder( size_t w, size_t h ): Order( w, h ) {}

	virtual void fill() override;

protected:
	ci::Rand mRand;
};

//! Start in the center and spiral out clockwise
class SpiralInOrder : public Order {
public:
	SpiralInOrder( size_t w, size_t h ): Order( w, h ) {}

	virtual void fill() override;
};

//! Start in the center and spiral out clockwise
class SpiralOutOrder : public SpiralInOrder {
public:
	SpiralOutOrder( size_t w, size_t h ): SpiralInOrder( w, h ) {}

	virtual void fill() override;
};

//! Start in the top left and zig-zag to the bottom right
class ZigZagOrder : public Order {
public:
	ZigZagOrder( size_t w, size_t h ) : Order( w, h ) {}

	virtual void fill() override;
};

template <class T>
OrderRef createOrder( size_t w, size_t h ) {
	auto order = std::make_shared<T>( w, h );
	order->fill();
	return order;
}

};
