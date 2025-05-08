/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpi_gnvs.h>
#include <soc/nvs.h>

/* FIXME: check this function.  */
void mainboard_fill_gnvs(struct global_nvs *gnvs)
{
	/* The lid is open by default. */
	gnvs->lids = 1;

	/* Temperature at which OS will shutdown */
	gnvs->tcrt = 105; // This is listed as TJMax in Intel's documentation
	/* Temperature at which OS will throttle CPU */
	gnvs->tpsv = 99;
}
