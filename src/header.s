    .section .header.pointers
    .long __clheader_romfirst
    .long __clheader_romlast
    .long 0xa5a5a5a5 /* Placeholder checksum */
    .long 0xffffffff
    .long __clheader_sramfirst
    .long __clheader_sramlast
    .long 0xfffffffe

    ! NOT REQUIRED, you can put anything you want here.
    ! 100 bytes available. Pad first 4 for nice alignment.
    ! Example in the format of Wanwan header:
!    .section .header.copyright
!    .long 0
!    .asciz "GAMEBLABLA 24 CUBE 3D DEMO       "
!    .asciz "ver 1.01"

