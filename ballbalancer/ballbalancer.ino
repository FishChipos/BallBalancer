// Separate into x and y.

// PID controller for the x direction.
const float Kp_x = 5;
const float Ki_x = 5;
const float Kd_x = 5;
const float setpoint_x = 0;
float process_x = 0;

float angle_x = 0;


// PID controller for the y direction.
const float Kp_y = 5;
const float Ki_y = 5;
const float Kd_y = 5;
const float setpoint_y = 0;
float process_x = 0;

float angle_y = 0;

// Parameters for integrals.
float total_time = 0;
float integral_sum_x = 0;
float integral_sum_y = 0;

// Time keeping.
float last_time = millis();
float curr_time = millis();

void setup() {
  // put your setup code here, to run once:
  calculate_pid();
}

void calculate_pid() {
  float error_x = process_x - setpoint_x;
  float error_y = process_y - setpoint_y;

  float p_x = Kp_x * error_x;
  float p_y = Kp_y * error_y;

  float dt = delta_time();

  integral_sum_x = (integral_sum_x * total_time + error_x) / (total_time + dt);
  integral_sum_y = (integral_sum_y * total_time + error_y) / (total_time + dt);
  total_time += dt;

  
}

void loop() {
  // put your main code here, to run repeatedly:

}

float delta_time() {
  curr_time = millis();
  float delta = curr_time  last_time;
  last_time = curr_time;
  return delta;
}
