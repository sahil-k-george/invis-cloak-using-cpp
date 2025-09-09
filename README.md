# Harry Potter Invisibility Cloak using C++ and Qt
Read more about it at: 
## invis-cloak-using-cpp
# NOTE: 
Use Qt Creator for compiling/building/running the program for a seamless expereience unless you are familiar with importing Qt Binaries into your default IDE.
## Concepts:
A. Programming & Development Concepts

  1. C++ with Qt Framework – instead of the common Python + OpenCV approach.

  2. Qt Binaries/Classes – using built-in Qt functionality for handling multimedia and UI instead of relying on external libraries.

  3. Multithreading – splitting heavy operations (like frame processing) across threads to prevent UI freeze and crashes.

  4. Timers & Event Loop Control – creating a custom “frame-skip” mechanism by using timers to control when to process/skip frames.

B. Computer Vision Concepts

  1. Real-time Camera Input Handling – accessing and displaying webcam streams within a Qt application.

  2. Frame Capture & Storage – capturing background images and storing them for later reference.

  3 Chroma Keying (Color Keying) – removing a specific color range from live video (basis of the invisibility cloak).

  4. Sliders for Thresholding – providing UI controls to dynamically select and fine-tune which color gets keyed out.

