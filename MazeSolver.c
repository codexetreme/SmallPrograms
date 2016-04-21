#include<arduino.h>
#define numSensors 5
#define BasePWMspeed 170


//PINS
const int IRInputs[4] = {2, 3, 4, 5, 6};


char path[100] = "";
int turnDelayTime = 600;
int correctionTime = 50; // this is the extra time required in case after alighning perpendicular with the turning line, the body still is a bit away from a proper turn
int path_length = 0;
int SensorValues[numSensors];

void Adjust(char dir, int speed){
	if (dir == 'r')
	moveRight();
	else if (dir == 'l')
	moveLeft();
	
	analogWrite(PWMotors[0], speed + adjustThreshold);
	analogWrite(PWMotors[1], speed - adjustThreshold);
}

void FollowLine()
{
  
  while(1){
    
    int val = ReadSensors();  
    Serial.println(val);  
    if (val == 11011){ 
      analogWrite(PWMotors[1],255);
      analogWrite(PWMotors[0],255);
    }
    else if (val==11101){
      analogWrite(PWMotors[1],BasePWMspeed - 50);
      analogWrite(PWMotors[0],BasePWMspeed + 50);
    }
    else if (val==10111 ){
      analogWrite(PWMotors[1],BasePWMspeed + 50);
      analogWrite(PWMotors[0],BasePWMspeed - 50); 
    }
    moveStraight();
    if (val == 11111)
      return;
    if (val ==11100 || val == 00111 || val == 01111 || val == 11110)
      return;
  } 
}



int ReadSensors(){
	int num = 0;
	for(int i =0; i<numSensors; i++){
		//SensorValues[i] = analogRead(IRInputs[i]);
		SensorsValues[i] = digitalRead(IRInputs[i]);
		num = num*10 + SensorValues[i];
	}
	return num;
}





int DistanceFromLineAnalog(){
	int val =0;
	unsigned long sum = 0;
	unsigned long avg = 0;
	bool on_line = false;
	static int lastValue = 0;
	for(int i =0; i<numSensors; i++){
		val = SensorValues[i];
		
		if (val > 200){
			// we are on the line just a little bit off
			on_line = true;
		}	
		if(val > noiseThreshold){	
			avg += (long) value *( i * 1000);
			sum +=value;
 		}
	}	
	if(!on_line)
	{
		// If it last read to the left of center, return 0.
		if(last_value < (numSensors-1)*1000/2)
			return 0;

		// If it last read to the right of center, return the max.
		else
			return (numSensors-1)*1000;

	}
    last_value = avg/sum;
	return last_value;	
}




void Turn(char direction)
{	
	switch(direction){
		case 'L':	
			
			delay(correctionTime);
			moveLeft();
		    analogWrite(PWMotors[0], 200);
		    analogWrite(PWMotors[1], 200);
		    delay(turnDelayTime);
		    // now find the line again
			int lineValue = ReadSensors();
			
			// wait for the robo to turn till it is centered
			while(lineValue != 11011){// || lineValue != 11101 || lineValue != 11111){
				
				lineValue = ReadSensors();
			}
			
			
			analogWrite(PWMotors[1], 0);
		    analogWrite(PWMotors[0], 0);			
			break;			
		case 'R':
			moveRight();
		    analogWrite(PWMotors[0], 200);
		    analogWrite(PWMotors[1], 200);
		    delay(turnDelayTime);
		    
			int lineValue = DistanceFromLineAnalog();
			
			// wait for the robo to turn till it is centered
			while(lineValue >2500){	
				lineValue = DistanceFromLineAnalog();
			}
			
			analogWrite(PWMotors[0], 0);
			analogWrite(PWMotors[1], 0);
		    	
			break;
		
		case 'S':
			break;
	}
	
}

char SelectTurn(int found_left, int found_right, int found_straight)
{
  // Make a decision about how to turn.  The following code
  // implements a left-hand-on-the-wall strategy, where we always
  // turn as far to the left as possible.
  if(found_left)
    return 'L';
  else if(found_straight)
    return 'S';
  else if(found_right)
    return 'R';
  else
    return 'B';
}





void SolveMaze()
{
	int lineVal = 0;
	while(1){
		
		followLine();
		
		
		int left = 0,right = 0,straight = 0;
		lineVal = ReadSensors();
		
		if(SensorValues[0]==0)
			left = 1;
		if (SensorValues[numSensors-1]==0)
			right = 1;
		moveStraight();
		analogWrite(PWMotors[0],200);
		analogWrite(PWMotors[1],200);
		delay(50);
		
		lineVal = ReadSensors();		
		
		if (val == 100)
			straight = 1;
		
		if (val == 0)
			break;
		
			
		dir = SelectTurn(left,right,straight);
		Turn(dir);
		path[path_length] = dir;
		path_length ++;
		simplify_path();
		
	}	
	
	
	delay(2000);
	
	while(1){
		
		for(int i =0; i<path_length; i++){
			
			followLine();
			turn(path[i]);
			
		}	
	}
}


void simplify_path()
{
  // only simplify the path if the second-to-last turn was a 'B'
  if (path_length < 3 || path[path_length - 2] != 'B')
    return;

  int total_angle = 0;
  int i;
  for (i = 1; i <= 3; i++)
  {
    switch (path[path_length - i])
    {
      case 'R':
        total_angle += 90;
        break;
      case 'L':
        total_angle += 270;
        break;
      case 'B':
        total_angle += 180;
        break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  total_angle = total_angle % 360;

  // Replace all of those turns with a single one.
  switch (total_angle)
  {
    case 0:
      path[path_length - 3] = 'S';
      break;
    case 90:
      path[path_length - 3] = 'R';
      break;
    case 180:
      path[path_length - 3] = 'B';
      break;
    case 270:
      path[path_length - 3] = 'L';
      break;
  }

  // The path is now two steps shorter.
  path_length -= 2;

} // end simplify_path