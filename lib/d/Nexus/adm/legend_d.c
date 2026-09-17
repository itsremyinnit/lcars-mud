// /d/Nexus/adm/legend_d.c: the T2T-style legend card, plus an offline snapshot.
#include <mudlib.h>
#include <uid.h>
inherit DAEMON;

#define SAVE_FILE "/d/Nexus/data/legends"
#define BANISH_D  "/d/Nexus/adm/banish_d"

mapping snap;   // name : ([ card fields ]) for offline lookups

void create() {
    seteuid(getuid());
    snap = ([ ]);
    restore_object(SAVE_FILE);
    if (!snap || !mapp(snap)) snap = ([ ]);
}

void clean_up() { }

// Called from the player save path so offline cards stay current.
void record(object who) {
    string name;
    object link;
    if (!who || previous_object() != who) return;
    name = (string)who->query("name");
    if (!name) return;
    link = who->query_link();
    snap[name] = ([
        "race"     : who->query("race"),
        "gender"   : who->query("gender"),
        "age"      : who->query("age"),
        "wizard"   : who->query("wizard") ? 1 : 0,
        "title"    : who->getenv("TITLE"),
        "info"     : who->getenv("INFO"),
        "mailhome" : who->getenv("MAILHOME"),
        "story"    : (file_size(user_path(name) + ".story") > 0) ? 1 : 0,
        "last_on"  : (link && link->query("last_on")) ? link->query("last_on") : time(),
    ]);
    save_object(SAVE_FILE);
}

private string field(mixed v) { return (stringp(v) && v != "") ? v : 0; }

private string rank_of(string name, int wiz) {
    if (adminp(name)) return "Admin";
    if (wiz) return "Wizard";
    return "Player";
}

private string title_line(string name, string race, string title, int wiz) {
    string cap = capitalize(name);
    if (title) {
        title = replace_string(title, "%^RESET%^", "");
        if (wiz || adminp(name)) {
            if (strsrch(title, "$N") != -1) return replace_string(title, "$N", cap);
            return cap + " " + title;
        }
        return cap + " the " + title;
    }
    return cap + " the " + (race ? race : "wanderer");
}

string legend(string name, object viewer) {
    object live, link;
    mapping d;
    string msg, cap, race, gender, title, info, mailhome, when, mailline, storyline;
    int wiz, online, is_admin, is_wiz, age;

    name = lower_case(name);
    live = find_player(name);

    if (live) {
        online = 1;
        link = live->query_link();
        race     = live->query("race");
        gender   = live->query("gender");
        age      = (int)live->query("age");
        wiz      = live->query("wizard") ? 1 : 0;
        title    = live->getenv("TITLE");
        info     = live->getenv("INFO");
        mailhome = live->getenv("MAILHOME");
    } else {
        d = snap[name];
        if (!d || !mapp(d)) return 0;
        race     = d["race"];
        gender   = d["gender"];
        age      = (int)d["age"];
        wiz      = d["wizard"];
        title    = d["title"];
        info     = d["info"];
        mailhome = d["mailhome"];
    }

    cap = capitalize(name);
    is_admin = viewer && adminp((string)viewer->query("name"));
    is_wiz   = viewer && (is_admin || viewer->query("wizard"));

    msg = title_line(name, race, field(title), wiz) + "\n";

    if (BANISH_D->query_banished(name)) {
        msg += "Banished on " + ctime(BANISH_D->query_banished_at(name));
        if (is_admin) msg += "  (released " + ctime(BANISH_D->query_expires(name))[4..10] + ")";
        msg += "\n";
    } else {
        if (online) {
            int since = (link && link->query("last_on")) ? time() - (int)link->query("last_on") : 0;
            when = "On for:  " + format_time(since, 1);
        } else {
            int lo = live ? time() : (int)snap[name]["last_on"];
            when = "Last on: " + (lo ? ctime(lo)[4..9] + ctime(lo)[19..23] : "unknown");
        }
        msg += sprintf("%-42sGender: %s\n", when, gender ? gender : "?");
    }

    msg += sprintf("%-42sRank: %s\n", "Age: " + format_time(age, 1), rank_of(name, wiz));

    mailline = field(mailhome) ? "Can be mailed: " + cap + "@" + mailhome : "";
    storyline = ((live && file_size(user_path(name) + ".story") > 0) ||
                 (!live && snap[name]["story"])) ? cap + " has recorded a life story." : "";
    msg += sprintf("%-42s%s\n", mailline, storyline);

    if (field(info)) msg += "Info:  " + replace_string(info, "%^RESET%^", "") + "\n";

    if (is_wiz) {
        string home = user_path(name);
        msg += "----------------- wizard -----------------\n";
        msg += sprintf("Home: %-22sIdle: %s\n",
            (file_size(home) == -2 ? home : "(none)"),
            online ? format_time(query_idle(live), 1) : "-");
        if (online && live->getenv("PLAN"))
            msg += "Plan: " + live->getenv("PLAN") + "\n";
    }

    if (is_admin) {
        msg += "----------------- admin ------------------\n";
        if (online && link) {
            string rn = link->RNAME;
            string em = link->query("email");
            string ip = link->query("ip");
            msg += sprintf("Real name: %-18sEmail: %s\n",
                (rn && rn != "") ? rn : "?", (em && em != "") ? em : "?");
            msg += "Host: " + ((ip && ip != "") ? ip : "?") + "\n";
        } else {
            msg += "Real name, email, and host: shown only while online.\n";
        }
    }
    return msg;
}
