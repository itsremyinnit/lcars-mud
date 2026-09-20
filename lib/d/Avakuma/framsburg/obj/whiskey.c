// /d/Avakuma/framsburg/obj/whiskey.c
#include <mudlib.h>
inherit OBJECT;

void create() {
    set("id", ({ "whiskey", "shot", "shot of homemade whiskey", "glass" }));
    set("short", "A shot of homemade whiskey");
    set("long",
"This small, clear shot glass is full of delicious-looking, golden whiskey.\n");
    set("bulk", 8); set("mass", 25);
    set("value", ({ 0, "copper" }));
    set("no_container", 1);
    set("hands", 1);
}

void init() {
    add_action("do_drink", "drink");
}

int do_drink(string str) {
    object empty;

    if (!str || !id(str)) return 0;
    if (environment() != this_player()) {
        notify_fail("You are not holding that.\n");
        return 0;
    }
    write("You drink the whiskey, and sigh with contentment.\n");
    say((string)this_player()->query("cap_name") + " knocks back a shot.\n");
    empty = clone_object("/d/Avakuma/framsburg/obj/empty_glass");
    if (empty) empty->move(this_player());
    "/adm/daemons/disposal_d"->kill_object(this_object());
    return 1;
}
