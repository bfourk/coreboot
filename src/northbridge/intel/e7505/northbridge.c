/* SPDX-License-Identifier: GPL-2.0-only */

#include <assert.h>
#include <console/console.h>
#include <device/pci_ops.h>
#include <device/device.h>
#include <device/pci.h>
#include <cpu/cpu.h>

#include "e7505.h"

static void mch_domain_read_resources(struct device *dev)
{
	int idx;
	unsigned long tolmk;
	uint64_t tom, remapbase, remaplimit;
	struct device *mc_dev;

	pci_domain_read_resources(dev);

	mc_dev = pcidev_on_root(0, 0);
	if (!mc_dev)
		die("Could not find MCH device\n");

	tolmk = pci_read_config16(mc_dev, TOLM) >> 11;
	tolmk <<= 17;

	tom = pci_read_config8(mc_dev, DRB_ROW_7);
	tom <<= 26;

	/* Remapped region with a 64 MiB granularity in register
	   definition. Limit is inclusive, so add one. */
	remapbase = pci_read_config16(mc_dev, REMAPBASE) & 0x3ff;
	remapbase <<= 26;

	remaplimit = pci_read_config16(mc_dev, REMAPLIMIT) & 0x3ff;
	remaplimit += 1;
	remaplimit <<= 26;

	/* Report the memory regions */
	idx = 10;
	ram_resource_kb(dev, idx++, 0, tolmk);
	mmio_resource_kb(dev, idx++, 0xa0000 / KiB, (0xc0000 - 0xa0000) / KiB);


	ASSERT(tom == remapbase);
	upper_ram_end(dev, idx++, remaplimit);
}

static void mch_domain_set_resources(struct device *dev)
{
	assign_resources(dev->link_list);
}

static struct device_operations pci_domain_ops = {
	.read_resources   = mch_domain_read_resources,
	.set_resources    = mch_domain_set_resources,
	.scan_bus         = pci_domain_scan_bus,
	.ops_pci          = &pci_dev_ops_pci,
};

static void cpu_bus_init(struct device *dev)
{
	initialize_cpus(dev->link_list);
}

static struct device_operations cpu_bus_ops = {
	.read_resources   = noop_read_resources,
	.set_resources    = noop_set_resources,
	.init             = cpu_bus_init,
};

static void enable_dev(struct device *dev)
{
	/* Set the operations if it is a special bus type */
	if (dev->path.type == DEVICE_PATH_DOMAIN) {
		dev->ops = &pci_domain_ops;
	}
	else if (dev->path.type == DEVICE_PATH_CPU_CLUSTER) {
		dev->ops = &cpu_bus_ops;
	}
}

struct chip_operations northbridge_intel_e7505_ops = {
	CHIP_NAME("Intel E7505 Northbridge")
	.enable_dev = enable_dev,
};
