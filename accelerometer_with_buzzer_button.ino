#define xPin A1
#define yPin A2
#define zPin A3

//--------------------------------------------------------------
//calibrated minimum and maximum Raw Ranges for each axis
//use calibration.ino file to get these values
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
int xMin = 279;
int xMax = 422;
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
int yMin = 280;
int yMax = 424;
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
int zMin = 296;
int zMax = 436;
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//--------------------------------------------------------------
// Take multiple samples to reduce noise
const int samples = 10;

//--------------------------------------------------------------
int buttonpin = 3;  //Definisce il pin a cui è collegato il pulsante
int val;  
void setup() 
{
  pinMode(7,OUTPUT);
  //analogReference(EXTERNAL);
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonpin, INPUT);
}


void loop() 
{
  //--------------------------------------------------------------
  //Read raw values
  int xRaw=0,yRaw=0,zRaw=0;
  for(int i=0;i<samples;i++)
  {
    xRaw+=analogRead(xPin);
    yRaw+=analogRead(yPin);
    zRaw+=analogRead(zPin);
  }
  xRaw/=samples;
  yRaw/=samples;
  zRaw/=samples;
  //--------------------------------------------------------------
  //Convert raw values to 'milli-Gs"
  //Convert value of RawMin to -1000
  //Convert value of RawMax to 1000
  long xMilliG = map(xRaw, xMin, xMax, -1000, 1000);
  long yMilliG = map(yRaw, yMin, yMax, -1000, 1000);
  long zMilliG = map(zRaw, zMin, zMax, -1000, 1000);
  //--------------------------------------------------------------
  // re-scale to fractional Gs
  float x_g_value = xMilliG / 1000.0;
  float y_g_value = yMilliG / 1000.0;
  float z_g_value = zMilliG / 1000.0;
  //--------------------------------------------------------------
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  //Serial.print(x_g_value,0);
  //Serial.print(x_g_value,2);
  //Serial.print("G");
  //Serial.print("\t");
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  //Serial.print(y_g_value,0);
  //Serial.print(y_g_value,2);
  //Serial.print("G");
  //Serial.print("\t");
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  Serial.print(z_g_value,0);
  //Serial.print(z_g_value,2);
  Serial.println("G");
  if (z_g_value <=0){
  Serial.println("RESCUE");
  analogWrite(7,200);
  }
  else{
    analogWrite(7,0);
  }
  
  
  
  Serial.println();
  //MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
  //--------------------------------------------------------------
   val = digitalRead(buttonpin); // controlla lo stato del pulsante
  if (val == LOW)
  {
   digitalWrite(LED_BUILTIN, LOW); // se si preme il pulsante, accende il LED
  }
   else
  {
    digitalWrite(LED_BUILTIN, HIGH); // oppure spegne il LED
  }
  delay(200);
}