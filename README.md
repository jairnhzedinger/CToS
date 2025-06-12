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

## Compilando no Windows, Linux e macOS

### Windows

1. Instale o [MSYS2](https://www.msys2.org/) ou ative o WSL (Windows Subsystem for Linux).
2. No MSYS2, abra o terminal *MSYS2 MinGW 32-bit* e execute:
   ```
   pacman -S make gcc nasm mingw-w64-i686-binutils qemu
   ```
   Isso instala as ferramentas necessarias para rodar `make`.
3. Clone o repositorio e execute `make` na raiz para gerar `ctos.img`.
4. Como alternativa, usando WSL (Ubuntu), instale:
   ```
   sudo apt install build-essential nasm qemu-system-x86
   ```
   e siga os mesmos passos de compilacao do Linux.

### Linux

1. Certifique-se de ter `gcc`, `make`, `nasm`, `binutils` e `qemu` instalados. Em
   distribuições baseadas em Debian:
   ```
   sudo apt install build-essential nasm qemu-system-x86 gnu-efi
   ```
2. Execute `make` para compilar o bootloader BIOS e o kernel. Para o loader
   UEFI, rode `make -C bootloader/uefi`.

### macOS

1. Instale o [Homebrew](https://brew.sh/) se ainda nao o tiver.
2. Pelo Homebrew, instale as dependencias:
   ```
   brew install gcc nasm qemu gnu-efi
   ```
3. Execute `make` normalmente no Terminal. Os binarios serao gerados na pasta
   correspondente.


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
