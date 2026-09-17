// /d/Nexus/adm/banish_d.c: 90-day banishment. The character is parked, finger
// shows the banishment, login and re-creation are refused, and on day 90 the
// data and home folder are archived to the attic and the name is freed.
#include <mudlib.h>
#include <config.h>
#include <uid.h>
inherit DAEMON;

#define SAVE_FILE "/d/Nexus/data/banishments"
#define DURATION  (90 * 86400)

mapping banished;   // name : ([ "at", "by" ])

void create() {
    seteuid(ROOT_UID);
    banished = ([ ]);
    restore_object(SAVE_FILE);
    if (!banished) banished = ([ ]);
    call_out("sweep", 60);
}

void clean_up() { }

private int trusted_caller() {
    object po = previous_object();
    string f;
    if (!po) return 0;
    f = file_name(po);
    return strsrch(f, "/cmds/adm/_banish") == 0 || strsrch(f, "/cmds/adm/_unbanish") == 0;
}

int query_banished(string name) { return name && mapp(banished[lower_case(name)]); }
int query_banished_at(string name) { return query_banished(name) ? banished[lower_case(name)]["at"] : 0; }
int query_expires(string name) { return query_banished(name) ? query_banished_at(name) + DURATION : 0; }
string *query_banished_names() { return keys(banished); }

int add_banish(string name, string by) {
    if (!trusted_caller() || !name) return 0;
    banished[lower_case(name)] = ([ "at" : time(), "by" : by ]);
    save_object(SAVE_FILE);
    return 1;
}

int remove_banish(string name) {
    if (!trusted_caller() || !query_banished(name)) return 0;
    map_delete(banished, lower_case(name));
    save_object(SAVE_FILE);
    return 1;
}

private void archive_character(string name) {
    string dest, home, user_file, conn_file;

    dest = ARCHIVE_DIR + "banished";
    if (file_size(ARCHIVE_DIR[0..<2]) != -2) mkdir(ARCHIVE_DIR[0..<2]);
    if (file_size(dest) != -2) mkdir(dest);
    dest += "/" + name + "-" + time();
    mkdir(dest);

    user_file = DATA_DIR + "/std/user/" + name[0..0] + "/" + name + __SAVE_EXTENSION__;
    conn_file = PDATA_DIR + name[0..0] + "/" + name + __SAVE_EXTENSION__;
    if (file_exists(user_file)) rename(user_file, dest + "/user" + __SAVE_EXTENSION__);
    if (file_exists(conn_file)) rename(conn_file, dest + "/connection" + __SAVE_EXTENSION__);
    if (file_size("/data/mail/" + name + "-mbox.o") >= 0)
        rename("/data/mail/" + name + "-mbox.o", dest + "/mail-mbox.o");

    home = user_path(name);
    if (home[<1] == '/') home = home[0..<2];
    if (file_size(home) == -2) rename(home, dest + "/home");

    log_file("banishments", ctime(time()) + ": " + name + " archived to " + dest + "\n");
}

void sweep() {
    string *names = keys(banished);
    int i, changed;

    remove_call_out("sweep");
    for (i = 0; i < sizeof(names); i++) {
        if (time() < banished[names[i]]["at"] + DURATION) continue;
        archive_character(names[i]);
        map_delete(banished, names[i]);
        changed = 1;
    }
    if (changed) save_object(SAVE_FILE);
    call_out("sweep", 86400);
}
