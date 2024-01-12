#include "debounce.hpp"

/**
 * @brief init function for Debounce class
 *
 */
void Debounce::init(void)
{
    this->en_deb_mode=EN_DEB_MODE_COUNT;
    this->en_deb_state=EN_DEB_STATE_NONE;
    this->u16_time_ms = 0;
    this->u16_count = 0;
    this->u16_count_idx = 0;
    this->u16_time_idx_ms = 0;
    this->u16_time_start_ms = 0;
    this->ptr_time_ms=nullptr;
}

/**
 * @brief Construct a new Debounce:: Debounce object
 *
 * @param en_deb_mode mode of debouncing
 * @param u16_time_ms time limit in case en_deb_mode is EN_DEB_MODE_TIME, default 0
 * @param u16_count count limit in case en_deb_mode is EN_DEB_MODE_COUNT, default 0
 * @param ptr_time_ms pointer for get time in ms, default nullptr
 */
Debounce::Debounce(EN_DEB_MODE en_deb_mode,
                    uint16_t u16_time_ms = 0,
                    uint16_t u16_count = 0,
                    uint16_t (*ptr_time_ms)(void) = nullptr)
{
    this->init();
    this->en_deb_mode = en_deb_mode;
    this->u16_count = u16_count;
    this->u16_time_ms = u16_time_ms;
    this->ptr_time_ms = ptr_time_ms;
}

/**
 * @brief trigger the debouncing
 *
 * @return EN_DEB_STATE
 */

EN_DEB_STATE Debounce::trigger(void)
{
    switch (this->en_deb_state)
    {
        case EN_DEB_STATE_NONE:
        case EN_DEB_STATE_READY:
        {
            if (this->en_deb_mode = EN_DEB_MODE_COUNT)
            {
                this->u16_count_idx = this->u16_count;
            }
            else if ((this->en_deb_mode = EN_DEB_MODE_TIME) &&
                     (this->ptr_time_ms != nullptr))
            {
                this->u16_time_start_ms = this->ptr_time_ms();
            }
            else
            {
                break;
            }
            this->en_deb_state = EN_DEB_STATE_START;
            break;
        }
        case EN_DEB_STATE_START:
        {
            if (this->en_deb_mode = EN_DEB_MODE_COUNT)
            {
                if (this->u16_count_idx == 0)
                {
                    this->en_deb_state = EN_DEB_STATE_READY;
                }
                else
                {
                    this->u16_count_idx--;
                }
            }
            else if (this->en_deb_mode = EN_DEB_MODE_TIME)
            {
                uint16_t u16_time_idx = this->ptr_time_ms();
                if ((u16_time_idx > this->u16_time_start_ms) &&
                    ((u16_time_idx - this->u16_time_start_ms) > this->u16_time_ms))
                {
                    this->en_deb_state = EN_DEB_STATE_READY;
                }
                else if ((u16_time_idx < this->u16_time_start_ms) &&
                         ((uint16_t)(-1) - (this->u16_time_start_ms - u16_time_idx)) > this->u16_time_ms)
                {
                    this->en_deb_state = EN_DEB_STATE_READY;
                }
            }
            break;
        }
    }
}

/**
 * @brief getter for debounce state
 *
 * @return EN_DEB_STATE
 */
EN_DEB_STATE Debounce::get_state()
{
    return this->en_deb_state;
}