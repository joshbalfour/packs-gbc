/*
 Custom Logo Appender
 Version: 1.0
 Author: Alex from insideGadgets (www.insidegadgets.com)
 Created: 29/11/2019
 Last Modified: 1/12/2019
 License: GPL
  
 Drag and drop both of ROM files. This is for the 512KB Custom Logo Flash Cart.
 
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <libgen.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

uint8_t nintendoLogo[] = {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
									0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
									0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};


int main(int argc, char **argv) {
	
	printf("insideGadgets - Custom Logo Appender v1.0\n");
	printf("#########################################\n");
	printf("The resulting file can only be used on insideGadgets Gameboy Flash Carts that support it.\n\n");
	
	if (argc >= 3) {
		char outputFile[255];
		
		// Read the logo from both files
		FILE *romReadFile1 = fopen(argv[1], "rb");
		fseek (romReadFile1, 0x104, SEEK_SET);
		uint8_t romFileLogo1[48];
		fread(romFileLogo1, 1, 48, romReadFile1);
		fseek (romReadFile1, 0, SEEK_END);
		long fileSize1 = ftell(romReadFile1);
		fclose(romReadFile1);
		
		FILE *romReadFile2 = fopen(argv[2], "rb");
		fseek (romReadFile2, 0x104, SEEK_SET);
		uint8_t romFileLogo2[48];
		fread(romFileLogo2, 1, 48, romReadFile2);
		fseek (romReadFile2, 0, SEEK_END);
		long fileSize2 = ftell(romReadFile1);
		fclose(romReadFile2);
		
		// Check file for logo
		uint8_t logoCheck = 1;
		for (uint16_t logoAddress = 0; logoAddress < 48; logoAddress++) {
			if (nintendoLogo[logoAddress] != romFileLogo1[logoAddress]) {
				logoCheck = 0;
				break;
			}
		}
		if (logoCheck == 0) {
			logoCheck = 2;
			for (uint16_t logoAddress = 0; logoAddress < 48; logoAddress++) {
				if (nintendoLogo[logoAddress] != romFileLogo2[logoAddress]) {
					logoCheck = 0;
					break;
				}
			}
		}
		
		// First file has valid logo
		if (logoCheck == 1) {
			// Strip file extension
			char romMapFileName[250];
			strncpy(romMapFileName, argv[1], strlen(argv[1])-3);
			romMapFileName[strlen(argv[1])-3] = 0;
			
			// New file
			strncpy(outputFile, romMapFileName, 220);
			strncat(outputFile, "_custom_logo.gbc", 16);
			romReadFile1 = fopen(argv[1], "rb");
			FILE *romWriteFile = fopen(outputFile, "wb");
			uint8_t buffer[1] = {0xFF};
			
			// Copy 0x0000-0x3FFF from the existing file to a buffer
			uint8_t bank0Buffer[0x4000];
			fread(bank0Buffer, 1, 0x4000, romReadFile1);
			
			// Copy contents of original file to the new file
			if (fileSize1 > 507904) {
				fileSize1 = 507904; // Limit to 496KB
			}
			fseek (romReadFile1, 0, SEEK_SET);
			for (uint32_t x = 0; x < fileSize1; x++) {
				fread(buffer, 1, 1, romReadFile1);
				fwrite(buffer, 1, 1, romWriteFile);
			}
			
			// Write 0xFFs until the size is 507904 bytes
			for (uint32_t x = fileSize1; x < 507904; x++) {
				buffer[0] = 0xFF;
				fwrite(buffer, 1, 1, romWriteFile);
			}
			
			// Overwrite the logo area with the other file's logo
			for (uint16_t logoAddress = 0x104; logoAddress <= 0x133; logoAddress++) {
				bank0Buffer[logoAddress] = romFileLogo2[(logoAddress-0x104)];
			}
			
			// Jump to 496KB and write the first bank with the custom logo
			fseek (romReadFile1, 507904, SEEK_SET);
			fwrite(bank0Buffer, 1, 0x4000, romWriteFile);
			
			fclose(romReadFile1);
			fclose(romWriteFile);
			
			printf("Completed.\n");
		}
		else if (logoCheck == 2) {
			// Strip file extension
			char romMapFileName[250];
			strncpy(romMapFileName, argv[2], strlen(argv[2])-3);
			romMapFileName[strlen(argv[2])-3] = 0;
			
			// New file
			strncpy(outputFile, romMapFileName, 220);
			strncat(outputFile, "_custom_logo.gb", 16);
			romReadFile2 = fopen(argv[2], "rb");
			FILE *romWriteFile = fopen(outputFile, "wb");
			uint8_t buffer[1] = {0xFF};
			
			// Copy 0x0000-0x3FFF from the existing file to a buffer
			uint8_t bank0Buffer[0x4000];
			fread(bank0Buffer, 1, 0x4000, romReadFile2);
			
			// Copy contents of original file to the new file
			if (fileSize2 > 507904) {
				fileSize2 = 507904; // Limit to 496KB
			}
			fseek (romReadFile2, 0, SEEK_SET);
			for (uint32_t x = 0; x < fileSize2; x++) {
				fread(buffer, 1, 1, romReadFile2);
				fwrite(buffer, 1, 1, romWriteFile);
			}
			
			// Write 0xFFs until the size is 507904 bytes
			for (uint32_t x = fileSize2; x < 507904; x++) {
				buffer[0] = 0xFF;
				fwrite(buffer, 1, 1, romWriteFile);
			}
			
			// Overwrite the logo area with the other file's logo
			for (uint16_t logoAddress = 0x104; logoAddress <= 0x133; logoAddress++) {
				bank0Buffer[logoAddress] = romFileLogo1[(logoAddress-0x104)];
			}
			
			// Jump to 496KB and write the first bank with the custom logo
			fseek (romReadFile2, 507904, SEEK_SET);
			fwrite(bank0Buffer, 1, 0x4000, romWriteFile);
			
			fclose(romReadFile2);
			fclose(romWriteFile);
			
			printf("Completed.\n");
		}
		else {
			printf("Neither of the rom files have a valid Nintendo Logo. Won't continue.\n");
			return 1;
		}
	}
	else {
		printf("Please drag and drop 2 files or pass them as agruments.");
	}
	
	return 0;
}