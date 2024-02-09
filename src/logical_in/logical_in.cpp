#include "logical_in.hpp"

/**
 * @brief Construct a new Logical In:: LogicalIn object
 *
 * @param en_get_mode   mode, poll or trigger
 * @param get_value_hw  pointer to hardware function for reading the input
 */
LogicalIn::LogicalIn(EN_LOG_IN_MODE en_get_mode,
                     uint16_t (*get_value_hw)(void))
{
    this->init();
    this->get_value_hw=get_value_hw;
    this->en_read_mode = en_get_mode;
}

/**
 * @brief Construct a new Logical In:: LogicalIn object with debouncing
 *
 * @param en_get_mode   mode, poll or trigger
 * @param get_value_hw  pointer to hardware function for reading the input
 * @param ptr_debounce  pointer to debounce object
 */
LogicalIn::LogicalIn(EN_LOG_IN_MODE en_get_mode,
                     uint16_t (*get_value_hw)(),
                     Debounce *ptr_debounce)
{
    this->init();
    this->en_read_mode = en_get_mode;
    this->get_value_hw=get_value_hw;
    this->debounce = ptr_debounce;
}

/**
 * @brief helper function for init a new LogicalIn object
 *
 */
void LogicalIn::init()
{
    this->debounce = nullptr;
    this->en_value = EN_VAL_NONE;
    this->en_read_mode = EN_MODE_POLL;
    this->get_value_hw = nullptr;
}

/**
 * @brief getter for the in value
 *
 * @return EN_LOG_IN_VALUE
 */
EN_LOG_IN_VALUE LogicalIn::get_value()
{
    return this->en_value;
}

/**
 * @brief function for get the in value
 *
 */
void LogicalIn::trigger()
{
    if (this->get_value_hw != nullptr)
    {
        if (this->debounce != nullptr)
        {
            this->debounce->trigger();
            if (this->debounce->get_state() == EN_DEB_STATE_READY)
            {
                this->en_value = this->read_input();
            }
        }
        else
        {
            this->en_value = this->read_input();
        }
    }
    else
    {
        this->en_value = EN_VAL_NONE;
    }
}

/**
 * @brief helper function to read input from the hardware and convert this in EN_LOG_IN_VALUE
 *
 * @return EN_LOG_IN_VALUE
 */
EN_LOG_IN_VALUE LogicalIn::read_input()
{
    uint16_t u16_value;
    u16_value = this->get_value_hw();

    if (u16_value == 0)
        return EN_VAL_LOW;
    else if (u16_value == 1)
        return EN_VAL_HIGH;

    return EN_VAL_NONE;
}