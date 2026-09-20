// /d/Avakuma/guild/guild_shop.c
// A working shop in the original. The sign is readable and carries the
// full command list; the shop mechanics are deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
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
    set("exit_order", ({ "south" }));

    set("objects", ([
        "/d/Avakuma/guild/npc/belinda" : 1,
    ]));
    spawn_objects();
}

void init() {
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
"list <w | weapon> - list all weapons for sale. Can be used with 'a'\n"
"                    for 'armour' and other type of items\n"
"list < 50         - list everything worth less than 50 gold. Can be\n"
"                    also used to query more '>' or equal '=', and\n"
"                    in combination with the above\n"
"list armour <part>      - list all armours that cover <part>\n"
"list armour <part> only - list all armours that only cover <part>\n"
"handle <item>     - allows you to handle an item and look at it\n"
"return <item>     - return the item you are handling\n"
"buy <item>        - buy an item from the shop\n"
"sell <item>       - sell an item in your inventory\n"
"sell <item> from <container> - sell an item from a container\n"
"sell <item> except <item>    - sell items excluding certain items\n"
"sell <item> from <container> except <item> - you get the idea\n"
"value <item>      - tells you how much gold you would recieve when\n"
"                    selling the item. Can be used in the same format\n"
"                    as 'sell'\n"
"\n"
"<item> is usually the name of an object, like \"sword\".  It can \n"
"also specify multiple items \"all\" or multiple items of the same\n"
"type \"all sword\".  For multiples, it can specify a specific order\n"
"of item \"sword 1\", \"sword 2\", etc.\n");
    return 1;
}
