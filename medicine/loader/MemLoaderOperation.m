/**
  * GreenPois0n Medicine - MemLoaderOperation.m
  * Copyright (C) 2010 Chronic-Dev Team
  * Copyright (C) 2010 Nicolas Haunold
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

#import "MemLoaderOperation.h"


@implementation MemLoaderOperation
@synthesize url = _url, callback = _callback;

- (void)main {
	if(!self.url || !self.callback) return;
	
	NSURLRequest *req = [NSURLRequest requestWithURL:self.url];
	NSData *d = [NSURLConnection sendSynchronousRequest:req returningResponse:nil error:nil];
	
	[self.callback setObject:d];
	[self.callback fireOnMainThread:YES];
}

@end
