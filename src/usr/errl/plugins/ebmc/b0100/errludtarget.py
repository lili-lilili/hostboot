# IBM_PROLOG_BEGIN_TAG
# This is an automatically generated prolog.
#
# $Source: src/usr/errl/plugins/ebmc/b0100/errludtarget.py $
#
# OpenPOWER HostBoot Project
#
# Contributors Listed Below - COPYRIGHT 2020,2022
# [+] International Business Machines Corp.
#
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
# implied. See the License for the specific language governing
# permissions and limitations under the License.
#
# IBM_PROLOG_END_TAG

# This file is generated by src/usr/targeting/common/xmltohb/xmltohb.pl

import json
from udparsers.helpers.errludP_Helpers import hexConcat, intConcat, findNull, strConcat
from udparsers.helpers.entityPath import errlud_parse_entity_path

""" User Details Parser Target called by b0100.py

@param[in] ver: int value of subsection version
@param[in] data: memoryview object of data to be parsed
@returns: JSON string of parsed data
"""
def ErrlUserDetailsParserTarget(ver, data):
    LABEL_TAG = 0xEEEEEEEE
    MASTER_LABEL_TAG = 0xFFFFFFFF
    i = 0

    attrClass = {
                  0x00: "CLASS_NA",
                  0x01: "CLASS_CARD",
                  0x02: "CLASS_ENC",
                  0x03: "CLASS_CHIP",
                  0x04: "CLASS_UNIT",
                  0x05: "CLASS_DEV",
                  0x06: "CLASS_SYS",
                  0x07: "CLASS_LOGICAL_CARD",
                  0x08: "CLASS_BATTERY",
                  0x09: "CLASS_LED",
                  0x0A: "CLASS_SP",
                  0x0B: "CLASS_ASIC",
                  0x0C: "CLASS_MAX",
                }

    attrType = {
                 0x00: "TYPE_NA",
                 0x01: "TYPE_SYS",
                 0x02: "TYPE_NODE",
                 0x03: "TYPE_DIMM",
                 0x04: "TYPE_MEMBUF",
                 0x05: "TYPE_PROC",
                 0x06: "TYPE_EX",
                 0x07: "TYPE_CORE",
                 0x08: "TYPE_L2",
                 0x09: "TYPE_L3",
                 0x0A: "TYPE_L4",
                 0x0B: "TYPE_MCS",
                 0x0D: "TYPE_MBA",
                 0x0E: "TYPE_XBUS",
                 0x0F: "TYPE_ABUS",
                 0x10: "TYPE_PCI",
                 0x11: "TYPE_DPSS",
                 0x12: "TYPE_APSS",
                 0x13: "TYPE_OCC",
                 0x14: "TYPE_PSI",
                 0x15: "TYPE_FSP",
                 0x16: "TYPE_PNOR",
                 0x17: "TYPE_OSC",
                 0x18: "TYPE_TODCLK",
                 0x19: "TYPE_CONTROL_NODE",
                 0x1A: "TYPE_OSCREFCLK",
                 0x1B: "TYPE_OSCPCICLK",
                 0x1C: "TYPE_REFCLKENDPT",
                 0x1D: "TYPE_PCICLKENDPT",
                 0x1E: "TYPE_NX",
                 0x1F: "TYPE_PORE",
                 0x20: "TYPE_PCIESWITCH",
                 0x21: "TYPE_CAPP",
                 0x22: "TYPE_FSI",
                 0x23: "TYPE_EQ",
                 0x24: "TYPE_MCA",
                 0x25: "TYPE_MCBIST",
                 0x26: "TYPE_MI",
                 0x27: "TYPE_DMI",
                 0x28: "TYPE_OBUS",
                 0x2A: "TYPE_SBE",
                 0x2B: "TYPE_PPE",
                 0x2C: "TYPE_PERV",
                 0x2D: "TYPE_PEC",
                 0x2E: "TYPE_PHB",
                 0x2F: "TYPE_SYSREFCLKENDPT",
                 0x30: "TYPE_MFREFCLKENDPT",
                 0x31: "TYPE_TPM",
                 0x32: "TYPE_SP",
                 0x33: "TYPE_UART",
                 0x34: "TYPE_PS",
                 0x35: "TYPE_FAN",
                 0x36: "TYPE_VRM",
                 0x37: "TYPE_USB",
                 0x38: "TYPE_ETH",
                 0x39: "TYPE_PANEL",
                 0x3A: "TYPE_BMC",
                 0x3B: "TYPE_FLASH",
                 0x3C: "TYPE_SEEPROM",
                 0x3D: "TYPE_TMP",
                 0x3E: "TYPE_GPIO_EXPANDER",
                 0x3F: "TYPE_POWER_SEQUENCER",
                 0x40: "TYPE_RTC",
                 0x41: "TYPE_FANCTLR",
                 0x42: "TYPE_OBUS_BRICK",
                 0x43: "TYPE_NPU",
                 0x44: "TYPE_MC",
                 0x45: "TYPE_TEST_FAIL",
                 0x46: "TYPE_MFREFCLK",
                 0x47: "TYPE_SMPGROUP",
                 0x48: "TYPE_OMI",
                 0x49: "TYPE_MCC",
                 0x4A: "TYPE_OMIC",
                 0x4B: "TYPE_OCMB_CHIP",
                 0x4C: "TYPE_MEM_PORT",
                 0x4D: "TYPE_I2C_MUX",
                 0x4E: "TYPE_PMIC",
                 0x4F: "TYPE_NMMU",
                 0x50: "TYPE_PAU",
                 0x51: "TYPE_IOHS",
                 0x52: "TYPE_PAUC",
                 0x53: "TYPE_FC",
                 0x54: "TYPE_LPCREFCLKENDPT",
                 0x55: "TYPE_GENERIC_I2C_DEVICE",
                 0x56: "TYPE_MDS_CTLR",
                 0x57: "TYPE_DCM",
                 0x58: "TYPE_LAST_IN_RANGE",
                }

    attrModel = {
                  0x00: "MODEL_NA",
                  0x10: "MODEL_RESERVED",
                  0x11: "MODEL_VENICE",
                  0x12: "MODEL_MURANO",
                  0x13: "MODEL_NAPLES",
                  0x14: "MODEL_NIMBUS",
                  0x15: "MODEL_CUMULUS",
                  0x16: "MODEL_AXONE",
                  0x30: "MODEL_CENTAUR",
                  0x31: "MODEL_OCMB",
                  0x50: "MODEL_JEDEC",
                  0x51: "MODEL_CDIMM",
                  0x70: "MODEL_POWER8",
                  0x90: "MODEL_POWER9",
                  0x91: "MODEL_POWER10",
                  0x92: "MODEL_CECTPM",
                  0x93: "MODEL_BMC",
                  0x94: "MODEL_AST2500",
                  0x95: "MODEL_AST2600",
                  0x96: "MODEL_PCA9847",
                  0x97: "MODEL_UCD9090",
                  0x98: "MODEL_UCD90120A",
                  0x99: "MODEL_UCD90320",
                }

    label = "Target"
    dictArray = []
    while (i+4) <= len(data):
        subd = dict()
        word, i=intConcat(data, i, i+4)
        if word == MASTER_LABEL_TAG:
            subd["Target"]="MASTER_PROCESSOR_CHIP_TARGET_SENTINEL"
        elif word == LABEL_TAG:
            # Data Layout
            #  4 bytes  : Label Tag (word)
            # 24 bytes  : Label

            label=strConcat(data, i, findNull(data, i, i+24))[0]
            i += 24 #skip over any trailing null chars
        else:
            if i+(4*4) <= len(data):
                # Data Layout
                # 4 bytes  : HUID (word)
                # 4 bytes  : Class
                # 4 bytes  : Type
                # 4 bytes  : Model
                # N bytes  : Entity Path 1
                # N bytes  : Entity Path 2

                subd[label]="HUID = " + f'0x{word:08X}'
                subd["  ATTR_CLASS"]=attrClass.get(intConcat(data, i, i+4)[0], "UNKNOWN_CLASS")
                i += 4
                subd["  ATTR_TYPE"]=attrType.get(intConcat(data, i, i+4)[0], "UNKNOWN_TYPE")
                i += 4
                subd["  ATTR_MODEL"]=attrModel.get(intConcat(data, i, i+4)[0], "UNKNOWN_MODEL")
                i += 4
                for x in range(2):
                    pathType,i=intConcat(data, i, i+4)
                    if (pathType == 0xf7abb7c or #ATTR_PHYS_PATH
                        pathType == 0xb5afcd7): #ATTR_AFFINITY_PATH
                        outString, i=errlud_parse_entity_path(data, i)
                        if pathType == 0xf7abb7c:
                            subd["  ATTR_PHYS_PATH"]=outString
                        if pathType == 0xb5afcd7:
                            subd["  ATTR_AFFINITY_PATH"]=outString
            dictArray.append(subd)
    jsonStr = json.dumps(dictArray)
    return jsonStr
