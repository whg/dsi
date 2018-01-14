//
// Created by whg on 09/01/18.
//

#pragma once

#include <vector>
#include <memory>

namespace dsi {

using lookup_table_t = std::vector<size_t>;

using OrderRef = std::shared_ptr<class Order>;

class Order {
public:
	Order() = default;

	static OrderRef create( size_t w, size_t h );

	const lookup_table_t getTable() const { return mTable; }

protected:
	lookup_table_t mTable;

	virtual void fill();
};

//class NormalOrder : public Order {
//public:
//	const lookup_table_t getTable() const override;
//};

};
