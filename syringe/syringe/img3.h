/**
 * GreenPois0n Syringe - img3.h
 * Copyright (C) 2010 Chronic-Dev Team
 * Copyright (C) 2010 Joshua Hill
 *
 * Functions for handling with Apple's IMG3 format
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef IMG3_H
#define IMG3_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	kNorContainer = 0x696D6733,  // img3
	kImg3Container = 0x496D6733, // Img3
	k8900Container = 0x30303938, // 8900
	kImg2Container = 0x494D4732  // IMG2
} img3_container_type_t;

typedef enum {
	kDataElement = 0x44415441, // DATA
	kTypeElement = 0x54595045, // TYPE
	kKbagElement = 0x4B424147, // KBAG
	kShshElement = 0x53485348, // SHSH
	kCertElement = 0x43455254, // CERT
	kChipElement = 0x43484950, // CHIP
	kProdElement = 0x50524F44, // PROD
	kSdomElement = 0x53444F4D, // SDOM
	kVersElement = 0x56455253, // VERS
	kBordElement = 0x424F5244, // BORD
	kSepoElement = 0x5345504F, // SEPO
	kEcidElement = 0x45434944, // ECID
	kUnknElement = 0x53414c54  // FIXME
} img3_element_type_t;

typedef struct {
	unsigned int signature;
	unsigned int full_size;
	unsigned int data_size;
	unsigned int shsh_offset;
	unsigned int image_type;
} img3_header_t;

typedef struct {
	unsigned int signature;
	unsigned int full_size;
	unsigned int data_size;
} img3_element_header_t;

typedef struct {
	img3_element_header_t* header;
	img3_element_type_t type;
	unsigned char* data;
} img3_element_t;

typedef struct img3_t {
	char* data;
	img3_header_t* header;
	img3_element_t* type_element;
	img3_element_t* data_element;
	img3_element_t* vers_element;
	img3_element_t* sepo_element;
	img3_element_t* bord_element;
	img3_element_t* kbag1_element;
	img3_element_t* kbag2_element;
	img3_element_t* ecid_element;
	img3_element_t* shsh_element;
	img3_element_t* cert_element;
	img3_element_t* unkn_element;
} img3_t;

img3_t* img3_create();
void img3_free(img3_t* image);
img3_element_t* img3_parse_element(char* data);
void img3_free_element(img3_element_t* element);
img3_t* img3_parse_file(char* data, int size);
int img3_get_data(img3_t* image, char** pdata, int* psize);
int img3_replace_signature(img3_t* image, char* signature);


#ifdef __cplusplus
}s
#endif

#endif
