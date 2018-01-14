//
// Created by whg on 09/01/18.
//

#include "transform.hpp"

namespace dsi { namespace transform {

AudioRef create( const ImageRef &image, const OrderRef &order ) {

	auto audio = std::make_shared<Audio>();

	const uint8_t *id = image->getData();
	size_t n = image->size();

	float *ad = new float[n];
	const auto &table = order->getTable();
	for ( size_t i = 0; i < table.size(); i++ ) {
		ad[i] = id[table[i]] / 128.f - 1.f;
	}

	audio->setData( ad, n );

	delete[] ad;

	return audio;
}

ImageRef create( const AudioRef &audio, const OrderRef &order ) {

	auto image = Image::create( order->getWidth(), order->getHeight() );

	const float *ad = audio->getData();
	size_t n = audio->size();

	uint8_t *id = new uint8_t[n];
	const auto &table = order->getTable();
	for ( size_t i = 0; i < table.size(); i++ ) {
		id[i] = static_cast<uint8_t>( ad[table[i]] * 128.f + 128.f );
	}

	image->setData( id, n );

	delete[] id;

	return image;
}

} }