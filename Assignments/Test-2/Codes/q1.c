#define BUFSIZ 1024

int count = 0;
int buf[BUFSIZ];

void dumpx() {
  extern int x;

  buf[count] = get_time_in_usec();
  count = (count + 1) % BUFSIZ;

  buf[count] = x;
  count = (count + 1) % BUFSIZ;
}
