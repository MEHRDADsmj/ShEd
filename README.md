# ShEd - A Shader Editor
ShEd, named after the phrase "Shader Editor", is a simple and lightweight shader editing tool used for creating basic GLSL shaders and exporting them as .glsl files.
Despite the wide timespan of the commits on git, ShEd was made during a small amount of time. It utilizes an easy-to-use interface with almost no prerequisites, so shader enthusiasts can just run the program and start writing shaders.



## Technical Overview
Originally created as a university project, ShEd uses the Qt framework to provide users with easy-to-use UI, understandable source code, and maximum performance.<br/>
ShEd makes good use of Qt's famous "Signals & Slots" to allow the program to broadcast events with maximum speed and reliability, also making it super easy to extend and develop. UI and core modules work in a layered architecture, while the core itself and shader compiling process are implemented linearly to achieve the best compiling and error detection speed.<br/>
ShEd uses GLSL shaders, which is the standard shading language for OpenGL and almost every GPU available on the market. Shaders made using ShEd can be easily modified to be used in game engines such as Unity and Unreal Engine. With the efficiency of ShEd, you can easily detect the performance-heavy parts of the shader without worrying about whether it is the shader or the program that is lagging.<br/>
ShEd also provides its users with an FPS counter to show how performant their shaders are and helps detect syntax errors using its "On-Compile Error Detection" which is almost performing as well as a real-time error detection system.<br/>
In the benchmarks performed by myself comparing ShEd and SHADERed, a similar shader editing app, running shader "Cube", which is available in the samples directory in GitHub, ShEd performed around 6-7% faster than its competitor. ShEd also requires no preconfig or setup to start creating a shader for beginners, making it relatively easier for those who want to start learning shader programming or just want to make quick edits to their code.<br/>
ShEd supports file extensions such as .txt, .glsl, and .shader and can export files as .glsl and .shader. ShEd supports OpenGL 3.3 and later and works using vertex and fragment (pixel) shaders.
