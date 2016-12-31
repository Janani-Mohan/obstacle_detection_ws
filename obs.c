int L = 5;

int L1 = 6;

int obs1 = 3;

int obs2 = 4;

int R = 9;

int R1 = 10;

long sensor_ave;

int sensor_sum;

long sensor[] = {0,0,0,0,0};

int position;

int prop;

int integral = 0;

int deriv = 0;

int last_prop = 0;

int error;

int prev_error=0;

int left1;

int left2;

int right1;

int right2;

int kp = 2;

int ki = 0;

int kd = 1;
 

void setup()
{

  pinMode(obs1,INPUT);

  pinMode(obs2,INPUT);

}

void loop()
{

sensors_read();

if(digitalRead(obs1)==HIGH&&digitalRead(obs2)==LOW)
{

pid_calc();

calc_turn();

motor_drive(right1,right2,left1,left2);

}

if(digitalRead(obs1)==LOW&&digitalRead(obs2)==LOW)

{

  analogWrite(R,0);

 analogWrite(R1,255);

 analogWrite(L,0);

 analogWrite(L1,255);

 delay(200);

 analogWrite(R,255);

 analogWrite(R1,0);

 analogWrite(L,0);

 analogWrite(L1,255);

 delay(300);

 analogWrite(R , 170);

  analogWrite(R1, 0);

  analogWrite(L, 200);

  analogWrite(L1, 0);

  delay(1250);
}

if(digitalRead(obs1)==HIGH&&digitalRead(obs2)==HIGH)

{

  analogWrite(R,0);

 analogWrite(R1,255);

 analogWrite(L,0);

 analogWrite(L1,255);

 delay(200);

analogWrite(R,0);

 analogWrite(R1,255);

 analogWrite(L,255);

 analogWrite(L1,0);

 delay(300);

 analogWrite(R , 200);

  analogWrite(R1, 0);

  analogWrite(L, 170);

  analogWrite(L1, 0);

  delay(1250);
}

}

void sensors_read()
{

sensor_ave = 0;

sensor_sum = 0;

for(int i=0;i<5;i++)
{

sensor[i] = analogRead(i);

if (sensor[i] < 500)
{

sensor[i] = 0;

}

else
{

sensor[i] = 1;

}

sensor_ave += sensor[i]*i*180;

sensor_sum += sensor[i];

}

if(sensor_sum == 0)

{

 sensor_ave = 360;

 sensor_sum = 1;

}
 

}

void pid_calc()

{

position = int(sensor_ave/sensor_sum);

prop = position - 360;

integral = integral + prop;

deriv = prop - last_prop;

last_prop = prop;

error = int(prop*kp - integral*ki + deriv*kd);

prev_error=error;

}

void calc_turn()

{

if(sensor[0]==1&& sensor[1]==1 && sensor[2]==1 && sensor[3]==1 && sensor[4]==1)
{

  error=prev_error;

}
else
{

if(error < -255)
{

error = -255;

}

if(error > 255)
{

error = 255;

}

if (error < 0)
{

right1 = 255 + error;

right2 = 0 - error;

left1 = 255;

left2 = 0;

}
else
{

left1 = 255 - error;

left2 = error;

right1 = 255;

right2 = 0;

}

}

}

void motor_drive ( int right1,int right2,int left1,int left2)

{

    analogWrite(R , right1);

    analogWrite(R1, right2);

    analogWrite(L, left1);

    analogWrite(L1, left2);

}
