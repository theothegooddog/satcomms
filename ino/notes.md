# satcomms INO notes

# CONTENTS
[misc](#misc)/[hardware](#hardware)/[usage](#usage)

## misc

- this is c++
  - specifically ino (or arduino)
  - not python

## hardware

- built for [arduino uno r3](https://docs.arduino.cc/hardware/uno-rev3/) but you can use anything arduino uno that has serial commnication
- uses the FS1000A module ([docs download](https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://content.instructables.com/FUT/M44H/KYR9VTKC/FUTM44HKYR9VTKC.pdf&ved=2ahUKEwiR08eh3s-UAxWfFVkFHTZAOpQQFnoECA0QAQ&usg=AOvVaw3vvIa48ATDWR6ZfUCGHwBN))
- on ports 2, 3, and 4 *(markings: GND on 4, VCC on 3, DATA on 2)*

## usage
- for example testing, plug into a non-serial port for 10 seconds and it will broadcast a test message (literally "test")
- for custom broadcasting, run on a computer, open serial monitor and type your message, followed by a semicolon
