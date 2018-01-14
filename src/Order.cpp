//
// Created by whg on 09/01/18.
//

#include "Order.hpp"

#include "cinder/Rand.h"

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


}