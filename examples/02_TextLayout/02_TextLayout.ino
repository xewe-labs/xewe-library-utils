// XeWeUtils (mid): box drawing and text layout over plain Serial.
// These are the primitives XeWeSerial builds its headers and tables from,
// so you can render a framed panel without pulling in another library.
#include <XeWeUtils.h>

constexpr uint16_t WIDTH = 44;

// One framed row: | <margin> content padded to the field <margin> |
static void row(std::string_view text, char align = 'l') {
    Serial.println(xewe::str::compose_box_line(text, "|", WIDTH - 4, 1, 1, align).c_str());
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // +------...------+   fill is cycled, so "-=" would work too
    const std::string rule = xewe::str::make_rule_line(WIDTH, "-", "+");

    Serial.println(rule.c_str());
    row("XeWe Text Layout", 'c');
    Serial.println(rule.c_str());

    // wrap_words respects word boundaries; wrap_fixed chops at exactly N chars
    for (const auto& line : xewe::str::wrap_words("compose_box_line pads each chunk into the field width", WIDTH - 6)) {
        row(line);
    }

    Serial.println(xewe::str::make_spacer_line(WIDTH, "|").c_str());   // blank row, edges kept

    for (const auto& line : xewe::str::wrap_fixed("0123456789ABCDEF0123456789ABCDEF", 16)) {
        row(line, 'c');
    }

    Serial.println(rule.c_str());

    // align_into is what does the padding inside a field
    row(xewe::str::align_into("left", 12, 'l') + "|" +
        xewe::str::align_into("centre", 12, 'c') + "|" +
        xewe::str::align_into("right", 12, 'r'));

    Serial.println(rule.c_str());

    // repeat_pattern cycles a multi-character pattern to an exact length
    Serial.println(xewe::str::repeat_pattern("-=", WIDTH).c_str());

    const uint8_t mac[6] = {0x24, 0x6F, 0x28, 0x01, 0xAB, 0xCD};
    Serial.print(xewe::str::format("to_hex: %s\n", xewe::str::to_hex(mac, sizeof(mac)).c_str()).c_str());   // 246F2801ABCD
}

void loop() {}
