//
// Created by whg on 09/01/18.
//

#include "transform.hpp"

namespace dsi { namespace transform {

AudioRef create( const ImageRef &image ) {

	auto audio = std::make_shared<Audio>();

	const uint8_t *id = image->getData();
	size_t n = image->size();

	float *ad = new float[n];

	for ( size_t i = 0; i < n; i++ ) {
		ad[i] = id[i] / 128.f - 1.f;
		std::cout << ad[i] << " ";
	}
	std::cout << std::endl;

	audio->setData( ad, n );

	delete[] ad;

	return audio;
}

ImageRef create( const AudioRef &audio ) {

	auto image = std::make_shared<Image>();

	const float *ad = audio->getData();
	size_t n = audio->size();

	uint8_t *id = new uint8_t[n];

	for ( size_t i = 0; i < n; i++ ) {
		id[i] = static_cast<uint8_t>( ad[i] * 128.f + 128.f );
	}

	image->setData( id, n );

	delete[] id;

	return image;
}

} }