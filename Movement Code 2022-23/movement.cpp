#include "vex.h"

using namespace vex;

class Chassis {
private:
    motor frontLeftMotor;
    motor frontRightMotor;
    motor rearLeftMotor;
    motor rearRightMotor;
    inertial gyro; 

public:
    Chassis(motor fl, motor fr, motor rl, motor rr, inertial gyroSensor) : 
        frontLeftMotor(fl), frontRightMotor(fr), rearLeftMotor(rl), rearRightMotor(rr), gyro(gyroSensor) {
        gyro.calibrate();
    }

    void drive(int yAxis, int xAxis, int rotation) {
        frontLeftMotor.spin(directionType::fwd, yAxis + xAxis + rotation, velocityUnits::pct);
        frontRightMotor.spin(directionType::fwd, yAxis - xAxis - rotation, velocityUnits::pct);
        rearLeftMotor.spin(directionType::fwd, yAxis - xAxis + rotation, velocityUnits::pct);
        rearRightMotor.spin(directionType::fwd, yAxis + xAxis - rotation, velocityUnits::pct);
    }

    double getRotation() {
        return gyro.rotation(degrees);
    }
};

class PIDController {
private:
    double kP;
    double kI;
    double kD;
    double error;
    double integral;
    double derivative;
    double previousError;
    double target;

public:
    PIDController(double kp, double ki, double kd) : kP(kp), kI(ki), kD(kd) {
        error = 0;
        integral = 0;
        derivative = 0;
        previousError = 0;
        target = 0;
    }

    void setTarget(double setpoint) {
        target = setpoint;
    }

    double calculate(double input) {
        error = target - input;
        integral += error;
        derivative = error - previousError;
        previousError = error;
        return (kP * error) + (kI * integral) + (kD * derivative);
    }
};

int main() {
    // Controller setup
    controller Controller1 = controller();

    // Drive motors setup
    motor frontLeftMotor = motor(PORT1, ratio18_1, false);
    motor frontRightMotor = motor(PORT2, ratio18_1, true);
    motor rearLeftMotor = motor(PORT3, ratio18_1, false);
    motor rearRightMotor = motor(PORT4, ratio18_1, true);

    // Arm motor setup
    motor armMotor = motor(PORT5, ratio36_1, false);

    // Shooter motor setup
    motor shooterMotor = motor(PORT6, ratio36_1, false);

    // Gyroscope setup
    inertial gyroSensor = inertial(PORT7);

    // Create the chassis object
    Chassis chassis(frontLeftMotor, frontRightMotor, rearLeftMotor, rearRightMotor, gyroSensor);

    // Constants for arm control
    const int armSpeedUp = 100;     // Speed for raising the arm
    const int armSpeedDown = -50;   // Speed for lowering the arm

    // Constants for shooter control
    const int shooterSpeed = 75;    // Speed for the shooter

    // PID constants for chassis rotation control
    const double rotationKP = 0.5;
    const double rotationKI = 0.01;
    const double rotationKD = 0.1;

    PIDController rotationController(rotationKP, rotationKI, rotationKD);

    while (true) {
        // Drive control
        int yAxis = Controller1.Axis3.position();
        int xAxis = Controller1.Axis4.position();
        int rotation = Controller1.Axis1.position();
        chassis.drive(yAxis, xAxis, rotation);

        // Arm control
        if (Controller1.ButtonUp.pressing()) {
            armMotor.spin(directionType::fwd, armSpeedUp, velocityUnits::pct);
        } else if (Controller1.ButtonDown.pressing()) {
            armMotor.spin(directionType::fwd, armSpeedDown, velocityUnits::pct);
        } else {
            armMotor.stop(brakeType::hold);
        }

        // Shooter control
        if (Controller1.ButtonA.pressing()) {
            shooterMotor.spin(directionType::fwd, shooterSpeed, velocityUnits::pct);
        } else if (Controller1.ButtonB.pressing()) {
            shooterMotor.spin(directionType::rev, shooterSpeed, velocityUnits::pct);
        } else {
            shooterMotor.stop(brakeType::coast);
        }

        // Chassis rotation control using gyro and PID
        double targetRotation = Controller1.Axis1.position();
        rotationController.setTarget(targetRotation);
        double rotationCorrection = rotationController.calculate(chassis.getRotation());
        chassis.drive(yAxis, xAxis, rotationCorrection);

        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
