#!/bin/bash
#

/home/metal/warez/rkdeveloptool/rkdeveloptool ld
/home/metal/warez/rkdeveloptool/rkdeveloptool db /home/metal/dev/edk2-axon/workspace/rk3588_spl_loader_v1.08.111.bin
/home/metal/warez/rkdeveloptool/rkdeveloptool wl 0 /home/metal/dev/edk2-rk35xx/RK3588_NOR_FLASH.img
/home/metal/warez/rkdeveloptool/rkdeveloptool rd
