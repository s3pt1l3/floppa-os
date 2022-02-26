#include <efi.h>
#include <efilib.h>

EFI_STATUS WriteLine(CHAR16* Line, EFI_SYSTEM_TABLE* SystemTable) {
	EFI_STATUS Status;

	Status = SystemTable->ConOut->OutputString(SystemTable->ConOut, Line);
	if (EFI_ERROR(Status)) {
		return Status; //If printing failed, return
	}

	Status = SystemTable->ConIn->Reset(SystemTable->ConIn, FALSE); // Empty the Console Input Buffer
	if (EFI_ERROR(Status)) {
		return Status;
	}
	
	return Status;
}

EFI_FILE* LoadKernel(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {
	EFI_FILE* LoadedFile;

	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

	if (Directory == NULL) {
		FileSystem->OpenVolume(FileSystem, &Directory);
	}

	EFI_STATUS Status = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if (Status != EFI_SUCCESS) {
		return NULL;
	}
	return LoadedFile;
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	EFI_STATUS Status;
	EFI_FILE* Kernel;

	Status = WriteLine(L"Booting the kernel...\n\r", SystemTable);
	Kernel = LoadKernel(NULL, L"kernel.elf", ImageHandle, SystemTable);
	if (Kernel == NULL) {
		Status = WriteLine(L"Could not load the kernel\n\r", SystemTable);
	}
	else {
		Status = WriteLine(L"Kernel loaded successfully\n\r", SystemTable);
	}

	return Status; // Exit the UEFI application
}
