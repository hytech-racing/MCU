#ifndef __EEPROMINTERFACE_H__
#define __EEPROMINTERFACE_H__
#include <cstdlib>
#include <cstddef>
#include <SharedDataTypes.h>

// what this is:
// this interface will encompass any and all interfacing / writing of the eeprom on a micro platform (for now: teensy)

// first goal of this interface: be able to keep a log of our mileage with intermittent updates of the current km driven.

// we will be writing a struct to the memory that will contain the mileage data / any of the other
// data we will write and be able to read / recall from the eeprom


// this class will also manage the time in which we update the EEPROM values so that we can safely call the update function
// repeatedly without concern for the life of the underlying EEPROM.
class EEPROMInterface
{
    public:
        struct params
        {
            unsigned int write_interval_ms;
        };

        EEPROMInterface(params p = {120000000}) :
            _params(p) {
                _last_write_time_millis = 0;
                _last_written_distance_m = 0;
                _eeprom_written_data = {};
            }

        /// @brief initialize the EEPROMInterface by reading the last written data from the EEPROM. 
        //         reads first the size of the low level data in bytes (a uint16_t) and then 
        //         proceeds to read that amount of data.

        /// @brief 
        /// @param reset_eeprom use this flag to write 
        void init(bool reset_eeprom);

        void update_eeprom(const SharedCarState_s & car_state);
        EEPROMInterfaceData_s get_current_data();

    private:
        unsigned long _last_write_time_millis;
        int _last_written_distance_m;
        params _params;
        std::byte _data_buffer[4284]; // 4284 bytes is the size of the EEPROM on the teensy41

        EEPROMInterfaceData_s _eeprom_written_data;
};
#endif // __EEPROMINTERFACE_H__