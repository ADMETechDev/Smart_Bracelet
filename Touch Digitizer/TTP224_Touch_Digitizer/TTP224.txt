The TTP224 is a capacitive touch digitizer module with 4 touch-sensitive keys. It communicates using an I2C interface and can be easily interfaced with an ESP32.

This example code reads the touch status from the TTP224 module and prints the status of each touch key to the Serial Monitor.

***Explanation***

Initialization:

Wire.begin(21, 22): Initializes the I2C communication with the ESP32. GPIO 21 is used for SDA, and GPIO 22 is used for SCL.
Reading Data:

Wire.beginTransmission(TTP224_ADDR): Begins communication with the TTP224 module.

Wire.write(0x00): Requests data from the status register (0x00).

Wire.endTransmission(): Ends the communication with the module.

***Requesting Data***

Wire.requestFrom(TTP224_ADDR, 1): Requests 1 byte of data from the module.

Wire.read(): Reads the touch status byte.

Processing Data:
The touch data byte is read, where each bit represents the status of a touch key. The code checks each bit to determine if a key is touched.

Output:
The touch data and the status of each touch key are printed to the Serial Monitor.

***Notes***

I2C Address: The default I2C address for the TTP224 module is 0x5D. If your module uses a different address, adjust TTP224_ADDR accordingly.

Touch Data: Each bit of the touch data byte corresponds to a touch key. If a bit is set, the corresponding key is touched.

Pull-up Resistors: Ensure that the I2C lines (SDA and SCL) have pull-up resistors if your module or setup doesn’t include them.