//
// Created by whg on 09/01/18.
//

#pragma once

#include <vector>

#include "Image.hpp"
#include "Audio.hpp"

namespace dsi { namespace transform {

AudioRef create( const ImageRef &image );
ImageRef create( const AudioRef &audio );

} }

