#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/audio/audio.h"

#include "Image.hpp"
#include "Audio.hpp"
#include "Order.hpp"
#include "transform.hpp"

using namespace std;
using namespace ci;
using namespace ci::app;

class dsiApp : public App {
  public:
    void setup() override;
	void quit() override;
    void draw() override;

    void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;

	audio::BufferPlayerNodeRef mBufferPlayer;
	audio::GainNodeRef mGain;
	audio::VoiceRef mVoice;
	float mPhase;

	dsi::ImageRef mImage;
	dsi::AudioRef mAudio;


};

void dsiApp::setup() {
    getWindow()->setTitle( "CinderApp" );
	ivec2 windowSize( 1920, 1080 );
	setWindowSize( windowSize );

	auto imageSize = windowSize / 10;
	auto order = make_shared<dsi::RandomOrder>( imageSize.x, imageSize.y );

//	dsi::ImageRef image = dsi::Image::create( "/home/whg/workspace/tiling-inter/intersection/assets/test-comp-3.jpg" );
//	mImage = dsi::Image::create( "/home/whg/workspace/sine_hd10_0.01.png" );
//	mAudio = dsi::transform::create( mImage, order );

	mAudio = dsi::Audio::create( "/home/whg/workspace/sine50hz.wav" );
//	mImage = dsi::transform:::create( mAudio, order );
	mImage = dsi::transform::create( mAudio, order );

	auto ctx = audio::Context::master();
	mBufferPlayer = ctx->makeNode( new audio::BufferPlayerNode( mAudio->getBuffer() ) );
//	mBufferPlayer->loadBuffer( sourceFile );

	mGain = ctx->makeNode( new audio::GainNode );
	mGain->setValue( 0.5f );

//	mVoice = audio::Voice::create( [this] ( audio::Buffer *buffer, size_t sampleRate ) {
//	   float *channel0 = buffer->getChannel( 0 );
//
//	   // generate a 440 hertz sine wave
//	   float phaseIncr = ( 440.0f / (float)sampleRate ) * 2 * (float)M_PI;
//	   for( size_t i = 0; i < buffer->getNumFrames(); i++ )    {
//		   mPhase = fmodf( mPhase + phaseIncr, 2 * M_PI );
//		   channel0[i] = std::sin( mPhase );
//	   }
//	} );
//	mVoice->start();
	mBufferPlayer >> mGain >> ctx->getOutput();



	mBufferPlayer->start();

	ctx->enable();
}

void dsiApp::quit() {

}

void dsiApp::mouseDown( MouseEvent event ) {}
void dsiApp::keyDown( KeyEvent event ) {
	mBufferPlayer->start();
}

void dsiApp::draw() {

	gl::clear( Color( 0.f, 0.f, 0.f ) );

	mImage->draw();
}

CINDER_APP( dsiApp, RendererGl )
