import themidibus.*;

import processing.sound.*;

//input dev...
AudioIn input;
Amplitude rms;
FFT fft;
// Define how many FFT bands we want
int bands = 128;
// Create a smoothing vector
float[] sum = new float[bands];
// Create a smoothing factor
float smooth_factor = 0.2;
// Declare a scaling factor
int scale=3;
// declare a drawing variable for calculating rect width
float r_width;


// Create a MidiBus object
MidiBus mb;

// Setup sketch
void setup() {
  size(400, 400);
  background(0,0,0);
  // List available MIDI inputs and outputs
  MidiBus.list();
  MidiBus.unavailableDevices();
  // Instantiate the MidiBus
  mb = new MidiBus(this, -1, "VirMIDI [hw:2,0,0]");
  
   //Create an Audio input and grab the 1st channel
  input = new AudioIn(this, 0);
  
  // start the Audio Input
  input.start();
  
  // create a new Amplitude analyzer
  rms = new Amplitude(this);
  
  // Patch the input to an volume analyzer
  rms.input(input);  
  
  // Create and patch the FFT analyzer
  fft = new FFT(this, bands);
    // Calculate the width of the rects depending on how many bands we have
  r_width = width/float(bands);
  fft.input(input);
}

// Draw loop
void draw() {
    background(125,255,125);
  fill(255,0,150);
  println("Playing note");
  // Play a note on our 1st (and only) channel
  int channel = 1;
  int pitch = 60;
  int velocity = 127;
  //mb.sendNoteOn(channel, pitch, velocity); 
  //delay(500);
  //mb.sendNoteOff(channel, pitch, velocity);
  //delay(500);
    fft.analyze();
 noStroke();
  for (int i = 0; i < bands; i++) {
    
    // smooth the FFT data by smoothing factor
    sum[i] += (fft.spectrum[i] - sum[i]) * smooth_factor;
    
    // draw the rects with a scale factor
    rect( i*r_width, height, r_width, -sum[i]*height*scale );
  }
}