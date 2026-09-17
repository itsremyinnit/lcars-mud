// /d/Nexus/rooms/rookery.c
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

void create() {
    ::create();
    set("short", "The Rookery");
    set("long", @EndText
Perches line this tall, round room from floor to rafters, and messenger
birds of every kind doze, preen, and bicker upon them: ravens and owls,
swift grey falcons, and one small, very determined sparrow. Pigeonholes
of polished wood fill one wall, each labeled in a careful hand, and the
air is full of soft wingbeats and the dry rustle of letters. The Commons
lies back to the west.
EndText
    );
    set("item_desc", ([
        "birds" : "They eye you with polite professional interest.\n",
        "sparrow" : "It looks back at you as if it would carry a boulder across the world if asked.\n",
        "pigeonholes" : "Most are empty. A few already have names written beneath them.\n",
        "perches" : "Worn smooth by claws, rising all the way into the rafters.\n",
    ]));
    set("exits", ([
        "west" : "/d/Nexus/rooms/commons",
    ]));
}

void init() {
    add_action("do_register", "register");
}

int do_register(string str) {
    string home = (string)this_player()->getenv("MAILHOME");
    if (home == "Nexus") {
        write("The Rookery already holds your name. Letters find you here.\n");
        return 1;
    }
    this_player()->set_env("MAILHOME", "Nexus");
    this_player()->save_data();
    write("You give your name to the sparrow, who repeats it back with grave importance\n" +
          "and files it somewhere among the perches. Letters can now find you at the Nexus.\n");
    say((string)this_player()->query("cap_name") + " registers with the Rookery.\n");
    return 1;
}
