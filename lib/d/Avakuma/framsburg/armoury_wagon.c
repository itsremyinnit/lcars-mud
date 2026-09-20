// /d/Avakuma/framsburg/armoury_wagon.c
// A working shop in the original. The sign lists the shop commands and
// is readable; the shop mechanics themselves are deferred.
#include "/d/Avakuma/avakuma.h"
inherit AVAKUMA_ROOM;

void create() {
    ::create();
    set("short", "The armoury wagon");
    set("long", @EndText
    Inside the armoury wagon, where a man may buy or sell most of what
he needs. Weapons and armour of many kinds hang about the walls. A small
sign hangs behind a small partition, and it would be worth reading before
you reach for anything.
EndText
    );
    set("item_desc", ([
        "weapons" : @EndText
    Hanging here and there about the wagon, waiting to be bought.
EndText
        ,
        "armours" : @EndText
    Primitive work, and it will still keep more off you than your shirt
will.
EndText
        ,
        "armour" : @EndText
    Primitive work, and it will still keep more off you than your shirt
will.
EndText
        ,
        "sign" : @EndText
    Letters, certainly. Reading them would be the next step.
EndText
        ,
        "partition" : @EndText
    Short, this being a small wagon. Its business is keeping customers
on their own side of the merchandise.
EndText
        ,
    ]));
    set("exits", ([
        "out" : "/d/Avakuma/framsburg/armoury_house",
    ]));
    set("exit_order", ({ "out" }));

    set("objects", ([
        "/d/Avakuma/framsburg/npc/malcolm" : 1,
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
"    Shoplifters will be killed and Eaten, YOU HAVE BEEN WARNED.\n"
"Use the following commands here.\n"
"*List : lists the items for sale in the shop\n"
"*Buy <item> : lets you purchase the item\n"
"*Sell <item> : lets you sell the item\n"
"*Value <item> : the shopkeeper will tell you how much he will pay for item\n"
"*Handle <item> : the shopkeeper will let you try it out..\n"
"  (You must RETURN item in order to leave the shop)\n");
    return 1;
}
