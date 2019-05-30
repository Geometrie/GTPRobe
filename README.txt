Welcome to try GTPRobe! This is a software that provides a graphical user interface of AutoGTP program that provides training data for the computer go software Leela Zero.

If you're interested in more information about Leela Zero and AutoGTP, please browse the following website:

zero.sjeng.org

GTPRobe can help you to play Go againt Leela Zero or analyze the Go game records with Leela Zero to improve your strength of the game.

GTPRobe is written in C++ pragramming language with a GUI Library named wxWidgets.

So if you would like to compile GTPRobe, you have to download and install the wxWidgets library first.Please look up the following website:

www.wxwidgets.org

It is not difficult to compile GTPRobe with Visual Studio or Code::Blocks.

If you try to compile GTPRobe, you should create a Win32 GUI empty project and add the files, including.h files, .cpp files, a .rc file, a .ico file and.bmp files.

Don't forget appending include and lib dictionaries of wxWidgets in the setting of your project.

Code::Blocks supports creating a wxWidgets project containing the path of wxWidgets, this maybe make it simpler to compile GTPRobe.

In order to create a more harmonic game running, GTPRobe need not to set the engine path, but you have to put the GTPRobe.exe file in the same dictionary with autogtp.exe

In addition, the file name of “autogtp.exe” is not allowed to change, otherwice GTPRobe cannot find the engine.

If you used command “q” to exit the previous running autogtp, then a file with random name but an extention name of “.sgf” file storing game record would occured.

In order to make sure that you can watch the game playing, before running the engine, please import this .sgf file with the “Open” button in the file menu or toolbar. Otherwise autogtp would delete that sgf file and you could not watch that game running correctly.

In the course of playing a game, you can use the “Undo” or “Redo” function to go backward or forward, even add trying branches in the game, which won't interfere game playing.

But if one game has ended, if you will continue to watch the next game played automatically bu auto gtp, please go the the last step with the “Redo” button, until the dialog with one side reign or game end occurs.

Then press the “new game” button in the file menu or tool bar, and the “Redo” button can be used to persue the progress of the new game. Please keep in mind that do not press the button “New Game”, otherwise the info of the running game will be lost.

If you want to close the engine before a game ends, you can use “Close Engine” button in edit menu or tool bar. This is equivalent to input command “q” in auto gtp, which makes autogtp save the process info, and a new .sgf file will be created. Don't forget to import this file into GTPRobe before playing the game next time.

Due to autogtp will take several seconds to replay “q”, so please wait patiently when you closing the engine or exit the program.

If you want to continue the game playing after you close the engin with the button in edit menu or toolbar, please do not open the engine directionly. You have to open the new .sgf file when you closed the engine, other the last step before you close the engine will be lost in the demostrating gameboard.

Wish every one enjoy the game playing!
