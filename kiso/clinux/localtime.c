struct tm _tmbuf;

struct tm *localtime(const time_t *t){
  return __tz_convert(t, 1, &_tmbuf);
}
