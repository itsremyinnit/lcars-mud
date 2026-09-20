// /d/Avakuma/framsburg/kitchen.c
// A working tavern in the original: the menu prices beer, whiskey and
// stew. "read menu" carries the list; the shop itself is deferred.
#include <move.h>
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "A ruined house that has a smell of stew all about it");
    set("long", @EndText
    Someone has made this place habitable out of sheer stubbornness.
The walls and windows are as ruined as anywhere else in Framsburg, but
there are curtains up, and a rug thrown down so that nobody has to sit
in the dirt. A pot hangs over a cooking fire, and there is a menu on the
wall.
EndText
    );
    set("item_desc", ([
        "curtains" : @EndText
    Ragged strips of faded cloth. They should not make as much
difference as they do.
EndText
        ,
        "rug" : @EndText
    Five feet by eight, and worked with designs worth stooping to look
at properly.
EndText
        ,
        "pot" : @EndText
    A big iron pot, with a hearty stew going in it.
EndText
        ,
        "fire" : @EndText
    A good cooking fire, throwing out a great deal of heat.
EndText
        ,
        "menu" : @EndText
    A list of what the house serves, and what it charges. Worth reading.
EndText
        ,
        "walls" : "    Falling apart, like every other wall in this town.\n",
        "windows" : @EndText
    Only the south wall has any, the others having become windows on
their own account.
EndText
        ,
        "floor" : @EndText
    Dirt, with the rug covering as much of it as a rug that size can.
EndText
        ,
    ]));
    set("exits", ([
        "east"  : "/d/Avakuma/framsburg/corner_house",
        "north" : "/d/Avakuma/framsburg/hospital",
        "west"  : "/d/Avakuma/framsburg/leaders_house",
    ]));
    set("exit_order", ({ "east", "north", "west" }));

    set("objects", ([
        "/d/Avakuma/obj/trash_can" : 1,
        "/d/Avakuma/framsburg/npc/father" : 1,
        "/d/Avakuma/framsburg/npc/meryne" : 1,
    ]));
    spawn_objects();
}

// What Meryne serves, and what it costs. Paid on order, not on
// consumption: you can carry a lidded bowl of stew away and eat it
// somewhere else.
#define MENU ([ \
    "beer"    : ({ 2,  "/d/Avakuma/framsburg/obj/beer" }), \
    "whiskey" : ({ 10, "/d/Avakuma/framsburg/obj/whiskey" }), \
    "stew"    : ({ 13, "/d/Avakuma/framsburg/obj/stew" }), \
])

void init() {
    add_action("do_read", "read");
    add_action("do_order", "order");
}

int do_order(string str) {
    mapping menu;
    mixed *item;
    object ob, who;
    int price;

    who = this_player();
    menu = MENU;

    if (!str || !menu[str]) {
        notify_fail("Meryne says: I do not serve that. Look at the menu.\n");
        return 0;
    }

    item = menu[str];
    price = item[0];

    if ((int)who->query("wealth/gold") < price) {
        notify_fail("Meryne says: You cannot pay for that.\n");
        return 0;
    }

    ob = clone_object(item[1]);
    if (!ob) {
        notify_fail("Meryne says: I am out of that, sorry.\n");
        return 0;
    }

    if (ob->move(who) != MOVE_OK) {
        "/adm/daemons/disposal_d"->kill_object(ob);
        write("Your hands are full!\n");
        notify_fail("Meryne says: You can't carry it!\n");
        return 0;
    }

    who->debit("gold", price);
    write("Meryne says: Thanks for your order!\n");
    say((string)who->query("cap_name") + " orders " + str + ".\n", who);
    return 1;
}

int do_read(string str) {
    if (str != "menu") {
        notify_fail("Read what?\n");
        return 0;
    }
    write(
"I serve the following food and drinks:\n"
"beer            2\n"
"whiskey         10\n"
"stew            13\n");
    return 1;
}
