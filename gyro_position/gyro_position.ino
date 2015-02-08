// 3Axis gyro comunication program by Babak Manafi

#include <Wire.h>


char WHO_AM_I = 0x00;
char SMPLRT_DIV= 0x15;
char DLPF_FS = 0x16;
char GYRO_XOUT_H = 0x1D;
char GYRO_XOUT_L = 0x1E;
char GYRO_YOUT_H = 0x1F;
char GYRO_YOUT_L = 0x20;
char GYRO_ZOUT_H = 0x21;
char GYRO_ZOUT_L = 0x22;

char DLPF_CFG_0 = (1<<0);
char DLPF_CFG_1 = (1<<1);
char DLPF_CFG_2 = (1<<2);
char DLPF_FS_SEL_0 = (1<<3);
char DLPF_FS_SEL_1 = (1<<4);

char itgAddress = 0x69;



void setup()
{
  int counter=0;
int maxV=1000000;
   Serial.begin(9600);
   Wire.begin();
 
    char id=0;
  id = itgRead(itgAddress, 0x00); 
 
 
    itgWrite(itgAddress, DLPF_FS, (DLPF_FS_SEL_0|DLPF_FS_SEL_1|DLPF_CFG_0));
   itgWrite(itgAddress, SMPLRT_DIV, 9);

int  prevX[5]={maxV,maxV,maxV,maxV,maxV};
int  prevY[5]={maxV,maxV,maxV,maxV,maxV};
int  prevZ[5]={maxV,maxV,maxV,maxV,maxV};
  int xMinTolerance=4;
  int xMaxTolerance=-4;
  int yMinTolerance=4;
  int yMaxTolerance=-4;
  int zMinTolerance=4;
  int zMaxTolerance=-4;
  int counter =50;
    int xRate;
    int yRate;
    int zRate;
       int xStartRate;
       int yStartRate;
       int zStartRate;
           int xoffset;
           int yoffset;
           int zoffset;
                        int n=6;
                        int flag=1;
     float angleX=0;
     float angleY=0;
     float angleZ=0;
           long startTime=0;
           long stopTime;
           long elapsedTime;
     float X=0;
     float Y=0;
     float Z=0;
                // change this number to make it more accurate
                int calibrationFactor=7200;
   }          
void loop()
{
    counter++;
    if(
      if( angleX>xMaxTolerance & angleX<xMinTolerance & angleY>yMaxTolerance & angleY<yMinTolerance & angleZ>zMaxTolerance & angleZ<zMinTolerance){
        if(counter == counterPref && checkPrev(angleX,angleY,angleZ)){
          xAxis = 0;
          yAxis = 0;
          zAxis = 0;
          counter=0;
        }
    }
  
       if (flag==1)
       {
              for (int i=1;i<10;i++)
               {
                 xoffset = readX();
                 yoffset = readY();
                 zoffset = readZ();
               }
                              angleX=0;
                              angleY=0;
                              angleZ=0;
      startTime=millis();
               xStartRate=readX()-xoffset;
               if (abs(xStartRate)<n)xStartRate=0;
          yStartRate=readY()-yoffset;
          if (abs(yStartRate)<n)yStartRate=0;
                       zStartRate=readZ()-zoffset;
                       if (abs(zStartRate)<n)zStartRate=0;
             flag=0;
       }
         
          // send anything to Arduino serial port to reset the angles
          if (Serial.available()!=0)
            {
              flag=1;
              Serial.flush();
            }
           
  xRate = readX()-xoffset;
  if (abs(xRate)<n)xRate=0;

  yRate = readY()-yoffset;
   if (abs(yRate)<n)yRate=0;

  zRate = readZ()-zoffset;
   if (abs(zRate)<n)zRate=0;
   
             stopTime=millis();
             elapsedTime=stopTime-startTime;
             startTime=stopTime;
   
   angleX=angleX+(xRate+xStartRate)/2*elapsedTime;
   angleY=angleY+(yRate+yStartRate)/2*elapsedTime;
   angleZ=angleZ+(zRate+zStartRate)/2*elapsedTime;
   
                                    X=angleX/calibrationFactor;
                                    Y=angleY/calibrationFactor;
                                    Z=angleZ/calibrationFactor;
   
  Serial.print("X axis angle = ");
  Serial.print(X);
  Serial.print("\t\t");
  Serial.print("Y axis angle = ");
  Serial.print(Y);
  Serial.print("\t\t");
  Serial.print("Z axis angle = ");
  Serial.print(Z);
  Serial.println();  
  addPrev(angleX, angleY, angleZ); 
  delay(70);
}

boolean checkPrev(int x, int y, int z){
  for(k=0;k<sizeof(prevX);k++){
    if(prevX[k]==x && prevY[k]==y && prevZ[k]==z){
      return false;
    }
  }
  return true;
}

void addPrev(int x, int y, int z){
  add(prevX,x);
  add(prevY,y);
  add(prevZ,z);
}

int[] add(int[] x, int value){
  boolean lol =false;
  for(k=0;k<sizeof(x);k++){
    if(x[k]==maxV){
      x[k]=value;
      return x;
    }
  }
  x[0]=value;
  return x;
}


void itgWrite(char address, char registerAddress, char data)
{
 
  Wire.beginTransmission(address);
    Wire.write(registerAddress);
    Wire.write(data);
   Wire.endTransmission();
}

unsigned char itgRead(char address, char registerAddress)
{
   unsigned char data=0;
 
   Wire.beginTransmission(address);
   Wire.write(registerAddress);
   Wire.endTransmission();
 
   Wire.beginTransmission(address);
  Wire.requestFrom(address, 1);
 
   if(Wire.available()){
       data = Wire.read();
  }
 
    Wire.endTransmission();
 
   return data;
}

int readX(void)
{
  int data=0;
  data = itgRead(itgAddress, GYRO_XOUT_H)<<8;
  data |= itgRead(itgAddress, GYRO_XOUT_L); 
 
  return data;
}

int readY(void)
{
  int data=0;
  data = itgRead(itgAddress, GYRO_YOUT_H)<<8;
  data |= itgRead(itgAddress, GYRO_YOUT_L); 
 
  return data;
}

int readZ(void)
{
  int data=0;
  data = itgRead(itgAddress, GYRO_ZOUT_H)<<8;
  data |= itgRead(itgAddress, GYRO_ZOUT_L); 
 
  return data;
}

