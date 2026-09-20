// /d/Avakuma/framsburg/obj/empty_bottle.c
#include <mudlib.h>
inherit OBJECT;
void create() {
    set("id", ({ "bottle", "empty bottle" }));
    set("short", "An empty bottle");
    set("long", "This bottle is empty.\n");
    set("bulk", 10); set("mass", 40);
    set("value", ({ 0, "copper" }));
}
