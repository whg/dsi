#include "Image.hpp"
#include "Audio.hpp"
#include "Order.hpp"
#include "transform.hpp"


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/audio/audio.h"


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
	dsi::OrderRef mOrder;
	gl::TextureRef mOrderTexture;

	gl::FboRef mFbo;
	gl::GlslProgRef mShader;

	double mLastStartTime;
};

void dsiApp::setup() {
//    getWindow()->setTitle( "CinderApp" );
	ivec2 windowSize( 1920, 1080 );
	setWindowSize( windowSize );

//	auto order = dsi::createOrder<dsi::SpiralInOrder>( 8, 6 );
//
//	std::terminate();

//	auto imageSize = windowSize / 7;
//	mOrder = make_shared<dsi::SpiralInOrder>( imageSize.x, imageSize.y );
//	mOrder = dsi::createOrder<dsi::ZigZagOrder>( imageSize.x, imageSize.y );
//	mOrder = dsi::Order::create<dsi::RandomOrder>( imageSize.x, imageSize.y );
//
//	dsi::ImageRef image = dsi::Image::create( "/home/whg/workspace/tiling-inter/intersection/assets/test-comp-3.jpg" );
	mImage = dsi::Image::create( "/home/whg/workspace/sine_hd10_0.01.png" );
	auto imageSize = mImage->getSize();
	mOrder = dsi::createOrder<dsi::SpiralOutOrder>( imageSize.x, imageSize.y );
	mAudio = dsi::transform::create( mImage, mOrder );



//	mAudio = dsi::Audio::create( "/home/whg/workspace/sine50hz.wav" );
//	mImage = dsi::transform::create( mAudio, mOrder );

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
//	   for( size_t i = 0; i < 	void fill();
//buffer->getNumFrames(); i++ )    {
//		   mPhase = fmodf( mPhase + phaseIncr, 2 * M_PI );
//		   channel0[i] = std::sin( mPhase );
//	   }
//	} );
//	mVoice->start();
	mBufferPlayer >> mGain >> ctx->getOutput();



	mBufferPlayer->start();
	mLastStartTime = app::getElapsedSeconds();

	mShader = gl::GlslProg::create(gl::GlslProg::Format()
										   .vertex(app::loadAsset("shaders/time.vert.glsl"))
										   .fragment(app::loadAsset("shaders/time.frag.glsl")));

	mFbo = gl::Fbo::create( imageSize.x, imageSize.y, true );
	mFbo->getColorTexture()->setMagFilter( GL_NEAREST );


	mOrderTexture = mOrder->getTexture( ctx->getSampleRate() );
	ctx->enable();
}

void dsiApp::quit() {

}

void dsiApp::mouseDown( MouseEvent event ) {}
void dsiApp::keyDown( KeyEvent event ) {
	mBufferPlayer->start();
	mLastStartTime = app::getElapsedSeconds();

}

void dsiApp::draw() {

	gl::clear( Color( 1.f, 0.f, 0.f ) );

	{
		gl::ScopedFramebuffer fbo( mFbo );
		gl::clear();

		auto imageTexture = mImage->getTexture();
		gl::ScopedViewport vp( imageTexture->getSize() );
		gl::ScopedMatrices sm;
		gl::setMatricesWindow( mFbo->getSize() );

		gl::ScopedGlslProg shader( mShader );
		gl::ScopedTextureBind tex0( mImage->getTexture(), 0 );
		gl::ScopedTextureBind orderTex( mOrderTexture, 1 );

		mShader->uniform( "uOrderTex", 1 );
		mShader->uniform( "uPlayhead", static_cast<float>( getElapsedSeconds() - mLastStartTime ) );

		gl::drawSolidRect( Rectf( 0, 0, imageTexture->getWidth(), imageTexture->getHeight() ) );

//		gl::draw( imageTexture );
	}

//	cout << mImage->getTexture()->getInternalFormat() << endl;
//	gl::draw( mImage->getTexture(), Rectf( vec2(), vec2( app::getWindowSize() ) ) );

//	gl::drawSolidRect( Rectf( vec2(), vec2( )));

	gl::draw( mFbo->getColorTexture(), Rectf( vec2(), vec2( app::getWindowSize() ) ) );
}

CINDER_APP( dsiApp, RendererGl )
