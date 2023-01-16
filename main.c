#include <types.h>
#include <kos_drv.h>
#include <pci.h>

#define MODNAME "ENS1370"
#define SERVICE "SOUND"

#define VENDOR_ID 0x1274
#define DEVICE_ID 0x5000
#define ENS1370_ID PCI_ID(VENDOR_ID, DEVICE_ID)

struct {
    char*   name;
	u32     base;	    /* changed to 32 bits */
	u8      irq; 
	u8      revision;	/* version of the device */
    pci_id_t pdev_id;
} ens1370_dev;

bool find_device(pci_dev_t *pci_dev, u32 id)
{
    pci_dev_t *proot = GetPCIList();
    pci_dev_t *pdev = proot;

    do {
        if (pdev->id.val == id) {
            *pci_dev = *pdev;
            return true;
        }
        pdev = pdev->next;
    } while (proot != pdev); 

    return false;
}

int __stdcall sound_service(ioctl_t *ioctl)
{
    return 0;
}

int drvEntry(int action, char *cmdline)
{
    static pci_dev_t pdev;

    if(action != 1)
        return 0;

    if (!find_device(&pdev, ENS1370_ID)) {
        putstring("Not device found!\n");
        return 0;
    }

    ens1370_dev.base = PciRead32(pdev.bus, pdev.devfn, PCI_BAR) & 0xfffffffe;
    ens1370_dev.irq = PciRead8(pdev.bus,pdev.devfn, PCI_ILR); 

    int retval = RegService(SERVICE, sound_service);
    AttachIntHandler(ens1370_dev.irq, sound_service, 0);

    printk("IRQ: %x\n", ens1370_dev.irq);

    return retval;
};
