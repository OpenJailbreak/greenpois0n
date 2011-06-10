/**
  * GreenPois0n Medicine - immutable.mm
  * Copyright (C) 2011 Chronic-Dev Team
  * Copyright (C) 2011 Nicolas Haunold
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

#include <Foundation/Foundation.h>
#include <sys/sysctl.h>
#include <stdio.h>

int file_write(const char* file, const char* buf, unsigned int length) {
	FILE* fd = NULL;
	fd = fopen(file, "w+");
	if(fd == NULL) {
		return -1;
	}
	
	unsigned int bytes = fwrite((const void*)buf, 1, (unsigned int)length, fd);
	if(bytes != length) {
		fclose(fd);
		return -1;
	}
	fclose(fd);
	return bytes;
}

int main(int argc, char **argv, char **envp) {
    NSAutoreleasePool *p = [[NSAutoreleasePool alloc] init];

    NSDictionary *sysDict = [[NSDictionary alloc] initWithContentsOfFile:@"/System/Library/CoreServices/SystemVersion.plist"];
    NSString *buildVersion = [sysDict objectForKey:@"ProductBuildVersion"];
	const char *bld = [buildVersion UTF8String];
	size_t size = strlen(bld);

	//hacky workaround for 4.3 + for now


	
	[buildVersion writeToFile:@"/private/var2/mobile/Media/buildversion" atomically:YES encoding:NSASCIIStringEncoding error:nil];
	file_write("/private/var2/mobile/Media/buildversion", bld, size);

	
	 
	// deprecated, doesnt work in 4.3+ because sysctl is read only
	 
	int v[2];

    v[0] = 1;
    v[1] = 65;

    
	 sysctl(v, 2, NULL, NULL, (void *)bld, size);
	 
	 

    [sysDict release];

    [p drain];
}

// vim:ft=objc

