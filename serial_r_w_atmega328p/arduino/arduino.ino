#define SIZE 64
uint8_t buffer[SIZE];
uint8_t* buffer_w = buffer;
uint8_t* buffer_r = buffer;

uint8_t is_buffer_empty() {
    return buffer_r == buffer_w;
}

uint8_t read() {
    uint8_t c = *buffer_r;
    buffer_r++;
    if (buffer_r >=  buffer + SIZE) {
        buffer_r = buffer;
    }
    return c;
}

void write(uint8_t c) {
    *buffer_w = c;
    buffer_w++;
    if (buffer_w >= buffer + SIZE) {
        buffer_w = buffer;
    }
}
void setup() {
    Serial.begin(9600);
}


void loop() {
    if (Serial.available() > 0) {
        write(Serial.read());
    }
    if (!is_buffer_empty()) {
        Serial.write(read());
    }
}

