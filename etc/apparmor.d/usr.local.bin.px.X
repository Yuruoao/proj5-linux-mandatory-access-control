#include <tunables/global>


/usr/local/bin/px/X {
  #include <abstractions/base>
  capability setuid,
  /bin/dash Ux,
  /bin/bash Ux,
}
