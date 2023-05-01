
# ESP32 - M1

The project is focused on learning new technologies while making it a fun experience. Here, I will gather every software idea I can think of and create tools that will make it easier to develop new applications in the future. All the drivers are written in C++ and utilize the ESP-IDF framework.

This repository has been created for individuals who are struggling with ESP-IDF and need access to code examples. I hope that this will be a helpful resource for them in the future.

![Logo](data:image/png;base64,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)


## Authors

- [@Daironn](https://github.com/Daironn)


## Documentation

Documentation will be under development here:

[Documentation](https://github.com/Daironn/ESP32-M1-Doc)


## Roadmap

- Finishing button driver implementation

- Adding new driver to handle LCD Display
