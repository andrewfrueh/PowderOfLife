/* ====================================================================================================

  Powder Of Life
  Arduino Library
  ---
  MPU Sensor
  
  ===========================

  The MPU sensor is designed to interface with MPU-6050 chips.
  Most MPU breakout boards provide SDA/SCL pins, enabling communication via the I2C ("two-wire") interface.
   
  ===========================

  Powder Of Life, Copyright (C) Andrew Frueh, 2018-2025
  Powder Of Life is under the GNU General Public License. See "LICENSE.txt" file included with this library.

==================================================================================================== */



#define MPU_DATA_LENGTH 7
#define MPU_DATA_DEPTH 32767 // int bounds

// Also, wire
#include<Wire.h>


class MPUSensor : public Sensor {
  private:
    // Properties
	// This address is 0x68 by default, but can be switched to 0x69 via the AD0 pin (low/high)
	// ... this allows multiple devices on same two wires, but you have to add a third wire for each device, and use up your GPIO pins on the controller
	int MPUAddress = 0x68; // I2C address of the MPU-6050
  protected:
    void wake();
    void work();
    void workFast();
    byte mode;
    byte axis;
    int mpuData[MPU_DATA_LENGTH]; // accel x/y/z, temp, gyro x/y/z
    //float frameTime = 0.001;
  public:
    MPUSensor();
    //
    enum modes : byte { accelerometer, gyroscope, temperature };
    enum axes : byte { x, y, z, all };
    //
    void setMode(modes newMode);
    void setAxis(axes newAxis);
};


// Constructor
MPUSensor::MPUSensor() {
  setMode(modes::accelerometer);
  setAxis(axes::x);
  setNormal(normalMode::custom, normalClip::overflow, 0, MPU_DATA_DEPTH, true ); 
}

void MPUSensor::wake() {
  // Wire, MPU startup
  Wire.begin();
  Wire.beginTransmission(MPUAddress);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}


void MPUSensor::workFast() {
}

void MPUSensor::work() {
  // Here we set the starting register so the data is aligned correctly
  Wire.beginTransmission(MPUAddress);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H) - data from the MPU is from registers 0x3B to 0x48
  Wire.endTransmission(false); // end? false?

  // Here we request data (of x length) from the MPU
  Wire.requestFrom(MPUAddress, MPU_DATA_LENGTH * 2, true); // request a total of 14 registers

  // Then we read the data
  mpuData[0] = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  mpuData[1] = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  mpuData[2] = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  mpuData[3] = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  mpuData[4] = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  mpuData[5] = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  mpuData[6] = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  // END read data

  // Now set the interval value based on the mode and axis
  switch (mode) {
    case accelerometer:
      switch (axis) {
        case x:
          setInternalValue(mpuData[0]);
          break;
        case y:
          setInternalValue(mpuData[1]);
          break;
        case z:
          setInternalValue(mpuData[2]);
          break;
        case all:
          setInternalValue( (mpuData[0] + mpuData[1] + mpuData[2]) / 3 );
          break;
      }
      break;
    case gyroscope:
      switch (axis) {
        case x:
          setInternalValue(mpuData[4]);
          break;
        case y:
          setInternalValue(mpuData[5]);
          break;
        case z:
          setInternalValue(mpuData[6]);
          break;
        case all:
          setInternalValue( (mpuData[4] + mpuData[5] + mpuData[6]) / 3 );
          break;
      }
      break;
    case temperature:
      setInternalValue(mpuData[3]); // just the one value
      break;
  }

}

void MPUSensor::setMode(modes newMode) {
  mode = newMode;
}

void MPUSensor::setAxis(axes newAxis) {
  axis = newAxis;
}


// EOF
