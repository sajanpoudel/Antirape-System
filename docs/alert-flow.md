# What happens during an alert

1. The watch sends the byte `a` over the 433 MHz link when the button is pressed.
2. `loop()` receives it with `driver.recv()` and checks it against `ALERT_SIGNAL`.
3. `send1()` texts the rescue message to every number in `contacts`, with `SMS_GAP_MS` between messages.
4. `sendcall()` dials the last registered number.
5. `output()` writes the warning on the LCD and `blinkAlertLight()` flashes the light `BLINK_COUNT` times.
