#include "Game.hpp"
#include <iostream>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <string>


using namespace std;

void RoomGraphics(string name, char roomGraphic[]) {
    char SpaceShip1[] = "              ______________ \n             <--------------\\ \n             .>-------------<--------------.______________ \n            /____________________                         `----.__ \n          .'         /.----------.__       ======-----====>       `. \n        .'          //              `--._     ______________________`. \n      .'           //                    `.--'  -------------------------. \n ,------------------------------------.==[=====]=========@================== \n|     (========\\____________      [_=__)  `-.________________________.---' \n \\     \\===========_________)   .--| |##)     `--.___           _.-' \n  \\____________________________/---'-`-'             `---------'";
    char Kitchen[] = "   .-.    .-.    .-.    .-.  .-.  .-\"-.  .-.      .--.      .-.  .--.\n  <   |  <   |  <   |   | |  | |  | | |  | |      |()|     /  |  |  |\n   )  |   )  |   )  |   | |  | |  | | |  | |      |  |     |  |  |  |\n   )()|   )()|   )()|   |o|  | |  | | |  | |      |  |     |  |  |()|\n   )()|   )()|   )()|   |o|  | |  | | |  | |      |  |     |  |  |()|\n  <___|  <___|  <___|   |\\|  | |  | | |  | |      |  |     |  |  |__|\n   }  |   || |   =  |   | |  | |  `-|-'  | |      |  |     |  |  |   L\n   }  |   || |   =  |   | |  | |   /A\\   | |      |  |     |  |  |   J\n   }  |   || |   =  |   |/   | |   |H|   | |      |  |     |  |  |    L\n   }  |   || |   =  |        | |   |H|   | |     _|__|_    |  |  |    J\n   }  |   || |   =  |        | |   |H|   | |    | |   |    |  |  | A   L\n   }  |   || |   =  |        | |   \\V/   | |    | |   |     \\ |  | H   J\n   }  |   FF |   =  |        | |    \"    | |    | \\   |      ,Y  | H A  L\n   }  |   LL |    = |       _F J_       _F J_   \\  `--|       |  | H H  J\n   }  |   LL |     \\|     /       \\   /       \\  `.___|       |  | H H A L\n   }  |   \\\\ |           J         L |  _   _  |              |  | H H U J\n   }  |    \\\\|           J         F | | | | | |             /   | U \".-'\n    } |     \\|            \\       /  | | | | | |    .-.-.-.-/    |_.-'\n     \\|                    `-._.-'   | | | | | |   ( (-(-(-( )";
    char SleepingQuarters[] = "          !__________!                    !__________! \n          |____  ____|                    |____  ____| \n          !__________!                    !__________!\n          %%%%%%%%%%%%                    %%%%%%%%%%%% \n         %%%%%%%%%%%%%%                  %%%%%%%%%%%%%% \n        %%%%%%%%%%%%%%%%                %%%%%%%%%%%%%%%%\n       %%%%%%%%%%%%%%%%%%              %%%%%%%%%%%%%%%%%%\n      %%%%%%%%%%%%%%%%%%%%            %%%%%%%%%%%%%%%%%%%%\n     ||||||||||||||||||||||          ||||||||||||||||||||||\n     ||||||||||||||||||||||          ||||||||||||||||||||||";
    char ConnectionTube[] = " *   .        *       .       .       *\n   .     *\n           .     .  *        *\n       .                .        .\n.  *           *                     *\n                             .\n         *          .   *\n\n             +  .        _            .-.\n                     3==({)_    .    (   \\\n    +  .             _  )`\\-|      *  )   \\\n            .       /_`' // |\\     .-'     `-\n  .                B'/`-'M\\_| )   /       .\n          . *       //       (   /      .\n                   B'         `-'";
    char EngineRoom[] = "        __  _____________________\n    __-/__\\/  |     |_____|   _  -__        _.-----._\n   /  \\       |           |  (_)    `-.  .-' | |  /  `-._\n  / /| \\      |___________|      _.-'  `' @  | |  `-._o/ `-._\n | /_/  \\__________________..--''      ||__  | |        | |  `-._\n |      | / | \\   / | \\    |     |`-.    ||---__        | |    /\\\\\n |      ||  |  | |  |  |   |     | O |   ||   __)       | |   |  |)\n |  _   |_\\_O_/___\\_O_/____|     |,-'    __---       _  | |    \\//\n | \\ \\  /      ___________ ``--,,_     ||    | |  ,-' o\\| | _.-'\n  \\ \\| /      |           |   _   `-.  '` @  | |  \\ _,-/_.-'\n   \\__/ __    |      _____|  (_)  __.-'  `-._| |    _.-'\n      -\\__/\\__|_____|_____|______-           `-----'";
    char EscapePod[] = "                 ___\n             ,--'___`--,            \n           ,'   / _ \\   `,          \n          /   _/ / \\ \\_   \\          \n         '-,-'\\ /   \\ /`-,-`        \n __.----==-|   |     |   |-==----.__\n `---==|---|   |     |   |---|==---'\n         .-`-,/|     |\\,-'-.        \n         |    \\ `---' /    |        \n         `   \\ \\     / /   '        \n          |   \\| --- |/   |          \n          `    |     |    '          \n           |   |     |   |          \n            \\  `.   ,'  /            \n             \\  |   |  /            \n              \\ |   | /              \n               \\`. .'/              \n               -o|_|o-              \n                 (_) ";
    char StorageRoom[] = "                   ________________  _______________\n                 .'               .'               .|\n               .'               .'               .' |\n             .'_______________.'______________ .'   |\n             | ___ _____ ___ || ___ _____ ___ |     |\n             ||_=_|__=__|_=_||||_=_|__=__|_=_||     |\n      _______||_____===_____||||_____===_____||     |\n    .'       ||_____===_____||||_____===_____||    .|\n  .'         ||_____===_____||||_____===_____||  .' |\n.'___________|_______________||_______________|.'   |\n|.----------.|.-----___-----.||.-----___-----.|     |\n|]          |||_____________||||_____________||     |\n||          ||.-----___-----.||.-----___-----.|     |\n||          |||_____________||||_____________||     |\n||          ||.-----___-----.||.-----___-----.|     |\n|]         o|||_____________||||_____________||     |\n||          ||.-----___-----.||.-----___-----.|     |\n||          |||             ||||_____________||     |\n||          |||             |||.-----___-----.|    .'\n|]          |||             ||||             ||  .'\n||__________|||_____________||||_____________||.'\n''----------'''------------------------------''";
    char ComputerRoom[] = "                          _______\n                         | ___  o|\n                         |[_-_]_ |\n      ______________     |[_____]|\n     |.------------.|    |[_____]|\n     ||            ||    |[====o]|\n     ||            ||    |[_.--_]|\n     ||            ||    |[_____]|\n     ||            ||    |      :|\n     ||____________||    |      :|\n .==.|\"\"  ......    |.==.|      :|\n |::| '-.________.-' |::||      :|\n |''|  (__________)-.|''||______:|\n `\"\"`_.............._\\\"\"`______\n    /:::::::::::'':::\\`;'-.-.  `\\\n   /::=========.:.-::\"\\ \\ \\--\\   \\\n   \\`\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`/  \\ \\__)   \\\n    `\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`    '========'";
    char Weapon[] = "              ____,----._\n   ,--'| _|\" o;.  `.____        ____  ,,=====._\n .=|.':| U| ;:;:  .- \\,,`-.===='}.,'\\//       \"`\n(]=|;: |o |  ,.  (  :;)::(     ):;::>}X==========-\n `=| :;|  | ,: o  `-_/``,-`====.}___/\\\\       _,\n   `--.|__|_ .:  _,' \"\"\"              ``=====''\n       ~  ~`----'";
	char TubeEntrance[] = "             .,-:;//;:=,\n         . :H@@@MM@M#H/.,+%;,\n      ,/X+ +M@@M@MM%=,-%HMMM@X/,\n     -+@MM; $M@@MH+-,;XMMMM@MMMM@+-\n    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.\n  ,%MM@@MH ,@%=            .---=-=:=,.\n  -@#@@@MX .,              -%HX$$%%%+;\n =-./@M@M$                  .;@MMMM@MM:\n X@/ -$MM/                    .+MM@@@M$\n,@M@H: :@:                    . -X#@@@@-\n,@@@MMX, .                    /H- ;@M@M=\n.H@@@@M@+,                    %MM+..%#$.\n /MMMM@MMH/.                  XM@MH; -;\n  /%+%$XHH@$=              , .H@@@@MX,\n   .=--------.           -%H.,@@@@@MX,\n   .%MM@@@HHHXX$$$%+- .:$MMX -M@@MM%.\n     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=\n       =%@M@M#@$-.=$@MM@@@M; %M%=\n         ,:+$+-,/H#MMMMMMM@- -,\n               =++%%%%+/:-.\n";
	char Bridge[] = "   ___________________________________________________________\n    |                                                           |\n   |                                                           |\n   |                                                           |\n   |                                                           |\n   |   ______                                                  |\n   |  |  ____|                                                 |\n   |  | |__   _ __ ___   ___ _ __ __ _  ___ _ __   ___ _   _   |\n   |  |  __| | '_ ` _ \\ / _ \\ '__/ _` |/ _ \\ '_ \\ / __| | | |  |\n   |  | |____| | | | | |  __/ | | (_| |  __/ | | | (__| |_| |  |\n   |  |______|_| |_| |_|\\___|_|  \\__, |\\___|_| |_|\\___|\\__, |  |\n   |                              __/ |                 __/ |  |\n   |                             |___/                 |___/   |\n   |                                                           |\n   |                                                           |\n   |                                                           |\n   |                                                           |\n   |                                                           |\n   |___________________________________________________________|\n																\n																\n        __________________________________________________ 		\n       /                            ___                   \\		\n      /  o o o                     [___]                   \\	\n     /______________________________________________________\\	\n";
	char LockerRoom[] = "	_________________________________\n   |				|               |\n   |				|               |\n   |     ______     |    ______     |\n   |	 ______     |    ______     |\n   |     ______     |    ______     |\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   |				|				|\n   ----------------------------------\n";
	//char EquipmentRoom
	char Observatory[] = "             _\n            /(_))\n          _/   /\n         //   /\n        //   /\n        /\\__/\n        \\O_/=-.\n    _  / || \\  ^o\n    \\/ ()_) \\.\n     ^^ <__> \\()\n       //||\\\n      //_||_\\\n     // \\||/ \\\n    //   ||   \\\n   \\/    |/    \\/\n   /     |      \\n  /      |       \\n         |\n";
	char TrainingRoom[] = "         _                                       _\n    _  _ | |                                     | | _  _\n   | || || |                                     | || || |\n =H| || || |=====================================| || || |H=\n   |_||_|| |                                     | ||_||_|\n         |_|                                     |_|\n";
	char ScienceLab[] = "     o                                      \n       o                                      \n     ___              ___  ___  ___  ___      \n     | |        ._____|_|__|_|__|_|__|_|_____.\n     | |        |__________________________|%|\n     |o|          | | |%|  | |  | |  |~| | |  \n    .' '.         | | |%|  | |  |~|  |#| | |  \n   /  o  \\        | | :%:  :~:  : :  :#: | |  \n  :____o__:     ._|_|_."    "    "    "._|_|_.\n  '._____.'     |___|%|                |___|%|\n";
 
	if (name == "Kitchen") {
		strcpy(roomGraphic, Kitchen);
	} else if (name == "Entrance to Connection Tube") {
		strcpy(roomGraphic, TubeEntrance);
	} else if (name == "Connection Tube") {
		strcpy(roomGraphic, ConnectionTube);
	} else if (name == "Sleeping Quarters 1") {
		strcpy(roomGraphic, SleepingQuarters);
	} else if (name == "Sleeping Quarters 2") {
		strcpy(roomGraphic, SleepingQuarters);
	} else if (name == "Engine Room") {
		strcpy(roomGraphic, EngineRoom);
	} else if (name == "Computer Room") {
		strcpy(roomGraphic, ComputerRoom);
	} else if (name == "Escape Pods") {
		strcpy(roomGraphic, EscapePod);
	} else if (name == "Storage Room") {
		strcpy(roomGraphic, StorageRoom);
	} else if (name == "Weapons Room") {
		strcpy(roomGraphic, Weapon);
	} else if (name == "Science Lab"){
		strcpy(roomGraphic, ScienceLab);
	} else if (name == "Observatory") {
		strcpy(roomGraphic, Observatory);
	} else if (name == "Training Room") {
		strcpy(roomGraphic, TrainingRoom);
	} else if (name == "Locker Room") {
		strcpy(roomGraphic, LockerRoom);
	} else if (name == "Bridge") {
		strcpy(roomGraphic, Bridge);
	} else
		strcpy(roomGraphic, SpaceShip1);
}

/*void ItemGraphics(string item, char itemGraphic[]) {
	char SpaceShip1[] = "              ______________ \n             <--------------\\ \n             .>-------------<--------------.______________ \n            /____________________                         `----.__ \n          .'         /.----------.__       ======-----====>       `. \n        .'          //              `--._     ______________________`. \n      .'           //                    `.--'  -------------------------. \n ,------------------------------------.==[=====]=========@================== \n|     (========\\____________      [_=__)  `-.________________________.---' \n \\     \\===========_________)   .--| |##)     `--.___           _.-' \n  \\____________________________/---'-`-'             `---------'";
    char Planet[] = "                                                    ___ \n                                                  ,o88888 \n                                               ,o8888888' \n                         ,:o:o:oooo.        ,8O88Pd8888\" \n                     ,.::.::o:ooooOoOoO. ,oO8O8Pd888'\" \n                    ,.:.::o:ooOoOoOO8O8OOo.8OOPd8O8O\" \n                  , ..:.::o:ooOoOOOO8OOOOo.FdO8O8\" \n                 , ..:.::o:ooOoOO8O888O8O,COCOO\" \n                , . ..:.::o:ooOoOOOO8OOOOCOCO\" \n                 . ..:.::o:ooOoOoOO8O8OCCCC\"o \n                    . ..:.::o:ooooOoCoCCC\"o:o \n                    . ..:.::o:o:,cooooCo\"oo:o: \n                 `   . . ..:.:cocoooo\"'o:o:::' \n                 .`   . ..::ccccoc\"'o:o:o:::' \n                :.:.    ,c:cccc\"':.:.:.:.:.' \n              ..:.:\"'`::::c:\"'..:.:.:.:.:.' \n            ...:.'.:.::::\"'    . . . . .' \n           .. . ....:.\"' `   .  . . '' \n         . . . ....\"' \n         .. . .\"'     \n        . ";
    char Satelitte[] = "           / : \\ \n          / o0o \\ \n    _____\"~~~~~~~\"_____ \n    \\+###|U * * U|###+/ \n  \\...!(.&gt;..&lt;)!.../ \n      ^^^^o|   |o^^^^ \n   +=====}:^^^^^:{=====+# \n   .____  .|!!!|.  ____. \n   |#####:/\" \" \"\\:#####| \n   |#####=|  O  |=#####| \n|#####&gt;\\_____/&lt;#####| \n    ^^^^^   | |   ^^^^^ \n            o o";
    char Satelitte2[] = "                }--O--{ \n                  [^] \n                 /ooo\\ \n ______________:/o   o\\:______________ \n|=|=|=|=|=|=|:A|\":|||:\"|A:|=|=|=|=|=|=| \n^\"\"\"\"\"\"\"\"\"\"\"\"\"\"!::{o}::!\"\"\"\"\"\"\"\"\"\"\"\"\"\"^ \n                \\     / \n                 \\.../ \n      ____       \"---\"       ____ \n     |\\/\\/|=======|*|=======|\\/\\/| \n     :----\"       /-\\       \"----: \n                 /ooo\\ \n                #|ooo|# \n                 \\___/ ";
    char Alien1[] = "           \\.   \\.      __,-\"-.__      ./   ./ \n       \\.   \\`.  \\`.-'\"\" _,=\"=._ \"\"`-.'/  .'/   ./ \n        \\`.  \\_`-''      _,=\"=._      ``-'_/  .'/ \n         \\ `-',-._   _.  _,=\"=._  ,_   _.-,`-' / \n      \\. /`,-',-._\"\"\"  \\ _,=\"=._ /  \"\"\"_.-,`-,'\\ ./ \n       \\`-'  /    `-._  \"       \"  _.-'    \\  `-'/ \n       /)   (         \\    ,-.    /         )   (\\ \n    ,-'\"     `-.       \\  /   \\  /       .-'     \"`-, \n  ,'_._         `-.____/ /  _  \\ \\____.-'         _._`, \n /,'   `.                \\_/ \\_/                .'   `,\\ \n/'       )                  _                  (       `\\ \n        /   _,-'\"`-.  ,++|T|||T|++.  .-'\"`-,_   \\ \n       / ,-'        \\/|`|`|`|'|'|'|\\/        `-, \\ \n      /,'             | | | | | | |             `,\\ \n     /'               ` | | | | | '               `\\ \n                        ` | | | ' \n                          ` | '";
    char Alien2[] = "         __.,,------.._ \n      ,'\"   _      _   \"`.\n     /.__, ._  -=- _\"`    Y\n    (.____.-.`      \"\"`   j\n     VvvvvvV`.Y,.    _.,-'       ,     ,     ,\n        Y    ||,   '\"\\         ,/    ,/    ./\n        |   ,'  ,     `-..,'_,'/___,'/   ,'/   ,\n   ..  ,;,,',-'\"\\,'  ,  .     '     ' \"\"' '--,/    .. ..\n ,'. `.`---'     `, /  , Y -=-    ,'   ,   ,. .`-..||_|| ..\nff\\\\`. `._        /f ,'j j , ,' ,   , f ,  \\=\\ Y   || ||`||_..\nl` \\` `.`.\"`-..,-' j  /./ /, , / , / /l \\   \\=\\l   || `' || ||...\n `  `   `-._ `-.,-/ ,' /`\"/-/-/-/-\"'''\"`.`.  `'.\\--`'--..`'_`' || ,\n            \"`-_,',  ,'  f    ,   /      `._    ``._     ,  `-.`'//         ,\n          ,-\"'' _.,-'    l_,-'_,,'          \"`-._ . \"`. /|     `.'\\ ,       |\n        ,',.,-'\"          \\=) ,`-.         ,    `-'._`.V |       \\ // .. . /j\n        |f\\\\               `._ )-.\"`.     /|         `.| |        `.`-||-\\\\/\n        l` \\`                 \"`._   \"`--' j          j' j          `-`---'\n         `  `                     \"`,-  ,'/       ,-'\"  /\n                                 ,'\",__,-'       /,, ,-'\n                                 Vvv'            VVv'";
    char SpaceSuit1[] = "        .-\"\"\"-.       ||\n       /=      \\      ||\n      |- /~~~\\  |     ||\n      |=( '.' ) |     ||\n      \\__\\_=_/__/     ||\n       {_______}      ||\n     /` *       `'--._||\n    /= .     [] .     { >\n   /  /|ooo     |`'--'||\n  (   )\\_______/      ||\n   \\``\\/       \\      ||\n    `-| ==    \\_|     ||\n      /         |     ||\n     |=   >\\  __/     ||\n     \\   \\ |- --|     ||\n      \\ __| \\___/     ||\n      _{__} _{__}     ||\n     (    )(    )     ||\n      `\"\"\"  `\"\"\"  ";
    char SpaceSuitHelmet[] = "                          _______________________\n                         //     _..--~~~--.._    \\\\\n                        ||_____/ |  |  |  |  \\ __/ |\n                        ||    /   ________    \\    |\n                        ||__ /   /........\\    |   |\n                        |   |   /........  \\   |   |\n   _____________________|  _|  /.........   \\  |   |________________\n    ;   . . .   .       |_/ | |.........     | |   | .''.\"...  ... .\n   ___   ..~.         _.'  /| |........      | |   |         . ~\n    .      '     .   / \\_.' | |........      | |   |\\ ~.   ._..---._\n                    |. /|    \\ \\........    / /    |/ .    /\\      /\\\n      '\"\"\" ... ~~~  | \\||  _.'\\ \\........  / /'._ _|      // ~-._./ -\\\n    ..~             |  |_.~\\\\  \\ \\________/ / // '.|     /__       __.\\\n    ___   ..~.      |_.~    \\   \\__________/  /   _ ~-.  ~~~~..  ~~~~~.\n                   .~ -.     \\__.---.________/   ______\\.\n   .''.\"...  ... ./\\        _|      |---|  = |__ \\__\\===\\   '\"\"\" ... ~~~";
    char KeyCard[] = "  ___________________\n /,-----------------.\\\n||        .^.        ||\n||      .'   `.      ||\n||    .'   _   `.    ||\n||  .'    (_)    `.  ||\n||.'    .--~--.    `.||\n|| ~~|  `-----'  |~~ ||\n||   | |~|~~~|~| |   ||\n||   |  `~~~~~'  |   ||\n||   |  \\|~|~|/  |   ||\n|| __|   == ==   |__ ||\n||`.     -- --     .'||\n||  `.   -- --   .'  ||\n||    `.       .'    ||\n||      `.   .'      ||\n||        `.'        ||\n|\\___________________/|\n `-------------------'";
    char SteelBar[] = "------------------------------------\n------------------------------------\n";
    char Flashlight[] = "                      _.----.\n    .----------------\" /  /  \\\n   (                | |   |) |\n    `----------------._\\  \\  /\n                       \"----'";
    char ScrewDriver[] = "                                    ____________________________\n   _____                          ,\\\\    ___________________    \\\n  |     `------------------------'  ||  (___________________)   `|\n  |_____.------------------------._ ||  ____________________     |\n                                  `//__(____________________)___/";
    char Hammer[] = "                          \\`.    \n.--------------.___________) \\   \n|//////////////|___________[ ]   \n`--------------'           ) (     \n                           '-' ";
    char FuelCell[] = "    _________\n   /|\\     /|\\\n  / |  \\ /  | \\\n /__|__/ \\__|__\\\n|\\  |  | |  |  /|\n| \\ |----|--| / |\n| /\\----|----/\\ |\n|/_____|\\|_____\\|\n \\  |  \\ /  |  /\n  \\ |  / \\  | /\n   \\|/     \\|/\n    ---------";
    char Button[] = "  ____\n /\\__/\\\n/_/  \\_\\\n\\ \\__/ /\n \\/__\\/";
    char BackupGen[] = "             .-----.----.-----.  \n            / /-.| |////| |.-\\ \\  \n           / /|_|| |////| ||_|\\ \\   \n          /  :   : |////| :   :  \\\n         /  /___:  |////|  :___\\  \\\n        /   :   |_ |////| _|   :___\\    \n       /   /    |_||////||_|    \\   \\    \n      /    :    |_||////||_|    :    \\\n     /____/____ |_||////||_| ____\\____\\\n    /     :    |   |////|   |    :     \\\n   /     /     | _ |////| _ |     \\     \\\n   \\     :     || ||////|| ||     :     /\n    \\   /    .'-\\ ||////|| /-`.    \\   /";
    char Weapon[] = "              ____,----._\n   ,--'| _|\" o;.  `.____        ____  ,,=====._\n .=|.':| U| ;:;:  .- \\,,`-.===='}.,'\\//       \"`\n(]=|;: |o |  ,.  (  :;)::(     ):;::>}X==========-\n `=| :;|  | ,: o  `-_/``,-`====.}___/\\\\       _,\n   `--.|__|_ .:  _,' \"\"\"              ``=====''\n       ~  ~`----'";

}*/

bool isLook(char * input){
    char look[] = "look  ";
    int len = strlen(input);
    if(len <= 6){
        for(int i = 0; i < len; i++){
            if(input[i] != look[i]) return false;
        }
    }
    else return false;
    return true;
}

void strToCstr(string input, char * output){
	/*for(unsigned int i = 0; i < input.length(); i++){
		output[i] = input[i];
	}*/
	int totalLength = input.length();
	int inPos = 0;
	int outPos = 0;
	int wordCount = 0;
	int lineCount = 0;
	int width = 105;
	while(inPos < totalLength){
		wordCount = 0;
		while(input[inPos + wordCount] != ' ' && input[inPos + wordCount] != '\n' && inPos + wordCount < totalLength - 2){
			wordCount++;
		}
		if(input[inPos + wordCount] == '\n'){
			lineCount = 0;
		}
		wordCount++;
		if(wordCount + lineCount > width){
			output[outPos] = '\n';
			outPos++;
			lineCount = 0;
		}
		int curPos = inPos;
		while(inPos < curPos + wordCount){
			output[outPos] = input[inPos];
			outPos++;
			inPos++;
			lineCount++;
		}
	}
}

string cstrToStr(char * input){
	string output = "";
	int len = strlen(input);
	for(int i = 0; i < len; i++){
		output += input[i];
	}
	return output;
}

string getItemName(string input){
    string str1 = "You have picked up the ";
    if(input.substr(0, str1.length()) == str1){
        return input.substr(str1.length(), input.length() - str1.length() - 1);
    }
    int position = 0;
    while(input[position] != ':'){
        position++;
    }
    return input.substr(0, position);
    return "No match.";
}

int main(){

    int parent_x, parent_y;
    int middle_size = 22;
    int bottom_size = 3;
    char TitleScreen[] ="   _____                         _____ _        _   _ \n                 / ____|                       / ____| |      | | (_)         \n                | (___  _ __   __ _  ___ ___  | (___ | |_ __ _| |_ _  ___  _ __ \n                 \\___ \\| '_ \\ / _` |/ __/ _ \\  \\___ \\| __/ _` | __| |/ _ \\| '_ \\ \n                 ____) | |_) | (_| | (_|  __/  ____) | || (_| | |_| | (_) | | | |\n                |_____/| .__/ \\__,_|\\___\\___| |_____/ \\__\\__,_|\\__|_|\\___/|_| |_| \n                       | |       _  _   _  _   _  _   _  _ \n                       |_|      | || | | || | | || | | || |\n                                | || |_| || |_| || |_| || |_ \n                                |__   _|__   _|__   _|__   _|\n                                   | |    | |    | |    | |\n                                   |_|    |_|    |_|    |_|";
    char HelpMenu[] = "HELP MENU - COMMANDS\nUse 'go [room name]', 'go [clockwise/counter-clockwise]',\nor just '[room name]'/'[counter-clockwise/clockwise]' to move to another room.\nUse 'look' to get full room description.\nUse 'look at [item name]' to get description of something in a room.\nUse 'check' to get a list of all the items you have picked up.\nUse 'check [item name]' to get a description of an item you have picked up.\nUse 'open [item name]' top open something and see what's inside.\nUse 'grab [item name]' to pick up an item.\nUse 'patch [item name] with [item name]' to patch and item.\nUse 'insert [item name] into [item name]' to insert one item into another.\nUse 'install [item name] into [item name]' to install one item in another.\nUse 'fly [item name]' to fly something, like an airplane.\nUse 'hit [item name] with [item name]' to hit one item with another.\nUse 'quit' to exit. (Will not work when responding to an event.\nUse 'help' at any point during the game to see these instructions again.\nType 'START' and hit enter to begin the game.";
	char Introduction[] = "Space Station 4444 is the last line of defense for the Planet Hobbly Knees, a planet rich in\nuntamed resources and a warning to chartographers everywhere not to let their kids get involved \nin the naming process. You've been serving on this station for the better part of a year -- not\nquite a newbie yet not quite a regular. Nevertheless, you've bonded well with the other crew and \nthe captain has proven to be strict by understanding.\n\nIt's the afternoon watch, and you're alone on the bridge -- the rest of the crew are either in \nthe training room or in the science lab. You're relaxing in the captain's chair on the bridge,\nspinning a pen in your hand daydreaming about sipping exotic cocktails on a beach when the proximity\nsensors begin blaring. Before you even have time to sit up, the wall above you explodes and the furious\nscreech of air being sucked into space deafens you.\n\nEverything goes black... \nPress a key to continue...";
    Game game;
    
    initscr();
    //noecho();

	int row, col;
	getmaxyx(stdscr,row,col);
	if(row < 60 || col < 115){
		endwin();
		cout << "Your terminal windows must have at least 115 columns and 60 rows.\n";
		cout << "Your current terminal size is: " << row << " rows and " << col << " columns.\n";
		cout << "Please resize and restrart the game.\n";
		return 1;
	}

	curs_set(TRUE);
    keypad(stdscr, TRUE);
	
    // get our maximum window dimensions
    //getmaxyx(stdscr, parent_y, parent_x);
    
    // preset window settings
    parent_x = 110;
    parent_y = 50;
    
    // set up the initial windows
    WINDOW* topborder = newwin(parent_y - middle_size, parent_x, 0, 0);
    WINDOW* top = newwin(parent_y - middle_size - 2, parent_x - 2, 1, 1);
    WINDOW* middleborder = newwin(middle_size - bottom_size, parent_x, parent_y - middle_size, 0);
    WINDOW* middle = newwin(middle_size - bottom_size - 2, parent_x - 3, parent_y - middle_size + 1, 2);
    WINDOW* bottomborder = newwin(bottom_size, parent_x, parent_y - bottom_size, 0);
    WINDOW* bottom = newwin(bottom_size - 2, parent_x - 2, parent_y - bottom_size + 1, 1);

    // initalize color
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);

    bkgd(COLOR_PAIR(1));
    wbkgd(top, COLOR_PAIR(1));
    wbkgd(middle, COLOR_PAIR(1));
    wbkgd(bottom, COLOR_PAIR(1));
    
    // draw to our windows
    mvwaddstr(top, 8, 15, TitleScreen);
    mvwaddstr(middle, 0, 0, HelpMenu);
    mvwaddstr(bottom, 1, 1, " ");
    
	box(topborder, 0, 0);
	box(middleborder, 0, 0);
	box(bottomborder, 0, 0);
    
    refresh();
    wrefresh(topborder);
    wrefresh(top);
    wrefresh(middleborder);
    wrefresh(middle);
    wrefresh(bottomborder);
    wrefresh(bottom);

   	//String and c-string used to get input!	
	string curRoom = "";
	char RoomInfo[3000];
	char cInput[1000];
	string input = "";

	do{
		refresh();
		werase(bottom);
        wrefresh(bottom);

		mvwaddstr(bottom, 1, 1, " ");
		box(bottomborder, 0, 0);
		wrefresh(bottom);
		move(48, 2);
		refresh();

		getstr(cInput);
		input = cstrToStr(cInput);
		for(unsigned int i = 0; i < input.length(); i++){
			input[i] = tolower(input[i]);
		}
	}while(input != "start");

	clear();
	refresh();
	
	// introduction window message
	box(topborder, 0, 0);
	mvwprintw(top, 5, 1, Introduction);
	refresh();
	wrefresh(topborder);
	wrefresh(top);
	
	getchar();

	clear();
	refresh();


	while(game.getPlayerStatus()){
   
	 	//This gets the "strings" (room name, event name, descriptions, etc.)
		//from the current room.
		//The starting room is set as the brdige when the game loads.
		currentRoomStrings res = game.getCurrentRoomStrings();
   
	   	//This string will cumulatively hold the strings to be display for the room.
		//    !!!! Important !!!!
		//    We display EITHER room info OR event info!!!
        string RoomInfoStr; 
       
	   	//Here's where we do the dumping. If there's an active event, grab
		//all those strings and dump them into res.	
		if(res.activeEvent){
			//Get room name, event name, and event description
			RoomInfoStr = res.roomName + "\n" + res.eventName + "\n" + res.eventDescription + "\n";
			//We also need the options for the event.
			RoomInfoStr += "Event options: ";
			for(unsigned int i = 0; i < res.currentOptions->size(); i++){
				RoomInfoStr += res.currentOptions->at(i) + ", ";
			}
		} 
		//If there is no active event, just get the room name and description.
		else {
			RoomInfoStr = res.roomName + "\n" + res.roomDescription;
		}

		//Make sure RoomInfo is empty, please!
		memset(RoomInfo, '\0', 3000);

		//Convert our string with the room info into a c-string for nCurses.
		strToCstr(RoomInfoStr, RoomInfo);
		
		//Initialize graphic display array and make it empty
		char roomGraphic[3000];
		memset(roomGraphic, '\0', 3000);
	    
        if(res.activeEvent)    
            RoomGraphics(res.eventName, roomGraphic);
        else 
		    RoomGraphics(res.roomName, roomGraphic);
	
		//If we have moved to a new room or there is an active event, display it.
		//Otherwise, skip to getting input from user.	
		if(curRoom != res.roomName){
			werase(stdscr); 
			werase(middle);
   
			// draw to our windows
			mvwprintw(top, 8, 15, roomGraphic);
			mvwprintw(middle, 1, 1, RoomInfo);
			mvwprintw(bottom, 1, 1, "");
		
			box(topborder, 0, 0);
			box(middleborder, 0, 0);
			box(bottomborder, 0, 0);
					
			// refresh each window
			refresh();
			wrefresh(topborder);
			wrefresh(top);
			wrefresh(middleborder);
			wrefresh(middle);
			wrefresh(bottomborder);
			wrefresh(bottom);

			curRoom = res.roomName;
		}

		//Make sure our input c-string is nice and empty, please!
		memset(cInput, '\0', 1000);

		//Put our cursor in the text entry box.
		move(48,1);
		refresh();

		//Get input from the user!
		getstr(cInput);

		if(strlen(cInput) < 2 || isLook(cInput)){
			strcpy(cInput, "look");
            memset(roomGraphic, '\0', 3000);
            
            if(res.activeEvent)    
                RoomGraphics(res.eventName, roomGraphic);
            else 
                RoomGraphics(res.roomName, roomGraphic);
		}

		//Convert cInput to string
       	input = cstrToStr(cInput);
       	
       	//Initialize graphic display array and make it empty
		char itemGraphic[3000];
		memset(itemGraphic, '\0', 3000);
		
		//ItemGraphics(res.roomName, itemGraphic);

		//We'll pass input to the game object to get the result
		//of the player's command. Note that if there is an 
		//active event, it will go to respondToEvent.
		//Otherwise, it goes to processPlayerInput.
		string result = "";
		if(res.activeEvent){
			result = game.respondToEvent(input).at(0);
		} else {
			result = game.processPlayerInput(input);
		}

        string itemName = getItemName(result);
        if(itemName != "No match."){

        }

		// refresh each window
        refresh();
        werase(middle);
        wrefresh(middle);
		werase(bottom);
        wrefresh(bottom);

		//We'll reuse RoomInfo here and convert the result
		//to a c-string which goes into RoomInfo.
		memset(RoomInfo, '\0', 3000);
		strToCstr(result, RoomInfo);
        
		// draw to our windows
        mvwprintw(top, 3, 15, roomGraphic);
        mvwprintw(middle, 1, 1, RoomInfo);
        mvwprintw(bottom, 1, 1, "");

		box(topborder, 0, 0);
		box(middleborder, 0, 0);
		box(bottomborder, 0, 0);
        
       	// refresh each window
        refresh();
        wrefresh(topborder);
        wrefresh(top);
        wrefresh(middleborder);
        wrefresh(middle);
        wrefresh(bottomborder);
        wrefresh(bottom);
	}

    cout << "\n\n\nPress any key to quit.\n";
    getchar();

	endwin();
	
	return 0;
}
