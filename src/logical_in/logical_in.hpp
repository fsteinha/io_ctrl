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
 * @brief class for handling inputs based on HIGH/LOW
 *
 */
class LogicalIn
{
    private:
        EN_LOG_IN_VALUE en_value;
        EN_LOG_IN_MODE  en_get_mode;
        Debounce        *debounce;
        uint16_t (*get_value_hw) ();
        void init();

    public:
        LogicalIn(EN_LOG_IN_MODE en_get_mode,
                  void(*get_value_hw)());
        LogicalIn(EN_LOG_IN_MODE en_get_mode,
                  void(*get_value_hw)(),
                  Debounce *ptr_debounce);
        void trigger(void);
        EN_LOG_IN_VALUE get_value();
};