#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned long long size_t;

/// <summary>
/// Basic console output with status checking
/// </summary>
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

/// <summary>
/// Loads kernel file (ELF)
/// </summary>
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

/// <summary>
/// Memory compare for ELF kernel file. Checks that header values are correct.
/// </summary>
int memcmp(const void* aptr, const void* bptr, size_t n) {
	const unsigned char* a = aptr, *b = bptr;
	for (size_t i = 0; i < n; i++) {
		if (a[i] < b[i]) return -1;
		else if (a[i] > b[i]) return 1;
	}
	return 0;
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	EFI_STATUS Status;
	EFI_FILE* Kernel;

	Status = WriteLine(L"Booting the kernel...\n\r", SystemTable);
	Kernel = LoadKernel(NULL, L"kernel.elf", ImageHandle, SystemTable);
	if (Kernel == NULL) {
		Status = WriteLine(L"Error: could not load the kernel\n\r", SystemTable);
	}
	else {
		Status = WriteLine(L"Kernel loaded successfully\n\r", SystemTable);
	}

	Elf64_Ehdr header; // ELF Kernel header
	{
		UINTN FileInfoSize;
		EFI_FILE_INFO* FileInfo;
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void**)&FileInfo);
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, (void**)&FileInfo);

		UINTN size = sizeof(header);
		Kernel->Read(Kernel, &size, &header);
	}

	// Checking that kernel file is actually executable ELF file and all header values are correct.
	if (memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 ||
		header.e_ident[EI_CLASS] != ELFCLASS64 ||
		header.e_ident[EI_DATA] != ELFDATA2LSB ||
		header.e_type != ET_EXEC ||
		header.e_machine != EM_X86_64 ||
		header.e_version != EV_CURRENT)
	{
		WriteLine(L"Error: kernel format is bad\r\n", SystemTable);
	}
	else {
		WriteLine(L"Kernel header successfully verified\r\n", SystemTable);
	}

	Elf64_Phdr* phdrs; // ELF program headers
	{
		Kernel->SetPosition(Kernel, header.e_phoff);
		UINTN size = header.e_phnum * header.e_phentsize;
		SystemTable->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs);
		Kernel->Read(Kernel, &size, phdrs);
	}

	for (Elf64_Phdr* phdr = phdrs; (char*)phdr < (char*)phdrs + header.e_phnum * header.e_phentsize; phdr = (Elf64_Phdr*)((char*)phdr + header.e_phentsize)) {
		switch (phdr->p_type) {
			case PT_LOAD:
			{
				int pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000;
				Elf64_Addr segment = phdr->p_paddr;
				SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

				Kernel->SetPosition(Kernel, phdr->p_offset);
				UINTN size = phdr->p_filesz;
				Kernel->Read(Kernel, &size, (void*)segment);
				break;
			}
		}
	}

	WriteLine(L"Kernel loaded\n\r", SystemTable);

	int (*KernelStart)() = ((__attribute__((sysv_abi)) int (*)()) header.e_entry);

	InitializeLib(ImageHandle, SystemTable);
	Print(L"%d\r\n", KernelStart());

	return Status; // Exit the UEFI application
}
