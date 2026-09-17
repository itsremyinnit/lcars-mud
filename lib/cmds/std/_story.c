// /cmds/std/_story.c: read, write, or clear a character's life story. LCARS-MUD
#include <mudlib.h>
inherit DAEMON;

#define MAX_LINES 200

private string story_path(string name) { return user_path(name) + ".story"; }

int cmd_story(string str) {
    string me, path, tmp;

    me = (string)this_player()->query("name");
    if (str == "me" || str == "self") str = "";

    // story <name> : read someone's story
    if (str && str != "" && str != "clear") {
        str = lower_case(str);
        if (!user_exists(str)) { write("There is no one by that name.\n"); return 1; }
        path = story_path(str);
        if (file_size(path) <= 0) {
            write(capitalize(str) + " has not recorded a life story.\n");
            return 1;
        }
        write(capitalize(str) + "'s story reads:\n");
        this_player()->more(explode(read_file(path), "\n"));
        return 1;
    }

    // story clear : delete your own
    if (str == "clear") {
        path = story_path(me);
        if (file_size(path) <= 0) { write("You have no story to clear.\n"); return 1; }
        rm(path);
        write("Your life story fades back into untold possibility.\n");
        this_player()->save_data();
        return 1;
    }

    // story : write or replace your own
    write("Compose your life story. It will be saved when you finish.\n");
    tmp = "/tmp/story." + me + "." + time();
    rm(tmp);
    this_player()->edit(tmp, "story_done", this_object());
    return 1;
}

int story_done(string ignore) {
    object writer = this_player();
    string fname, body, *lines, me;

    me = (string)writer->query("name");
    fname = (string)writer->query_edit_filename();
    if (!fname || file_size(fname) < 0) {
        write("Story unchanged.\n");
        return 1;
    }
    body = read_file(fname);
    rm(fname);
    writer->set_edit_filename("");

    if (!body || body == "") { write("Story unchanged.\n"); return 1; }
    lines = explode(body, "\n");
    if (sizeof(lines) > MAX_LINES) {
        write("That's over " + MAX_LINES + " lines. Please trim it and try again.\n");
        return 1;
    }

    seteuid(me);
    if (write_file(story_path(me), body, 1)) {
        write("Your life story is recorded.\n");
        writer->save_data();
    } else {
        write("Something went wrong; your story was not saved.\n");
    }
    return 1;
}

string help() {
    return "Syntax:\n  story          - write or replace your own life story\n" +
           "  story <name>   - read someone's life story\n" +
           "  story clear    - erase your own life story\n\n" +
           "Your story appears on your legend, and can be up to " + MAX_LINES + " lines.\n";
}
