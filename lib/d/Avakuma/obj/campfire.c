// /d/Avakuma/obj/campfire.c
// The fire in the orcs' meeting house. Not a light source you can take:
// it refuses to be extinguished and refuses to give up a brand, which is
// the whole of its behaviour in the original.
#include <mudlib.h>
inherit OBJECT;

void create() {
    // No ::create() here: OBJECT defines none, unlike CONTAINER.
    seteuid(getuid());
    set("id", ({ "fire", "campfire", "large campfire", "flames", "brand" }));
    set("short", "A large campfire (burning)");
    set("long", @EndText
    In the middle of the room there is a large campfire.  It is a good-
looking fire, with flames about three feet high.  There is a well-trodden
area of dirt around the fire.  It looks like the fire is a central point
that everyone gathers around. The fire looks much too hot to extinguish
or even pull a brand from.
EndText
    );
    set("bulk", 2000);
    set("mass", 10000);
    set("no_get", 1);
    set("prevent_get", 1);
    set("light", 1);
}

void init() {
    add_action("do_pull", "pull");
    add_action("do_extinguish", "extinguish");
    add_action("do_extinguish", "douse");
    add_action("do_extinguish", "put");
}

int do_pull(string str) {
    if (!str) return 0;
    if (str != "brand" && str != "brand from fire" &&
        str != "brand from campfire" && str != "fire")
        return 0;
    write("The fire is too hot to try and pull a brand from!\n");
    return 1;
}

int do_extinguish(string str) {
    if (!str) return 0;
    // "put out fire" as well as "extinguish fire".
    if (str != "fire" && str != "campfire" &&
        str != "out fire" && str != "out campfire")
        return 0;
    write("The fire is far too hot to go near, let alone put out.\n");
    return 1;
}
