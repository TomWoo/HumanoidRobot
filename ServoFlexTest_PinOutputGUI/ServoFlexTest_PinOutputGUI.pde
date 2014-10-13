
import processing.serial.*;
import g4p_controls.*;

Serial myPort;
int kPin0 = 14;
int kNumPins = 5;
int[] pinVals = new int[kNumPins];
boolean get = false;

GLabel[] getLabels = new GLabel[kNumPins];
GTextField[] getTextFields = new GTextField[kNumPins];
GButton getButton;

// set
int kNum = 12;
boolean set = false;
GLabel[] setLabels = new GLabel[kNum];
GTextField[] setTextFields = new GTextField[kNum];
GButton setButton;

String s = "";
boolean contact = false;

// dummy serial monitor
GTextArea serialMonitor;

// calibrate lower
GButton lowerButton;
boolean lower = false;
// calibrate upper
GButton upperButton;
boolean upper = false;

void setup() {
  size(300+700, 40*(kNumPins+2)+300, JAVA2D);
  startGUI();
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  s = myPort.readStringUntil('\n');
  serialMonitor.appendText(s);
  
  if (!contact && s==null) {
    println("no contact");
  } else if (!contact && s!=null) {
    myPort.clear();
    println("contact");
    contact = true;
  } else if (contact && s!=null) {
    s = trim(s);
    if (s.length()>1) {
      // get
      pinVals = int(split(s, ','));
      for (int i=0; i<kNumPins; i++) {
//        getTextFields[i].setText(""+pinVals[i]);
      }
      // set
//      pinVals = int(split(s, ','));
//      for (int i=0; i<kNum; i++) {
//        setTextFields[i].setText(""+pinVals[i]);
//      }
    }
  }
  
  // get button was pressed - ask for pin values
  if (get) {
    myPort.write(1);
    println(1);
    get = false; // reset get button
  }
  
  // set button was pressed - give calibration thresholds to Arduino
  if (set) {
    myPort.write(2);
    for(int i=0; i<kNum-1; i++) {
      String out = setTextFields[i].getText() + ',';
      for(int j=0; j<out.length(); j++) {
        myPort.write(out.charAt(j));
      }
      myPort.write('\n');
    }
    println(2);
    set = false; // reset set button
  }
  
  // lower
  if (lower) {
    myPort.write(3);
    println(3);
    lower = false; // reset set button
  }
  // upper
  if (upper) {
    myPort.write(4);
    println(4);
    upper = false; // reset set button
  }
}

public void startGUI() {
  G4P.messagesEnabled(false);
  G4P.setGlobalColorScheme(GCScheme.BLUE_SCHEME);
  G4P.setCursor(ARROW);
  if (frame != null) {
    frame.setTitle("Pin Output");
  }
  
  // get
  for (int i=0; i<kNumPins; i++) {
    getLabels[i] = new GLabel(this, 20, 20+40*i, 80, 20);
    getLabels[i].setText(String.valueOf(kPin0+i));
  }
  for (int i=0; i<kNumPins; i++) {
    getTextFields[i] = new GTextField(this, 120, 20+40*i, 160, 30, G4P.SCROLLBARS_NONE);
    getTextFields[i].setOpaque(true);
  }
  getButton = new GButton(this, 160, 40*(kNumPins+0.75), 80, 30);
  getButton.setText("Get");
  getButton.addEventHandler(this, "getButtonClick");
  
  // set
  for (int i=0; i<kNum; i++) {
    setLabels[i] = new GLabel(this, 20, 20+40*i, 80, 20);
    setLabels[i].setText(String.valueOf(kPin0+i));
  }
  for (int i=0; i<kNum; i++) {
    setTextFields[i] = new GTextField(this, 360, 20+40*i, 160, 30, G4P.SCROLLBARS_NONE);
    setTextFields[i].setOpaque(true);
  }
  setButton = new GButton(this, 400, 40*(kNum+0.75), 80, 30);
  setButton.setText("Set");
  setButton.addEventHandler(this, "setButtonClick");
  
  // dummy serial monitor
  serialMonitor = new GTextArea(this, 600, 20, 300, 500, G4P.SCROLLBARS_VERTICAL_ONLY);
  
  // calibration buttons
  getButton = new GButton(this, 160, 40*(kNumPins+0.75)+150, 80, 30);
  getButton.setText("lower");
  getButton.addEventHandler(this, "lowerButtonClick");
  getButton = new GButton(this, 160, 40*(kNumPins+0.75)+200, 80, 30);
  getButton.setText("upper");
  getButton.addEventHandler(this, "upperButtonClick");
}

public void getButtonClick(GButton source, GEvent event) {
  get = true;
}

// set button
public void setButtonClick(GButton source, GEvent event) {
  set = true;
}

// automatic calibration
public void lowerButtonClick(GButton source, GEvent event) {
  lower = true;
}

public void upperButtonClick(GButton source, GEvent event) {
  upper = true;
}

