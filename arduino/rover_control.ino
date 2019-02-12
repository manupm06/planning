int pin1A=10, pin2A=9, pin3A=8, pin4A=12, pin1B=3, pin2B=4, pin3B=5, pin4B=6, en_aA=11, en_bA=13, en_aB=2, en_bB=7,x;
 
#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle  nh;



float lin=0,ang=0;
int pos;
void control_cb( const geometry_msgs::Twist& msg){
  lin=msg.linear.x;
  ang=msg.angular.z;
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
}


ros::Subscriber<geometry_msgs::Twist> sub("/turtle1/cmd_vel", control_cb);

void setup(){
  pinMode(13, OUTPUT);
  pinMode (2,OUTPUT);
  pinMode (3,OUTPUT);
  pinMode (4,OUTPUT);
  pinMode (5,OUTPUT);
  pinMode (6,OUTPUT);
  pinMode (7,OUTPUT);pinMode (8,OUTPUT);pinMode (9,OUTPUT);pinMode (10,OUTPUT);
  pinMode (11,OUTPUT);
  pinMode (12,OUTPUT);
  pinMode (13,OUTPUT);

  nh.initNode();
  nh.subscribe(sub);

  analogWrite (en_aA,200);
  analogWrite (en_bA,200);
  analogWrite (en_aB,200);
  analogWrite (en_bB,200);
}

void loop(){
  nh.spinOnce();
  delay(1);
  if(lin>0 && ang==0){
    digitalWrite (pin1A, HIGH);
    digitalWrite (pin2A, LOW);
    digitalWrite (pin3A, LOW);
    digitalWrite (pin4A, HIGH);
    
    digitalWrite (pin1B, HIGH);
    digitalWrite (pin2B, LOW);
    digitalWrite (pin3B, LOW);
    digitalWrite (pin4B, HIGH);
    }
  if(lin<0 && ang==0){
    digitalWrite (pin1A, LOW);
    digitalWrite (pin2A, HIGH);
    digitalWrite (pin3A, HIGH);
    digitalWrite (pin4A, LOW);
    
    digitalWrite (pin1B, LOW);
    digitalWrite (pin2B, HIGH);
    digitalWrite (pin3B, HIGH);
    digitalWrite (pin4B, LOW);  
    }
  if(lin==0 && ang<0){
    digitalWrite (pin1A, LOW);
    digitalWrite (pin2A, HIGH);
    digitalWrite (pin3A, LOW);
    digitalWrite (pin4A, HIGH);
    
    digitalWrite (pin1B, LOW);
    digitalWrite (pin2B, HIGH);
    digitalWrite (pin3B, LOW);
    digitalWrite (pin4B, HIGH); 
  }
  if(lin==0 && ang>0){
    digitalWrite (pin1A, HIGH);
    digitalWrite (pin2A, LOW);
    digitalWrite (pin3A, HIGH);
    digitalWrite (pin4A, LOW);
    
    digitalWrite (pin1B, HIGH);
    digitalWrite (pin2B, LOW);
    digitalWrite (pin3B, HIGH);
    digitalWrite (pin4B, LOW);  
  }
  delay(50);
  lin=0;
  ang=0;
  digitalWrite (pin1A, HIGH);
  digitalWrite (pin2A, HIGH);
  digitalWrite (pin3A, HIGH);
  digitalWrite (pin4A, HIGH);
  
  digitalWrite (pin1B, HIGH);
  digitalWrite (pin2B, HIGH);
  digitalWrite (pin3B, HIGH);
  digitalWrite (pin4B, HIGH);
}
