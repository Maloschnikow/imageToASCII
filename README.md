# imageToASCII
### Description
Transfers image files to ASCII characters and creates a HTML (and CSS) file with colored characters

This program uses parts of the following libary: https://github.com/nothings/stb

### Installation

#### Direct Download

Choose a release version from the github page (https://github.com/Maloschnikow/imageToASCII) and download it.

#### From source code
Download the repository\
`git clone https://github.com/Maloschnikow/imageToASCII.git`

Navigate into the folder and create a "build" folder\
`cd imageToASCII`\
`mkdir build`

Run cmake\
`cmake -S src/ -B build/`

Navigate into the build folder and make (compile)\
`cd build`\
`make`

The compiled binary file "imageToASCII" should now be in the build folder



### Usage
Linux bash: `./imageToASII <path to image> <path to config>`\
Example: `./imageToASCII ../rcs/example.png ../example_config.txt`\
If a configuration file is not provided, the program will try to read a config.txt file
If the configuration file is not set up properly, the program will ask you to override the given config file with a standard configuartion.

### Config file
A configuration file needs to hold the following definitions:

**newWidth**=\<Integer>\
**brightnessType**=\<LUMINANCE/AVERAGE> (LUMINACE more realistic)\
**brightnessBoost**=\<Integer> (Standard: 1)\
**ASCII**=<String of characters, which will represent the image> (Darkest on left side and brightest on right side. Note that the darkest character should always be a space character. Example: .,:;!?$#@)\

There are also example configuration files provided.
