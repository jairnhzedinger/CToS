# CToS

CToS e um projeto de sistema operacional simples para PCs x86 com suporte a boot via BIOS e UEFI. Este repositorio contem um esqueleto basico com bootloaders e um kernel inicial escrito em C. O projeto se inspira no sistema operacional ficticio presente no jogo *Watch Dogs*.

## Estrutura

- `bootloader/bios`  - Bootloader MBR para BIOS
- `bootloader/uefi`  - Bootloader para UEFI (GPT)
- `kernel`           - Kernel inicial
- `iso`              - Diretorio para imagens

## Como compilar

Para gerar somente a imagem BIOS execute:

```
make
```

Para testar rapidamente no QEMU utilize:

```
make run
```

Para limpar os binarios gerados utilize:

```
make clean
```

Para compilar apenas o bootloader UEFI:

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

- `help`   - mostra esta lista de comandos
- `about`  - informa a inspiracao no jogo Watch Dogs
- `cls`    - limpa a tela
- `ver`    - exibe a versao do CToS
- `beep`   - aciona o alto-falante do PC
- `reboot` - reinicia a maquina
- `time`   - mostra o horario do RTC
- `rand`   - imprime um numero aleatorio
- `color X`- altera a cor do texto (0-7)
- `echo`   - repete o texto fornecido
- `gui`    - entra em uma interface simples com cursor movido por WASD ou setas

## Help for Dummies

1. Instale o [VirtualBox](https://www.virtualbox.org/).
2. Compile o projeto com `make` na raiz do repositorio.
3. Crie uma nova maquina virtual usando o tipo *Other/Unknown (32-bit)*.
4. Aponte o arquivo `ctos.img` gerado para a unidade de disquete ou como disco.
5. Inicie a VM para ver o CToS em execucao.

Para mudar a cor do texto em tempo de execucao basta digitar `color` seguido de
um numero de 0 a 7, por exemplo `color 2` para verde.
