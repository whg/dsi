//
// Created by whg on 09/01/18.
//

#pragma once

#include <vector>
#include <memory>
#include <cinder/Rand.h>

class ci::Rand;

namespace dsi {

using lookup_table_t = std::vector<size_t>;

using OrderRef = std::shared_ptr<class Order>;

class Order {
public:
	Order() = default;
	Order( size_t w, size_t h );

	const lookup_table_t getTable() const { return mTable; }

protected:
	size_t mWidth, mHeight;
	lookup_table_t mTable;

	virtual void fill();
};

class ColumnMajorOrder : public Order {
public:
	ColumnMajorOrder( size_t w, size_t h ): Order( w, h ) { this->fill(); }
protected:
	void fill();
};

class RandomOrder : public Order {
public:
	RandomOrder( size_t w, size_t h ): Order( w, h ) { this->fill(); }
protected:
	void fill();
	ci::Rand mRand;
};

};
