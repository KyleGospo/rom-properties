#!/bin/sh
set -ev

# Standard string tables
./strtbl_parser.py CBM_C64_cart_type CBM_C64_Cartridge_Type_data.txt CBM_C64_Cartridge_Type_data.h
./strtbl_parser.py CBM_Plus4_cart_type CBM_Plus4_Cartridge_Type_data.txt CBM_Plus4_Cartridge_Type_data.h
./strtbl_parser.py CBM_VIC20_cart_type CBM_VIC20_Cartridge_Type_data.txt CBM_VIC20_Cartridge_Type_data.h
./strtbl_parser.py ELFMachineTypes ELFMachineTypes_data.txt ELFMachineTypes_data.h
./strtbl_parser.py ELF_OSABI ELF_OSABI_data.txt ELF_OSABI_data.h
./strtbl_parser.py SegaTCode SegaPublishers_data.txt SegaPublishers_data.h

# Customized string tables
# NOTE: EXENEEntries_data.py requires a Wine source tree.
./EXEMachineTypes_parser.py EXELEMachineTypes_data.txt EXELEMachineTypes_data.h LE
./EXEMachineTypes_parser.py EXEPEMachineTypes_data.txt EXEPEMachineTypes_data.h PE
./NESMappers_parser.py NESMappers_data.txt NESMappers_data.h
./NintendoPublishers_parser.py NintendoPublishers_data.txt NintendoPublishers_data.h
./NintendoPublishers_FDS_parser.py NintendoPublishers_FDS_data.txt NintendoPublishers_FDS_data.h
./XboxPublishers_parser.py XboxPublishers_data.txt XboxPublishers_data.h
