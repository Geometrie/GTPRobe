#ifndef INTERNATIONAL_H
#define INTERNATIONAL_H
#define LANGUAGE_CHINESE_SIMPLIFIED
#ifdef LANGUAGE_CHINESE_SIMPLIFIED
#define STR_NEW "新对局"
#define STR_HANDICAP "让子对局"
#define STR_HANDICAP_NUM "设置让子数"
#define STR_OPEN "打开"
#define STR_SAVE "保存"
#define STR_EXIT "退出"
#define STR_BACKWARD "撤消"
#define STR_FORWARD "重做"
#define STR_SEND_COMMAND "发送命令"
#define STR_SELECT_ENGINE "选择引擎"
#define STR_RUN_ENGINE "启动引擎"
#define STR_CLOSE_ENGINE "关闭引擎"
#define STR_RESULT "计算胜负"
#define STR_INPUT_COMMAND "输入命令"
#define STR_STEP "显示棋步序号"
#define STR_COORDINATE "棋盘坐标"
#define STR_COORD_NULL "隐藏坐标"
#define STR_COORD_NET "网棋客户端坐标"
#define STR_COORD_NUM "纯数字坐标"
#define STR_COORD_SGF "SGF字母坐标"
#define STR_COORD_GTP "GTP协议坐标"
#define	STR_SET_GAMEBOARD_COLOR "设置棋盘颜色"
#define STR_MANUAL "使用说明"
#define STR_ABOUT "关于GTPRobe"
#define STR_FILE "文件"
#define STR_EDIT "编辑"
#define STR_VIEW "视图"
#define STR_LINK "连接"
#define STR_HELP "帮助"
#define STR_NO_ENGINE "引擎未运行"
#define STR_TIP "提示"
#define STR_ADD_BRANCH_INQUIRY "确定增加分支么？"
#define STR_DELETE_BRANCH_INQUIRY "确定删除分支么？"
#define STR_CURRENT_SITUATION "当前局势"
#define STR_BLACK_RESIGN "黑认输，白中盘胜"
#define STR_WHITE_RESIGN "白认输，黑中盘胜"
#define STR_BLACK_OWN "黑领先%.1f"
#define STR_WHITE_OWN "白领先%.1f"
#define STR_DISCARD_RECORD_INQUIRY "检测到对局信息，确定要丢弃么？"
#define STR_CLOSE_ENGINE_INQUIRY "确定关闭引擎么？"
#define STR_CHANGE_PATH "检测到你修改了引擎的路径，是否保存？"
#define STR_RESTART_ENGINE "引擎崩溃，正在重启"
#define STR_ENGINE_OPENING "引擎正在启动，请耐心等待"
#define STR_ENGINE_AVAILABLE "引擎已启动"
#define STR_ENGINE_CLOSING "引擎正在关闭"
#define STR_VERSION "当前版本：1.01 测试版"
#define STR_CLOSE "关闭"
#define STR_MOVE_TURN "着子权"
#define STR_PRISONERS "提子"
#define STR_PASS "放弃一手"
#define STR_RESIGN "认输"
#define STR_GAME_PROCESS "对局进程"
#define STR_DIRECTION "欢迎试用GTPRobe！这是一个用来为人工智能围棋软件LeelaZero训练权重跑谱的程序AutoGTP提供图形界面的程序。\n\n\
如果你想了解关于LeelaZero和AutoGTP跑谱更多的信息，请访问下面的网址：\n\n\
zero.sjeng.org\n\n\
LZGTP可以帮助你使用AutoGTP跑谱，让跑谱工作不那么枯燥。\n\n\
LZRobe是基于C++语言写的，并使用了一个叫wxWidgets的图形界面库。\n\n\
所以如果你想编译LZRobe，你需要先下载并配置wxWidgets库，请浏览下在的网址：\n\n\
www.wxwidgets.org\n\n\
使用Visual Studio或者Code::Blocks编译GTPRobe并不困难。\n\n\
如果你想试着编译LZRobe，首先要建立一个基于Win32图形用户界面的项项目，然后把.h文件、.cpp文件，一个.rc文件，一个.ico文件和.bmp文件包含进去。\n\n\
记得在工程设置中把wxWidgets的包含文件和库文件的路径加进去。\n\n\
Code::Blocks支持创建一个wxWidgets项目，自动包含wxWidgets的相关路径，这样也许可以简化编译流程。\n\n\
在你成功编译好程序以后，告诉你如何用GTPRobe。\n\n\
为了让跑谱过程更和谐，GTPRobe不必再设置跑谱引擎路径，但你需要把GTPRobe.exe放到与autogtp.exe同一个目录下。\n\n\
另外，autogtp.exe的文件名也不能改，否则会导致GTPRobe找不到引擎。\n\n\
你以前跑的autogtp.exe如果使用的是q命令退出，那在同一目录下会生成一个文件名随机，但扩展名是.sgf的棋谱保存文件。\n\n\
为了保证你顺利观看跑谱，在打开引擎之前，一定要先使用文件菜单或者工具栏里的“打开”按键导入那个.sgf文件，否则autogtp在导入它的以后会把它删掉，你无法正常观看跑谱。\n\n\
在跑谱的过程中，你也可以使用“撤消”或者“重做”的功能前进或者后退，或者在里面试下，这个不影响跑谱。\n\n\
但如果一局跑谱结束以后，如果你想再看autogtp自动进行的下一局跑谱，请务必先用菜单或工具栏里的“重做”键跑到本谱的最后一步，直到出现一方认输或者棋局结束的对话框。\n\n\
然后点一下文件菜单或工具栏里的“新对局”，即可使用“重做”键来追随跑新谱的进度了。注意没跑完的谱切不能点“新对局”，否则会丢失没跑完的棋谱信息！\n\n\
如果一谱没有跑完，你想要关闭引擎，可以使用编辑菜单或工具栏里的“关闭引擎”，相当于在autogtp里输入命令“q”，autogtp会自动保存进度，也会有个新的“.sgf”文件出现，下次借助GTPRobe跑谱的时候不要忘记导入。\n\n\
需要注意的是，由于autogtp对“q”的反应需要几秒到十几秒的时间，所以关闭跑谱引擎或者退出程序的时候，一定要耐心等待一会儿。\n\n\
祝大家跑谱愉快！\n\n"
#else
#define STR_NEW "new"
#define STR_HANDICAP "handicap game"
#define STR_HANDICAP_NUM "handicap number"
#define STR_OPEN "open"
#define STR_SAVE "save"
#define STR_EXIT "exit"
#define STR_BACKWARD "undo"
#define STR_FORWARD "redo"
#define STR_SEND_COMMAND "send command"
#define STR_SELECT_ENGINE "select engine"
#define STR_RUN_ENGINE "run engine"
#define STR_CLOSE_ENGINE "close engine"
#define STR_RESULT "calculate result"
#define STR_INPUT_COMMAND "input command"
#define STR_STEP "show step index"
#define STR_COORDINATE "game board coordinates"
#define STR_COORD_NULL "hide coordinates"
#define STR_COORD_NET "net client coordinates"
#define STR_COORD_NUM "pure digital coordinates"
#define STR_COORD_SGF "sgf alphabet coordinates"
#define STR_COORD_GTP "gtp protocal coordinates"
#define	STR_SET_GAMEBOARD_COLOR "set game board color"
#define STR_MANUAL "manual"
#define STR_ABOUT "about LZRobe"
#define STR_FILE "File"
#define STR_EDIT "Edit"
#define STR_VIEW "View"
#define STR_LINK "Link"
#define STR_HELP "Help"
#define STR_NO_ENGINE "no engine"
#define STR_TIP "Tip"
#define STR_ADD_BRANCH_INQUIRY "Are you sure to add branch?"
#define STR_DELETE_BRANCH_INQUIRY "Are you sure to delete branch?"
#define STR_CURRENT_SITUATION "Current situation"
#define STR_BLACK_RESIGN "Black has resigned, white win!"
#define STR_WHITE_RESIGN "White has resigned, black win!"
#define STR_BLACK_OWN "Black ahead %f"
#define STR_WHITE_OWN "White ahead %f"
#define STR_DISCARD_RECORD_INQUIRY "Are you sure to discard the previous game record?"
#define STR_CLOSE_ENGINE_INQUIRY "Are you sure to close the engine?"
#define STR_CHANGE_PATH "You have changed the path of engine, would you like to save this change?"
#define STR_ENGINE_OPENING "Engine is starting, please wait."
#define STR_ENGINE_AVAILABLE "Engine is available"
#define STR_ENGINE_CLOSING "Engine is closing"
#define STR_VERSION "Current version: 1.01 beta"
#define STR_CLOSE "Close"
#define STR_MOVE_TURN "Move Turn"
#define STR_PRISONERS "Prisoners"
#define STR_PASS "Pass"
#define STR_RESIGN "Resign"
#define STR_GAME_PROCESS "Game Process"
#define STR_DIRECTION "Welcome to try GTPRobe! This is a software that provides a graphical user interface of AutoGTP program that provides training data for the computer go software Leela Zero.\n\n\
If you're interested in more information about Leela Zero and AutoGTP, please browse the following website:\n\n\
zero.sjeng.org\n\n\
LZRobe can help you to play Go againt Leela Zero or analyze the Go game records with Leela Zero to improve your strength of the game.\n\n\
LZRobe is written in C++ pragramming language with a GUI Library named wxWidgets.\n\n\
So if you would like to compile LZRobe, you have to download and install the wxWidgets library first.Please look up the following website:\n\n\
www.wxwidgets.org\n\n\
It is not difficult to compile LZRobe with Visual Studio or Code::Blocks.\n\n\
If you try to compile LZRobe, you should create a Win32 GUI empty project and add the files, including.h files, .cpp files, a .rc file, a .ico file and.bmp files.\n\n\
Don't forget appending include and lib dictionaries of wxWidgets in the setting of your project.\n\n\
Code::Blocks supports creating a wxWidgets project containing the path of wxWidgets, this maybe make it simpler to compile LZRobe.\n\n\
In order to create a more harmonic game running, GTPRobe need not to set the engine path, but you have to put the GTPRobe.exe file in the same dictionary with autogtp.exe\n\n\
In addition, the file name of \"autogtp.exe\" is not allowed to change, otherwice GTPRobe cannot find the engine.\n\n\
If you used command \"q\" to exit the previous running autogtp, then a file with random name but an extention name of \".sgf\" file storing game record would occured.\n\n\
In order to make sure that you can watch the game playing, before running the engine, please import this .sgf file with the \"Open\" button in the file menu or toolbar. Otherwise autogtp would delete that sgf file and you could not watch that game running correctly.\n\n\
In the course of playing a game, you can use the \"Undo\" or \"Redo\" function to go backward or forward, even add trying branches in the game, which won't interfere game playing.\n\n\
But if one game has ended, if you will continue to watch the next game played automatically bu auto gtp, please go the the last step with the \"Redo\" button, until the dialog with one side reign or game end occurs.\n\n\
Then press the \"new game\" button in the file menu or tool bar, and the \"Redo\" button can be used to persue the progress of the new game. Please keep in mind that do not press the button \"New Game\", otherwise the info of the running game will be lost.\n\n\
If you want to close the engine before a game ends, you can use \"Close Engine\" button in edit menu or tool bar. This is equivalent to input command \"q\" in auto gtp, which makes autogtp save the process info, and a new .sgf file will be created. Don't forget to import this file into GTPRobe before playing the game next time.\n\n\
Due to autogtp will take several seconds to replay \"q\", so please wait patiently when you closing the engine or exit the program.\n\n\
Wish every one enjoy the game playing!\n\n"
#endif
#endif