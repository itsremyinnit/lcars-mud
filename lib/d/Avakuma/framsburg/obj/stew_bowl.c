// /d/Avakuma/framsburg/obj/stew_bowl.c
// The bowl the stew comes in, and what is left after eating it. Has a
// lid, which is why stew can go in a backpack and the beer cannot.
#include <mudlib.h>
inherit OBJECT;
void create() {
    set("id", ({ "bowl", "lid", "bowl with a lid" }));
    set("short", "A bowl with a lid");
    set("long", "A wooden bowl with a close-fitting lid. It is empty.\n");
    set("bulk", 25); set("mass", 80);
    set("value", ({ 0, "copper" }));
}
