#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <TM1637Display.h>
#include <NTPClient.h>

#include "business.h"


// hard technical
const int CLK_DISPLAY_PIN = 5; // D1
const int DIO_DISPLAY_PIN = 4; // D2
const int COLON_DISPLAY_BITMASK = 0b01000000;

// soft technical
const int SERIAL_BAUD = 115200;
const int NTP_UPDATE_INTERVAL_IN_MINUTES = 60;
const int DISPLAY_MAX_BRIGHTNESS = 0x0a;
const int WIFI_CONNECTION_CHECK_INTERVAL = 500; // miliseconds
const int MAIN_LOOP_DELAY = 5000; // miliseconds

// derivative
const int NTP_UPDATE_INTERVAL = NTP_UPDATE_INTERVAL_IN_MINUTES * 60 * 1000; // miliseconds
const int TZ_DIFF_FROM_UTC = TZ_DIFF_FROM_UTC_IN_HOURS * 60 * 60; // seconds

TM1637Display display(CLK_DISPLAY_PIN, DIO_DISPLAY_PIN);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


void setup()
{
    timeClient.setTimeOffset(TZ_DIFF_FROM_UTC);
    timeClient.setUpdateInterval(NTP_UPDATE_INTERVAL); // 1h in miliseconds

    Serial.begin(SERIAL_BAUD);
    WiFi.begin(SSID, PASSWORD);
    timeClient.begin();

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(WIFI_CONNECTION_CHECK_INTERVAL);
    }
    Serial.println("\nconnected!");

    display.setBrightness(DISPLAY_MAX_BRIGHTNESS);
}


void loop()
{
    timeClient.update();

    Moment m = Moment(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());

    Timedelta t = computeRemainingSleepTime(m);

    display.showNumberDecEx(formatTimedeltaForDisplay(t), 0 | COLON_DISPLAY_BITMASK);

    delay(MAIN_LOOP_DELAY);
}
