/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/usr/isteps/bios_attr_accessors/bios_attr_parsers.C $      */
/*                                                                        */
/* OpenPOWER HostBoot Project                                             */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2021,2023                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/** @file  bios_attr_parsers.C
 *  @brief This file contains the implementations of the functions that
 *         lookup a PLDM BIOS attribute using one of the APIs defined
 *         in hb_bios_attrs.H. These functions will use the value returned
 *         to set the appropriate attribute(s) on the appropriate target(s).
 */

// Local Module
#include <isteps/bios_attr_accessors/bios_attr_parsers.H>

// Userspace Modules
#include <attributeenums.H>
#include <errl/errlmanager.H>
#include <initservice/isteps_trace.H>
#include <isteps/hwpisteperror.H>
#include <isteps/istep_reasoncodes.H>
#include <pldm/base/hb_bios_attrs.H>
#include <pldm/pldm_errl.H>
#include <targeting/common/mfgFlagAccessors.H>
#include <targeting/common/targetservice.H>
#include <targeting/targplatutil.H>
#include <targeting/common/utilFilter.H>
#include <trace/interface.H>

using namespace TARGETING;

namespace ISTEP
{

void parse_hb_proc_favor_aggressive_prefetch(std::vector<uint8_t>& io_string_table,
                                    std::vector<uint8_t>& io_attr_table,
                                    ISTEP_ERROR::IStepError & io_stepError)
{
    // Create a variable to hold the retrieved value from the BMC BIOS
    ATTR_PROC_FAVOR_AGGRESSIVE_PREFETCH_type l_favor_aggressive_prefetch(0);

    // Cache a handle to the system target
    const auto l_sys = UTIL::assertGetToplevelTarget();

    // Get attribute from the BMC BIOS
    errlHndl_t l_errl = PLDM::getProcFavorAggressivePrefetch(io_string_table, io_attr_table, l_favor_aggressive_prefetch);

    if ( unlikely(l_errl != nullptr) )
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                   "parse_hb_proc_favor_aggressive_prefetch(): An error occurred getting the "
                   "PROC_FAVOR_AGGRESSIVE_PREFETCH from the BMC BIOS. Leaving the value for "
                   "the system as is, with value %d (0 = disabled, 1 = enabled).",
                   l_sys->getAttr<ATTR_PROC_FAVOR_AGGRESSIVE_PREFETCH>() );
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }
    else
    {
        l_sys->setAttr<ATTR_PROC_FAVOR_AGGRESSIVE_PREFETCH>(l_favor_aggressive_prefetch);

        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                   "parse_hb_proc_favor_agggressive_prefetch(): Set to %d "
                   "(0 = disabled, 1 = enabled).",
                   l_sys->getAttr<ATTR_PROC_FAVOR_AGGRESSIVE_PREFETCH>() );
    }
} // parse_hb_proc_favor_aggressive_prefetch

void parse_hb_lateral_cast_out_mode(std::vector<uint8_t>& io_string_table,
                                    std::vector<uint8_t>& io_attr_table,
                                    ISTEP_ERROR::IStepError & io_stepError)
{
    // Create a variable to hold the retrieved LCO value from the BMC BIOS
    ATTR_PROC_LCO_MODE_DISABLE_type l_lcoMode(0);

    // Cache a handle to the system target
    const auto l_sys = UTIL::assertGetToplevelTarget();

    // Get the LCO from the BMC BIOS
    errlHndl_t l_errl = PLDM::getLateralCastOutMode(io_string_table, io_attr_table, l_lcoMode);

    if ( unlikely(l_errl != nullptr) )
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                   "parse_hb_lateral_cast_out_mode(): An error occurred getting the "
                   "Lateral Cast Out(LCO) mode from the BMC BIOS. Leaving the LCO for "
                   "the system as is, with value %d (0 = LCO enabled, 1 = LCO disabled).",
                   l_sys->getAttr<ATTR_PROC_LCO_MODE_DISABLE>() );
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }
    else
    {
        l_sys->setAttr<ATTR_PROC_LCO_MODE_DISABLE>(l_lcoMode);

        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                   "parse_hb_lateral_cast_out_mode(): Set LCO mode to %d "
                   "(0 = LCO enabled, 1 = LCO disabled).",
                   l_sys->getAttr<ATTR_PROC_LCO_MODE_DISABLE>() );
    }
} // parse_hb_lateral_cast_out_mode

void parse_hb_tpm_required(std::vector<uint8_t>& io_string_table,
                           std::vector<uint8_t>& io_attr_table,
                           ISTEP_ERROR::IStepError & io_stepError)
{
    // Create a variable to hold the retrieved TPM Required Policy value from the BMC BIOS
    // Default to TPM is required
    TARGETING::ATTR_TPM_REQUIRED_type l_tpmRequiredPolicy(1);

    // Get the TPM Required Policy from the BMC BIOS
    errlHndl_t l_errl = PLDM::getTpmRequiredPolicy(io_string_table, io_attr_table,
                                                   l_tpmRequiredPolicy);

    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();

    if ( unlikely(l_errl != nullptr) )
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                   "parse_hb_tpm_required(): An error occurred getting "
                   "the TPM Required Policy from the BMC BIOS. Leaving the system "
                   "attribute ATTR_TPM_REQUIRED at its current value %d.",
                   static_cast<uint16_t>(l_sys->getAttr<ATTR_TPM_REQUIRED>()) );
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );

    }
    else
    {
        // Set the system attribute ATTR_TPM_REQUIRED to the retrieved value
        l_sys->setAttr<TARGETING::ATTR_TPM_REQUIRED>(l_tpmRequiredPolicy);
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                   "parse_hb_tpm_required(): Succeeded in getting the BMC "
                   "BIOS TPM Required Policy value %d, and setting the attribute "
                   "ATTR_TPM_REQUIRED to %d for the system",
                    l_tpmRequiredPolicy,
                    static_cast<uint16_t>(l_sys->getAttr<ATTR_TPM_REQUIRED>()) );
    }
    return;
}

void parse_hb_field_core_override(std::vector<uint8_t>& io_string_table,
                                  std::vector<uint8_t>& io_attr_table,
                                  ISTEP_ERROR::IStepError & io_stepError)
{
    // Create a variable to hold the retrieved FCO value from the BMC BIOS
    TARGETING::ATTR_FIELD_CORE_OVERRIDE_type l_fieldCoreOverride(0);

    // Get the FCO from the BMC BIOS
    errlHndl_t l_errl = PLDM::getFieldCoreOverride(io_string_table, io_attr_table,
                                                   l_fieldCoreOverride);
    if ( unlikely(l_errl != nullptr) )
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                   "parse_hb_field_core_override(): An error occurred getting "
                   "the Field Core Override(FCO) from the BMC BIOS. Leaving the FCO for "
                   "the individual NODE targets as is." );
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }
    else
    {
        // Iterate over all of the nodes, not just functional, and set ALL the node's
        // attribute ATTR_FIELD_CORE_OVERRIDE to the retrieved BMC FCO BIOS value.
        // Setting all of the nodes and not just functional nodes, because discover
        // targets has not been run yet and therefore no functional targets have
        // been established.
        PredicateCTM predNode(CLASS_ENC, TYPE_NODE);
        PredicatePostfixExpr nodeCheckExpr;
        nodeCheckExpr.push(&predNode);

        const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();

        TargetHandleList l_nodeTargetList;
        targetService().getAssociated(l_nodeTargetList, l_sys,
                        TargetService::CHILD, TargetService::IMMEDIATE,
                        &nodeCheckExpr);

        for(const auto& l_nodeTarget : l_nodeTargetList)
        {
            l_nodeTarget->setAttr<ATTR_FIELD_CORE_OVERRIDE>(l_fieldCoreOverride);
            TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                       "parse_hb_field_core_override(): Succeeded in getting the BMC "
                       "BIOS Field Core Override(FCO) attribute %d, and setting the attribute "
                       "ATTR_FIELD_CORE_OVERRIDE to %d for NODE target 0x%0.8x",
                        l_fieldCoreOverride,
                        l_nodeTarget->getAttr<ATTR_FIELD_CORE_OVERRIDE>(),
                        get_huid(l_nodeTarget) );
        }
    }
    return;
}

void parse_hb_memory_mirror_mode(std::vector<uint8_t>& io_string_table,
                                 std::vector<uint8_t>& io_attr_table,
                                 ISTEP_ERROR::IStepError & io_stepError)
{
    // Create a variable to hold the retrieved Mirror Memory value from the BMC BIOS
    TARGETING::ATTR_PAYLOAD_IN_MIRROR_MEM_type l_mirrorMemory(0);

    // Get the Mirror Memory from the BMC BIOS
    errlHndl_t l_errl = PLDM::getMirrorMemory(io_string_table, io_attr_table,
                                              l_mirrorMemory);

    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();

    if (unlikely(l_errl != nullptr))
    {
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                  "parse_hb_memory_mirror_mode(): An error occurred getting "
                  "Mirror Memory value from the BMC BIOS. Leaving the system "
                  "attribute ATTR_PAYLOAD_IN_MIRROR_MEM at its current value %d",
                  l_sys->getAttr<ATTR_PAYLOAD_IN_MIRROR_MEM>());
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }
    else
    {
        // Set the system attribute ATTR_PAYLOAD_IN_MIRROR_MEM to the retrieved value
        l_sys->setAttr<ATTR_PAYLOAD_IN_MIRROR_MEM>(l_mirrorMemory);
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                  "parse_hb_memory_mirror_mode(): Succeeded in getting the BMC "
                  "BIOS Mirror Memory value %d and setting the attribute "
                  "ATTR_PAYLOAD_IN_MIRROR_MEM",
                  l_mirrorMemory);
    }
    return;
}

void parse_hb_key_clear_request(std::vector<uint8_t>& io_string_table,
                                std::vector<uint8_t>& io_attr_table,
                                ISTEP_ERROR::IStepError & io_stepError)
{
    // Create a variable to hold the retrieved Key Clear Request value from the BMC BIOS
    TARGETING::ATTR_KEY_CLEAR_REQUEST_type l_keyClearRequest = TARGETING::KEY_CLEAR_REQUEST_INVALID;

    // Get the Key Clear Request from the BMC BIOS
    errlHndl_t l_errl = PLDM::getKeyClearRequest(io_string_table, io_attr_table,
                                                 l_keyClearRequest);

    if (unlikely(l_errl != nullptr) || l_keyClearRequest == TARGETING::KEY_CLEAR_REQUEST_INVALID)
    {
        // if there was an error reading the BIOS attr or the KEY_CLEAR_REQUEST returned is
        // INVALID, then default to seting all nodes to KEY_CLEAR_REQUEST_NONE
        l_keyClearRequest = KEY_CLEAR_REQUEST_NONE;
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                  "parse_hb_key_clear_request(): An error occurred getting "
                  "Key Clear Request from the BMC BIOS. Defaulting all node "
                  "attributes to KEY_CLEAR_REQUEST_NONE (0x%X)",
                  l_keyClearRequest);
        if(unlikely(l_errl != nullptr))
        {
            l_errl->collectTrace("ISTEPS_TRACE",256);
            errlCommit( l_errl, ISTEP_COMP_ID );
        }
    }
    else
    {
        // Set the node attribute ATTR_KEY_CLEAR_REQUEST to the retrieved value
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                  "parse_hb_key_clear_request(): Succeeded in getting the BMC "
                  "BIOS Key Clear Request 0x%X",
                  l_keyClearRequest);
    }

    // Iterate over all of the nodes, not just functional, and set ALL the node's
    // attribute ATTR_KEY_CLEAR_REQUEST to l_keyClearRequest.
    // Setting all of the nodes and not just functional nodes, because discover
    // targets has not been run yet and therefore no functional targets have
    // been established.
    TargetHandleList l_nodeTargetList;
    getEncResources(l_nodeTargetList, TARGETING::TYPE_NODE, TARGETING::UTIL_FILTER_ALL);

    for(const auto& l_nodeTarget : l_nodeTargetList)
    {
        l_nodeTarget->setAttr<ATTR_KEY_CLEAR_REQUEST>(l_keyClearRequest);
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                   "parse_hb_key_clear_request(): setting the Hostboot attribute "
                   "ATTR_KEY_CLEAR_REQUEST to 0x%X for NODE target 0x%0.8x",
                    l_keyClearRequest,
                    get_huid(l_nodeTarget) );
    }

    return;
}

void parse_hb_number_huge_pages(std::vector<uint8_t>& io_string_table,
                                std::vector<uint8_t>& io_attr_table,
                                ISTEP_ERROR::IStepError & io_stepError)
{
    ATTR_HUGE_PAGE_COUNT_type huge_page_count = 0;
    const size_t DEFAULT_HUGE_PAGE_COUNT = 0;

    errlHndl_t l_errl = PLDM::getHugePageCount(io_string_table,
                                               io_attr_table,
                                               huge_page_count);
    if(l_errl)
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                "parse_hb_number_huge_pages: "
                "An error occurred getting Huge Page Count from the BMC, using default 0x%X",
                DEFAULT_HUGE_PAGE_COUNT );

        // Set count to default, commit the error and continue
        huge_page_count = DEFAULT_HUGE_PAGE_COUNT;
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }

    TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
            "parse_hb_number_huge_pages: Set ATTR_HUGE_PAGE_COUNT = 0x%X",
            huge_page_count );
    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();
    l_sys->setAttr<ATTR_HUGE_PAGE_COUNT>(huge_page_count);

    return;
}

void parse_hb_huge_page_size(std::vector<uint8_t>& io_string_table,
                             std::vector<uint8_t>& io_attr_table,
                             ISTEP_ERROR::IStepError & io_stepError)
{
    ATTR_HUGE_PAGE_SIZE_type huge_page_size = TARGETING::HUGE_PAGE_SIZE_PAGE_IS_16_GB;
    errlHndl_t l_errl = PLDM::getHugePageSize(io_string_table,
                                              io_attr_table,
                                              huge_page_size);
    if(l_errl)
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                "parse_hb_huge_page_size: An error occurred getting Huge Page Size from the BMC, using default 0x%X",
                TARGETING::HUGE_PAGE_SIZE_PAGE_IS_16_GB );

        // Set size to default, commit the error and continue
        huge_page_size = TARGETING::HUGE_PAGE_SIZE_PAGE_IS_16_GB;
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }

    TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
            "parse_hb_huge_page_size: Set ATTR_HUGE_PAGE_SIZE = 0x%X",
            huge_page_size );
    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();
    l_sys->setAttr<ATTR_HUGE_PAGE_SIZE>(huge_page_size);

    return;
}

void parse_hb_memory_region_size(std::vector<uint8_t>& io_string_table,
                                 std::vector<uint8_t>& io_attr_table,
                                 ISTEP_ERROR::IStepError & io_stepError)
{
    ATTR_LMB_SIZE_type lmb_size = 0;

    errlHndl_t l_errl = PLDM::getLmbSize(io_string_table,
                                         io_attr_table,
                                         lmb_size);
    if(l_errl)
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                   "parse_hb_memory_region_size: An error occurred getting LMB Size from the BMC, using default 0x%X",
                   PLDM::LMB_SIZE_ENCODE_256MB );

        // Set size to default, commit the error and continue
        lmb_size = PLDM::LMB_SIZE_ENCODE_256MB;
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }

    TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
            "parse_hb_memory_region_size: Set ATTR_LMB_SIZE = 0x%X",
            lmb_size );
    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();
    l_sys->setAttr<ATTR_LMB_SIZE>(lmb_size);

    return;
}

void parse_hb_mfg_flags(std::vector<uint8_t>& io_string_table,
                        std::vector<uint8_t>& io_attr_table,
                        ISTEP_ERROR::IStepError & io_stepError)
{
    ATTR_MFG_FLAGS_typeStdArr mfg_flags = {0};
    const ATTR_MFG_FLAGS_typeStdArr DEFAULT_MFG_FLAGS = {0};

    errlHndl_t l_errl = PLDM::getMfgFlags(io_string_table,
                                          io_attr_table,
                                          mfg_flags);
    if(l_errl)
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                "parse_hb_mfg_flags: An error occurred getting Mfg Flags from the BMC, using default 0" );

        // Set flags to default, commit the error and continue
        mfg_flags = DEFAULT_MFG_FLAGS;
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }

    TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
            "parse_hb_mfg_flags: Set ATTR_MFG_FLAGS = 0x%X 0x%X 0x%X 0x%X",
            mfg_flags[0], mfg_flags[1], mfg_flags[2], mfg_flags[3] );
    TARGETING::setAllMfgFlags(mfg_flags);

    return;
}

void parse_hb_hyp_switch(std::vector<uint8_t>& io_string_table,
                         std::vector<uint8_t>& io_attr_table,
                         ISTEP_ERROR::IStepError & io_stepError)
{
    do{

    ATTR_PAYLOAD_KIND_type payload_kind = PAYLOAD_KIND_UNKNOWN;

    errlHndl_t l_errl = PLDM::getHypervisorMode(io_string_table,
                                                io_attr_table,
                                                payload_kind);

    // If we get an error, or are returned a payload_kind
    // that is not PHYP or SAPPHIRE then we do not know
    // what payload to pick. We cannot assume the payload
    // kind as booting for the incorrect hypervisor could
    // result in loss of data in NVRAM that was generated
    // by the hypervisor on previous boots.
    if(l_errl)
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                "parse_hb_hyp_switch: An error occurred getting Hypervisor Mode from the BMC" );
        break;
    }

    if(payload_kind != PAYLOAD_KIND_PHYP &&
            payload_kind != PAYLOAD_KIND_SAPPHIRE)
    {
        /*@
         * @errortype
         * @severity   ERRL_SEV_UNRECOVERABLE
         * @moduleid   ISTEP::MOD_BIOS_ATTR_PARSERS
         * @reasoncode ISTEP::RC_INVALID_PAYLOAD_KIND
         * @userdata1  Payload Kind that BMC returned
         * @userdata2  unused
         * @devdesc    Software problem, bad data from BMC
         * @custdesc   A software error occurred during system boot
         */
        l_errl = new ErrlEntry(ERRL_SEV_UNRECOVERABLE,
                ISTEP::MOD_BIOS_ATTR_PARSERS,
                ISTEP::RC_INVALID_PAYLOAD_KIND,
                payload_kind,
                0,
                ErrlEntry::NO_SW_CALLOUT);
        PLDM::addBmcErrorCallouts(l_errl);
        io_stepError.addErrorDetails( l_errl );
        break;
    }
    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();
    l_sys->setAttr<ATTR_PAYLOAD_KIND>(payload_kind);

    } while(0);

    return;
}

void parse_pvm_fw_boot_side(std::vector<uint8_t>& io_string_table,
                            std::vector<uint8_t>& io_attr_table,
                            ISTEP_ERROR::IStepError & io_stepError)
{
    do{

    TARGETING::ATTR_HYPERVISOR_IPL_SIDE_type bootside = HYPERVISOR_IPL_SIDE_UNKNOWN;

    errlHndl_t l_errl = PLDM::getBootside(io_string_table, io_attr_table, bootside);

    if (l_errl != nullptr)
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                "parse_pvm_fw_boot_side: An error occurred getting bootside from the BMC" );
        break;
    }

    if ((bootside != HYPERVISOR_IPL_SIDE_PERM) && (bootside != HYPERVISOR_IPL_SIDE_TEMP))
    {
        /*@
         * @errortype
         * @severity   ERRL_SEV_UNRECOVERABLE
         * @moduleid   ISTEP::MOD_BIOS_ATTR_PARSERS
         * @reasoncode ISTEP::RC_INVALID_BOOTSIDE
         * @userdata1  Bootside that BMC returned
         * @userdata2  unused
         * @devdesc    Software problem, bad data from BMC
         * @custdesc   A software error occurred during system boot
         */
        l_errl = new ErrlEntry(ERRL_SEV_UNRECOVERABLE,
                ISTEP::MOD_BIOS_ATTR_PARSERS,
                ISTEP::RC_INVALID_BOOTSIDE,
                bootside,
                0,
                ErrlEntry::NO_SW_CALLOUT);
        PLDM::addBmcErrorCallouts(l_errl);
        io_stepError.addErrorDetails(l_errl);
        break;
    }
    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();
    l_sys->setAttr<TARGETING::ATTR_HYPERVISOR_IPL_SIDE>(bootside);

    } while(0);

    return;
}

void parse_hb_host_usb_enablement(std::vector<uint8_t>& io_string_table,
                                  std::vector<uint8_t>& io_attr_table,
                                  ISTEP_ERROR::IStepError & io_stepError)
{
    // Create a variable to hold the retrieved USB Enablement value from the BMC BIOS
    TARGETING::ATTR_USB_SECURITY_type l_usbEnablement(0);

    // Get the USB Enablement from the BMC BIOS
    errlHndl_t l_errl = PLDM::getUsbEnablement(io_string_table, io_attr_table,
                                               l_usbEnablement);

    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();

    if (unlikely(l_errl != nullptr))
    {
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                  "getAndSetUsbEnablementFromBmcBios(): An error occurred getting "
                  "USB Enablement from the BMC BIOS. Leaving the system "
                  "attribute ATTR_USB_SECURITY at its current value %d",
                  l_sys->getAttr<ATTR_USB_SECURITY>());
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }
    else
    {
        // Set the system attribute ATTR_USB_SECURITY to the retrieved value
        l_sys->setAttr<ATTR_USB_SECURITY>(l_usbEnablement);
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                  "getAndSetUsbEnablementFromBmcBios(): Succeeded in getting the BMC "
                  "BIOS USB Enablement attribute %d and setting the attribute "
                  "ATTR_USB_SECURITY",
                  l_usbEnablement);
    }
    return;
}

void parse_hb_ioadapter_enlarged_capacity(std::vector<uint8_t>& io_string_table,
                                          std::vector<uint8_t>& io_attr_table,
                                          ISTEP_ERROR::IStepError & io_stepError)
{
    // Create a variable to hold the retrieved Enlarged Capacity value from the BMC BIOS
    TARGETING::ATTR_ENLARGED_IO_SLOT_COUNT_type l_enlargedCapacity(0);

    // Get the Enlarged Capacity from the BMC BIOS
    errlHndl_t l_errl = PLDM::getEnlargedCapacity(io_string_table, io_attr_table,
                                                  l_enlargedCapacity);

    // Only need to update master node
    TARGETING::Target* l_masterNode = nullptr;
    TARGETING::UTIL::getMasterNodeTarget(l_masterNode);

    if (unlikely(l_errl != nullptr))
    {
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                  "parse_hb_ioadapter_enlarged_capacity(): An error occurred getting "
                  "Enlarged Capacity from the BMC BIOS. Leaving the node "
                  "attribute ATTR_ENLARGED_IO_SLOT_COUNT at its current value %d",
                  l_masterNode->getAttr<ATTR_ENLARGED_IO_SLOT_COUNT>());
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }
    else
    {
        // Set the node attribute ATTR_ENLARGED_IO_SLOT_COUNT to the retrieved value
        l_masterNode->setAttr<ATTR_ENLARGED_IO_SLOT_COUNT>(l_enlargedCapacity);
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace, INFO_MRK
                  "parse_hb_ioadapter_enlarged_capacity(): Succeeded in getting the BMC "
                  "BIOS Enlarged Capacity attribute %d and setting the attribute "
                  "ATTR_ENLARGED_IO_SLOT_COUNT",
                  l_enlargedCapacity);
    }
    return;
}

void parse_hb_inhibit_bmc_reset(std::vector<uint8_t>& io_string_table,
                                std::vector<uint8_t>& io_attr_table,
                                ISTEP_ERROR::IStepError & io_stepError)
{
    bool inhibit_resets = false;

    errlHndl_t l_errl = PLDM::getInhibitBmcResetValue(io_string_table, io_attr_table, inhibit_resets);

    if (l_errl)
    {
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace,
                  ERR_MRK"parse_hb_inhibit_bmc_reset(): An error occurred getting "
                  "the PLDM Inhibit BMC Reset BIOS attribute from the BMC. Setting the BMC reset "
                  "inhibition attribute to false.");

        inhibit_resets = false;
        l_errl->collectTrace("ISTEPS_TRACE", 256);
        errlCommit(l_errl, ISTEP_COMP_ID); // don't cause a TI by attaching to io_stepError
    }
    else
    {
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace,
                  INFO_MRK"parse_hb_inhibit_bmc_reset(): Succeeded in getting the PLDM Inhibit BMC Reset "
                  "BIOS attribute from the BMC. Setting the BMC reset inhibition attribute "
                  "to %s",
                  inhibit_resets ? "true" : "false");
    }

    const auto sys = TARGETING::UTIL::assertGetToplevelTarget();
    sys->setAttr<TARGETING::ATTR_HYP_INHIBIT_RUNTIME_BMC_RESET>(inhibit_resets ? 1 : 0);
}

void parse_hb_cap_freq_mhz(std::vector<uint8_t>& io_string_table,
                           std::vector<uint8_t>& io_attr_table,
                           ISTEP_ERROR::IStepError & io_stepError)
{
    const uint64_t IGNORE_CAP_VALUE = 0;
    uint64_t cap_freq_mhz = IGNORE_CAP_VALUE;


    errlHndl_t l_errl = PLDM::getCapFreqMhz(io_string_table,
                                            io_attr_table,
                                            cap_freq_mhz);
    if(l_errl)
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                "parse_hb_cap_freq_mhz: "
                "An error occurred getting HB CAP FREQ MHZ from the BMC" );
        l_errl->collectTrace("ISTEPS_TRACE",256);
        errlCommit( l_errl, ISTEP_COMP_ID );
    }
    else if (cap_freq_mhz != IGNORE_CAP_VALUE) // don't need range check if just setting to ignore
    {
        // grab the PLDM BIOS attr values as the SYSTEM_CORE attrs haven't been setup yet
        uint32_t cap_freq_mhz_min = 0;
        uint32_t cap_freq_mhz_max = 0;
        l_errl = PLDM::getCapFreqMhzMinMax(io_string_table,
                                           io_attr_table,
                                           cap_freq_mhz_min,
                                           cap_freq_mhz_max);
        if (l_errl)
        {
            TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                "parse_hb_cap_freq_mhz: "
                "An error occurred getting HB CAP FREQ MHZ MIN/MAX values from the BMC");
            l_errl->collectTrace("ISTEPS_TRACE",256);
            errlCommit( l_errl, ISTEP_COMP_ID );
        }
        else
        {
            const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();

            // now verify the value is inclusively between min and max PLDM BIOS values
            if ((cap_freq_mhz < cap_freq_mhz_min) ||
                (cap_freq_mhz > cap_freq_mhz_max) )
            {
                TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace, ERR_MRK
                    "parse_hb_cap_freq_mhz: requested frequency %ld is outside boundary (%ld - %ld). "
                    "Terminating IPL as this is an invalid requested freq",
                    cap_freq_mhz, cap_freq_mhz_min, cap_freq_mhz_max );
                /*@
                 * @errortype
                 * @severity   ERRL_SEV_UNRECOVERABLE
                 * @moduleid   ISTEP::MOD_BIOS_ATTR_PARSERS
                 * @reasoncode ISTEP::RC_REQUESTED_FREQ_OUTSIDE_BOUNDARY
                 * @userdata1  Requested cap frequency in MHz (hb_cap_freq_mhz_request)
                 * @userdata2[0:31]  Minimum frequency in MHz (hb_cap_freq_mhz_min)
                 * @userdata2[32:63] Maximum frequency in MHz (hb_cap_freq_mhz_max)
                 * @devdesc    Software problem, user requested frequency is outside the boundary.
                 *             Requested frequency is from BMC.
                 * @custdesc   A software error occurred during system boot
                 */
                l_errl = new ErrlEntry(ERRL_SEV_UNRECOVERABLE,
                                       ISTEP::MOD_BIOS_ATTR_PARSERS,
                                       ISTEP::RC_REQUESTED_FREQ_OUTSIDE_BOUNDARY,
                                       cap_freq_mhz,
                                       TWO_UINT32_TO_UINT64(cap_freq_mhz_min,cap_freq_mhz_max),
                                       ErrlEntry::NO_SW_CALLOUT);
                PLDM::addBmcErrorCallouts(l_errl);
                l_errl->collectTrace("ISTEPS_TRACE",256);
                errlCommit( l_errl, ISTEP_COMP_ID );

                // disable the requested frequency and just use system settings
                l_sys->setAttr<ATTR_FREQ_SYSTEM_CORE_CEILING_MHZ_OVERRIDE>(IGNORE_CAP_VALUE);
            }
            else
            {
                TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                    "parse_hb_cap_freq_mhz: requested frequency %ld is inside boundary (%ld - %ld)",
                    cap_freq_mhz, cap_freq_mhz_min, cap_freq_mhz_max );
                TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                    "parse_hb_cap_freq_mhz: Set ATTR_FREQ_SYSTEM_CORE_CEILING_MHZ_OVERRIDE = 0x%X",
                    cap_freq_mhz );

                l_sys->setAttr<ATTR_FREQ_SYSTEM_CORE_CEILING_MHZ_OVERRIDE>(cap_freq_mhz);
            }
        }
    }
    // else, do nothing if cap_freq_mhz = IGNORE_CAP_VALUE
}


void parse_hb_secure_ver_lockin_enabled(std::vector<uint8_t>& io_string_table,
                                        std::vector<uint8_t>& io_attr_table,
                                        ISTEP_ERROR::IStepError & io_stepError)
{
    TARGETING::ATTR_SECURE_VERSION_LOCKIN_POLICY_type lockinEnabled = false;

    errlHndl_t l_errl = PLDM::getSecVerLockinEnabled(io_string_table,
                                                     io_attr_table,
                                                     lockinEnabled);

    if (l_errl)
    {
        lockinEnabled = false;

        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace,
                  ERR_MRK"parse_hb_secure_ver_lockin_enabled(): An error occurred getting "
                  "the PLDM Secure Version Lockin Enabled BIOS attribute from the BMC. "
                  "Setting the Secure Version Lockin Policy attribute to false (%d)",
                  lockinEnabled);

        l_errl->collectTrace("ISTEPS_TRACE", 256);
        l_errl->collectTrace("PLDM", 256);
        errlCommit(l_errl, ISTEP_COMP_ID); // don't cause a TI by attaching to io_stepError
    }
    else
    {
        TRACFCOMP(ISTEPS_TRACE::g_trac_isteps_trace,
                  INFO_MRK"parse_hb_secure_ver_lockin_enabled(): Succeeded in getting "
                  "the PLDM Secure Version Lockin Enabled BIOS attribute from the BMC. "
                  "Setting the Secure Version Lockin Policy attribute to %d",
                  lockinEnabled);
    }

    const auto sys = TARGETING::UTIL::assertGetToplevelTarget();
    sys->setAttr<TARGETING::ATTR_SECURE_VERSION_LOCKIN_POLICY>(lockinEnabled);
}

void parse_hb_ps_config(std::vector<uint8_t>& io_string_table,
                        std::vector<uint8_t>& io_attr_table,
                        ISTEP_ERROR::IStepError & io_stepError)
{
    uint32_t NumberOfPowerSupplies = 0;
    uint16_t InputVoltPowerSupplies = 0;
    uint16_t CcinPowerSupplies = 0;

    errlHndl_t l_errl = PLDM::getPowerSupplyConfig(io_string_table,
                                                   io_attr_table,
                                                   NumberOfPowerSupplies,
                                                   InputVoltPowerSupplies,
                                                   CcinPowerSupplies);

    if(l_errl)
    {
        TRACFCOMP( ISTEPS_TRACE::g_trac_isteps_trace,
                   "parse_hb_ps_config: An error occurred getting data from the BMC");
        l_errl->collectTrace("PLDM", 256);
        NumberOfPowerSupplies = 0;
        InputVoltPowerSupplies = 0;
        CcinPowerSupplies = 0;

        errlCommit( l_errl, ISTEP_COMP_ID );
    }

    // INDEX: Byte 0,1:CCIN   Not_Used(0000), CCIN, Any(FFFF)
    //        Byte 1  :Type   Not_Used(00), 110(01),  220(02)
    //        Byte 2  :#_PS   Not_Used(00), Number of PS should be installed.

    // Set Byte 3 for number of PS.
    uint32_t bulk_power_index = NumberOfPowerSupplies;

    // Set Byte 2 for input Voltage
    if (InputVoltPowerSupplies == 110)
    {
        bulk_power_index = bulk_power_index | 0x00000100;
    }
    else if (InputVoltPowerSupplies == 220)
    {
        bulk_power_index = bulk_power_index | 0x00000200;
    }
    // Set Byte 0&1 for PS CCIN
    bulk_power_index = bulk_power_index | (CcinPowerSupplies << 16);

    const auto l_sys = TARGETING::UTIL::assertGetToplevelTarget();
    l_sys->setAttr<ATTR_INDEX_BULK_POWER>(bulk_power_index);
}

} // end of namespace ISTEP