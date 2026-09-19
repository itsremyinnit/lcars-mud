// /d/Avakuma/guild/guild_bar.c
// The dart game is a real playable game in the original, with a
// persistent scoreboard. Preserved here as a plaque under "read
// scoreboard": the board exactly as it stood. The game is deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The Guild's Bar");
    set("long", @EndText
    In from the Grand Entrance Hall is the Guild's watering hole, run by
an adventurous halfling. The bar is set along the south wall with stools
lined up at it, and a number of wooden tables stand in a semi-circle
around the fireplace on the west wall. A dartboard hangs on the east wall
with three darts in it, and a scoreboard beside it with a piece of chalk
on a string. There is a menu on the wall.
EndText
    );
    set("item_desc", ([
        "bar" : @EndText
    Highly polished black walnut under a thick coat of varnish, put
there to stop the top warping from spilled drinks and other accidents.
It sits high off the ground with brass rails around the whole outside
edge, and a small wooden flap at one end for the bartender.
EndText
        ,
        "stools" : @EndText
    The same dark wood as the bar, lined along its outside edge, with
red leather cushions.
EndText
        ,
        "tables" : @EndText
    Stout wood, arranged in a semi-circle around the fireplace, and not
embellished in the least, which keeps the cost down when the patrons get
rowdy. There are matching chairs.
EndText
        ,
        "fireplace" : @EndText
    A large stone fireplace in the west wall with a comfortable fire in
it, and a metal screen propped in front to keep errant sparks from
taking the whole Guild with them.
EndText
        ,
        "dartboard" : @EndText
    Cork, with painted sections and numbers marking out the different
areas of the board, and a lone red dot dead centre. Three darts come
with it.
EndText
        ,
        "darts" : @EndText
    Three metal darts hanging from the board, well balanced and made for
throwing, with red fletched feathers standing out of the sides.
EndText
        ,
        "scoreboard" : @EndText
    A slate board beside the dartboard with a piece of chalk on a
string. It carries the records of the Rim-Ainacam dart board, and it is
worth reading.
EndText
        ,
        "chalk" : @EndText
    A small piece of white chalk on a string attached to the slate. It
is for keeping score.
EndText
        ,
        "menu" : @EndText
    A list of what the house serves and what it charges. Worth reading.
EndText
        ,
    ]));
    set("exits", ([
        "north" : "/d/Avakuma/guild/entrance_hall",
    ]));
    set("exit_order", ({ "north" }));
}

void init() {
    add_action("do_read", "read");
}

int do_read(string str) {
    if (str == "menu") {
        write("Beer: 5   Wine: 7   Whiskey: 9   Muffin: 6   Donut: 10   Coffee: 35\n");
        return 1;
    }
    if (str == "scoreboard" || str == "slate" || str == "board") {
        write(
"Rim-Ainacam Dart Board:\n"
"Name           Bullseyes        Darts Thrown        Percentage\n"
"Bentelbow        116133            873861              13.29\n"
"Delotha          96352             615345              15.66\n"
"Josi             32792             217239              15.09\n"
"Cozoq            31382             236079              13.29\n"
"Colven           17766             138669              12.81\n"
"Aires            10062              84180              11.95\n"
"Grifford         10000              55665              17.96\n"
"Zerka             7920              52311              15.14\n"
"Lomar             7472              36327              20.57\n"
"Valkyrja          6969              71565              9.74\n"
"Eaoden            6249              42222              14.80\n"
"Arcticfox         4320              27123              15.93\n"
"Tevildo           3379              18459              18.31\n"
"Zelindo           3356              22689              14.79\n"
"Hiral             3326              23466              14.17\n"
"Alzreth           2508              16764              14.96\n"
"Cifke             2088              16902              12.35\n"
"Kahlan            1355              8658               15.65\n"
"Crytzch           1235              5685               21.72\n"
"Strudwicke        1202              6924               17.36\n");
        return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
