// XeWeUtils: string and validation helpers
#include <XeWeUtils.h>

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println(xewe::str::capitalize("kitchen lights").c_str());   // Kitchen Lights

    uint16_t minutes = 0;
    if (xewe::str::parse_time("07:30", minutes)) {
        Serial.printf("07:30 is %u minutes after midnight\n", minutes);
    }

    auto brightness = xewe::validate<int>("180", 0, 255);
    if (brightness) Serial.printf("valid brightness: %d\n", *brightness);

    for (const auto& line : xewe::str::wrap_words("wrap this sentence into short lines", 12)) {
        Serial.println(line.c_str());
    }
}

void loop() {}
