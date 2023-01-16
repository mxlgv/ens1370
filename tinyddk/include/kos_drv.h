#ifndef __KOS_DRV_H__
#define __KOS_DRV_H__

#include <types.h>

typedef struct pci_dev_s pci_dev_t;

typedef union {
    u32 val;
    struct {
        u16 vendor;
        u16 device;
    };
} pci_id_t;

struct pci_dev_s {
    pci_dev_t *prev;
    pci_dev_t *next;
    pci_id_t  id;
    u32     class;
    u8      devfn;
    u8      bus;
    u8      reserved[2];
    u32     owner;
} __packed;

typedef struct {
    u32     handle;
    u32     io_code;
    void    *input;
    int     in_size;
    void    *output;
    int     out_size;
} __packed ioctl_t;

#define putstring(x) SysMsgBoardStr(x)

typedef int (__stdcall *srv_proc_t)(ioctl_t *);

int drvEntry(int, char *) __asm__("_drvEntry");

pci_dev_t* __import GetPCIList() __asm__("_GetPCIList");

u8 __import __stdcall  PciRead8(u32 bus, u32 devfn, u32 reg) __asm__("_PciRead8");
u16 __stdcall __import PciRead16(u32 bus, u32 devfn, u32 reg) __asm__("_PciRead16");
u32 __stdcall __import PciRead32(u32 bus, u32 devfn, u32 reg) __asm__("_PciRead32");

u32 __stdcall __import PciWrite8(u32 bus, u32 devfn, u32 reg, u8 val) __asm__("_PciWrite8");
u32 __stdcall __import PciWrite16(u32 bus, u32 devfn, u32 reg, u16 val) __asm__("_PciWrite16");
u32 __stdcall __import PciWrite32(u32 bus, u32 devfn, u32 reg, u32 val) __asm__("_PciWrite32");

int __stdcall __import RegService(const char *name, srv_proc_t proc) __asm__("_RegService");
int __stdcall __import AttachIntHandler(int irq, void *handler, u32 access) __asm__("_AttachIntHandler");

static inline void SysMsgBoardStr(char *text)
{
    __asm__ __volatile__(
        "call *__imp__SysMsgBoardStr" 
        ::"S" (text)
        :"memory");
}

void printk(char *text, ...);

#endif //__KOS_DRV_H__
