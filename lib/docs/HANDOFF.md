# Nexus-96: Shattered Sector — Project Handoff

A living orientation doc for anyone (human or AI) picking up this project. It is the **map and the traps**, not a code dump. Read the actual repo files for detail.

> **Before you build anything:** check the source of truth, not this document's paraphrase of it. Read the actual `.c` file. If the task is "make it like The Two Towers," log into t2tmud.org and look. Two separate sessions have now burned hours building from this doc's wording instead of from the thing itself.

---

## 1. What this is

A private, self-hosted MUD recreating the feel of **The Two Towers** (t2tmud.org), the LPMUD that Jeremy and his friend **Jarrod** played years ago. It runs the **TMI-2 mudlib** on the modern **FluffOS** driver. It's a **shared sandbox** for the two of them to build in and goof off together, reached through a themed hub called the **Nexus** (branded "Nexus-96: Shattered Sector"). One of the first worlds they'll build together is a walkthrough of their old high school.

Admin character: **Trelane**. GitHub: **itsremyinnit/lcars-mud**.

---

## 2. Infrastructure map

**The VM (`LCARS-MUD`)** — Ubuntu Server, hostname `lcars-mud`, `192.168.4.33` (static DHCP reservation, `lcars.local` A/PTR records). Runs on Hyper-V host **LCARS-SRV** (`192.168.4.41`).

- Isolated by Hyper-V ACLs: can reach the internet and LCARS-SRV/router, but **not** the rest of the LAN. IPv6 disabled.
- SSH only from LCARS-SRV (key-only). To connect: from LCARS-SRV PowerShell, `ssh lcars_admin@lcars-mud.lcars.local`.

**Ports (public via Eero forward + ufw `limit`):**
- `5555` — plain telnet, **local only** (blocked at the firewall from outside; used for testing from LCARS-SRV)
- `5556` — telnet + TLS (Mudlet: host `mud.mettech.org`, port 5556, "secure")
- `5557` — TLS websocket, the **browser web client** at `https://mud.mettech.org:5557/`

**Service accounts on the VM:**
- `mud` — owns and runs the driver (systemd service `lcars-mud`). Sandboxed (noexec, ProtectSystem, etc.). **All lib files should be owned by `mud`.**
- `mudgit` — owns the git repo and runs the 10-minute auto-sync; holds a single-repo GitHub **deploy key**. In the `mud` group.
- `mudbackup` — forced-command SSH key; LCARS-SRV pulls the nightly data archive through it.
- `mudcert` — forced-command SSH key; LCARS-SRV pushes renewed TLS certs through it.

**LCARS-SRV side (Windows, scheduled tasks as Administrator):**
- `LCARS-MUD-Backup-Pull` (1:30 AM) — pulls the VM's nightly data archive into `D:\Backup\LCARS-MUD`, which Rclone mirrors to OneDrive at 2:00 AM.
- `LCARS-MUD-Cert-Renew` (3:00 AM) — Posh-ACME renews the Let's Encrypt cert (GoDaddy DNS validation, credentials reused from the existing `GoDaddyDDNS.ps1`) and deploys it to the VM.
- `LCARS-GoDaddy-DDNS` — keeps `vpn.mettech.org` (and via CNAME, `mud.mettech.org`) pointed at home.

**On the VM:**
- Driver binary: `/opt/mud/bin/driver` (root-owned, `mud`-group, mode 750)
- Mudlib: `/opt/mud/lib`
- Config: `/opt/mud/etc/config.tmi2` (root-owned; the running MUD can read, not write)
- TLS certs: `/opt/mud/etc/tls/` (locked down; only `mud` can read the key, via ACL)
- Compiled binaries: `/opt/mud/lib/data/binaries` (see §7)
- FluffOS source (for rebuilds): `~/src/fluffos` under `lcars_admin`
- Build recipe: `~/src/fluffos-build-notes.txt`
- Weekly maintenance restart: Sundays 4:00 AM Pacific (systemd timer) — this is how renewed certs get loaded.

---

## 2a. Git layout — READ THIS BEFORE ANY GIT COMMAND

**This is a split layout. There is no `.git` directory anywhere in the work tree.** An earlier version of this doc called `/opt/mud/lib` "the git work tree," which is wrong on both counts and has already cost one long session.

- **Bare repo:** `/var/lib/mudgit/lcars-mud.git`
- **Work tree:** `/opt/mud` (the parent of `lib/`, not `lib/` itself)
- **Runs as:** `mudgit`, which is the only account that can read the bare repo

So `git -C /opt/mud <anything>` fails with "not a git repository," and `git -C /opt/mud rev-parse --show-toplevel` **returns empty and exits nonzero.** That is expected, not a fault. Never chain a command onto `$(...)` capture of it; an empty path silently resolves to the caller's home directory and produces a misleading "Permission denied."

**Symptom of getting the work tree wrong:** passing `--work-tree=/opt/mud/lib` instead of `/opt/mud` does **not** error. Git looks for `lib/...` underneath `lib/`, finds nothing, and reports **every tracked file in the repo as deleted** while listing the real `adm/`, `d/`, `std/` directories as untracked. Hundreds of ` D ` lines in `status` means the work tree argument is wrong, not that the lib was wiped.

Every git command takes this shape:

```bash
sudo -u mudgit sh -c 'cd /opt/mud && git --git-dir=/var/lib/mudgit/lcars-mud.git --work-tree=/opt/mud <subcommand>'
```

Running as `mudgit` from `/` also emits `error: unable to open mailmap at .mailmap: Permission denied`. Cosmetic; silence it with `-c mailmap.file=/dev/null`.

Patch paths in the repo are relative to `/opt/mud`, so they begin `lib/...` and `git apply` wants the default `-p1`.

**Which user for what:**
- Git operations (`apply`, `checkout`, `status`, `log`, `commit`) → `sudo -u mudgit`
- Direct lib file edits outside git (`sed -i`, `tee`) → `sudo -u mudgit` also works and keeps group perms right; files must end up readable by `mud`
- Reading lib files → `sudo` (as `lcars_admin` you cannot descend into `/opt/mud/lib`)

**Ignore rules live outside the repo.** There is no `.gitignore` anywhere in the checkout. Exclusions (driver binary, `*.o` saves, logs, tmp, TLS, compiled binaries) are in `/var/lib/mudgit/lcars-mud.git/info/exclude`, invisible to anyone reading the repo on GitHub. Because the sync does `add -A` over the whole work tree, **anything new that writes runtime output needs a rule added there first**, or it gets committed and pushed to a public repo.

**Auto-sync:** `/usr/local/sbin/lcars-mud-sync` runs as `mudgit` every 10 minutes via `lcars-mud-sync.timer`. It does `add -A`, commits as "In-game edits \<timestamp\>", then fetch / rebase onto `origin/main` / push. It aborts on rebase conflict and says so. To keep it from committing a half-finished change mid-test, `sudo systemctl stop lcars-mud-sync.timer` first and start it again after.

**Never run `reset --hard`** against this work tree casually. It discards uncommitted in-game `ed` edits that the timer hasn't picked up yet, and those exist only in the nightly backup.

---

## 3. How to work on it

- **Two shells:** PowerShell on LCARS-SRV (Windows/Hyper-V/backup/cert tasks) and a bash SSH session on the VM. Always check the prompt before pasting; mixing them up is the #1 time-waster. Label every command block with where it runs.
- **Editing LPC:** change the file on disk, then `update /path/to/file` **in-game** (as Trelane) to recompile it live. Warnings are fine; `error:` is not. Errors get written to `/u/t/trelane/log` too.
- **`update` is safe on an occupied room.** `/cmds/object/_update.c` filters the room's inventory down to users, moves them to the void, destructs and reloads, then moves them back. No `dupdate` or re-`goto` needed for a single room.
- **Changing an inherited base does nothing on its own.** Inherited programs are compiled into each child, so after editing `/d/Nexus/std/nexus_room.c` you must `dupdate /d/Nexus/rooms` (or `update -R` per room) before the change appears anywhere.
- **Restart vs update:** most changes load with `update`. Things read only at boot need a service restart: **the master's groups/access files, the config file, and the preload list.** A restart saves players cleanly. See §3a before restarting.
- **Player saves survive restarts.** Runtime data (`.o` files, logs) is **not** in Git — it's covered by the nightly backup. Only code and config are tracked.
- **Colors:** the mudlib uses `%^COLOR%^` codes (valid names in `/adm/daemons/terminal.c`), translated per-client on output to a **logged-in player**. Pre-login text (the welcome screen) has no player to translate, so it must use **raw ANSI escapes** instead.
- **Room descriptions are stored pre-wrapped.** Rooms set `long` via a `@EndText` heredoc with hard line breaks at ~72 columns. Nothing re-wraps at output time. This matters any time you want to append to a description: the text will not reflow, so appended prose lands as its own overlong line unless you add wrapping yourself (see §5, exits).

---

## 3a. Boot integrity — what a restart can silently break

`groups` and `access` are **not** parsed at `epilog()`. They load lazily on the first `valid_read`/`valid_write`, and on failure `master.c` calls `shutdown()` directly. A parse failure therefore does not print a clean error and stop; it looks like the service dying a second or two into boot with systemd restarting it in a loop. Check `systemctl is-active` after a 15-second wait, not immediately.

**The silent one.** `/adm/obj/master/groups.c` verifies that each bare username in `/adm/etc/groups` has a save file at `/data/std/connection/<first-letter>/<name>.o`. If it is missing, the parser prints "Continuing parse" and **drops the name**. `(root) trelane` is the only real bare name in the file, and `admin`, `adminaccess`, `conveners`, `socket`, `www`, and `nexus` all derive from `root`. If `trelane.o` is absent at boot, the MUD comes up healthy, listens on all three ports, serves TLS, and has **no admin at all**. Because `.o` files are not in Git, a rebuild from the repo alone produces exactly that state. Restore runtime data from the nightly backup, not just the repo.

`Backbone` and `News` failing that same check is **normal**. They are pseudo-uids with no player save.

Undefined groups referenced in `/adm/etc/access` (`tmi` lowercase, `adm`, `lima`, `teachers`, `spells`) are dead entries, not parse errors; `load_access()` never validates group names. Related: `check_access()` hands any `/d/<Domain>/...` path straight to that domain's `d_master` before consulting the access mapping, so the `(/d/Nexus)` line in `access` never fires. Edit `d_master.c` for domain permissions, not the access file.

Preload failures are caught per-object and logged, not fatal. Grep the boot journal for `Got error`.

**Pre-flight before a restart:** confirm every `[Domain]` in `groups` has a `d_master.c`, every bare user has a save file, every preload path exists, and the driver can read the config and the TLS files. Afterwards, confirm `NRestarts=0` and that `openssl s_client -connect localhost:5556` serves the same cert dates as the files on disk. The weekly restart is the mechanism that loads renewed certs, so that check is the one that proves cert renewal actually works.

---

## 4. FluffOS-vs-1990s-mudlib gotchas (the expensive ones)

These are modern-driver incompatibilities that cost real time to find. If something old-mudlib breaks, check here first.

- **`static` is gone.** Modern FluffOS always has `SENSIBLE_MODIFIERS`. Old `static` on a variable → `nosave`; on a function → `protected`. But watch the combos: `private static` → just `private` (not `private protected`, which is illegal); `static` across a line break before the function name is easy to miss.
- **`export_uid()` is a no-op if the target already has an euid.** With `AUTO_SETEUID`, freshly-cloned objects get an euid immediately, so `export_uid` silently fails. Fix: have the object call `seteuid(0)` on itself first (see `connection.c`'s `logon()` / `clear_euid()` pattern) before `export_uid`. This bit us in finger, makewiz, and unwiz for offline players.
- **Variable declarations must be at the top of a function**, not partway through a nested block. Declaring mid-block throws confusing `Left argument of -> is not a class` errors.
- **`RNAME` etc. are macros**, not properties. `RNAME` expands to `query("real_name")`, so `link->RNAME` works but only as a bare top-level expression; don't wrap it in a larger expression or cast it.
- **Virtual objects:** TMI-2's `virtual_d` routing was written for paths **without** a leading slash; FluffOS passes them **with** one. Strip a leading `/` before the `sscanf` route-matching or every virtual room silently fails to load.
- **`external_start` / FFI are security risks.** FFI is denied via `master::valid_ffi()` (returns 0). The `external` package was compiled **out** entirely (`-DPACKAGE_EXTERNAL=OFF`). The service also runs with a noexec sandbox allowing only the driver's own shared libs.
- **`PACKAGE_PCRE=OFF`** — the old PCRE1 lib is gone from Ubuntu; TMI-2 doesn't need it.
- **The prompt is NOT set via the driver.** `set_prompt()` is a stub in this build. The driver draws the prompt by calling the interactive's **`write_prompt()`** (because `HAS_WRITE_PROMPT` is flagged). Our live prompt works by having `write_prompt()` in `/std/user/tsh.c` call `update_prompt()` in `/std/user.c`, which reads the template from the **`myprompt`** env var (not `prompt` — the driver's own `prompt` is kept empty so it never double-draws), substitutes `$hp/$HP/$sp/$SP/$me`, and sends via `message("prompt", ...)`. `set prompt` is intercepted in `/cmds/std/_set.c` to write `myprompt`.
- **`%^RESET%^` gets appended** to some env vars by `_set.c`; strip it when reading them back.
- **`ed`/editor temp files:** players can't write arbitrary paths. Use a writable temp path (e.g. `/tmp/...`), not a bare filename. `unique_name()` is not a global efun here.
- **A domain needs a `d_master.c`** (at `/d/<Domain>/adm/d_master.c`, inheriting `/adm/obj/master/d_master`) for its own objects to write in its data dir. The base grants the domain's own uid write access to `data/` and read to all. **Do not** add a `[Domain]` entry to `/adm/etc/groups` unless that domain master exists first, or the groups parse fails and **the master shuts the MUD down at boot.**
- **Admins bypass the settable-variable whitelist in `_set.c`.** Typing `set room exit parens` as Trelane silently creates a junk env var named `room` rather than erroring. `unset <n>` removes it.
- **`test -r` cannot see ACL-granted permissions.** `/opt/mud/etc/tls/` grants `mud` access through ACL entries rather than mode bits, and `sudo -u mud test -r <file>` returns false anyway. Verify ACL-protected paths with an actual read (`sudo -u mud head -c 32 <file>`), never with `test -r`. A false negative here will send you chasing a cert-permissions failure that does not exist.
- **Unsudoed commands after sudoed ones.** `lcars_admin` cannot descend into `/opt/mud/lib` or `/opt/mud/etc`. A glob like `sudo stat /opt/mud/etc/tls/*.pem` expands as `lcars_admin` **before** sudo runs and fails; so does a bare `ls -ld` on a path you just created with `sudo install -d`. Put the whole thing under `sudo`, or name files explicitly.

---

## 5. What's built (the Nexus)

All under `/d/Nexus/`. Wizards arrive at the **Threshold** on login; players still start in the TMI-2 quad.

- **Rooms:** a north-south spine (Threshold → Grand Concourse → Commons → Crafthall → Hall of Banners → Concourse of Arches → Far Concourse) with side rooms off it (Lamplit Hall, Kindled Hearth + Inn above, Hall of Records, Rookery, Workshop, Artificer's Stall, Proving Ground). Shared base: `/d/Nexus/std/nexus_room.c`. The exit graph is closed and reciprocal; verified 2026-09-19.
- **Arches:** ring-gated exits. Only a wizard wearing their own **Calenmîr** may pass. The **Bell Arch** (east from the Concourse of Arches) leads to a placeholder **Lobby** — this is where the **high school** will be built. Other arches are sealed ("not yet"). The gate is enforced through `pre_exit_func/<dir>`, and it holds on `go`, `sneak`, and ghost movement alike (all three resolve the same nested property).
- **Sealed arches appear in the exits line on purpose.** `add_arch()` sets `exits/<dir>` whether or not the arch is sealed, so the Far Concourse advertises east, west, and north even though all three always refuse. Accepted as flavor; do not "fix" it. Those three also point at `far_concourse` itself, harmless while sealed but repoint them if a seal is ever lifted.
- **Calenmîr, the focus ring** (`/d/Nexus/obj/calenmir.c`): bound to its bearer (can't drop/give/steal/put), keyed with a per-owner rune, has a voice (`ask ring about ...`). **Does not autoload** — the login re-forge is the single source (autoload caused rings to stack). Wearing it enables wizard commands; without it, "your will scatters."
- **Willpower gate:** in `cmd_hook` (`/std/user.c`), wizard-folder commands require the worn ring. Admins exempt.
- **Ring ceremony** (`/d/Nexus/adm/ceremony_d.c`): on `makewiz`, the ring appears; first wearing carries the wizard through "the Between" (paced narration) to the Threshold. Plays at next login if promoted offline.
- **Quarters:** virtual Inn wings + private rooms per wizard (`/d/Nexus/adm/quarters_d.c` + `/d/Nexus/virtual/server.c`). Slots go **vacant** on removal and are reused, so nobody's door moves. `invite`/`grant`/`revoke`/`guests` manage access.
- **Hearthside notice board** (`/d/Nexus/boards/hearth_board.c`): inherits `/std/board/bboard`, saves to `/d/Nexus/data` with its attic at `/d/Nexus/data/attic`. Loaded by `kindled_hearth.c` calling it at create time, so it has no separate preload entry.
- **Promotion/demotion/banishment:** `makewiz`, `unwiz` (demote; ring departs; quarters vacated), `banish [days] <n>` (parks the character 90 days by default; login refused; finger shows it; name reserved; archived on expiry via `/d/Nexus/adm/banish_d.c`; ASCII "phantom zone" broadcast), `unbanish`. Stock permanent name-ban is now `banishname`. `banish_d` is the only Nexus object in the preload list.
- **Legend system** (`/d/Nexus/adm/legend_d.c`): T2T-style `finger`/`legend` card with tiers (player/wizard/admin see progressively more), settable `TITLE` (wizards need `$N`; players get "Name the <race>") and `INFO`, life **stories** (`story` to write, `story <n>` to read, 200-line cap), and `register` in the Rookery to set a mail home. Offline lookups use a saved snapshot.
- **Live prompt:** default `HP:$hp EP:$sp>`; players `set prompt <template>` with `$hp $HP $sp $SP $me`. (See the prompt gotcha above.)
- **Welcome screen** (`/adm/news/welcome`): raw-ANSI "Nexus-96: Shattered Sector" fractured triptych (Seattle / alien world / fantasy keep).
- **Room exits** (`/cmds/std/_look.c`, done): keyed off the player's existing `brief` setting, not a separate toggle.
  - **Brief:** abbreviated exits in parens appended to the room name, e.g. `The Grand Concourse(w, e, n and s)`.
  - **Verbose:** a sentence flush left on its own line under the description, e.g. `The only obvious exits are west, east, north and south.`
  - **Known divergence from T2T:** real T2T flows that sentence into the description paragraph as its last sentence. We can't, because our room `long` values are pre-wrapped with hard newlines (see §3). Matching T2T exactly would mean stripping the trailing newline and running the whole description through `sprintf("%-=75s", long)` at output, which re-wraps every room and would flatten any deliberately shaped text (signs, inscriptions). Deferred on purpose.
  - The earlier standalone `roomexits` env var (parens/sentence/off) was **removed**; don't reintroduce it.

**Test characters:** `testwiz`, `testguy` exist for testing promotion/quarters/etc. Clean them up once Jarrod is onboarded and the flows are proven.

---

## 6. In flight / next up

1. **The Lobby description** — the placeholder room beyond the Bell Arch, to be replaced with the real high school lobby once Jeremy has photos.
2. **Bring Jarrod in as co-wizard/builder** — `mailreg jarrod` to register his name, deliver a starter password separately, and a short "how to connect" note (Mudlet on 5556, or the web client on 5557). Then `makewiz jarrod` for the full ring ceremony, and add `jarrod` to the Nexus `builders` group so he can build alongside Jeremy. Note that no `builders` group exists yet; `(nexus)` in `/adm/etc/groups` currently resolves to `(admin)` only.
3. **Optional later:** working shop/inn systems, the Proving Ground training construct, the recharge ceremony for the ring (original oath, not the GL/One-Ring text), IPv6, the FTP-vs-Git decision revisited.

---

## 7. Checkpoints & safety

Hyper-V checkpoints mark milestones (`Phase1-Baseline` … `Legend-Complete`, etc.). Everything is committed to GitHub, backed up nightly to OneDrive, and runs as a self-restarting service. It is always safe to stop.

**Morning health check** (VM): `systemctl is-active lcars-mud lcars-mud-sync.timer lcars-mud-backup.timer`. (LCARS-SRV): confirm the backup-pull and cert-renew tasks last ran with result 0.

**Compiled binaries:** `/opt/mud/lib/data/binaries` is runtime output (per `save binaries directory` in `config.tmi2`), owned by `mud`, and excluded from Git via `lib/data/binaries/` in `/var/lib/mudgit/lcars-mud.git/info/exclude`. If the directory goes missing, FluffOS silently recompiles the entire lib at every boot — slow, but not an error, so nothing will tell you.

**Repo visibility:** the repo was made public to allow direct read access during a working session. If it should go back to private, do that and note it here.
