/** @file

  Copyright (c) 2011-2018, ARM Ltd. All rights reserved.<BR>
  Copyright (c) 2022 Rockchip Electronics Co. Ltd.

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef LCD_GRAPHICS_OUTPUT_DXE_H_
#define LCD_GRAPHICS_OUTPUT_DXE_H_

#include <Base.h>

#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/RockchipDisplayLib.h>

#include <Protocol/Cpu.h>
#include <Protocol/DevicePath.h>
#include <Protocol/RockchipCrtcProtocol.h>
#include <Protocol/RockchipConnectorProtocol.h>

/** The enumeration maps the PL111 LcdBpp values used in the LCD Control
  Register
**/
typedef enum {
  LcdBitsPerPixel_1 = 0,
  LcdBitsPerPixel_2,
  LcdBitsPerPixel_4,
  LcdBitsPerPixel_8,
  LcdBitsPerPixel_16_555,
  LcdBitsPerPixel_24,
  LcdBitsPerPixel_16_565,
  LcdBitsPerPixel_12_444,
  LcdBitsPerPixel_Max
} LCD_BPP;

//
// Device structures
//
typedef struct {
  VENDOR_DEVICE_PATH            Guid;
  EFI_DEVICE_PATH_PROTOCOL      End;
} LCD_GRAPHICS_DEVICE_PATH;

typedef struct {
  UINT32                                Signature;
  EFI_HANDLE                            Handle;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  ModeInfo;
  EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE     Mode;
  EFI_GRAPHICS_OUTPUT_PROTOCOL          Gop;
  LCD_GRAPHICS_DEVICE_PATH              DevicePath;
  EFI_EVENT                             ExitBootServicesEvent;
} LCD_INSTANCE;

#define LCD_INSTANCE_SIGNATURE  SIGNATURE_32('l', 'c', 'd', '0')

#define LCD_INSTANCE_FROM_GOP_THIS(a)     CR (a, LCD_INSTANCE, Gop, LCD_INSTANCE_SIGNATURE)

//
// Function Prototypes
//

VOID
LcdGraphicsExitBootServicesEvent (
    IN EFI_EVENT  Event,
    IN VOID       *Context
);

EFI_STATUS
EFIAPI
LcdGraphicsQueryMode (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
  IN  UINT32                                ModeNumber,
  OUT UINTN                                 *SizeOfInfo,
  OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
);

EFI_STATUS
EFIAPI
LcdGraphicsSetMode (
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL  *This,
  IN UINT32                        ModeNumber
);

EFI_STATUS
EFIAPI
LcdGraphicsBlt (
  IN EFI_GRAPHICS_OUTPUT_PROTOCOL       *This,
  IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL  *BltBuffer,     OPTIONAL
  IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION  BltOperation,
  IN UINTN                              SourceX,
  IN UINTN                              SourceY,
  IN UINTN                              DestinationX,
  IN UINTN                              DestinationY,
  IN UINTN                              Width,
  IN UINTN                              Height,
  IN UINTN                              Delta           OPTIONAL
);

EFI_STATUS
EFIAPI
LcdGraphicsGetBpp (
  IN  UINT32                                ModeNumber,
  OUT LCD_BPP*                              Bpp
  );

UINTN
GetBytesPerPixel (
  IN  LCD_BPP       Bpp
  );

EFI_STATUS
EFIAPI
GraphicsOutputDxeInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
);

EFI_STATUS
InitializeDisplay (
  IN LCD_INSTANCE* Instance
);

#endif /* LCD_GRAPHICS_OUTPUT_DXE_H_ */
