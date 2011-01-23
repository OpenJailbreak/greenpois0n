/**
  * GreenPois0n Medicine - Callback.m
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

#include "Callback.h"

@implementation Callback
@synthesize target = _target, action = _action, object = _object;

- (id)initWithTarget:(id)t action:(SEL)a object:(id)o {
	if((self = [super init])) {
		self.target = t;
		self.action = a;
		self.object = o;
	}

	return self;
}

- (void)fire {
	[self fireOnMainThread:NO];
}

- (void)fireOnMainThread:(BOOL)b {
	if(b) {
		[self.target performSelectorOnMainThread:self.action withObject:self.object waitUntilDone:NO];
	} else {
		[self.target performSelector:self.action withObject:self.object];
	}
}

@end