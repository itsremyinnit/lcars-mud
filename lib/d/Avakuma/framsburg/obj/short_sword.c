#include <mudlib.h>
inherit WEAPON;
void create() {
    set("id", ({ "sword", "short sword" }));
    set("short", "a short sword");
    set("long", @EndText
    This is a standard sword issued to light infantry. It is
about 2 feet long and about 4 pounds. You can swing it with
great ease.
EndText
    );
    set("bulk", 50); set("mass", 400);
    set("value", ({ 60, "gold" }));
    set("weapon", 4); set("damage", ({ 3, 9 }));
    set("name", "sword");
    set_verbs(({ "slash at", "cut at", "thrust at" }));
    set("type", "cutting");
}
