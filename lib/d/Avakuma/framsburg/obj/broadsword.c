#include <mudlib.h>
inherit WEAPON;
void create() {
    set("id", ({ "broadsword", "large broadsword" }));
    set("short", "an extremely large broadsword");
    set("long", @EndText
     This is one of the largest swords you have ever seen. Its
blade is about 4 feet long and its handle is about a foot. It was
made for use by both hands and to do excessive amounts of damage
while keeping a sharp edge.
EndText
    );
    set("bulk", 130); set("mass", 1800);
    set("value", ({ 418, "gold" }));
    set("weapon", 9); set("damage", ({ 8, 20 }));
    set("nosecond", 1);
    set("name", "broadsword");
    set_verbs(({ "cleave at", "swing at", "hew at" }));
    set("type", "cutting");
}
