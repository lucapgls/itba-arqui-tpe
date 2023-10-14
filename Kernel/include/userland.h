#ifndef USERLAND_H
#define USERLAND_H

static void *const sampleCodeModuleAddress = (void*)0x400000;
static void *const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

#endif