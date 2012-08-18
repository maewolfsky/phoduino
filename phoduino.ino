/*
 Intervalometer, possible future rotation/panning with stepper motor?
 
 Borrowing heavily from http://openmoco.org/node/88
 
 */

// Pin setup
// Optocoupler
const int shutter = 13;  
const int startButton = 12;

// Other variables
int interval; //interval between each frame (in ms)
const int exposure = 1000; //exposure of each frame

int frames;    // total number of frames
const bool dumbmode = true; //dumb intervalometer
bool START = false;
// Below here are values for advanced method where phoduino controls exposure

// last time our camera fired
unsigned long last_tm = 0;

// counter for how long we've been exposing
unsigned long exp_tm  = 0;

// whether or not we're currently exposing
bool exposing = false;



void setup()  { 
  pinMode(shutter, OUTPUT);
  pinMode(startButton, INPUT);
  digitalWrite(startButton, HIGH); //set pullup resistor for startButton
  interval = 2000; // default value: 2 seconds
  frames = 5;      // default value: 5 frames     
  Serial.begin(9600); // for debugging output
} 

// Send an open/close to the shutter. Used in basic intervalometer mode
void triggerShutter() {
  //if the shutter length isn't specified, just open and close the shutter
  triggerShutter(200);
}

// Open the shutter for the specified length in ms
void triggerShutter(int ms) {
  digitalWrite(shutter, HIGH);
  Serial.println("Shutter open");
  delay(ms);
  digitalWrite(shutter, LOW);
  Serial.println("Shutter closed");
}

// Perhaps we want to adjust the interval as we go along to make the 
//  timelapse speed up (longer interval) or slow down (shorter interval)
void takePictures( int num_frames, int interval ) {
  for (int i = 0; i < num_frames; i++) {
    triggerShutter();
    delay(interval);
  }
    Serial.print("Finished taking: ");
    Serial.print(num_frames);
    Serial.println(" frames");
}

void checkforStart() {
  // when start pin goes high, set variable START
  // then return
  while(!START) {
    int value = digitalRead(startButton);

    if (value == LOW) {
      START = true;
      return;
    }
  }
}

// the loop routine runs over and over again forever:
void loop()  { 
  
  if(START) {
  

    if(dumbmode) {
      takePictures(frames,interval);
      START = false;

    }
  




    //Advanced stuff here for when phoduino is controlling shutter length
    // and to allow other work to be done
    // do some setup code here
  //   if ( exposing == false && millis() - last_tm > interval ) {
  //     //reset exposure timer
  //     exp_tm = millis();
    
  //     //set flag to indicate that we're currently exposing
  //     exposing = true;
  //     Serial.println(" Opening shuter");
  //     digitalWrite(shutter, HIGH);
  //   }
  //   else if (exposing == true && millis() - exp_tm > exposure) {
  //     // if we're currently exposing, and our exposure
  //     // time has elapsed...
     
      // disable optocoupler
  //     Serial.println(" Closing shutter");
  //     digitalWrite(shutter, LOW);

      // we set this now to ensure that our
      // interval time is measured from the
      // time an image is completed until the
      // time the next one is triggered
      //
      // if you want the interval time to be
      // measured between the time the image
      // is triggered and the next image is
      // triggered, move this to before
      // bringing the camera pin high
     
  //     last_tm = millis();
   
      // reset exposing flag
  //     exposing = false;
  //   }
  } 
  else { //the start switch/button hasn't been pressed
    checkforStart();
  }
}
