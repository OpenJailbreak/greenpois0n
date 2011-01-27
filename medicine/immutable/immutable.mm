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

int main(int argc, char **argv, char **envp) {
    NSAutoreleasePool *p = [[NSAutoreleasePool alloc] init];

    NSDictionary *sysDict = [[NSDictionary alloc] initWithContentsOfFile:@"/System/Library/CoreServices/SystemVersion.plist"];
    NSString *buildVersion = [sysDict objectForKey:@"ProductBuildVersion"];
    const char *bld = [buildVersion UTF8String];
    size_t size = strlen(bld);
    int v[2];

    v[0] = 1;
    v[1] = 65;

    sysctl(v, 2, NULL, NULL, (void *)bld, size);


    [sysDict release];

    [p drain];
}

// vim:ft=objc

