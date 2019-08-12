# libconfig-lookpup

A command line tool for extraction of single setting from libconfig syntax compatybile file. For more information about libconfig visit the [libconfig project page](https://hyperrealm.github.io/libconfig/).

Building
--------
```bash
gcc libconfig-lookup.c -lconfig++ -o libconfig-lookup
```

Usage
-----

libconfig-lookup \<file\> \<path\> \<type\>

*file* - Libconfig syntax compatybile file.

*path* - Path to the exact setting.

*type* - Type of setting [int|int64|float|bool|string].

Example
-------

If we have a configuration file *sample.cfg*:

```bash
libconfig-lookup sample.cfg users.[0].surnme string
```
This example matches extraction of 'surname' setting of first user in 'users' group.
