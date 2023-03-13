const int SENSOR_PIN = 36;

int touch(){
    int currentState = digitalRead(SENSOR_PIN);

    if(currentState == HIGH){
        Serial.println("The sensor is touched");
    }
    else if(currentState == LOW){
        Serial.println("The sensor is is released");
    }

    return currentState;
}