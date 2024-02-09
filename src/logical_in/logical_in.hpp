#include <cstddef>
#include <cstdint>

#include "debounce.hpp"
/**
 * @brief enum for trigger mode used in class LogicalIn
 *
 */
typedef enum
{
    EN_MODE_POLL,
    EN_MODE_TRG
}EN_LOG_IN_MODE;

/**
 * @brief enum for the status for a logical input, used by class LogicalIn
 *
 */
typedef enum
{
    EN_VAL_NONE = -1,
    EN_VAL_LOW  = 0,
    EN_VAL_HIGH = 1
}EN_LOG_IN_VALUE;

/**
 * @brief class for handling one input based on HIGH/LOW value
 *
 */
class LogicalIn
{
    private:
        //! store value
        EN_LOG_IN_VALUE en_value;
        //! mode how the input shall read
        EN_LOG_IN_MODE  en_read_mode;
        //! debounce object, default nullptr
        Debounce        *debounce;
        //! callback pointer for reading the input from hardware
        uint16_t (*get_value_hw) ();
        //! init function, used from constructors
        void init();
        //! read input and convert
        EN_LOG_IN_VALUE read_input();

    public:
        //! constructor without debounce object
        LogicalIn(EN_LOG_IN_MODE en_read_mode,
                  uint16_t (*get_value_hw)(void));
        //! constructor with debounce object
        LogicalIn(EN_LOG_IN_MODE en_read_mode,
                  uint16_t (*get_value_hw)(void),
                  Debounce *ptr_debounce);
        //! trigger function - this function is called from outside to read the input
        //! the pointer can used for interrupt functions
        void trigger(void);
        //! getter for stored value
        EN_LOG_IN_VALUE get_value();
};