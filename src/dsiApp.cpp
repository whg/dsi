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

//	mImage = dsi::Image::create( "/home/whg/workspace/face_gb.jpg" ); //sine2.png" ); //sine_hd10_0.01.png" );
//	auto imageSize = mImage->getSize();
//	mOrder = dsi::createOrder<dsi::ZigZagOrder>( imageSize.x, imageSize.y );
//	mAudio = dsi::transform::create( mImage, mOrder );

//	cout << imageSize << endl;


	ivec2 imageSize( 200, 1800 );
	mOrder = dsi::createOrder<dsi::ColumnMajorOrder>( imageSize.x, imageSize.y );

	mAudio = dsi::Audio::create( "/home/whg/workspace/tones_pan.wav" );
	mImage = dsi::transform::create( mAudio, mOrder );

	auto ctx = audio::Context::master();
	mBufferPlayer = ctx->makeNode( new audio::BufferPlayerNode( mAudio->getBuffer() ) );
//	mBufferPlayer->loadBuffer( sourceFile );

	mGain = ctx->makeNode( new audio::GainNode );
	mGain->setValue( 0.5f );

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

	hideCursor();
}

void dsiApp::quit() {

}

void dsiApp::mouseDown( MouseEvent event ) {}
void dsiApp::keyDown( KeyEvent event ) {
	mBufferPlayer->start( audio::master()->getNumProcessedSeconds() + 3 );
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
		mShader->uniform( "uPlayhead", static_cast<float>( mBufferPlayer->getReadPositionTime() ) );

		gl::drawSolidRect( Rectf( 0, 0, imageTexture->getWidth(), imageTexture->getHeight() ) );
	}

	gl::draw( mFbo->getColorTexture(), Rectf( vec2(), vec2( app::getWindowSize() ) ) );
}

CINDER_APP( dsiApp, RendererGl )
