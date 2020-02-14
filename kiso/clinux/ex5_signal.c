req.tv_sec = 60;
req.tv_nsec = 60;
val = nanosleep(&req, &rem);
printf("ret = %d remain = %d:%d\n", val, rem.tv_sec, rem.tv_nsec);
