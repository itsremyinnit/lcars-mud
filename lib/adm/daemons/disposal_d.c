// /adm/daemons/disposal_d.c
// Destroys objects on behalf of things that are not allowed to.
//
// WHY: /adm/simul_efun/overrides.c permits destruct() only when the
// caller's euid matches the target's, or the caller is root or an admin.
// A domain object (uid Avakuma, say) therefore cannot destroy a mudlib
// object (uid Backbone), which is what a trash can needs to do. And
// valid_seteuid() only lets an object claim an euid it already owns, so
// the domain object cannot elevate itself either.
//
// This daemon lives under /adm and so carries the root uid, which makes
// it able to do the destroying. It is deliberately narrow: it destroys
// the contents of a container and nothing else, it refuses livings, and
// it refuses anything flagged prevent_drop.
#include <mudlib.h>
inherit DAEMON;

void create() { seteuid(getuid()); }
void clean_up() { }

// Empty a container. Returns the number of things destroyed.
int empty(object holder) {
    object *inv;
    int i, count;

    if (!holder) return 0;

    inv = all_inventory(holder);
    count = 0;
    for (i = 0; i < sizeof(inv); i++) {
        if (!inv[i]) continue;
        if (living(inv[i])) continue;
        if (inv[i]->query("prevent_drop")) continue;
        destruct(inv[i]);
        count++;
    }
    return count;
}

// Destroy one object. Same guards as empty().
int kill_object(object ob) {
    if (!ob) return 0;
    if (living(ob)) return 0;
    if (ob->query("prevent_drop")) return 0;
    destruct(ob);
    return 1;
}
