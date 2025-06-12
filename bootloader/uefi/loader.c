#include <efi.h>
#include <efilib.h>

EFI_STATUS
EFIAPI
efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    Print(L"Iniciando CToS...\n");
    // Carrega e executa o kernel (simplificado - kernel como EFI)
    EFI_STATUS status;
    EFI_HANDLE kernelHandle;
    status = uefi_call_wrapper(SystemTable->BootServices->LoadImage, 6, FALSE, ImageHandle, NULL, NULL, 0, &kernelHandle);
    if (EFI_ERROR(status)) {
        Print(L"Falha ao carregar kernel\n");
        return status;
    }
    status = uefi_call_wrapper(SystemTable->BootServices->StartImage, 3, kernelHandle, NULL, NULL);
    return status;
}
