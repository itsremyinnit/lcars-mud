// /d/Avakuma/framsburg/obj/empty_glass.c
#include <mudlib.h>
inherit OBJECT;
void create() {
    set("id", ({ "glass", "empty glass", "shot glass" }));
    set("short", "An empty glass");
    set("long", "This small, clear shot glass is empty.\n");
    set("bulk", 5); set("mass", 20);
    set("value", ({ 0, "copper" }));
}
