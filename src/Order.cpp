//
// Created by whg on 09/01/18.
//

#include "Order.hpp"

namespace dsi {


OrderRef Order::create( size_t w, size_t h ) {
	auto output = std::make_shared<Order>();
	output->mTable.resize( w * h );
	output->fill();
	return output;
}

void Order::fill() {
	for ( size_t i = 0; i < mTable.size(); i++ ) {
		mTable[i] = i;
	}
}


}