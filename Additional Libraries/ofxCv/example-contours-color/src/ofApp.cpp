#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

ofColor Orange(200,107,94);
ofColor Blue(98,175,211);

void ofApp::setup() {
    
    
    movie.load("movie.mov");
    movie.play();
    
    contourFinder1.setMinAreaRadius(10);
    contourFinder1.setMaxAreaRadius(150);
    
    contourFinder2.setMinAreaRadius(10);
    contourFinder2.setMaxAreaRadius(150);
    //contourFinder.setInvert(true); // find black instead of white
    
    gui1.setup();
    gui1.add(threshold1.set("Threshold", 128, 0, 255));
    gui1.add(trackHs1.set("Track Hue/Saturation", false));
    gui2.setup();
    gui2.add(threshold2.set("Threshold", 0, 0, 0));
    gui2.add(trackHs2.set("Track Hue/Saturation", false));
}

void ofApp::update() {
    movie.update();
    if(movie.isFrameNew()) {
        contourFinder1.setTargetColor(targetColor1, trackHs1 ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
        contourFinder1.setThreshold(threshold1);
        contourFinder1.findContours(movie);
        contourFinder2.setTargetColor(targetColor2, trackHs2 ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
        contourFinder2.setThreshold(threshold2);
        contourFinder2.findContours(movie);
    }
}

void ofApp::draw() {
    ofSetColor(255);
    movie.draw(0, 0);
    
    ofSetLineWidth(2);
    contourFinder1.draw();
    contourFinder2.draw();
    gui1.draw();
    gui2.draw();
    
    //ofTranslate(200, 75);
    //ofFill();
    //ofSetColor(0);
    //ofDrawRectangle(-3, -3, 64+6, 64+6);
    //ofSetColor(targetColor);
    //ofDrawRectangle(0, 0, 64, 64);
}

void ofApp::mousePressed(int x, int y, int button) {
    targetColor1 = Orange;
    targetColor2 = Blue;
}
