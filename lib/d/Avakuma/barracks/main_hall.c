// /d/Avakuma/barracks/main_hall.c
// South is locked and answers neither knock nor bang. Sealed for now.
// The sign and the notice board both carry ASCII artifacts under "read".
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The main hall in the barracks");
    set("long", @EndText
    The main hall is built of stone and kept scrupulously. The wood floor
has been worn smooth by boots and polished anyway, and candles set along
the walls carry the light from end to end. A painting hangs on one wall,
with a sign and a notice board beside it for the guards. From the east
comes the smell of something cooking, and it does not improve on
acquaintance.
EndText
    );
    set("item_desc", ([
        "walls" : "    Stone, laid square and mortared tight.\n",
        "painting" : @EndText
    Canvas, and old. It shows a dark-bearded man with a proud set to his
eye, one of the founders of the barracks by the look of him.
EndText
        ,
        "floor" : @EndText
    Wood, well used and better maintained. The housekeeper takes a
particular interest in this room.
EndText
        ,
        "candles" : @EndText
    Set along the walls at intervals, and kept burning. Nobody here has
to feel their way.
EndText
        ,
        "sign" : @EndText
    A board of wood hung beside the painting, the letters cut into it
with a knife.
EndText
        ,
        "board" : @EndText
    The guards' notice board. It carries the duty roster and the week's
meals, which is optimistic of it.
EndText
        ,
        "smell" : @EndText
    It comes from the kitchen, through the messhall, and it has been
described as burning flesh by people being generous.
EndText
        ,
    ]));
    set("exits", ([
        "east" : "/d/Avakuma/barracks/messhall",
        "west" : "/d/Avakuma/barracks/lounge",
    ]));
    set("exit_order", ({ "east", "south", "west" }));
    add_sealed("south", "The door is locked.\n");
}

void init() {
    add_action("do_read", "read");
}

int do_read(string str) {
    if (str == "sign") {
        write(
"\n"
"        /------------------------     ------------------------\\\n"
"       /         WEST           |     |         EAST           \\\n"
"      /    Sleeping quarters    |     |    Sleeping quarters    \\\n"
"      \\    Lounge               |     | Mess hall               /\n"
"       \\   Office               |     | Kitchen                /\n"
"        \\------------------------     ------------------------/\n"
"\n");
        return 1;
    }
    if (str == "board") {
        write(
"\n"
"          --------------------------------------------\n"
"          |          Scheduled Work Hours            |\n"
"          |          --------------------            |\n"
"          |               Mon - Sun                  |\n"
"          |    0-6   Group 1     6-12  Group 2       |\n"
"          |   12-18  Group 1    18-24  Group 2       |\n"
"          | ---------------------------------------- |\n"
"          |           Menu for this Week             |\n"
"          |           ------------------             |\n"
"          |                                          |\n"
"          | Monday :    Mystery Meat                 |\n"
"          | Tuesday:    Left over Mystery Meat       |\n"
"          | Wednesday:  See Monday                   |\n"
"          | Thursday:   See Tuesday                  |\n"
"          | Friday:     Special Mixed Meat           |\n"
"          | Sat - Sun:  Bring your own food          |\n"
"          |                                          |\n"
"          | Questions regarding the nutritional      |\n"
"          | value of the food are forwarded to       |\n"
"          | the chef. (Don't ask! --The Chef)        |\n"
"          |                                          |\n"
"          |                    --The Management      |\n"
"          --------------------------------------------\n"
"\n");
        return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
