/**
  * GreenPois0n Medicine - animate.mm
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
#include <CoreGraphics/CoreGraphics.h>
#include <sys/sysctl.h>
#include <stdio.h>
#include <IOKit/IOKitLib.h>
#include <mach/mach_traps.h>

unsigned int CoreSurfaceBufferLock(void *fb, unsigned int type);
unsigned int CoreSurfaceBufferUnlock(void *fb);
unsigned int CoreSurfaceBufferGetHeight(void *fb);
unsigned int CoreSurfaceBufferGetWidth(void *fb);
unsigned int CoreSurfaceBufferGetBytesPerRow(void *fb);
void *CoreSurfaceBufferGetBaseAddress(void *fb);

unsigned int IOMobileFramebufferOpen(io_service_t t, mach_port_t task, unsigned int type, void *conn);
unsigned int IOMobileFramebufferGetLayerDefaultSurface(void *c, int u, void *data);

CGContextRef fb_open() {
	void *conn = NULL;
	int screenWidth, screenHeight, bytesPerRow;
	void *surfaceBuffer;
	void *frameBuffer;
	CGContextRef context = NULL;
	CGColorSpaceRef colorSpace;

	io_service_t fb_service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("AppleH1CLCD"));
	if(!fb_service) {
		fb_service = IOServiceGetMatchingService(kIOMasterPortDefault, IOServiceMatching("AppleM2CLCD"));

		if(!fb_service) {
			printf("Couldn't find framebuffer.\n");
			return NULL;
		}
	}

	IOMobileFramebufferOpen(fb_service, mach_task_self(), 0, &conn);
	IOMobileFramebufferGetLayerDefaultSurface(conn, 0, &surfaceBuffer);

	screenHeight = CoreSurfaceBufferGetHeight(surfaceBuffer);
	screenWidth = CoreSurfaceBufferGetWidth(surfaceBuffer);
	bytesPerRow = CoreSurfaceBufferGetBytesPerRow(surfaceBuffer);

	CoreSurfaceBufferLock(surfaceBuffer, 3);
	frameBuffer = CoreSurfaceBufferGetBaseAddress(surfaceBuffer);
	CoreSurfaceBufferUnlock(surfaceBuffer);

	// create bitmap context
	colorSpace = CGColorSpaceCreateDeviceRGB();
	context = CGBitmapContextCreate(frameBuffer, screenWidth, screenHeight, 8, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast);
	if(context == NULL) {
		printf("Couldn't create screen context!");
		return NULL;
	}

	CGColorSpaceRelease(colorSpace);

	return context;
}

int main(int argc, char **argv, char **envp) {
	NSAutoreleasePool *p = [[NSAutoreleasePool alloc] init];

	CGContextRef c = fb_open();

	// red
	CGContextSetRGBFillColor(c, 255, 0, 0, 1);
	CGContextFillRect(c, CGRectMake(10, 10, 40, 40));

	[p drain];
}

// vim:ft=objc

