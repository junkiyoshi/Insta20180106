#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetBackgroundAuto(false);
	ofSetWindowTitle("Insta");

	ofSetLineWidth(5);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->cap.open(1);

	this->cap_image.allocate(this->cap.get(CV_CAP_PROP_FRAME_WIDTH), this->cap.get(CV_CAP_PROP_FRAME_HEIGHT), OF_IMAGE_COLOR);
	this->cap_frame = cv::Mat(this->cap_image.getHeight(), this->cap_image.getWidth(), CV_MAKETYPE(CV_8UC3, this->cap_image.getPixels().getNumChannels()), this->cap_image.getPixels().getData(), 0);

	this->fbo.allocate(this->cap.get(CV_CAP_PROP_FRAME_WIDTH), this->cap.get(CV_CAP_PROP_FRAME_HEIGHT));
}

//--------------------------------------------------------------
void ofApp::update() {

	this->cap >> this->cap_frame;
	cv::cvtColor(this->cap_frame, this->cap_frame, cv::COLOR_BGR2RGB);
	cv::flip(this->cap_frame, this->cap_frame, 1);

	this->fbo.begin();
	ofClear(0, 0);

	ofDrawRectangle(ofGetMouseX() - (ofGetWidth() - this->cap_image.getWidth()) / 2, ofGetMouseY() - (ofGetHeight() - this->cap_image.getHeight()) / 2, 300, 300);
	
	this->fbo.end();

	this->cap_image.getTextureReference().setAlphaMask(this->fbo.getTexture());
	this->cap_image.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cap_image.draw(ofGetWidth() / 2, ofGetHeight() / 2 );
}

//--------------------------------------------------------------
int main() {
	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}