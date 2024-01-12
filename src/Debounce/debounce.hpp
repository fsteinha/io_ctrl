#include <cstddef>
#include <cstdint>

typedef enum
{
    EN_DEB_MODE_COUNT,
    EN_DEB_MODE_TIME
}EN_DEB_MODE;

typedef enum
{
    EN_DEB_STATE_NONE,
    EN_DEB_STATE_START,
    EN_DEB_STATE_READY,
}EN_DEB_STATE;

class Debounce
{
    private:
        EN_DEB_MODE en_deb_mode;
        EN_DEB_STATE en_deb_state;
        uint16_t u16_time_ms;
        uint16_t u16_count;

        uint16_t u16_time_idx_ms;
        uint16_t u16_time_start_ms;
        uint16_t u16_count_idx;

        uint16_t (*ptr_time_ms)(void);
        void init();
    public:
        Debounce(EN_DEB_MODE en_deb_mode,
                 uint16_t u16_time_ms,
                 uint16_t u16_count,
                 uint16_t (*ptr_time_ms)(void));

        EN_DEB_STATE trigger(void);
        EN_DEB_STATE get_state(void);

};
