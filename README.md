Project 440
==================
This fork is an adaptation of the visualisations for use on osx for live performances.



Install Notes
-------------------------------------------------

This is the raw OpenFrameworks app for quicker and more reliable source control.
It has some dependencies.

- Download the latest openframeworks (0072)
- Place Project-440-Master into apps/myapps
- Download and drop in ofxMidi and ofxKinectNui
- Changes need to be made to ofxKinectNui.h, change the access of the skeletonPoints array to be Public.
- It relies also on ofxXMLSettings, ofxOpenCV, ofxSVG, and ofxOsc, but those should come with the of download.


