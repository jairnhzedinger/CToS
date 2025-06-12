# Bootloader UEFI (GPT)

Este diretorio contem um exemplo de bootloader UEFI simples. Ele eh compilado utilizando a biblioteca gnu-efi e carrega o kernel tambem em formato EFI.

### Como compilar

```
make
```

O resultado `loader.efi` deve ser colocado em `EFI/BOOT/BOOTX64.EFI` na particao FAT do disco de boot.

### Como testar

Crie uma imagem GPT com uma particao FAT contendo `loader.efi` e o kernel. Um exemplo de execucao no QEMU:

```
qemu-system-x86_64 -bios OVMF.fd -drive format=raw,file=ctos_uefi.img
```

