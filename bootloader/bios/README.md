# BIOS Bootloader (MBR)

Esta pasta contem o bootloader para BIOS (modo MBR). O arquivo `boot.asm` eh assemblado com NASM e gera o setor de boot. Ele carrega o kernel em modo protegido a partir dos setores seguintes do disco.

### Como compilar

```
make
```

### Como testar

O comando a seguir cria uma imagem de disquete `ctos.img` com o bootloader e o kernel e executa no QEMU:

```
make run
```
