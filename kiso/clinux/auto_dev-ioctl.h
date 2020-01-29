struct args_ismountpoint{
  union{
    struct args_in{
      __u32 type;
    } in;
    struct args_out{
      __u32 devid;
      __u32 magic;
    }out;
  };
};
