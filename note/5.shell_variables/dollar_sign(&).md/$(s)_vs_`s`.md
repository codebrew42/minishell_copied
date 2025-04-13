https://unix.stackexchange.com/questions/5778/whats-the-difference-between-stuff-and-stuff

# don't care
( command1 | command2)


# parse : don't care
$(ls)


```bash
jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo $0 | echo $$
228180
jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ mv_name="jin"
jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo $mv_name
jin
jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ unset mv_name
jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo $mv_name

jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo $my

jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ name="hi"
jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo $(name)
Command 'name' not found, did you mean:
  command 'namei' from deb util-linux (2.37.2-4ubuntu3.4)
  command 'lame' from deb lame (3.100-3build2)
  command 'nama' from deb nama (1.216-1)
  command 'named' from deb bind9 (1:9.18.28-0ubuntu0.22.04.1)
  command 'nvme' from deb nvme-cli (1.16-3ubuntu0.3)
  command 'nam' from deb nam (1.15-5.2)
  command 'uname' from deb coreutils (8.32-4.1ubuntu1.2)
  command 'mame' from deb mame (0.242+dfsg.1-1)
Try: apt install <deb name>

jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo $name
hi
jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo `name`
Command 'name' not found, did you mean:
  command 'named' from deb bind9 (1:9.18.28-0ubuntu0.22.04.1)
  command 'namei' from deb util-linux (2.37.2-4ubuntu3.4)
  command 'nvme' from deb nvme-cli (1.16-3ubuntu0.3)
  command 'uname' from deb coreutils (8.32-4.1ubuntu1.2)
  command 'lame' from deb lame (3.100-3build2)
  command 'nama' from deb nama (1.216-1)
  command 'nam' from deb nam (1.15-5.2)
  command 'mame' from deb mame (0.242+dfsg.1-1)
Try: apt install <deb name>

jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo &`name`
[1] 230347

Command 'name' not found, did you mean:
  command 'mame' from deb mame (0.242+dfsg.1-1)
  command 'nvme' from deb nvme-cli (1.16-3ubuntu0.3)
  command 'nama' from deb nama (1.216-1)
  command 'named' from deb bind9 (1:9.18.28-0ubuntu0.22.04.1)
  command 'nam' from deb nam (1.15-5.2)
  command 'uname' from deb coreutils (8.32-4.1ubuntu1.2)
  command 'lame' from deb lame (3.100-3build2)
  command 'namei' from deb util-linux (2.37.2-4ubuntu3.4)
Try: apt install <deb name>
[1]+  Done                    echo
jiepark@c1b1c2:/sgoinfre/goinfre/Perso/jiepark$ echo $`name`
Command 'name' not found, did you mean:
  command 'namei' from deb util-linux (2.37.2-4ubuntu3.4)
  command 'lame' from deb lame (3.100-3build2)
  command 'mame' from deb mame (0.242+dfsg.1-1)
  command 'nvme' from deb nvme-cli (1.16-3ubuntu0.3)
  command 'nam' from deb nam (1.15-5.2)
  command 'uname' from deb coreutils (8.32-4.1ubuntu1.2)
  command 'named' from deb bind9 (1:9.18.28-0ubuntu0.22.04.1)
  command 'nama' from deb nama (1.216-1)
Try: apt install <deb name>
$


```