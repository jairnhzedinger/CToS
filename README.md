# CToS

CToS e um projeto de sistema operacional simples para PCs x86 com suporte a boot via BIOS e UEFI. Este repositorio contem um esqueleto basico com bootloaders e um kernel inicial escrito em C.

## Estrutura

- `bootloader/bios`  - Bootloader MBR para BIOS
- `bootloader/uefi`  - Bootloader para UEFI (GPT)
- `kernel`           - Kernel inicial
- `iso`              - Diretorio para imagens

## Compilacao rapida

Para compilar o bootloader BIOS e o kernel e executar no QEMU:

```
make run
```

Para compilar o bootloader UEFI:

```
make -C bootloader/uefi
```

## Dependencias sugeridas

- `nasm`
- `gcc` com suporte a 32 bits (`gcc-multilib`)
- `ld` e `objcopy` (binutils)
- `gnu-efi` para compilar o loader UEFI
- `qemu-system-x86_64` para testes

