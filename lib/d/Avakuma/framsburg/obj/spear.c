#include <mudlib.h>
inherit WEAPON;
void create() {
    set("id", ({ "spear", "long sharp spear", "sharp spear" }));
    set("short", "a long sharp spear");
    set("long", @EndText
    This is a good-looking spear about 6 feet long. It has an
iron tip on it that weighs about 2 pounds. It doesn't look all
that powerful but you know you wouldn't want to be poked with
it.
EndText
    );
    set("bulk", 80); set("mass", 500);
    set("value", ({ 32, "gold" }));
    set("weapon", 4); set("damage", ({ 3, 10 }));
    set("name", "spear");
    set_verbs(({ "jab at", "thrust at", "poke at" }));
    set("type", "piercing");
}
