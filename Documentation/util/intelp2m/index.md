Intel Pad to Macro (intelp2m) converter
=======================================

The utility generates `output/gpio.h` with the GPIO configuration for SoC or PCH from intel.
Use it to create coreboot port for your motherboard in the `src/mainboard/your-motherboard`
directory. Depending on the settings, you can create several configuration formats:
- [coreboot macros](../../getting_started/gpio.md);
- [Intel FSP macros](../../soc/intel/fsp/index.md).

Installing the latest version:

```bash
go install review.coreboot.org/coreboot.git/util/intelp2m@master
```

Including in the project as an external library:

```bash
go get review.coreboot.org/coreboot.git/util/intelp2m@master
```

## Build

Since the utility is written in Go, you need to install the official
[go-compiler and go-tools](https://go.dev/dl/) to build the executive
image.

```bash
cd util/intelp2m
make
./intelp2m -version
```

Set automatic argument completion:

```bash
complete -C `pwd`/intelp2m ./intelp2m
```

## Demo

```bash
./intelp2m -platform snr -file parser/testlog/inteltool_test.log
```

## Input data

The chipset register dump obtained using [inteltool](../../util.md) is used as input data.

```bash
cd util/inteltool
make
sudo ./inteltool -G > inteltool.log
```

After this step, you can generate `gpio.h`:

```bash
./intelp2m -file ../inteltool/inteltool.log
```

More details in the help:

```bash
./intelp2m -h
```

## Platforms

The utility supports the following chipsets from Intel:

* `adl` - Alder Lake PCH
* `apl` - Apollo Lake SoC
* `cnl` - CannonLake-LP or Whiskeylake/Coffeelake/Cometlake-U SoC
* `ebg` - Emmitsburg PCH with Xeon SP
* `ehl` - Elkhart Lake SoC
* `jsl` - Jasper Lake SoC
* `lbg` - Lewisburg PCH with Xeon SP
* `mtl` - MeteorLake SoC
* `snr` - Sunrise PCH or Skylake/Kaby Lake SoC
* `tgl` - TigerLake-H SoC

The `-platform` option allows you to identify one of the above platforms:

```bash
./intelp2m -platform <platform> -file path/to/inteltool.log
```

Show more details:

```bash
./intelp2m -platform ?
```

## Auto-check macro

The utility automatically checks the bit fields of the GPIO registers before generating the macro.
If the bit is set to 1 in a register but isn't used in the "short" macro, the "long" macro is
generated. This avoids data loss in the configuration.

```c
// the "short" macro:
PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_39, UP_20K, DEEP, NF1, TxLASTRxE, DISPUPD),

// the "long" macro:
_PAD_CFG_STRUCT(GPIO_39, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF), PAD_PULL(UP_20K) | PAD_IOSTERM(DISPUPD)),

// [*] PAD_TRIG(OFF) isn't used in the "short" macro.
```

The option `-u`, `-unchecked` is used to disable automatic verification.
In this case, all macros in `gpio.h` are generated in the "short" format:

```c
...
PAD_NC(GPP_F18, NONE),
PAD_CFG_NF(GPP_F19, NONE, PLTRST, NF1),
...
```

```bash
./intelp2m -unchecked -platform apl -file path/to/inteltool.log
```

## Excluding fields from the macro

The utility can generate "long" macros without fields that aren't used in "short" ones.
The `-e`, `-exclude` option is used to exclude these fields from the generated macros in
`gpio.h`:

```bash
./intelp2m -exclude -platform apl -file path/to/inteltool.log
```

```c
_PAD_CFG_STRUCT(GPIO_39, PAD_FUNC(NF1) | PAD_RESET(DEEP), PAD_PULL(UP_20K) | PAD_IOSTERM(DISPUPD)),

// [*] PAD_TRIG(OFF) field was excluded from the "long" macro.
```

## Packages

```text
+-------------------------------------------------------------------+
|                              main                                 |
+-------------------------------------------------------------------+
                         |                 |                 |
                         V                 V                 V
+------------+   +--------------+   +-------------+   +-------------+
|  template  |<--|    parser    |   |  generator  |   |   printer   |
+------------+   +--------------+   +-------------+   +-------------+
                         |
                         V
+-------------------------------------------------------------------+
|                           platforms                               |
+-------------------------------------------------------------------+
    |          |          |          |          |               |
    V          V          V          V          V               V
+-------+  +-------+  +-------+  +-------+  +-------+       +-------+
|  adl  |  |  apl  |  |  cnl  |  |  lbg  |  |  snr  | * * * | other |
+-------+  +-------+  +-------+  +-------+  +-------+       +-------+
    |          |          |          |          |               |
    V          V          V          V          V               V
+-------------------------------------------------------------------+
|                             common                                |
+-------------------------------------------------------------------+
                  |                           |              |
                  V                           |              |
+------------------------------------+        |              |
|               fields               |        |              |
+------------------------------------+        |              |
     |            |             |             |              |
     V            V             V             V              V
+--------+   +---------+   +---------+  +-----------+  +------------+
|   cb   |   |   raw   |   |   fsp   |  |   macro   |  |  register  |
+--------+   +---------+   +---------+  +-----------+  +------------+
```

## Format

Depending on the options -i, -ii, -iii, -iiiii (information level),
the utility can generate the configuration in different formats:

```bash
./intelp2m [-i | -ii | -iii | -iiii] -platform apl -file path/to/inteltool.log
```

* i adding a function name:

```c
_PAD_CFG_STRUCT(GPIO_39, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF), PAD_PULL(UP_20K) | PAD_IOSTERM(DISPUPD)), /* LPSS_UART0_TXD */
```

* ii adds configuration register values:

```c
/* GPIO_39 - LPSS_UART0_TXD */
/* DW0: 0x44000400, DW1: 0x00003100 */
_PAD_CFG_STRUCT(GPIO_39, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF), PAD_PULL(UP_20K) | PAD_IOSTERM(DISPUPD)),
```

* iii adds information about ignored fields:

```c
/* GPIO_39 - LPSS_UART0_TXD */
/* DW0: 0x44000400, DW1: 0x00003100 */
/* DW0 : PAD_TRIG(OFF) - IGNORED */
_PAD_CFG_STRUCT(GPIO_39, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF), PAD_PULL(UP_20K) | PAD_IOSTERM(DISPUPD)),
```

* iiii adds the "short" macro corresponding to the current one (possibly after excluding unused fields):

```c
/* GPIO_39 - LPSS_UART0_TXD */
/* DW0: 0x44000400, DW1: 0x00003100 */
/* DW0: PAD_TRIG(OFF) - IGNORED */
/* PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_39, UP_20K, DEEP, NF1, TxLASTRxE, DISPUPD), */
_PAD_CFG_STRUCT(GPIO_39, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF), PAD_PULL(UP_20K) | PAD_IOSTERM(DISPUPD)),
```

The same without automatic check:

```c
/* GPIO_39 - LPSS_UART0_TXD */
/* DW0: 0x44000400, DW1: 0x00003100 */
/* DW0: PAD_TRIG(OFF) - IGNORED */
/* _PAD_CFG_STRUCT(GPIO_39, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF), PAD_PULL(UP_20K) | PAD_IOSTERM(DISPUPD)), */
PAD_CFG_NF_IOSSTATE_IOSTERM(GPIO_39, UP_20K, DEEP, NF1, TxLASTRxE, DISPUPD),
```

iiii generates an original macro in the comments.

## Long macros with fields collection

Depending on the value of the option -fields, the utility can generate
long macros with different styles of the field collection:

```bash
./intelp2m -fields [fsp | cb | raw] -platform apl -file ../apollo-inteltool.log
```

* fsp

```c
{ GPIO_SKL_H_GPP_A12, { GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInvOut, GpioOutLow, GpioIntSci | GpioIntLvlEdgDis, GpioResetNormal GpioTermNone, GpioPadConfigLock },
```

* cb

```c
_PAD_CFG_STRUCT(GPIO_39, PAD_FUNC(NF1) | PAD_RESET(DEEP) | PAD_TRIG(OFF), PAD_PULL(UP_20K) | PAD_IOSTERM(DISPUPD)),
```

* raw

```c
_PAD_CFG_STRUCT(GPP_A10, 0x44000500, 0x00000000),
```

Show more details:

```bash
./intelp2m -fields ?
```

## Unit testing

Please run the tests before creating a new commit:

```bash
make test
```

If successful, all tests contain the PASS prefix.
