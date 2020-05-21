#include <QApplication>

#include "movieplayer.h"

//allows to play small .gif files
//See also:
// https://evileg.com/ru/post/266/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MoviePlayer player;
    player.show();
    //player.show();
    return app.exec();
}
