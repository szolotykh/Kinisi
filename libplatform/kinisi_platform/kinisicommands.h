// ----------------------------------------------------------------------------
// Kinisi motr controller commands.
// This file is auto generated by the commands generator from JSON file.
// Do not edit this file manually.
// Timestamp: 2023-12-14 20:17:00
// Version: 1.0.2
// ----------------------------------------------------------------------------

#ifndef LIBPLATFORM_COMMANDS_H
#define LIBPLATFORM_COMMANDS_H

#include <stdint.h>


// Commands// This command initializes a motor and prepares it for use.
#define INITIALIZE_MOTOR 0x01

// This command sets the speed of the specified motor.
#define SET_MOTOR_SPEED 0x02

// This command stops motor by setting its speed to 0.
#define STOP_MOTOR 0x03

// This command brakes motor.
#define BRAKE_MOTOR 0x04

// This command sets the controller for the specified motor.
#define INITIALIZE_MOTOR_CONTROLLER 0x05

// This command sets the target velocity for the specified motor.
#define SET_MOTOR_TARGET_VELOCITY 0x06

// This command deletes the controller for the specified motor.
#define DELETE_MOTOR_CONTROLLER 0x07

// This command initializes an encoder and prepares it for use.
#define INITIALIZE_ENCODER 0x11

// This command retrieves the current value of the encoder.
#define GET_ENCODER_VALUE 0x12

// This command initializes a digital pin and prepares it for use.
#define INITIALIZE_GPIO_PIN 0x20

// This command sets the specified pin to a state.
#define SET_GPIO_PIN_STATE 0x21

// This command gets the state of the specified pin.
#define GET_GPIO_PIN_STATE 0x22

// This command toggles the specified pin.
#define TOGGLE_GPIO_PIN_STATE 0x23

// This command sets the status LED to a state.
#define SET_STATUS_LED_STATE 0x25

// This command toggles the status LED.
#define TOGGLE_STATUS_LED_STATE 0x26

// This command initializes a mecanum platform and prepares it for use.
#define INITIALIZE_MECANUM_PLATFORM 0x30

// This command initializes a omni platform and prepares it for use.
#define INITIALIZE_OMNI_PLATFORM 0x31

// This command sets the velocity input for the platform.
#define SET_PLATFORM_VELOCITY_INPUT 0x40

// This command sets the controller for the platform.
#define SET_PLATFORM_CONTROLLER 0x41


// Commands class
class KinisiCommands {
public:
    virtual int read(unsigned int lenght) = 0;

    virtual int write(unsigned char* cmd, unsigned int size) = 0;

public:
    // INITIALIZE_MOTOR: This command initializes a motor and prepares it for use.
    void initialize_motor(uint8_t motor_index, bool is_reversed) {
        unsigned char cmd[] = { 0, INITIALIZE_MOTOR, motor_index, is_reversed };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // SET_MOTOR_SPEED: This command sets the speed of the specified motor.
    void set_motor_speed(uint8_t motor_index, uint8_t direction, uint16_t speed) {
        unsigned char cmd[] = { 0, SET_MOTOR_SPEED, motor_index, direction, speed };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // STOP_MOTOR: This command stops motor by setting its speed to 0.
    void stop_motor(uint8_t motor_index) {
        unsigned char cmd[] = { 0, STOP_MOTOR, motor_index };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // BRAKE_MOTOR: This command brakes motor.
    void brake_motor(uint8_t motor_index) {
        unsigned char cmd[] = { 0, BRAKE_MOTOR, motor_index };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // INITIALIZE_MOTOR_CONTROLLER: This command sets the controller for the specified motor.
    void initialize_motor_controller(uint8_t motor_index, double kp, double ki, double kd) {
        unsigned char cmd[] = { 0, INITIALIZE_MOTOR_CONTROLLER, motor_index, kp, ki, kd };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // SET_MOTOR_TARGET_VELOCITY: This command sets the target velocity for the specified motor.
    void set_motor_target_velocity(uint8_t motor_index, uint8_t direction, uint16_t speed) {
        unsigned char cmd[] = { 0, SET_MOTOR_TARGET_VELOCITY, motor_index, direction, speed };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // DELETE_MOTOR_CONTROLLER: This command deletes the controller for the specified motor.
    void delete_motor_controller(uint8_t motor_index) {
        unsigned char cmd[] = { 0, DELETE_MOTOR_CONTROLLER, motor_index };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // INITIALIZE_ENCODER: This command initializes an encoder and prepares it for use.
    void initialize_encoder(uint8_t encoder_index) {
        unsigned char cmd[] = { 0, INITIALIZE_ENCODER, encoder_index };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // GET_ENCODER_VALUE: This command retrieves the current value of the encoder.
    uint32_t get_encoder_value(uint8_t encoder_index) {
        unsigned char cmd[] = { 0, GET_ENCODER_VALUE, encoder_index };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
        return read(sizeof(uint32_t));
    }
    // INITIALIZE_GPIO_PIN: This command initializes a digital pin and prepares it for use.
    void initialize_gpio_pin(uint8_t pin_number, uint8_t mode) {
        unsigned char cmd[] = { 0, INITIALIZE_GPIO_PIN, pin_number, mode };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // SET_GPIO_PIN_STATE: This command sets the specified pin to a state.
    void set_gpio_pin_state(uint8_t pin_number, uint8_t state) {
        unsigned char cmd[] = { 0, SET_GPIO_PIN_STATE, pin_number, state };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // GET_GPIO_PIN_STATE: This command gets the state of the specified pin.
    uint8_t get_gpio_pin_state(uint8_t pin_number) {
        unsigned char cmd[] = { 0, GET_GPIO_PIN_STATE, pin_number };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
        return read(sizeof(uint8_t));
    }
    // TOGGLE_GPIO_PIN_STATE: This command toggles the specified pin.
    void toggle_gpio_pin_state(uint8_t pin_number) {
        unsigned char cmd[] = { 0, TOGGLE_GPIO_PIN_STATE, pin_number };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // SET_STATUS_LED_STATE: This command sets the status LED to a state.
    void set_status_led_state(uint8_t state) {
        unsigned char cmd[] = { 0, SET_STATUS_LED_STATE, state };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // TOGGLE_STATUS_LED_STATE: This command toggles the status LED.
    void toggle_status_led_state() {
        unsigned char cmd[] = { 0, TOGGLE_STATUS_LED_STATE, };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // INITIALIZE_MECANUM_PLATFORM: This command initializes a mecanum platform and prepares it for use.
    void initialize_mecanum_platform(bool is_reversed_0, bool is_reversed_1, bool is_reversed_2, bool is_reversed_3) {
        unsigned char cmd[] = { 0, INITIALIZE_MECANUM_PLATFORM, is_reversed_0, is_reversed_1, is_reversed_2, is_reversed_3 };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // INITIALIZE_OMNI_PLATFORM: This command initializes a omni platform and prepares it for use.
    void initialize_omni_platform(bool is_reversed_0, bool is_reversed_1, bool is_reversed_2, uint16_t wheels_diameter, uint16_t robot_radius) {
        unsigned char cmd[] = { 0, INITIALIZE_OMNI_PLATFORM, is_reversed_0, is_reversed_1, is_reversed_2, wheels_diameter, robot_radius };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // SET_PLATFORM_VELOCITY_INPUT: This command sets the velocity input for the platform.
    void set_platform_velocity_input(int8_t x, int8_t y, int8_t t) {
        unsigned char cmd[] = { 0, SET_PLATFORM_VELOCITY_INPUT, x, y, t };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
    // SET_PLATFORM_CONTROLLER: This command sets the controller for the platform.
    void set_platform_controller() {
        unsigned char cmd[] = { 0, SET_PLATFORM_CONTROLLER, };
        cmd[0] = sizeof(cmd) - 1;
        write(cmd, sizeof(cmd));
    }
};

#endif