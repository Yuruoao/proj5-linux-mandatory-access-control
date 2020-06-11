#include <tunables/global>


/var/Y/Y {
  #include <abstractions/base>
  /var/Y/** rw,
  /var/Y rw,
  deny network,
}
