#include <EEPROMInterface.h>
#include <EEPROM.h>
#include <cmath>
#include <cstring>
#include <bit>

void EEPROMInterface::init(bool reset_eeprom)
{
    // we know that the first 2 bytes tell us the size of the previously written data
    std::byte size_data[2];
    
    // if the reset eeprom flag is set, the eeprom previously written data will stay initialized to all zeros
    // so all previous data will be lost if there was any written as the new sums will not include this previous data.
    if(!reset_eeprom)
    {
        uint16_t written_size;
        
        size_data[0] = static_cast<std::byte>(EEPROM.read(0));
        size_data[1] = static_cast<std::byte>(EEPROM.read(1));
        memcpy(&written_size, size_data, 2);

        // proceed to read out all of the existing data

        for(int i = 2; i < written_size; i++)
        {
            _data_buffer[i] = static_cast<std::byte>(EEPROM.read(i));
        }

        memcpy(&_eeprom_written_data, _data_buffer, written_size);
    }
    // go ahead and updating the written size to the current struct size as we are now finished using the data
    uint16_t new_write_size = sizeof(LowLevelStatData_s);
    memcpy(size_data, &new_write_size, 2);
    EEPROM.write(0, static_cast<uint8_t>(size_data[0]));
    EEPROM.write(1, static_cast<uint8_t>(size_data[1]));
}

void EEPROMInterface::update_eeprom(const SharedCarState_s &car_state)
{

    if(car_state.systick.millis - _last_write_time_millis > _params.write_interval_ms)
    {
        // distanc_m current_session_distance = car_state.low_level_stats.session_distance;

        // get the difference between the last written distance to the previous driven meters;
        
        auto diff = static_cast<uint32_t>(abs(std::round(car_state.low_level_stats.session_distance)) - _last_written_distance_m);
        _eeprom_written_data.current_driven_m += diff;
        memcpy(_data_buffer, &_eeprom_written_data, sizeof(EEPROMInterfaceData_s));
        size_t byte_size_to_write = sizeof(EEPROMInterfaceData_s);
        for(size_t i = 0; i < byte_size_to_write; i++)
        {
            EEPROM.write(i+2, static_cast<uint8_t>(_data_buffer[i]));
        }

        _last_written_distance_m = car_state.low_level_stats.session_distance;
        _last_write_time_millis = car_state.systick.millis;
    }
}