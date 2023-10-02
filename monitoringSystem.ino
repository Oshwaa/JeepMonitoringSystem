#include <NewPing.h>

#define TRIGGER_PIN_1 2
#define ECHO_PIN_1 3
#define TRIGGER_PIN_2 4
#define ECHO_PIN_2 5
#define TRIGGER_PIN_3 6
#define ECHO_PIN_3 7
#define TRIGGER_PIN_4 8
#define ECHO_PIN_4 9
#define TRIGGER_PIN_5 10
#define ECHO_PIN_5 11
#define TRIGGER_PIN_6 12
#define ECHO_PIN_6 13

NewPing sensor[6] = {
  NewPing(TRIGGER_PIN_1, ECHO_PIN_1),
  NewPing(TRIGGER_PIN_2, ECHO_PIN_2),
  NewPing(TRIGGER_PIN_3, ECHO_PIN_3),
  NewPing(TRIGGER_PIN_4, ECHO_PIN_4),
  NewPing(TRIGGER_PIN_5, ECHO_PIN_5),
  NewPing(TRIGGER_PIN_6, ECHO_PIN_6)
};

int passengerCount = 0;
bool sitLastState[6] = {false};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 6; i++) {
    int distance = sensor[i].ping_cm();
    bool sit = (distance <= 40);

    // Increment passenger count if sensor is triggered and was not triggered before
    if (sit && !sitLastState[i]) {
      passengerCount++;
      sitLastState[i] = true;
    } else if (!sit && sitLastState[i]) {
      passengerCount--;
      sitLastState[i] = false;
    }
  }

  Serial.print("Passenger Count: ");
  Serial.println(passengerCount);

  delay(1000);
}