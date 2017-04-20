# Arduino Codes

These codes were used to program arduinos (mega type) using C code with some arduino functions. Each code programs a type of i/o device for sending or receiving data from the main platform device (the PSoC device in this configuration).

- **arduino_pid_car.c** : contains the pid controller for the simulated car velocity control example. This code does not use arduino function so it is compatible with other microcontroller solutions.

- **arduino_pid_water_level.c** : contains the pid controller for the simulated water level control example. This code does not use arduino function so it is compatible with other microcontroller solutions.

- **driver_PWM.c** : makes the arduino a device that generates a PWM output based on a value sent by the main component (PSoC device) using a serial connection.

- **valve_output.c** : makes the arduino a device that generates an analogic 0V~5V output based on a value sent by the main component (PSoC device) using a serial connection.

In case of questions, contact me at: isaacdiego@gmail.com
