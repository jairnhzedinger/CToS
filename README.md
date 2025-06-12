# CToS

CToS e um projeto de sistema operacional simples para PCs x86 com suporte a boot via BIOS e UEFI. Este repositorio contem um esqueleto basico com bootloaders e um kernel inicial escrito em C. O projeto se inspira no sistema operacional ficticio presente no jogo *Watch Dogs*.

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


## Funcoes basicas

O kernel inclui uma interface simples de linha de comando. Os comandos disponiveis sao:

- `help`  - mostra esta lista de comandos
- `about` - informa a inspiracao no jogo Watch Dogs
- `cls`   - limpa a tela

## Help for Dummies

1. Instale o [VirtualBox](https://www.virtualbox.org/).
2. Compile o projeto com `make` na raiz do repositorio.
3. Crie uma nova maquina virtual usando o tipo *Other/Unknown (32-bit)*.
4. Aponte o arquivo `ctos.img` gerado para a unidade de disquete ou como disco.
5. Inicie a VM para ver o CToS em execucao.
