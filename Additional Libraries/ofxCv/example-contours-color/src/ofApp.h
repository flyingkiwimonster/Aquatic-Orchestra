#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    
    ofVideoPlayer movie;
    ofxCv::ContourFinder contourFinder1;
    ofColor targetColor1;

    ofxCv::ContourFinder contourFinder2;
    ofColor targetColor2;
    
    ofxPanel gui1;
    ofxPanel gui2;
    ofParameter<float> threshold1;
    ofParameter<float> threshold2;
    ofParameter<bool> trackHs1;
    ofParameter<bool> trackHs2;
};
