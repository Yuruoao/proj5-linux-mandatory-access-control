# Project 5
## My Solution
### Program X

1. Because we have to let Program X be only execute by UserX, we set the group of Program X to UserX (`sudo chgrp UserX ./X`) and do `sudo chmod 070 ./X`. 
2. Since /var/X/ and /var/Y/ are only allowed written by root, we have to run the command `sudo chmod u+s ./X`. So that, we can create file under /var/X and /var/Y.
3. Final result:

![](https://i.imgur.com/RumhX00.png)

We use the below apparmor profile for Program X.
**`/etc/apparmor.d/usr.local.bin.px.X`**
```=
#include <tunables/global>


/usr/local/bin/px/X {
  #include <abstractions/base>
  capability setuid,
  /bin/dash Ux, 
  /bin/bash Ux, 
}
```
We have to load/parse the profile first.
`sudo apparmor_parser -r /etc/apparmor.d/usr.local.bin.px.X`
Then we execute `./X` as UserX and get the result:

![](https://i.imgur.com/3Bcv6sF.png)

We can see from the above result that we do achieve the scenario.
Here are something to dicuss.
1. Because we have to use `system()` in X, we have to use the rule `/bin/dash Ux,` or `/bin/bash Ux,`
2. Since Program X may need a bunch of .so shared libraries, we do `#include <abstractions/base>` to make sure it can work properly.
3. Because we have to let Program X run as root, we use `setuid(0)` in Program X and use the rule `capability setuid,` in profile.
### Program Y
We use the below apparmor profile for Program Y.
**`/etc/apparmor.d/var.Y.Y`**
```=
#include <tunables/global>


/var/Y/Y {
  #include <abstractions/base>
  /var/Y/** rw, 
  /var/Y rw,  
  deny network,
}
```
We have to load/parse the profile first.
`sudo apparmor_parser -r /etc/apparmor.d/var.Y.Y`

Then we execute `./X` and get the result:

![](https://i.imgur.com/ssEjLOO.png)

To make sure it really work, let's delete some rules in the file and see how it goes.

1. delete `/var/Y/** rw,` and `/var/Y rw,`

![](https://i.imgur.com/iLUacTN.png)

2. delete `deny network,` and add `network,`

![](https://i.imgur.com/5qlft78.png)

We can see from the above result that we do achieve the scenario.
Here are something to dicuss.
1. Because the profile doesn't allow any other directories or files, Program Y can't access those not been allow. We don't need other deny rule to restrict it.
2. Since Program Y may need a bunch of .so shared libraries, we do `#include <abstractions/base>` to make sure it can work properly.

### Combine both

![](https://i.imgur.com/jGqgBfO.png)
