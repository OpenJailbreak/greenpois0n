/**
  * GreenPois0n Medicine - capable.mm
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Dustin Howett
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

int main(int argc, char **argv, char **envp) {
	if(argc < 3) {
		fprintf(stderr, "I am not Jiminy Cricket.\n");
		return 1;
	}

	NSAutoreleasePool *p = [[NSAutoreleasePool alloc] init];

	NSString *platform = [[NSString stringWithUTF8String:argv[1]] retain];
	NSString *remove = [[NSString stringWithUTF8String:argv[2]] retain];

	NSString *plPath = [[NSString alloc] initWithFormat:@"/System/Library/CoreServices/SpringBoard.app/%@.plist", platform];
	NSMutableDictionary *plist = [[NSMutableDictionary alloc] initWithContentsOfFile:plPath];
	if(!plist) {
		fprintf(stderr, "I like my women like I like my coffee. Covered in beeeeeeeeeeeees!\n");
		return 1;
	}

	NSMutableDictionary *capabilities = [plist objectForKey:@"capabilities"];
	[capabilities removeObjectForKey:remove];
	[plist setObject:capabilities forKey:@"capabilities"];
	[plist writeToFile:plPath atomically:YES];
	[p drain];

	return 0;
}

// vim:ft=objc
