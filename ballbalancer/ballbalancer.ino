// Separate into x and y.

// PID controller for the x direction.
const float Kp_x = 5;
const float Ki_x = 5;
const float Kd_x = -5;
const float setpoint_x = 0;
float process_x = 0;

float angle_x = 0;

// PID controller for the y direction.
const float Kp_y = 5;
const float Ki_y = 5;
const float Kd_y = -5;
const float setpoint_y = 0;
float process_y = 0;

float angle_y = 0;

// Stuff for integrals.
float total_time = 0;
float integral_sum_x = 0;
float integral_sum_y = 0;

// Stuff for derivatives.
float last_error_x = 0;
float last_error_y = 0;

// Time keeping.
float last_time = millis();
float curr_time = millis();
// In seconds.
float dt = 0;

// Flags for serial reading and handshake.
bool input_received = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  handshake();
}

void calculate_pid() {
  float dt = delta_time();

  float error_x = process_x - setpoint_x;
  float error_y = process_y - setpoint_y;

  float p_x = Kp_x * error_x;
  float p_y = Kp_y * error_y;

  integral_sum_x += error_x * dt;
  integral_sum_y += error_y * dt;
  total_time += dt;

  float i_x = integral_sum_x / total_time;
  float i_y = integral_sum_y / total_time;

  float d_x = (error_x - last_error_x) / dt;
  float d_y = (error_y - last_error_y) / dt;

  last_error_x = error_x;
  last_error_y = error_y;

  angle_x = Kp_x * p_x + Ki_x * i_x + Kd_x * d_x;
  angle_y = Kp_y * p_y + Ki_y * i_y + Kd_y * d_y;

  return;
}

void move_motors() {
  // TBA
}

void loop() {
  check_serial();
  if (input_received) {
    // put your main code here, to run repeatedly:
    calculate_pid();
    move_motors();
  }
}

float delta_time() {
  curr_time = millis();
  float delta = curr_time - last_time;
  last_time = curr_time;
  return delta / 1000;
}

void handshake() {
  while (true) {
    if (Serial.available()) {
      if (Serial.readStringUntil("\n") == "READY?") {
        Serial.println("OK");
        return;
      }
    }
  }
}

void check_serial() {
  if (Serial.available()) {
    process_x = stof(Serial.readStringUntil(" "));
    process_y = stof(Serial.readStringUntil("\n"));
    input_received = true;
    return;
  }
  input_received = false;
  return;
}
