/**
  * GreenPois0n Medicine - MemLoaderOperation.h
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

#import <Foundation/Foundation.h>
#import "Callback.h"

@interface MemLoaderOperation : NSOperation {
	NSURL *_url;
	Callback *_callback;
}

@property (nonatomic, retain) NSURL *url;
@property (nonatomic, retain) Callback *callback;


@end
