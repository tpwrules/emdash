#ifndef BOOT_APP_H
#define BOOT_APP_H

// called before system init to boot application
// if that's possible
// (i.e. checksums match, not asked to bootload, etc)
void boot_app_if_possible(void);

#endif