# Harry Potter Invisibility Cloak using C++ and Qt
Read more about it at: https://medium.com/@sahilkgeorge/optimizing-magic-how-i-built-an-invisibility-cloak-for-a-2gb-ram-celeron-laptop-d8b1a94cb97d
## invis-cloak-using-cpp
# NOTE: 
Use Qt Creator for compiling/building/running the program for a seamless expereience unless you are familiar with importing Qt Binaries into your default IDE.

## How to Run

### 1. Clone the Repository

### 2. Install Dependencies
  Qt 6.x (or later) → Make sure you have Qt installed (with Qt Creator recommended).

  CMake → Minimum version 3.16+

  C++ Compiler → MinGW (Windows) or GCC/Clang (Linux/macOS)

### 3. Build the Project
  Using CMake directly:
```
mkdir build
cd build
cmake ..
cmake --build .
```
  Or, if using Qt Creator:

  Open the project (CMakeLists.txt) in Qt Creator.

  Select your kit (e.g., Desktop Qt 6.9.2 MinGW 64-bit).

  Click Configure Project.

  Hit Build & Run.

### 4. Run the Program
  Once compiled, launch the binary:

### Usage
  Launch the program.

  Capture Background → take a snapshot of your background (without the cloak).

  Adjust the sliders to fine-tune which color gets keyed out.
  
  Wrap yourself in the cloak → and disappear! 

⚡ Note: This project was tested on an Intel Celeron N3050 with 2GB RAM, but it should run faster on more capable hardware.

## Concepts Learned

Through building this project, I explored and strengthened several areas of programming and computer vision:

### 🔹 Programming & Development
- C++ with Qt Framework (instead of the typical Python + OpenCV route)
- Qt Binaries/Classes for multimedia handling and UI design
- Event-driven programming and timer-based controls
- Multithreading for smoother performance and crash prevention

### 🔹 Computer Vision
- Real-time camera input and video frame processing
- Frame capture & background storage for effect layering
- Chroma keying (color removal) techniques
- Dynamic threshold adjustment with UI sliders

### 🔹 Optimization Techniques
- Resolution scaling (down to 360p) to reduce processing overhead
- Frame skipping logic to balance speed and smoothness
- Manual performance tuning for **low-spec devices** (Intel Celeron N3050, 2GB RAM)

### 🔹 Problem-Solving & Growth
- Debugging system crashes and lock-ups under heavy load
- Breaking down a complex task into smaller, manageable steps
- Using AI tools to clarify documentation, learn unfamiliar Qt classes, and explore edge cases
- Documenting the entire journey as a **technical story** for better communication and knowledge sharing
