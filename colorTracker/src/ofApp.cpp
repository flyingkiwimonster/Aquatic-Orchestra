#include "ofApp.h"

using namespace ofxCv;
using namespace cv;



void ofApp::setup() {
    //Set colour values in RGB notation for the tracked fish
    ofColor yellow(239,201,0);
    ofColor red(241,0,0);

    targetColor1 = red;
    targetColor2 = yellow;
    //threshold = 108;
    
    //Load and play the video
    cam.load("Aquarium.mov");
    cam.play();
    
    //Set minimum and maximum threshold for the radius of detected object
    contourFinder1.setMinAreaRadius(10);
    contourFinder1.setMaxAreaRadius(150);
    contourFinder2.setMinAreaRadius(10);
    contourFinder2.setMaxAreaRadius(150);
    
    //Add GUI elements
    gui.setup();
    gui.add(threshold.set("Threshold", 128, 0, 255));     
    gui.add(trackHs.set("Track Hue/Saturation", false));
    
    //Load samples
    lead.load("lead.wav");
    backing.load("backing.wav");
    
    //Activates looping of samples
    lead.setLoop(true);
    backing.setLoop(true);
    
    //Set volume of the backing track
    backing.setVolume(0.60f);
}

void ofApp::update() {
    
    cam.update();
    if(cam.isFrameNew()) {
        //For every new frame in the video- sets target colour to be tracked, sets a threshold for the colour detection,
        //and finally finds contours of objects with the targeted colour
        contourFinder1.setTargetColor(targetColor1, trackHs ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
        contourFinder2.setTargetColor(targetColor2, trackHs ? TRACK_COLOR_HS : TRACK_COLOR_RGB);
        contourFinder1.setThreshold(threshold);
        contourFinder2.setThreshold(threshold);
        contourFinder1.findContours(cam);
        contourFinder2.findContours(cam);
        
        //Firstly it checks if red fish is present, secondly it checks if the backing track is playing already,
        //finally, if it isn't playing already then it plays the backing track
        if (contourFinder1.size() > 0) {
            if (!backing.isPlaying()) {
              backing.play();
            }
        } else {
            backing.stop();
        }
        //Firstly it checks if yellow fish is present, secondly it checks if the lead track is playing already,
        //finally, if it isn't playing already then it plays the lead track
        if(contourFinder2.size() > 0) {
            if (!lead.isPlaying()) {
                lead.play();
            }
        } else {
            lead.stop();
        }
    }
    
    //Everytime a yellow fish is detected, it's position is observed. The playback of the music is affected by the position of the detected fish.
    for (int i = 0; i < contourFinder2.size(); i++) {
        cv::Point2f pos = contourFinder2.getCenter(i);          //Gets position of yellow fish, stores it in a (x,y) vector
        float newPan = pos.x;       //Stores the x coordinate in newPan
        float newVol = pos.y;       //Stores the y coordinate in NewVol
        float mappedPan = ofMap(newPan, 0, ofGetScreenWidth(), -1, 1);      //Calculates normalised value for newPan within the limits -1 and 1
        float mappedVol = ofMap(newVol, ofGetScreenHeight(), 0, 0.30, 1);  //Calculates normalised value of newVol within the limits 0.30 and 1
        lead.setPan(mappedPan);     //Pans the lead track according to where the fish is on the x-axis of the video
        lead.setVolume(mappedVol);  //Controls the volume of the lead track according to where the fish is on the y-axis of the video
    }
}

void ofApp::draw() {
    ofSetColor(255);
    
    //Draws the video feed at the top left corner of the window
    cam.draw(0, 0);
    ofSetLineWidth(2);
    
    //Draws an outline of the contours it detects
    contourFinder1.draw();
    contourFinder2.draw();
    
    gui.draw();
    
    //Draws a square box filled with the targetColour1 which is the colour of the red fish
    ofTranslate(8, 75);
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(-3, -3, 64+6, 64+6);
    ofSetColor(targetColor1);
    ofDrawRectangle(0, 0, 64, 64);
    
    //Draws a square box filled with the targetColour2 which is the colour of the yellow fish
    ofTranslate(0, 75);
    ofFill();
    ofSetColor(0);
    ofDrawRectangle(-3, -3, 64+6, 64+6);
    ofSetColor(targetColor2);
    ofDrawRectangle(0, 0, 64, 64);
    
    
}
