#define trigPin 9
#define echoPin 10
#define led 11

#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

std_msgs::Int32 dist_msg;

ros::Publisher distance("distance", &dist_msg);

void setup() {
  Serial.begin (9600);
  nh.initNode();
  nh.advertise(distance);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  long duration; 
  int distance_;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance_ = (duration/2) / 29.1;
  if (distance_ < 4) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
  }  
  else {
    digitalWrite(led,LOW);
    Serial.print(distance_);
    Serial.println(" cm");
  }
  dist_msg.data = distance_;
  distance.publish(&dist_msg);
  nh.spinOnce();
  delay(500);
}
