/**
 * This header is generated by class-dump-z 0.2a.
 * class-dump-z is Copyright (C) 2009 by KennyTM~, licensed under GPLv3.
 *
 * Source: /System/Library/PrivateFrameworks/BackRow.framework/BackRow
 */

#import "BackRow-Structs.h"
#import "BRControl.h"

@class BRMediaPlayer, BRTransportLayer, NSArray, NSTimer, BRTextControl;

__attribute__((visibility("hidden")))
@interface BRTransportControl : BRControl {
@private
	long _duration;	// 40 = 0x28
	long _elapsedTime;	// 44 = 0x2c
	BRMediaPlayer *_player;	// 48 = 0x30
	BRTransportLayer *_layer;	// 52 = 0x34
	BRTextControl *_durationLayer;	// 56 = 0x38
	BRTextControl *_elapsedTimeLayer;	// 60 = 0x3c
	BRTextControl *_chapterLayer;	// 64 = 0x40
	NSArray *_chapterMarkers;	// 68 = 0x44
	NSTimer *_fadeTimer;	// 72 = 0x48
}
@property(assign) BOOL showChapterMarks;	// G=0x31605c1d; S=0x31605c41; converted property
- (id)init;	// 0x315a932d
- (void)_fadeTransport:(id)transport;	// 0x315aecb9
- (void)_handleBufferChanged:(id)changed;	// 0x31605af5
- (void)_handlePlayerAssetChanged:(id)changed;	// 0x31605bf5
- (void)_handlePlayerTimeChanged:(id)changed;	// 0x31605b21
- (void)_handleStateChange:(id)change;	// 0x315aa141
- (void)_handleTimeSkip:(id)skip;	// 0x315b7fa9
- (void)_handleVolumeChange:(id)change;	// 0x31605be1
- (void)_hideTransport;	// 0x315aa1d5
- (void)_showTransport;	// 0x315ae8b9
- (void)_showTransportWithTimeout;	// 0x315aebd1
- (void)_showTransportWithTimeoutInSeconds:(float)seconds;	// 0x31605b4d
- (id)_trackTimeAttributes;	// 0x31605fc5
- (void)_updateAll;	// 0x315aa2b9
- (void)_updateBufferingProgress;	// 0x315aa7c5
- (void)_updateTime;	// 0x315aa36d
- (void)animationDidStop:(id)animation finished:(BOOL)finished;	// 0x315aee1d
- (void)controlWasDeactivated;	// 0x315ab1cd
- (void)dealloc;	// 0x315ab7a9
- (void)hideTransport;	// 0x315aae01
- (BOOL)isHidden;	// 0x31605c65
- (void)layoutSubcontrols;	// 0x31605d61
- (void)setPlayer:(id)player;	// 0x315a9f85
// converted property setter: - (void)setShowChapterMarks:(BOOL)marks;	// 0x31605c41
// converted property getter: - (BOOL)showChapterMarks;	// 0x31605c1d
- (void)showTransport;	// 0x31605d49
- (void)showTransportWithLongTimeout;	// 0x31605c89
- (void)showTransportWithMediumTimeout;	// 0x31605cc9
- (void)showTransportWithShortTimeout;	// 0x31605d09
@end

