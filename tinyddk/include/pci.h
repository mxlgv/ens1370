#ifndef __PCI_H__
#define __PCI_H__

#define PCI_BAR                 0x10        /* Base Address Register */
#define     PCI_BAR_IO          0x00000001  /* Reg. refers to I/O space */
#define     PCI_BAR_TYPE        0x00000006  /* Memory BAR type */
#define     PCI_TYPE_32         0x00000000      /* 32-bit BAR */
#define         PCI_TYPE_32_1M  0x00000002  /* 32-bit below 1MB (legacy) */
#define         PCI_TYPE_64     0x00000004  /* 64-bit BAR */
#define     PCI_BAR_PREFETCH    0x00000008  /* Memory is prefetchable */
#define     PCI_BAR_IO_MASK     0xFFFFFFFC  /* I/O address mask */
#define     PCI_BAR_MEM_MASK    0xFFFFFFF0  /* Memory address mask */
#define PCI_BAR_2               0x14        /* Base Address Register */
#define PCI_BAR_3               0x18        /* Base Address Register */
#define PCI_BAR_4               0x1C        /* Base Address Register */
#define PCI_BAR_5               0x20        /* Base Address Register */
#define PCI_BAR_6               0x24        /* Base Address Register */

#define PCI_ILR                 0x3C    /* Interrupt Line Register */
#define     PCI_ILR_UNKNOWN     0xFF    /* IRQ is unassigned or unknown */

#define PCI_ID(vendor, device) (vendor + (device << 16))

#endif // __PCI_H__
