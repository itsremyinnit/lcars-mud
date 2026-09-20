// /d/Avakuma/guild/guild_shop.c
// Belinda's shop. Stock lives in /d/Avakuma/guild/storeroom.c, which
// restocks itself on a timer.
//
// This room inherits the shop base rather than AVAKUMA_ROOM: see the note
// at the top of /d/Avakuma/std/avakuma_shop.c for why the two cannot be
// combined. Consequences here are no exit_order and no spawn_objects, so
// Belinda is cloned directly and the single exit needs no ordering.
//
// Working: list, buy, sell, value. Advertised on the original sign but
// not yet built: handle, return, and the list filters.
#include <money.h>
inherit "/d/Avakuma/std/avakuma_shop";

void create() {
    ::create();
    set("light", 1);
    set_shopkeeper("Belinda");
    set("short", "The guild shop");
    set("long", @EndText
    Directly opposite the entrance stands the counter where the business
is done. Goods of every sort a sheriff might want hang on the walls and
behind it. Backpacks, an assortment of armour and a good many fine
weapons cover the walls and the shelves arranged in aisles down the
centre of the room. There is a sign on the wall.
EndText
    );
    set("item_desc", ([
        "counter" : @EndText
    Plain and well kept, opposite the entrance, with a thick rounded
wooden rail around it to lean on while haggling. For sale behind it are
weapons, armour and packs.
EndText
        ,
        "backpacks" : @EndText
    Various shapes and sizes, several types to choose between. They all
look as though they would weigh a good deal, and as though they would
carry the weight well.
EndText
        ,
        "armour" : @EndText
    Many different kinds, hung displayed on the walls or laid out on the
shelves standing in aisles down the centre of the room.
EndText
        ,
        "weapons" : @EndText
    Numerous, and hung on the walls or laid on the shelves like the
armour. They are of the finest make, and entirely suitable for
adventuring.
EndText
        ,
        "shelves" : @EndText
    Sturdy wood, built to hold the shop's merchandise where it can be
seen and still keep it in order.
EndText
        ,
        "goods" : @EndText
    Everything a sheriff heading out might need, and a good deal he
might only want.
EndText
        ,
        "sign" : @EndText
    A small sign saying that all anyone need do is ask Belinda for a
list of her goods and she will show what she has, and that they may buy
and sell as they see fit.
EndText
        ,
    ]));
    set("exits", ([
        "south" : "/d/Avakuma/guild/hallway_1",
    ]));
    set("pre_exit_func/south", "leaving");

    storeroom = clone_object("/d/Avakuma/guild/storeroom");
    spawn_here("/d/Avakuma/guild/npc/belinda");
    spawn_here("/d/Avakuma/obj/trash_can");
}

void init() {
    ::init();
    add_action("do_read", "read");
}

int do_read(string str) {
    if (str != "sign") {
        notify_fail("Read what?\n");
        return 0;
    }
    write(
"Valid commands in the shop:\n"
"\n"
"list              - list everything that is for sale\n"
"handle <item>     - allows you to handle an item and look at it\n"
"return <item>     - return the item you are handling\n"
"buy <item>        - buy an item from the shop\n"
"sell <item>       - sell an item in your inventory\n"
"value <item>      - tells you how much gold you would receive when\n"
"                    selling the item\n"
"\n"
"<item> is usually the name of an object, like \"axe\".\n");
    return 1;
}
