//
// Created by whg on 09/01/18.
//

#include "transform.hpp"

namespace dsi { namespace transform {

AudioRef create( const ImageRef &image, const OrderRef &order ) {

	const uint8_t *id = image->getData();
	const auto &channelOrder = image->getChannelOrder();
	auto ro = channelOrder.getRedOffset();
	auto go = channelOrder.getGreenOffset();
	auto bo = channelOrder.getBlueOffset();
	auto pinc = image->getPixelInc();

	auto n = image->size();

	auto audio = Audio::create( n );

	float *lad = audio->getLeftChannel();
	float *rad = audio->getRightChannel();
	const auto &table = order->getTable();

	size_t ti;
	for ( size_t i = 0; i < table.size(); i++ ) {
		ti = table[i];
		lad[ti] = id[i * pinc + go] / 128.f - 1.f;
		rad[ti] = id[i * pinc + bo] / 128.f - 1.f;
	}

	return audio;
}

ImageRef create( const AudioRef &audio, const OrderRef &order ) {

	auto image = Image::create( order->getWidth(), order->getHeight() );

	uint8_t *id = image->getData();
	const auto &channelOrder = image->getChannelOrder();
	auto ro = channelOrder.getRedOffset();
	auto go = channelOrder.getGreenOffset();
	auto bo = channelOrder.getBlueOffset();
	auto pinc = image->getPixelInc();

	const float *lad = audio->getLeftChannel();
	const float *rad = audio->getRightChannel();

	const auto &table = order->getTable();
	size_t N = std::min( table.size(), audio->size() );

	size_t ti;
	for ( size_t i = 0; i < N; i++ ) {
		ti = table[i];
//		id[ti * pinc + ro] = static_cast<uint8_t>( lad[i] * 128.f + 128.f );
		id[ti * pinc + go] = static_cast<uint8_t>( lad[i] * 128.f + 128.f );
		id[ti * pinc + bo] = static_cast<uint8_t>( rad[i] * 128.f + 128.f );
//		id[ti * pinc + ro] = 255;
	}

	return image;
}

} }