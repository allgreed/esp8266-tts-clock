# esp8266-tts-clock

A clock showing time-to-sleep, ESP8266 based 

As a part of my attempts to regulate my sleep cycle I've decided to increase exposure to time. This clock show how much sleep I would get if I went to sleep now.

## Hardware

- Wemos D1 mini + TM1637

### Wiring

```
TM1637 CLK <-> D1
TM1637 DIO <-> D2
```

## Minimal customization to work

This will *not* works as is, you need change the wifi credentials (under `// wifi` section)

I suggest tweaking the time settings `TZ_DIFF_FROM_UTC_IN_HOURS` and `WAKE_UP_HOUR` as well, unless you live in UTC+1 timezone and have same the sleeping schedule as I do.
