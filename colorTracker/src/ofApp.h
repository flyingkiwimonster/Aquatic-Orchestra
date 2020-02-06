#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    ofVideoPlayer cam;
    ofxCv::ContourFinder contourFinder1;
    ofxCv::ContourFinder contourFinder2;
    ofColor targetColor1;
    ofColor targetColor2;
    //ofColor green;
    
    ofxPanel gui;
    ofParameter<float> threshold;
    ofParameter<bool> trackHs;
    
    ofSoundPlayer lead;
    ofSoundPlayer backing;
};
