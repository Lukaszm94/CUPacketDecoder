/*
 * datatypes.h
 *
 *  Created on: 27 gru 2016
 *      Author: Luke
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <stdint.h>

#ifndef BM_BATTERY_CELLS_COUNT
#define BM_BATTERY_CELLS_COUNT 6
#endif

struct CurrentPacket {
  int16_t VESC1Current; // *10
  int16_t VESC2Current; // *10
};

struct TemperaturePacket {
  int16_t VESC1Temperature; // *100
  int16_t VESC2Temperature; // *100
  int16_t powerSwitchTemperature; // *100
  int16_t driversUnitCaseTemperature; // *100
};

struct BatteryPacket {
  uint16_t cellsVoltage[BM_BATTERY_CELLS_COUNT]; // *100
  uint16_t CUBatteryVoltage; // *100
  uint16_t VESCBatteryVoltage; // *100
  uint16_t ampHoursDrawn; // *1000
  uint16_t ampHoursCharged; // *1000
  uint8_t batteryCharge; // *1, in %
};

struct SpeedPacket {
  uint16_t speed; // *100, in m/s
};

struct ErrorPacket {
  uint16_t module;
  uint16_t code;
};

#endif /* DATATYPES_H_ */
