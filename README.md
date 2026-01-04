# alppad

A simple, minimalistic text editor application built with C++17 and the Qt framework.

## Prerequisites

To build and run this application, you will need:
* **Qt 6.10.1** (specifically for macOS)
* **C++17** or newer
* **CMake 3.20** or newer

## Project Structure

* **Source Code**: Includes logic for note management, main window handling, and custom widgets.
* **UI Files (`.ui`)**: XML definitions for the application's visual layout.
* **Icons Folder**: Contains the graphical assets (icons) used for the notepad interface.
* **Resources (`resources.qrc`)**: The Qt resource system used to bundle the icons into the application binary.

## Build Instructions

### Command Line

1.  **Create a build directory**:
    ```bash
    mkdir build && cd build
    ```

2.  **Configure with CMake**:
    Replace the path below with your actual Qt installation directory. For MacOS, should be something like this:
    ```bash
    cmake .. -DCMAKE_PREFIX_PATH="/Users/your_user/Qt/6.10.1/macos"
    ```

3.  **Build the project**:
    ```bash
    cmake --build .
    ```
### Tracelog
* Jan 2, 2026: XML serialization added for saving notes.
* Jan 5, 2026: Find, replace and regex search utility added. Dealing with MacOS quirks.

### Development Status

This project is a work in progress and will be updated with more features over time.
