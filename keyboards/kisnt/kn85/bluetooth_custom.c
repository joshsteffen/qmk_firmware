#include "bluetooth.h"
#include "quantum.h"

enum kn85_bt_cmd {
    CMD_REPORT_HID      = 0x91, // TODO: this might only be supported in 2.4GHz mode
    CMD_REPORT_KEYBOARD = 0xA1,
    CMD_REPORT_NKRO     = 0xA2,
    CMD_REPORT_CONSUMER = 0xA3,
    CMD_REPORT_SYSTEM   = 0xA4,
    CMD_REPORT_FN       = 0xA5,
    CMD_CONTROL         = 0xA6,
    CMD_REPORT_MOUSE    = 0xA8,
    CMD_SET_NAME        = 0xA9,

    CMD_LED_STATE = 0x5A,
    CMD_5B        = 0x5B, // TODO: name
};

enum kn85_bt_control_cmd {
    CTRL_00            = 0x00, // TODO: name
    CTRL_MODE_USB      = 0x11,
    CTRL_MODE_2P4GHZ   = 0x30,
    CTRL_MODE_BT1      = 0x31,
    CTRL_MODE_BT2      = 0x32,
    CTRL_MODE_BT3      = 0x33,
    CTRL_ENTER_PAIRING = 0x51,
};

enum kn85_bt_5b_cmd {
    CMD_5B_23 = 0x23, // TODO: name
    CMD_5B_32 = 0x32, // TODO: name
};

static const uint8_t ACK[] = {'a', '\r', '\n'};

static uint8_t led_state;
static uint8_t cmd_checksum;

static void cmd_begin(uint8_t cmd) {
    cmd_checksum = cmd;
    uprintf("cmd_begin %x\n", cmd);
    sdPut(&SD2, cmd);
}

static void cmd_put(uint8_t byte) {
    cmd_checksum += byte;
    uprintf("cmd_put %x\n", byte);
    sdPut(&SD2, byte);
}

static void cmd_write(const uint8_t *data, size_t len) {
    uprintf("cmd_write");
    for (size_t i = 0; i < len; i++) {
        uprintf(" %02x", data[i]);
        cmd_checksum += data[i];
    }
    uprintf("\n");
    sdWrite(&SD2, data, len);
}

static void cmd_end(void) {
    uprintf("cmd_end %x\n", cmd_checksum);
    sdPut(&SD2, cmd_checksum);
}

static void handle_ack(void) {
    uprintf("got ack\n");
}

static void handle_cmd(const uint8_t *cmd) {
    uprintf("got cmd %x\n", cmd[0]);

    bool ack = true;

    switch (cmd[0]) {
        case CMD_LED_STATE:
            led_state = cmd[1];
            break;
        default:
            break;
    }

    if (ack) {
        sdWrite(&SD2, ACK, sizeof(ACK));
    }
}

static void set_name(const char *name) {
    size_t len = strlen(name);
    cmd_begin(CMD_SET_NAME);
    cmd_put((uint8_t)len);
    cmd_write((const uint8_t *)name, len);
    cmd_end();
}

void kn85_bt_enter_pairing(void) {
    cmd_begin(CMD_CONTROL);
    cmd_put(CTRL_MODE_BT1);
    cmd_end();
    cmd_begin(CMD_CONTROL);
    cmd_put(CTRL_ENTER_PAIRING);
    cmd_end();
}

void bluetooth_init(void) {
    SerialConfig serial_config = {
        .speed           = 115200,
        .UART_WordLength = UART_WordLength_8b,
    };
    sdStart(&SD2, &serial_config);

    cmd_begin(CMD_CONTROL);
    cmd_put(CTRL_MODE_BT1);
    cmd_end();

    set_name("Hello");
}

void bluetooth_task(void) {
    static uint8_t receive_buf[32];
    static uint8_t receive_buf_len;

    while (!sdGetWouldBlock(&SD2) && receive_buf_len < sizeof(receive_buf)) {
        receive_buf[receive_buf_len++] = sdGet(&SD2);
    }

    if (receive_buf_len < 3) {
        return;
    }

    if (memcmp(receive_buf, ACK, sizeof(ACK)) == 0) {
        handle_ack();
    } else if (receive_buf[0] + receive_buf[1] == receive_buf[2]) {
        handle_cmd(receive_buf);
    }

    receive_buf_len -= 3;
    memmove(receive_buf, receive_buf + 3, receive_buf_len);
}

bool bluetooth_is_connected(void) {
    return true;
}

bool bluetooth_can_send_nkro(void) {
    return true;
}

uint8_t bluetooth_keyboard_leds(void) {
    return led_state;
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
    cmd_begin(CMD_REPORT_KEYBOARD);
    cmd_write(&report->mods, 8); // TODO: is this too gross?
    cmd_end();
}

void bluetooth_send_nkro(report_nkro_t *report) {
    cmd_begin(CMD_REPORT_NKRO);
    cmd_write(&report->bits[1], 14);
    cmd_end();
}

void bluetooth_send_mouse(report_mouse_t *report) {
    cmd_begin(CMD_REPORT_MOUSE);
    cmd_put(report->buttons);
    cmd_put(report->x);
    cmd_put(report->y);
    cmd_put(report->v);
    cmd_put(report->h);
    cmd_end();
}

void bluetooth_send_consumer(uint16_t usage) {
    cmd_begin(CMD_REPORT_CONSUMER);
    cmd_put(usage & 0xff);
    cmd_put(usage >> 8);
    cmd_end();
}

void bluetooth_send_system(uint16_t usage) {
    cmd_begin(CMD_REPORT_SYSTEM);
    cmd_put(usage);
    cmd_end();
}

void bluetooth_send_raw_hid(uint8_t *data, uint8_t length) {}
