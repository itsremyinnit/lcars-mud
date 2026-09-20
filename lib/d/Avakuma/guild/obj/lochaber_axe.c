// /d/Avakuma/guild/obj/lochaber_axe.c
#include <mudlib.h>
inherit WEAPON;

void create() {
    set("id", ({ "axe", "lochaber", "lochaber axe" }));
    set("short", "a lochaber axe");
    set("long", @EndText
    A long haft with a heavy curved blade set at the end of it, and a hook
behind the blade for pulling a rider down off his horse. It takes both
hands and a good deal of room.
EndText
    );
    set("bulk", 110);
    set("mass", 1400);
    set("value", ({ 144, "gold" }));
    set("weapon", 6);
    set("damage", ({ 6, 14 }));
    set("nosecond", 1);
    set("name", "axe");
    set_verbs(({ "swing at", "hook at", "hack at" }));
    set("type", "cutting");
}
