package cb

import (
	"review.coreboot.org/coreboot.git/util/intelp2m/config/p2m"
	"review.coreboot.org/coreboot.git/util/intelp2m/platforms/common"
)

type FieldCollection struct{}

// field - data structure for creating a new bitfield macro object
// PAD_FUNC(NF3)
// prefix       : PAD_FUNC
// name         : NF3; this value will be overridden if the configurator is used
// unhide       : conditions for hiding macros
// configurator : method for determining the current configuration of the bit field
type field struct {
	prefix       string
	name         string
	unhide       bool
	configurator func()
}

// generate - wrapper for generating bitfield macros string
// fields : field structure
func generate(macro *common.Macro, fields ...*field) {
	var allhidden bool = true
	for _, field := range fields {
		if field.unhide {
			allhidden = false
			macro.Or()
			if field.prefix != "" {
				macro.Add(field.prefix).Add("(")
			}
			if field.name != "" {
				macro.Add(field.name)
			} else if field.configurator != nil {
				field.configurator()
			}
			if field.prefix != "" {
				macro.Add(")")
			}
		}
	}
	if allhidden {
		macro.Add("0")
	}
}

// DecodeDW0 - decode value of DW0 register
func (FieldCollection) DecodeDW0(macro *common.Macro) *common.Macro {
	dw0 := macro.Platform.GetRegisterDW0()
	generate(macro,
		&field{
			prefix: "PAD_FUNC",
			// TODO: Find another way to hide PAD_FUNC(GPIO) in the comment with
			// ignored fields
			unhide:       p2m.Config.GenLevel < 3 || dw0.GetPadMode() != 0,
			configurator: func() { macro.Padfn() },
		},

		&field{
			prefix:       "PAD_RESET",
			unhide:       dw0.GetResetConfig() != 0,
			configurator: func() { macro.Rstsrc() },
		},

		&field{
			prefix:       "PAD_TRIG",
			unhide:       dw0.GetRXLevelEdgeConfiguration() != 0,
			configurator: func() { macro.Trig() },
		},

		&field{
			prefix: "PAD_IRQ_ROUTE",
			name:   "IOAPIC",
			unhide: dw0.GetGPIOInputRouteIOxAPIC() != 0,
		},

		&field{
			prefix: "PAD_IRQ_ROUTE",
			name:   "SCI",
			unhide: dw0.GetGPIOInputRouteSCI() != 0,
		},

		&field{
			prefix: "PAD_IRQ_ROUTE",
			name:   "SMI",
			unhide: dw0.GetGPIOInputRouteSMI() != 0,
		},

		&field{
			prefix: "PAD_IRQ_ROUTE",
			name:   "NMI",
			unhide: dw0.GetGPIOInputRouteNMI() != 0,
		},

		&field{
			prefix:       "PAD_RX_POL",
			unhide:       dw0.GetRxInvert() != 0,
			configurator: func() { macro.Invert() },
		},

		&field{
			prefix:       "PAD_BUF",
			unhide:       dw0.GetGPIORxTxDisableStatus() != 0,
			configurator: func() { macro.Bufdis() },
		},

		&field{
			name:   "(1 << 29)",
			unhide: dw0.GetRXPadStateSelect() != 0,
		},

		&field{
			name:   "(1 << 28)",
			unhide: dw0.GetRXRawOverrideStatus() != 0,
		},

		&field{
			name:   "(1 << 1)",
			unhide: dw0.GetGPIORXState() != 0,
		},

		&field{
			name:   "1",
			unhide: dw0.GetGPIOTXState() != 0,
		},
	)
	return macro
}

// DecodeDW1 - decode value of DW1 register
func (FieldCollection) DecodeDW1(macro *common.Macro) *common.Macro {
	dw1 := macro.Platform.GetRegisterDW1()
	generate(macro,
		&field{
			name:   "PAD_CFG1_TOL_1V8",
			unhide: dw1.GetPadTol() != 0,
		},

		&field{
			prefix:       "PAD_PULL",
			unhide:       dw1.GetTermination() != 0,
			configurator: func() { macro.Pull() },
		},

		&field{
			prefix:       "PAD_IOSSTATE",
			unhide:       dw1.GetIOStandbyState() != 0,
			configurator: func() { macro.IOSstate() },
		},

		&field{
			prefix:       "PAD_IOSTERM",
			unhide:       dw1.GetIOStandbyTermination() != 0,
			configurator: func() { macro.IOTerm() },
		},

		&field{
			prefix:       "PAD_CFG_OWN_GPIO",
			unhide:       macro.IsOwnershipDriver(),
			configurator: func() { macro.Own() },
		},
	)
	return macro
}

// GenerateMacro generates the field macro collection
func (f FieldCollection) GenerateMacro(macro *common.Macro) *common.Macro {
	macro.Add("_PAD_CFG_STRUCT(").Id().Add(", ")
	f.DecodeDW0(macro).Add(", ")
	return f.DecodeDW1(macro).Add("),")
}
