# Harry Potter Invisibility Cloak using C++ and Qt
Read more about it at: https://medium.com/@sahilkgeorge/optimizing-magic-how-i-built-an-invisibility-cloak-for-a-2gb-ram-celeron-laptop-d8b1a94cb97d
## invis-cloak-using-cpp
# NOTE: 
Use Qt Creator for compiling/building/running the program for a seamless expereience unless you are familiar with importing Qt Binaries into your default IDE.
## How to use this project
1. Keep the PC stable and ensure that there in nothing initially infront of camera.
2. Run the project.
3. A window with color, tolerance and capture background will appear, click on "Capture Background" ensuring that there in nothing infront of camera.
4. Adjust the RGB and Tolerance slider for the color of object/sheet to be in range.
5. Enjoy the "Invisiblilty cloak".

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
