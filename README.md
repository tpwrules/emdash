# Installation Instructions

The code can be built both for an included Mac/Windows/Linux simulator and the LPC11C24 ARM microcontroller. Please follow these directions carefully to learn how to build the code. I assume you have a basic knowledge of command line operation.


## Building the Base

Building the base covers downloading the code and installing Python. Python is required to build the various data files.

#### Installing Git

The Git source control system is used to hold the code. You must install the Git client in order to download the code correctly.

* Download and install Git for your operating system from <https://git-scm.com/downloads>.
    * for the Windows installer, the default options are fine
* Clone the source code
    * open a command prompt and change to the directory you want the source to be downloaded to
    * execute `git clone https://github.com/tpwrules/emdash` to get the code

#### Installing Python

The Python scripting language is used to build data files and run the simulator. Python 3.5 or above is required.

* Download and install the latest version of Python 3 for your operating system from <https://www.python.org/downloads/>
    * For the Windows installer, you must check "Add Python to Path" on the first page
    * Otherwise, the default options are fine

#### Installing Python Packages

Some Python packages are required to build the data files and run the simulator. Fortunately, Python makes them easy to install.

* Open up a command prompt.
* Run the command `python -m pip install pypng`
* If python isn't found, close and re-open the command prompt.

#### Testing the Base

Now that the base has been prepared, it's time to test to make sure it works.

* Open a command prompt
* Change directories to the `dashboard` directory within the downloaded code
    * Hint: you can drag that folder into the command prompt instead of typing out its location
* Run the command `build_src_gen.py`. If you see the message `SOURCE GENERATED SUCCESSFULLY`, the base has been successfully built!

## Building for LPC11C24

Building for LPC11C24 requires a working install of the base. It does not require the simulator. I use the free MCUXpresso IDE for development on the LPC11C24. You must install it and import the project in order to deploy the code onto the chip.

#### Installing MCUXpresso
You can download the MCUXpresso installer from [here](https://www.nxp.com/support/developer-resources/software-development-tools/mcuxpresso-software-and-tools/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE?tab=Design_Tools_Tab). Unfortunately, it does require an NXP account.

Run the installer using all the default options.

#### Importing the chip libraries
NXP has provided libraries to use the chip's hardware. These libraries must be imported into the MCUxpresso workspace so that the application software can use them. The easiest way to import them is to create a new project, but cancel creation after the libraries have been imported.

* Open MCUXpresso
* Select File -> New -> Project from the top menu
* Under the MCUxpresso IDE category, select New C/C++ Project and click Next
* Select the LPCXpresso11C24 board and click Next
* Select an LPCOpen - C Project and click Next
* Give the project whatever name you want. It doesn't matter, it won't be saved.
* Click the Import... button to import the chip libraries
* In the Import window, select Browse... next to the Archive entry.
* Choose the LPC11C24 libraries by looking in the LPCOpen folder for the file with `11c24` in its name, seelcting it, and clicking Open. Click next on the Import window.
* Select the `lpc_chip_11cxx_lib` project to import and click Finish.
* Click Cancel on the New Project window. Chip library import is now complete.

#### Importing the code
Now that the chip libraries are available, you can import this project into MCUXpresso.

* Select File -> Import
* Select to import Git -> Projects from Git and click Next
* Select the Existing local repository source and click Next.
* Click Add... and then Browse...
* Select the `emdash` folder in the code you downloaded and click OK.
* Check the `emdash\.git` repository in the results list and click Finish. 
* Select the `emdash` repository in the repository list and click Next twice, then Finish. Code import is now complete.

#### Building the code
Build the code for the chip by selecting the dash_11c24 project in the left pane and clicking the hammer icon in the top bar. If everything works, you will see a blue `Build finished` in the bottom window.

You can then use the green bug icon to program the chip with the code and enter the debugger. The first time you click the button, you will be asked to create a run configuration. Double-click the `C/C++ (NXP Semiconductor)` option in the left pane to create the correct configuration, then click Debug in the bottom to start it. Once this is done, the green button will launch the correct configuration automatically.

## Building for Simulation
A custom simulator is included which runs the same code that is downloaded on the chip. Running the simulator requires a working install of the base, but does not require MCUXpresso or the other LPC11C24 stuff. It also requires a compatible install of the Visual C++ Build Tools, which use several gigabytes of disk space.

#### Installing Python Packages
The simulator requires some additional Python packages to operate.

* Open a command prompt
* Run the command `python -m pip install cffi numpy pygame`

#### Installing Visual C++ Build Tools
The build tools provide the compiler used to compile the application for simulation. You try to compile the application to see if the tools are already installed. If they are not, an installation is necessary.

* Open a command prompt
* Change directories to the `dashboard/pc` directory inside the code
* Run the command `build_pc_app.py`. If there are no errors, you're finished building for simulation
* If it says you need to install Visual C++ 14.0, a compatible version of the build tools could not be found.
* Download the installer at <https://landinghub.visualstudio.com/visual-cpp-build-tools>.
* Once the main installer loads, check 'Visual C++ build tools' under the 'Workloads' tab and click Install
* Wait quite a while. Once finsihed, try to run the script again. If it says `PC APP BUILT SUCCESSFULLY`, you've successfully built the simulator and you should be able to run it by running `pc_app.py`.